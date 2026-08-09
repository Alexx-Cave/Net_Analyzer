#pragma once

#include <string>
#include <vector>
#include <ncurses.h>

#include <tui_background.h>

#define REPORT_FILE		"report.tmp"
#define BAD_ADDRESS_MSG	" - неверный IP адрес или имя хоста "

struct NetIface
{
	std::string name;
	std::string addr;
	std::string subnet;
	std::string mask;
};

bool isValidIpOrHostname(const std::string &str);

void TestPing(WINDOW *mainwin);
void TestTraceroute(WINDOW *mainwin);
void TestArp(WINDOW *mainwin);

void GetNetInterfaces(WINDOW *mainwin);
std::vector<NetIface> GetNetInterfaces();

void PrepareScanReport(const std::string &addr, const char *reportFile, TUIBackground *b);
