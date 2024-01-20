#ifndef NEXT2024_SRC_ENGINE_LOG_H_
#define NEXT2024_SRC_ENGINE_LOG_H_

#include <iostream>
#include <fstream>
#include <string>

class Log {
public:
	static void Init();

	static void Info(const std::string message);
	static void Warning(const std::string message);
	static void Error(const std::string message);
private:
	static const std::string M_LOG_FILE_NAME;

	static void Write(const std::string message);
};

#endif // NEXT2024_SRC_ENGINE_LOG_H_
