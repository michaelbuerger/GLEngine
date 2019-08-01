#include "GLEngine/logging/Log.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace GLEngine
{
std::shared_ptr<spdlog::logger> Log::m_EngineLogger;
std::shared_ptr<spdlog::logger> Log::m_AppLogger;

void Log::Init(const bool& on) // both loggers
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	m_EngineLogger = spdlog::stdout_color_mt("GLEngine");
	m_AppLogger = spdlog::stdout_color_mt("App");
	if(on) {
    	m_EngineLogger->set_level(spdlog::level::trace);
		m_AppLogger->set_level(spdlog::level::trace);
	} else {
		m_EngineLogger->set_level(spdlog::level::off);
		m_AppLogger->set_level(spdlog::level::off);
	}
}
void Log::Init(const bool& engineOn, const bool &appOn) {
	spdlog::set_pattern("%^[%T] %n: %v%$");

	m_EngineLogger = spdlog::stdout_color_mt("GLEngine");
	m_AppLogger = spdlog::stdout_color_mt("App");
	if(engineOn) {
    	m_EngineLogger->set_level(spdlog::level::trace);
	} else {
		m_EngineLogger->set_level(spdlog::level::off);
	}

	if(appOn) {
		m_AppLogger->set_level(spdlog::level::trace);
	} else {
		m_AppLogger->set_level(spdlog::level::off);
	}
}

void Log::Init(const spdlog::level::level_enum &level) // both loggers
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	m_EngineLogger = spdlog::stdout_color_mt("GLEngine");
	m_AppLogger = spdlog::stdout_color_mt("App");
	m_EngineLogger->set_level(level);
	m_AppLogger->set_level(level);
}
void Log::Init(const spdlog::level::level_enum &engineLevel, const spdlog::level::level_enum &appLevel) {
	spdlog::set_pattern("%^[%T] %n: %v%$");

	m_EngineLogger = spdlog::stdout_color_mt("GLEngine");
	m_AppLogger = spdlog::stdout_color_mt("App");
	m_EngineLogger->set_level(engineLevel);
	m_AppLogger->set_level(appLevel);
}
} // namespace GLEngine
