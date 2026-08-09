#include <vector>
#include <cstring>
#include <arpa/inet.h>

#include "IPaddr.h"

using namespace std;

const IPAddr IPAddr::v4_loopback("127.0.0.1");
const IPAddr IPAddr::v4_full("255.255.255.255");
const IPAddr IPAddr::v6_full("ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff");
const IPAddr IPAddr::v4_zero("0.0.0.0");
const IPAddr IPAddr::v6_zero("::");

IPAddr::IPAddr()
	: af(AF_UNSPEC)
{
}

IPAddr::IPAddr(const in_addr &addr)
	: af(AF_INET), a4(addr)
{
}

IPAddr::IPAddr(const in6_addr &addr)
	: af(AF_INET6), a6(addr)
{
}

IPAddr::IPAddr(const sockaddr_in &addr)
	: af(AF_INET), a4(addr.sin_addr)
{
}

IPAddr::IPAddr(const sockaddr_in6 &addr)
	: af(AF_INET6), a6(addr.sin6_addr)
{
	if (IN6_IS_ADDR_V4MAPPED(&a6)) {
		memcpy(&a4.s_addr, &a6.s6_addr[12], sizeof(a4.s_addr));
		af = AF_INET;
	}
}

IPAddr::IPAddr(const sockaddr *addr)
{
	af = addr->sa_family;
	if (af == AF_INET) {
		const sockaddr_in *p = reinterpret_cast<const sockaddr_in *>(addr);
		a4 = p->sin_addr;
	} else if (af == AF_INET6) {
		const sockaddr_in6 *p = reinterpret_cast<const sockaddr_in6 *>(addr);
		a6 = p->sin6_addr;
		if (IN6_IS_ADDR_V4MAPPED(&a6)) {
			memcpy(&a4.s_addr, &a6.s6_addr[12], sizeof(a4.s_addr));
			af = AF_INET;
		}
	} else {
		throw runtime_error("Unsupproted address type");
	}
}

IPAddr::IPAddr(const std::string &addr)
{
	if (inet_pton(AF_INET, addr.c_str(), &a4) == 1) {
		af = AF_INET;
	} else if (inet_pton(AF_INET6, addr.c_str(), &a6) == 1) {
		af = AF_INET6;
	} else {
		throw runtime_error("Failed to convert string to address");
	}
}

IPAddr::IPAddr(in_addr_t s_addr)
	: af(AF_INET)
{
	a4.s_addr = s_addr;
}

IPAddr::IPAddr (unsigned famliy, const void *addr)
{
	af = famliy;
	if (af == AF_INET) {
		memcpy(&a4, addr, sizeof(a4));
	} else if (af == AF_INET6) {
		memcpy(&a6, addr, sizeof(a6));
	} else {
		throw runtime_error("Unsupproted address type");
	}
}

IPAddr::operator in_addr() const
{
	checkInitialized();
	if (af == AF_INET) {
		return a4;
	}

	throw runtime_error("Failed to convert IPAddr to inet4");
}

IPAddr::operator uint32_t() const
{
	checkInitialized();
	if (af == AF_INET) {
		return a4.s_addr;
	}

	throw runtime_error("Failed to convert IPAddr to uint32_t");
}

IPAddr::operator in6_addr() const
{
	checkInitialized();
	if (af == AF_INET6) {
		return a6;
	}

	if (af == AF_INET) {
		in6_addr mapped = in6addr_any;
		mapped.s6_addr[10] = 0xff;
		mapped.s6_addr[11] = 0xff;
		memcpy(&mapped.s6_addr[12], &a4.s_addr, sizeof(a4.s_addr));
		return mapped;
	}

	throw runtime_error("Failed to convert IPAddr to inet6");
}

string IPAddr::str() const
{
	if (repr[0] != 0) {
		return repr;
	}

	checkInitialized();

	const void *addr = NULL;
	if (af == AF_INET) {
		addr = &a4;
	} else if (af == AF_INET6) {
		addr = &a6;
	} else {
		throw runtime_error("Invalid IPAddr");
	}

	if (inet_ntop(af, addr, const_cast<char *>(repr), INET6_ADDRSTRLEN) == NULL) {
		throw runtime_error("Failed to convert address to string");
	}

	return repr;
}

unsigned IPAddr::family() const
{
	return af;
}

void IPAddr::copy(sockaddr_storage *ss, in_port_t port) const
{
	checkInitialized();

	if (af == AF_INET) {
		sockaddr_in *p = (sockaddr_in *)(ss);
		p->sin_family = af;
		p->sin_port = port;
		p->sin_addr.s_addr = a4.s_addr;

	} else if (af == AF_INET6) {
		sockaddr_in6 *p = (sockaddr_in6 *)(ss);
		p->sin6_family = af;
		p->sin6_port = port;
		memcpy(&p->sin6_addr, &a6, sizeof(a6));
	}
}

