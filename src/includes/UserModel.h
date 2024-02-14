#ifndef USERMODEL_H
#define USERMODEL_H

#include <string>

class UserModel {
 public:
  UserModel(const std::string& username,
            const std::string& fullname,
            const std::string& password,
            const std::string& role);

  std::string getUsername() const;
  std::string getFullname() const;
  std::string getPassword() const;
  std::string getRole() const;

 private:
  std::string username_;
  std::string fullname_;
  std::string password_;
  std::string role_;
};

#endif  // USERMODEL_H
