#pragma once
#include <string>

#define LOG(message, severity) Logger::instance() << Log(message, severity, __FILE__, __LINE__);

// Singleton class, use to log information to a central place
// so that I can easily route messages if needed
struct Log;
class Logger
{
public:
	struct Configuration;
	enum class Severity;

	static Logger& instance();

	void init();
	void init(Configuration configuration);

	Logger& operator<<(const Log& log);

	struct Configuration
	{
		// If a filepath is supplied, the logger will write to the file
		const char* filePath = "";

		// Ignores logs that have a lower severity
		Severity filterSeverity = Severity::VERBOSE;
	};

	enum class Severity
	{
		// NONE will always be logged
		NONE,
		FATAL,
		WARNING,
		INFO,
		VERBOSE
	};

private:
	Logger();

	// This function has nothing to do with logger but only logger needs to know about it
	// Consider refactoring Severity to its own class
	static std::string severityToString(Logger::Severity severity);

	Configuration m_configuration;
};

// Structure containing log information. It is advised to use LOG macro instead
struct Log
{
	Log(const std::string& message, const Logger::Severity severity, const std::string file, const int line);

	const std::string message;
	const Logger::Severity severity;
	const std::string file;
	const int line;
};