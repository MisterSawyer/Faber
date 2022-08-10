#pragma once

#include "../macros/streamize.h"

#include <filesystem>
#include <fstream>
#include <sstream>

#define LOG_ENABLE 1

namespace fbr {

#if LOG_ENABLE

	const std::string LOG_FILE_PATH = "log";
	const std::string LOG_FILE_EXTENSION = "txt";
	const std::string PROJECT_NAME = "FaberFramework";

#ifdef _WIN32
	const std::string DIRECTORY_SEPARATOR = "\\";
#else
	const std::string DIRECTORY_SEPARATOR = "\/";
#endif

	constexpr unsigned int HIGHTLIGHT_COLOR = 10;
	constexpr unsigned int INF_COLOR = 8;
	constexpr unsigned int WAR_COLOR = 14;
	constexpr unsigned int ERR_COLOR = 12;

#ifdef _DEBUG
	constexpr bool ASSERTION = true;
#else
	constexpr bool ASSERTION = false;
#endif // _NDEBUG

	class Logger
	{
	public:
		Logger(Logger& other) = delete;
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(const Logger&) = delete;
		Logger& operator=(Logger&&) = delete;

		~Logger();

		static Logger& get();

		void writeLogToFile(const std::stringstream& msg);

	private:
		Logger();

		std::fstream file;
	};

	void printLog(const std::stringstream& msg, unsigned int color);

#define GETINFO(...) std::string{" "} << EXPAND(STREAMIZE(__VA_ARGS__)) << ""


#define MAKE_LOG(lv, msg, color)                                                                                            \
	do {                                                                                                                    \
		std::stringstream log;                                                                                              \
		std::string		  relative_path(__FILE__);                                                                          \
		if (relative_path.find(fbr::PROJECT_NAME) != std::string::npos)                                              \
			relative_path = relative_path.substr(relative_path.find(fbr::PROJECT_NAME));                             \
		log << lv << "[" << relative_path << "][" << __func__ << "()](" << std::to_string(__LINE__) << ") " << msg << "\n"; \
		fbr::printLog(log, color);                                                                                   \
		fbr::Logger::get().writeLogToFile(log);                                                                      \
	} while (0);

#define ASSERT_MSG(condition, msg)                                        \
	do {                                                                  \
		if (condition)                                                    \
			break;                                                        \
		MAKE_LOG("ASSERT", "<" << #condition << " : False> " << msg, 12); \
		if (fbr::ASSERTION) {                                      \
			fbr::Logger::get().~Logger();                          \
			std::abort();                                                 \
		}                                                                 \
	} while (0);

#define ASSERT(condition) ASSERT_MSG(condition, "")

#define LOG_ERR(msg) MAKE_LOG("ERR", msg, fbr::ERR_COLOR);

#define LOG_WAR(msg) MAKE_LOG("WAR", msg, fbr::WAR_COLOR);

#define LOG_INF(msg) MAKE_LOG("INF", msg, fbr::INF_COLOR);

#define HIGHTLIGHT(msg) MAKE_LOG("INF", msg, fbr::HIGHTLIGHT_COLOR);

#else
#define MAKE_LOG(...)
#define ASSERT_MSG(...)
#define ASSERT(...)
#define LOG_ERR(...)
#define LOG_WAR(...)
#define LOG_INF(...)
#define HIGHTLIGHT(...)
#endif
} // namespace fbr