#include "GLEngine/logging/Log.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace GLEngine { namespace logging
{
	std::shared_ptr<spdlog::logger> Log::m_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::m_AppLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		m_EngineLogger = spdlog::stdout_color_mt("GLEngine");
		m_EngineLogger->set_level(spdlog::level::trace);

		m_AppLogger = spdlog::stdout_color_mt("App");
		m_AppLogger->set_level(spdlog::level::trace);
	}

}}
