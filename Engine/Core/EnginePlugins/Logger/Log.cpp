#include "Log.h"

#include <iostream>
#include <chrono>
#include <ctime>

#define MessagColor "\033[32m"
#define ErrorColor "\033[31m"
#define DefaultColor "\033[0m"

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::time_t;
using std::ctime;
using std::left;
using std::right;
using std::setfill;
using std::setw;
using std::put_time;
using std::localtime;

auto Log::CollectCurrentTime()
{
	auto now = std::chrono::system_clock::now();
	time_t logTime = std::chrono::system_clock::to_time_t(now);
	return &logTime;
}

void Log::Message(const string& message)
{
	cout << MessagColor << "[" << put_time(localtime(CollectCurrentTime()), "%Y-%m-%d %H:%M:%S") << "] " 
		 << "Message: " << message << DefaultColor << "\n";
}

void Log::Error(const string& error)
{
	cerr << ErrorColor << "[" << put_time(localtime(CollectCurrentTime()), "%Y-%m-%d %H:%M:%S") << "] " 
		 << "Error: " << error << DefaultColor << "\n";
}


