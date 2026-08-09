#pragma once

#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static const uint32_t PORTABLE_AF_INET = 2;
static const uint32_t PORTABLE_AF_INET6 = 28;

class IPAddr {
public:
	IPAddr();
	IPAddr(const in_addr &addr);
	IPAddr(const in6_addr &addr);
	IPAddr(const sockaddr_in &addr);
	IPAddr(const sockaddr_in6 &addr);

	explicit IPAddr(const sockaddr *addr);
	explicit IPAddr(const std::string &addr);
	explicit IPAddr(in_addr_t s_addr);
	explicit IPAddr (unsigned famliy, const void *addr);

	operator in_addr() const;
	operator in6_addr() const;
	explicit operator uint32_t() const;

	unsigned family() const;
	std::string str() const;

	void copy(sockaddr_storage *ss, in_port_t port) const;
	void copy(void *addr) const;

	bool operator == (const IPAddr &a) const;
	bool operator != (const IPAddr &a) const;
	bool operator < (const IPAddr &a) const;
	bool operator <= (const IPAddr &a) const;
	bool operator > (const IPAddr &a) const;
	bool operator >= (const IPAddr &a) const;

	/// Наложение маски на адрес
	IPAddr operator & (const IPAddr &a) const;
	IPAddr operator | (const IPAddr &a) const;
	/// Взятие обратного значения, имеет смысл для масок.
	IPAddr operator ~() const;

	bool isValid() const;
	bool isZero() const;
	bool isFull() const;
	// Проверка маски на недырявость
	bool isMonotonic() const;

	static const IPAddr v4_loopback;

	// Полная маска
	static const IPAddr v4_full;
	static const IPAddr v6_full;

	// Нулевой адрес
	static const IPAddr v4_zero;
	static const IPAddr v6_zero;

private:
	uint32_t af;
	in_addr a4;
	in6_addr a6;
	/// "Кэшируемое" строковое представление адреса.
	char repr[INET6_ADDRSTRLEN] = { 0 };

	void checkInitialized() const;
};
