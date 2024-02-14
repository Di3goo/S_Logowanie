#include "includes/UserModel.h"

UserModel::UserModel(const std::string& username,
const std::string& fullname,
                     const std::string& password,
                     const std::string& role)
    : username_(username), fullname_(fullname), password_(password), role_(role) {}

std::string UserModel::getUsername() const {
  return username_;
}

std::string UserModel::getFullname() const {
  return fullname_;
}

std::string UserModel::getPassword() const {
  return password_;
}

std::string UserModel::getRole() const {
  return role_;
}
