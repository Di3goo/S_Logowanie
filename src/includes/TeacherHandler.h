#ifndef TEACHER_HANDLER_H
#define TEACHER_HANDLER_H

#include "UserHandler.h"

class TeacherHandler : public UserHandler {
public:
  bool checkTeacherRolePermission(const std::string& username, const std::string& password) override;
  void printUsers() override;
};

#endif  // TEACHER_HANDLER_H
