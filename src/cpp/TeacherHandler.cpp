#include <includes/TeacherHandler.h>

/** Returns true, if credentials are correct and given user have "teacher" role. */
bool TeacherHandler::checkTeacherRolePermission(const std::string& username, const std::string& password) {
  Logger* logger = new FileLogger(LOGIN_LOGS_FILENAME);
  bool hasPermission = doesUserExists(username, password, "teacher");

  logger->log("User: " + username + " -> " + (hasPermission ? "login successful" : "false login: incorrect password or lack of permissions of the role 'teacher'"));
  delete logger;

  return hasPermission;
}

void TeacherHandler::printUsers() {
  bsoncxx::builder::stream::document document{};
  document << ROLE_FIELD_KEY << "teacher";

  mongocxx::cursor cursor = collection_.find(document.view());
  for (const auto& doc : cursor) {
    std::cout << "Username: " << doc[USERNAME_FIELD_KEY].get_utf8().value << std::endl;
    std::cout << "Fullname: " << doc[FULLNAME_FIELD_KEY].get_utf8().value << std::endl;
    std::cout << "Password: " << doc[PASSWORD_FIELD_KEY].get_utf8().value << std::endl;
    std::cout << "Role: " << doc[ROLE_FIELD_KEY].get_utf8().value << std::endl;
    std::cout << "---------------------" << std::endl;
  }
}