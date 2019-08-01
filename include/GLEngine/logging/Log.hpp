#ifndef GLE_LOG_HPP
#define GLE_LOG_HPP

#include <memory> // Shared ptr
#include "spdlog/spdlog.h"

namespace GLEngine
{
class Log
{
private:
	static std::shared_ptr<spdlog::logger> m_EngineLogger;
	static std::shared_ptr<spdlog::logger> m_AppLogger;

public:
	static void Init(const bool& on); // both loggers
	static void Init(const bool& engineOn, const bool &appOn);

	static void Init(const spdlog::level::level_enum &level); // both loggers
	static void Init(const spdlog::level::level_enum &engineLevel, const spdlog::level::level_enum &appLevel);

	inline static std::shared_ptr<spdlog::logger> &GetEngineLogger() { return m_EngineLogger; };
	inline static std::shared_ptr<spdlog::logger> &GetAppLogger() { return m_AppLogger; };
};

} // namespace GLEngine

#define GLE_ENGINE_TRACE(...) GLEngine::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define GLE_ENGINE_INFO(...) GLEngine::Log::GetEngineLogger()->info(__VA_ARGS__)
#define GLE_ENGINE_WARN(...) GLEngine::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define GLE_ENGINE_ERROR(...) GLEngine::Log::GetEngineLogger()->error(__VA_ARGS__)
#define GLE_ENGINE_CRIT(...) GLEngine::Log::GetEngineLogger()->critical(__VA_ARGS__)

#define GLE_TRACE(...) GLEngine::logging::Log::GetAppLogger()->trace(__VA_ARGS__)
#define GLE_INFO(...) GLEngine::logging::Log::GetAppLogger()->info(__VA_ARGS__)
#define GLE_WARN(...) GLEngine::logging::Log::GetAppLogger()->warn(__VA_ARGS__)
#define GLE_ERROR(...) GLEngine::logging::Log::GetAppLogger()->error(__VA_ARGS__)
#define GLE_CRIT(...) GLEngine::logging::Log::GetAppLogger()->critical(__VA_ARGS__)

#endif /* end of include guard LOG_HPP */