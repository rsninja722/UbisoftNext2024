//-----------------------------------------------------------------------------
// Log.cpp
// class to handle logging to a local file
//-----------------------------------------------------------------------------

#include "stdafx.h"

#include "Log.h"

void Log::Init() {
	std::ofstream file;
	file.open(M_LOG_FILE_NAME, std::ios_base::out);
	file << "Log file created at " << __DATE__ << " " << __TIME__ << "\n";
	file.close();
}

void Log::Info(const std::string message)
{
	Write("[INFO] " + message + "\n");
}

void Log::Warning(const std::string message)
{
	Write("[WARNING] " + message + "\n");
}

void Log::Error(const std::string message)
{
	Write("[ERROR] " + message + "\n");
}

void Log::Write(const std::string message)
{
	std::ofstream file;
	file.open(M_LOG_FILE_NAME, std::ios_base::app);
	file << message;
	file.close();
}

const std::string Log::M_LOG_FILE_NAME = "log.txt";