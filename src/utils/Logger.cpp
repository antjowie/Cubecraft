#include <iostream>

#include "Logger.h"

Logger& Logger::instance()
{
	static Logger logger;
	return logger;
}

void Logger::init()
{
	init({});
}

void Logger::init(Configuration configuration)
{
	m_configuration = configuration;
}

Logger& Logger::operator<<(const Log& log)
{
	if (log.severity >= m_configuration.filterSeverity)
		return *this;

	std::printf("[%s] In file %s at line %d: %s",
		severityToString(log.severity).c_str(),
		log.file.c_str(),
		log.line,
		log.message.c_str());
	
	return *this;
}

Logger::Logger()
{
}

std::string Logger::severityToString(Logger::Severity severity)
{
	switch (severity)
	{
	case Logger::Severity::NONE:
		return "NONE";
		break;
	case Logger::Severity::ERROR:
		return "ERROR";
		break;
	case Logger::Severity::WARNING:
		return "WARNING";
		break;
	case Logger::Severity::INFO:
		return "INFO";
		break;
	case Logger::Severity::VERBOSE:
		return "VERBOSE";
		break;
	default:
		return "UNSPECIFIED???";
		break;
	}
}

//https://stackoverflow.com/questions/31050113/how-to-extract-the-source-filename-without-path-and-suffix-at-compile-time/38237385

constexpr bool is_path_sep(char c) {
	return c == '/' || c == '\\';
}

constexpr const char* strip_path(const char* path)
{
	auto lastname = path;
	for (auto p = path; *p; ++p) {
		if (is_path_sep(*p) && *(p + 1)) lastname = p + 1;
	}
	return lastname;
}

Log::Log(const std::string& message, const Logger::Severity severity, const std::string file, const int line)
	: message(message)
	, severity(severity)
	, file(strip_path(file.c_str()))
	, line(line)
{
}
