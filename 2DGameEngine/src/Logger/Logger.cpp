#include "Logger.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>


std::vector<LogEntry> Logger::messages;

static std::string current_date_time_to_string() 
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');
	std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));
	return output;
}

void Logger::Log(const std::string& message)
{
	LogEntry log_entry;
	log_entry.type = LOG_INFO;
	log_entry.message =  "LOG: [" + current_date_time_to_string() + "]: " + message;
	std::cout << "\x1B[32m" << log_entry.message << "\033[0m" << std::endl;

	messages.push_back(log_entry);
}

void Logger::Err(const std::string& message)
{
	LogEntry log_entry;
	log_entry.type = LOG_ERROR;
	log_entry.message = "ERR: [" + current_date_time_to_string() + "]: " + message;
	std::cout << "\x1B[91m" << log_entry.message << "\033[0m" << std::endl;

	messages.push_back(log_entry);
}
