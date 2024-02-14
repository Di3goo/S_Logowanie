#include <includes/UserHandler.h>

UserHandler::UserHandler() : collection_("users") {}

/** Creates user with given model. */
void UserHandler::addUser(const UserModel& user) {
  Logger* logger = new FileLogger(USERS_LOGS_FILENAME);

  bsoncxx::builder::stream::document document{};
  document << USERNAME_FIELD_KEY << user.getUsername()
           << FULLNAME_FIELD_KEY << user.getFullname()
           << PASSWORD_FIELD_KEY << user.getPassword()
           << ROLE_FIELD_KEY << user.getRole();
  collection_.addDocument(document.view());

  logger->log("Created user: " + user.getUsername());
  delete logger;
}

/** Removes user with given model. */
void UserHandler::removeUser(const UserModel& user) {
  bsoncxx::builder::stream::document document{};
  document << USERNAME_FIELD_KEY << user.getUsername();
  collection_.removeDocument(document.view());
}

/** Check if user with given username, password and role exists. */
bool UserHandler::doesUserExists(const std::string& username, const std::string& password, const std::string& role) {
  bsoncxx::builder::stream::document document{};
  document << USERNAME_FIELD_KEY << username
           << PASSWORD_FIELD_KEY << password;

  if (!role.empty()) {
    document << ROLE_FIELD_KEY << role;
  }

  mongocxx::cursor cursor = collection_.find(document.view());
  return (cursor.begin() != cursor.end());
}
/** Print documents collected in users collection. Only for debug purposes. */
void UserHandler::printUsers() {
  collection_.printDocuments();
}

/** Returns fullname for given username, or empty string if given user does not exists. */
std::string UserHandler::getUserFullname(const std::string& username) {
  bsoncxx::builder::stream::document document{};
  document << USERNAME_FIELD_KEY << username;

  mongocxx::cursor cursor = collection_.find(document.view());
  if (cursor.begin() != cursor.end()) {
    for (const auto& doc : cursor) {
      const auto& view = doc[FULLNAME_FIELD_KEY];
      if (view) {
        std::string fullname(view.get_utf8().value);
        return fullname;
      }
    }
  }

  return "";
}

std::string UserHandler::Password::generateRandom() {
  const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@$#%^&*";
  std::string password;
  
  srand(static_cast<unsigned int>(time(0)));
  
  for (int i = 0; i < 16; ++i) {
    int index = rand() % characters.size();
    password += characters[index];
  }
  
  return password;
}

bool UserHandler::checkTeacherRolePermission(const std::string& username, const std::string& password) {
  return false;
}

