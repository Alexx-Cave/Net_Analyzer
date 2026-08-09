#include <algorithm>
#include <fstream>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <string.h>

#include <tui_background.h>
#include <tui_lineedit.h>
#include <tui_showinfo.h>
#include <tui_commandview.h>

#include "IPaddr.h"
#include "tools.h"

using namespace std;

static string pingIP;
static string tracerouteIP;

bool isValidIpOrHostname(const string &str)
{
	try
	{
		size_t pos = str.rfind('/');

		if (pos == string::npos)
		{
			IPAddr ip(str);
			if (ip.isValid()) return true;
		}
		else
		{
			IPAddr ip(str.substr(0, pos));
			if (! ip.isValid()) return false;

			int m = stoi(str.substr(pos + 1));

			if (m < 8 || m > 32) return false;

			uint32_t mask, addr = ntohl(static_cast<uint32_t>(ip));

			for (mask = 0; m; m--)
			{
				mask >>= 1;
				mask |= 0x80000000;
			}

			if ((addr & mask) != addr) return false;

			return true;
		}
	}
	catch (const exception &)
	{ 
		// this can be host name
	}

	const string valid_symbols = "_-."; // symbols allowed in host name

	auto iter = find_if(str.begin(), str.end(), [&](char c)
	{
		if (! isalnum(c) && valid_symbols.find(c) == string::npos) return true;

		return false;
	});

	if (iter == str.end()) return true;

	return false;
}

void ExecCmd(WINDOW *mainwin, const string &cmd, const string &winTitle)
{
	TUICommandView view(mainwin, winTitle, RIGHT, 1);
	view.runCommand(cmd);
	view.exec();
}

void TestPing(WINDOW *mainwin)
{
	TUILineEdit edit(mainwin, "Команда PING", " Адрес ");
	edit.setValue(pingIP);
	edit.exec();
	if (! edit.exitType()) return;

	string ipAddr = edit.getValue();

	if (ipAddr.size())
	{
		if (! isValidIpOrHostname(ipAddr))
		{
			showInfo(mainwin, ipAddr + BAD_ADDRESS_MSG);
			return;
		}

		pingIP = ipAddr;
		ExecCmd(mainwin, string("ping -c 4 ") + ipAddr + " 2>&1 ", "Результаты PING");
	}
}

void TestTraceroute(WINDOW *mainwin)
{
	TUILineEdit edit(mainwin, "Команда TRACEROUTE", " Адрес ");
	edit.setValue(tracerouteIP);
	edit.exec();
	if (! edit.exitType()) return;

	string ipAddr = edit.getValue();

	if (ipAddr.size())
	{
		if (! isValidIpOrHostname(ipAddr))
		{
			showInfo(mainwin, ipAddr + BAD_ADDRESS_MSG);
			return;
		}

		tracerouteIP = ipAddr;
		ExecCmd(mainwin, string("sudo traceroute -I ") + ipAddr + " 2>&1 ", "Результаты TRACEROUTE");
	}
}

void TestArp(WINDOW *mainwin)
{
	ExecCmd(mainwin, string("arp -e -n 2>&1"), "Таблица ARP");
}

void GetNetInterfaces(WINDOW *mainwin)
{
	string cmd = "nmap --iflist | grep -E "
			"'IP/MASK|[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}.*ethernet'";
	ExecCmd(mainwin, cmd, "Сетевые интерфейсы");
}

void PrepareScanReport(const string &addr, const char *reportFile, TUIBackground *b)
{
	string cmd = "sudo nmap -F -sV -O ";
	ofstream fileout(reportFile, ios_base::out | ios_base::trunc);

	string fHost = "Nmap scan report for ";
	string fMAC = "MAC Address: ";
	string fOS = "Service Info: ";

	FILE *fp;
	bool portTable = false;
	int count = 0;
	size_t pos;
	char buf[256];

	b->showInfo(" Сканирование. Пожалуйста подождите... ");

	cmd += addr;
	fp = popen(cmd.c_str(), "r");

	while (fp && fgets(buf, sizeof(buf), fp))
	{
		while (strlen(buf) > 0 && (buf[strlen(buf) - 1] == '\n' || buf[strlen(buf) - 1] == '\r'))
		{
			buf[strlen(buf) - 1] = 0;
		}

		string line(buf);

		if (portTable)
		{
			if (line.find("open") != string::npos ||
				line.find("closed") != string::npos)
			{
				fileout << line << endl;
				continue;
			}
			else
			{
				fileout << endl;
				portTable = false;
			}
		}

		pos = line.find(fHost);
		if (pos != string::npos)
		{
			if (count > 0)
			{
				for (int i = 0; i < 80; i++) fileout << "*";
				fileout << endl << endl;
			}

			string host = " Хост: ";
			host += line.substr(pos + fHost.size());
			host += " ";

			fileout << host << endl << endl;
			b->draw();
			b->showInfo(host);
			count++;
			continue;
		}

		if (line.find("PORT") != string::npos &&
			line.find("STATE") != string::npos &&
			line.find("SERVICE") != string::npos &&
			line.find("VERSION") != string::npos)
		{
			fileout << line << endl;
			for (int i = 0; i < 40; i++) fileout << "-";
			fileout << endl;
			portTable = true;
			continue;
		}

		pos = line.find(fMAC);
		if (pos != string::npos)
		{
			fileout << "MAC адрес: " << line.substr(pos + fMAC.size()) << endl << endl;
			continue;
		}

		pos = line.find(fOS);
		if (pos != string::npos)
		{
			fileout << "Информация: " << line.substr(pos + fOS.size()) << endl << endl;
		}
	}

	if (fp) pclose(fp);
}

vector<NetIface> GetNetInterfaces()
{
	struct ifaddrs *ifaddr, *ifa;
	vector<NetIface> interfaces;

	if (getifaddrs(&ifaddr)) return {};

	for (ifa = ifaddr; ifa; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) // IPv4?
		{
			IPAddr addr(ifa->ifa_addr);
			IPAddr mask(ifa->ifa_netmask);

			uint32_t a = ntohl(static_cast<uint32_t>(addr));
			uint32_t m = ntohl(static_cast<uint32_t>(mask));

			IPAddr sub(static_cast<in_addr_t>(htonl(a & m)));

			int i;

			for (i = 0; m; i++) m <<= 1;
			
			NetIface rec;

			rec.name   = ifa->ifa_name;
			rec.addr   = addr.str();
			rec.subnet = sub.str();
			rec.mask   = to_string(i);

			if (rec.name != "lo" && rec.addr != "127.0.0.1")
			{
				interfaces.emplace_back(rec);
			}
		}
	}

	freeifaddrs(ifaddr);
	return interfaces;
}
