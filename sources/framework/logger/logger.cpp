#include "logger.h"
#include <windows.h>
#include <iostream>

namespace fbr {
#if LOG_ENABLE
	void Logger::writeLogToFile(const std::stringstream& msg)
	{
		if (file.good())
			file << __TIME__ << " " << __DATE__ << " | " << msg.str();
		else {
			std::stringstream ss;
			ss << "Cannot write to log file\n";
			printLog(ss, 12);
		}
	}

	Logger::Logger()
	{
		time_t now = time(0);
		tm	   ltm;
		localtime_s(&ltm, &now);

		std::string relative_path(__FILE__);
		if (relative_path.find(PROJECT_NAME) != std::string::npos)
			relative_path = relative_path.substr(0, relative_path.find(PROJECT_NAME));

		std::string date = std::to_string(ltm.tm_hour) + "-" + std::to_string(ltm.tm_min) + "-" + std::to_string(ltm.tm_hour) + "_" + std::to_string(ltm.tm_mday) + "-" + std::to_string(ltm.tm_mon + 1) + "-" + std::to_string(ltm.tm_year + 1900);
		std::string log_dir_path = relative_path + PROJECT_NAME + DIRECTORY_SEPARATOR + "logs";
		std::string log_path = log_dir_path + DIRECTORY_SEPARATOR + LOG_FILE_PATH + "_" + date + "." + LOG_FILE_EXTENSION;

		if (std::filesystem::exists(log_dir_path)) {
			printLog(std::stringstream("Found logs directory in " + log_dir_path + "\n"), INF_COLOR);
		}
		else {
			printLog(std::stringstream("Creating logs directory in " + log_dir_path + "\n"), INF_COLOR);
			if (std::filesystem::create_directory(log_dir_path)) {
				printLog(std::stringstream("Creating logs directory succeeded\n"), INF_COLOR);
			}
			else {
				printLog(std::stringstream("Creating logs directory failed\n"), ERR_COLOR);
			}
		}

		file.open(log_path, std::fstream::out | std::fstream::app);

		if (file.good()) {
			printLog(std::stringstream("Successfully created new log file : " + LOG_FILE_PATH + "_" + date + "\n"), HIGHTLIGHT_COLOR);
		}
		else {
			printLog(std::stringstream("Cannot create log file\n"), ERR_COLOR);
		}
	}

	Logger::~Logger()
	{
		file.close();
	}

	Logger& Logger::get()
	{
		static Logger instance_;
		return instance_;
	}

	void printLog(const std::stringstream& log, unsigned int color)
	{
		static CONSOLE_SCREEN_BUFFER_INFO Info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
		static WORD Attributes = Info.wAttributes;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
		std::cerr << log.rdbuf();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attributes);
	}
#endif
} // fbr