#ifndef USER_HANDLER_H
#define USER_HANDLER_H

#define USERNAME_FIELD_KEY "username"
#define FULLNAME_FIELD_KEY "fullname"
#define PASSWORD_FIELD_KEY "password"
#define ROLE_FIELD_KEY "role"

#include <string>
#include <includes/UserModel.h>
#include "bsoncxx/builder/stream/document.hpp"
#include "FileLogger.h"
#include "MongoDBCollection.h"

class UserHandler {
public:
  UserHandler();

  void addUser(const UserModel& user);
  void removeUser(const UserModel& user);
  bool doesUserExists(const std::string& username, const std::string& password, const std::string& role = "");
  std::string getUserFullname(const std::string& username);

  virtual void printUsers();
  virtual bool checkTeacherRolePermission(const std::string& username, const std::string& password);

  class Password {
    public:
      static std::string generateRandom();
  };

protected:
  MongoDBCollection collection_;
};

#endif  // USER_HANDLER_H
