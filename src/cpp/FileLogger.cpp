#include "includes/FileLogger.h"

FileLogger::FileLogger(const std::string& filename) {
    file_.open(filename, std::ios::app);
    if (!file_) {
        // Tworzenie pliku, jeśli nie istnieje
        file_.open(filename);
    }
    if (!file_.is_open()) {
        // Obsługa błędu otwarcia pliku
        throw std::runtime_error("Failed to open the file: " + filename);
    }
}

FileLogger::~FileLogger() {
    if (file_.is_open()) {
        file_.close();
    }
}

void FileLogger::log(const std::string& message) {
    if (file_.is_open()) {
        file_ << message << std::endl;
    }
}
