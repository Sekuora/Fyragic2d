#pragma once

#include <string>
using std::string;

class Log
{
public:

	static void Message(const string& message);

	static void Error(const string& error);


private:

	static auto CollectCurrentTime();
};