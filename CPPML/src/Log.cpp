#include "CPPML/Log.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace CPPML {
	std::shared_ptr<spdlog::logger> Log::m_logger;

	void Log::Init(bool on)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		m_logger = spdlog::stdout_color_mt("CPPML");
		if(on) {
        	m_logger->set_level(spdlog::level::trace);
		} else {
			m_logger->set_level(spdlog::level::off);
		}
	}

	void Log::Init(spdlog::level::level_enum level)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		m_logger = spdlog::stdout_color_mt("CPPML");
        m_logger->set_level(level);
	}

}
