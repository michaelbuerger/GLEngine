#ifndef CPPML_LOG_HPP
#define CPPML_LOG_HPP

#include <memory>
#include "spdlog/spdlog.h"

namespace CPPML {
	class Log
	{
	    private:
		    static std::shared_ptr<spdlog::logger> m_logger;
	    public:
		    static void Init(bool on);
			static void Init(spdlog::level::level_enum level);

		    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_logger; };
	};

}

#endif /* end of include guard CPPML_LOG_HPP */

#define CPPML_TRACE(...) CPPML::Log::GetLogger()->trace(__VA_ARGS__)
#define CPPML_INFO(...) CPPML::Log::GetLogger()->info(__VA_ARGS__)
#define CPPML_WARN(...) CPPML::Log::GetLogger()->warn(__VA_ARGS__)
#define CPPML_ERROR(...) CPPML::Log::GetLogger()->error(__VA_ARGS__)
#define CPPML_CRIT(...) CPPML::Log::GetLogger()->critical(__VA_ARGS__)