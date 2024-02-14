#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#define LOGIN_LOGS_FILENAME "logs-login.txt"
#define USERS_LOGS_FILENAME "logs-users.txt"

#include "Logger.h"
#include <fstream>

class FileLogger : public Logger {
public:
    FileLogger(const std::string& filename);
    ~FileLogger();

    void log(const std::string& message) override;

private:
    std::ofstream file_;
};

#endif  // FILE_LOGGER_H
