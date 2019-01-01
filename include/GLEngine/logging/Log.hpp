#ifndef LOG_HPP
#define LOG_HPP

#include <memory> // Shared ptr
#include "spdlog/spdlog.h"

namespace GLEngine { namespace logging
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; };
	};

}}

#endif /* end of include guard LOG_HPP */

#ifndef GLE_ENGINE_DEBUG_LOG_OFF

#define GLE_ENGINE_TRACE(...) GLEngine::logging::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define GLE_ENGINE_INFO(...) GLEngine::logging::Log::GetEngineLogger()->info(__VA_ARGS__)
#define GLE_ENGINE_WARN(...) GLEngine::logging::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define GLE_ENGINE_ERROR(...) GLEngine::logging::Log::GetEngineLogger()->error(__VA_ARGS__)
#define GLE_ENGINE_CRIT(...) GLEngine::logging::Log::GetEngineLogger()->critical(__VA_ARGS__)

#endif

#ifndef APPLICATION_DEBUG_LOG_OFF

#define GLE_TRACE(...) GLEngine::logging::Log::GetAppLogger()->trace(__VA_ARGS__)
#define GLE_INFO(...) GLEngine::logging::Log::GetAppLogger()->info(__VA_ARGS__)
#define GLE_WARN(...) GLEngine::logging::Log::GetAppLogger()->warn(__VA_ARGS__)
#define GLE_ERROR(...) GLEngine::logging::Log::GetAppLogger()->error(__VA_ARGS__)
#define GLE_CRIT(...) GLEngine::logging::Log::GetAppLogger()->critical(__VA_ARGS__)

#endif
