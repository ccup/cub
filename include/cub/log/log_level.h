#ifndef H3A332558_B92E_4CED_B246_A8857695EAC6
#define H3A332558_B92E_4CED_B246_A8857695EAC6

#include "cub/log/log_color.h"
#include "cub/base/EnumCast.h"

CUB_NS_BEGIN

enum class LogLevel : unsigned int {
	NONE  = 0x0,
    DEBUG = 0x01,
	INFO  = 0x02,
	SUCC  = 0x04,
	WARN  = 0x08,
	ERROR = 0x10,
	FATAL = 0x20,
	TOTAL = 0xFF
};

#define EG_LOG_LEVEL_STRING(LEVEL)         case LogLevel::LEVEL  : return #LEVEL;
#define EG_LOG_LEVEL_COLOR(LEVEL, COLOR)   case LogLevel::LEVEL  : return to_color_fmt(LogColor::COLOR);

constexpr const char* to_string(LogLevel level) {
	switch (level) {
	EG_LOG_LEVEL_STRING(NONE);
	EG_LOG_LEVEL_STRING(DEBUG);
	EG_LOG_LEVEL_STRING(INFO);
	EG_LOG_LEVEL_STRING(SUCC);
	EG_LOG_LEVEL_STRING(WARN);
	EG_LOG_LEVEL_STRING(ERROR);
	EG_LOG_LEVEL_STRING(FATAL);
	EG_LOG_LEVEL_STRING(TOTAL);
	}
	return "UNKNOWN";
}

constexpr const char* color_fmt_of(LogLevel level) {
	switch (level) {
	EG_LOG_LEVEL_COLOR(NONE,  WHITE);
	EG_LOG_LEVEL_COLOR(DEBUG, BLUE);
	EG_LOG_LEVEL_COLOR(INFO,  CYAN);
	EG_LOG_LEVEL_COLOR(SUCC,  GREEN);
	EG_LOG_LEVEL_COLOR(WARN,  YELLOW);
	EG_LOG_LEVEL_COLOR(ERROR, RED);
	EG_LOG_LEVEL_COLOR(FATAL, RED);
	EG_LOG_LEVEL_COLOR(TOTAL, WHITE);
	}
	return to_color_fmt(LogColor::WHITE);
}

constexpr bool level_enabled(LogLevel level) {
	constexpr unsigned int enabled_levels = enum_underlying_cast(LogLevel::FATAL)
										  | enum_underlying_cast(LogLevel::ERROR)
										  | enum_underlying_cast(LogLevel::WARN)
										  | enum_underlying_cast(LogLevel::SUCC)
										  | enum_underlying_cast(LogLevel::INFO)
//										  | enum_underlying_cast(LogLevel::DEBUG)
										  ;
	return enum_underlying_cast(level) & enabled_levels;
}

CUB_NS_END

#endif