void IPAddr::copy(void *addr) const
{
	checkInitialized();

	if (af == AF_INET) {
		memcpy(addr, &a4, sizeof(a4));
	} else if (af == AF_INET6) {
		memcpy(addr, &a6, sizeof(a6));
	}
}

bool IPAddr::isZero() const
{
	if (af == AF_INET) {
		return a4.s_addr == 0;
	}

	if (af == AF_INET6) {
		return memcmp(&a6, &v6_zero.a6, sizeof(a6)) == 0;
	}

	throw runtime_error("Unsupproted address type");
}

bool IPAddr::isFull() const
{
	if (af == AF_INET) {
		return a4.s_addr == 0xffffffffU;
	}

	if (af == AF_INET6) {
		return memcmp(&a6, &v6_full.a6, sizeof(a6)) == 0;
	}

	throw runtime_error("Unsupproted address type");
}

bool IPAddr::isMonotonic() const
{
	in6_addr paddr;
	size_t psize;
	if (af == AF_INET) {
		memcpy(paddr.s6_addr, &a4.s_addr, sizeof(a4.s_addr));
		psize = sizeof(a4);
	} else if (af == AF_INET6) {
		paddr = a6;
		psize = sizeof(a6);
	} else {
		throw runtime_error("Unsupproted address type");
	}

	bool prev_zero = (((paddr.s6_addr[0] >> 7)& 0x1) == 0);
	bool monotonic_down = !prev_zero;
	bool one_only = !prev_zero;
	for (uint32_t i = 1; i < (psize * 8); i++) {
		bool zero = (((paddr.s6_addr[i/8] >> (7-i % 8)) & 0x1) == 0);
		if (monotonic_down && prev_zero && !zero) {
			return false;
		}

		if (zero) {
			one_only = false;
		}

		prev_zero = zero;
	}

	return one_only || monotonic_down;
}

bool IPAddr::operator == (const IPAddr &a) const
{
	if (af == a.af) {
		if (af == AF_INET) {
			return a4.s_addr == a.a4.s_addr;
		}

		if (af == AF_INET6) {
			return memcmp(&a6, &a.a6, sizeof(a6)) == 0;
		}
	}

	return false;
}

bool IPAddr::operator != (const IPAddr &a) const
{
	return !(*this == a);
}

bool IPAddr::operator < (const IPAddr &a) const
{
	checkInitialized();

	if (af != a.af) {
		return af < a.af;
	}

	if (af == AF_INET) {
		return ntohl(a4.s_addr) < ntohl(a.a4.s_addr);
	}

	// AF_INET6
	return memcmp(&a6, &a.a6, sizeof(a6)) < 0;
}

bool IPAddr::operator > (const IPAddr &a) const
{
	return !(*this <= a);
}

bool IPAddr::operator <= (const IPAddr &a) const
{
	return *this < a || *this == a;
}

bool IPAddr::operator >= (const IPAddr &a) const
{
	return !(*this < a);
}

IPAddr IPAddr::operator & (const IPAddr &a) const
{
	checkInitialized();

	if (af != a.af) {
		throw runtime_error("Operands mismatch in operator &");
	}

	if (af == AF_INET) {
		in_addr r = { a4.s_addr & a.a4.s_addr };
		return r;
	}

	// AF_INET6
	in6_addr r;
	for (unsigned i = 0; i < sizeof(a6.s6_addr); ++i) {
		r.s6_addr[i] = a6.s6_addr[i] & a.a6.s6_addr[i];
	}

	return r;
}

IPAddr IPAddr::operator | (const IPAddr &a) const
{
	checkInitialized();

	if (af != a.af) {
		throw runtime_error("Operands mismatch in operator |");
	}

	if (af == AF_INET) {
		in_addr r = { a4.s_addr | a.a4.s_addr };
		return r;
	}

	// AF_INET6
	in6_addr r;
	for (unsigned i = 0; i < sizeof(a6.s6_addr); ++i) {
		r.s6_addr[i] = a6.s6_addr[i] | a.a6.s6_addr[i];
	}
	return r;
}

IPAddr IPAddr::operator ~ () const
{
	checkInitialized();

	if (af == AF_INET) {
		in_addr tmp = { ~a4.s_addr };
		return tmp;
	}

	// AF_INET6
	in6_addr r;
	for (unsigned i = 0; i < sizeof(a6.s6_addr); ++i) {
		r.s6_addr[i] = ~a6.s6_addr[i];
	}

	return r;
}

bool IPAddr::isValid() const
{
	return af != AF_UNSPEC;
}

void IPAddr::checkInitialized() const
{
	if (af == AF_UNSPEC) {
		throw runtime_error("Uninitialized IPAddr");
	}
}
