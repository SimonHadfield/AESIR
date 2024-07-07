#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/bundled/core.h>
#include <spdlog/fmt/bundled/ostream.h>



namespace Aesir {

	class AESIR_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define AE_CORE_TRACE(...)     ::Aesir::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AE_CORE_INFO(...)      ::Aesir::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AE_CORE_WARN(...)      ::Aesir::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AE_CORE_ERROR(...)     ::Aesir::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AE_CORE_CRITICAL(...)  ::Aesir::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define AE_TRACE(...)     ::Aesir::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AE_INFO(...)      ::Aesir::Log::GetClientLogger()->info(__VA_ARGS__)
#define AE_WARN(...)      ::Aesir::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AE_ERROR(...)     ::Aesir::Log::GetClientLogger()->error(__VA_ARGS__)
#define AE_CRITICAL(...)  ::Aesir::Log::GetClientLogger()->critical(__VA_ARGS__)