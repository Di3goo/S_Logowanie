#ifndef STUDENT_HANDLER_H
#define STUDENT_HANDLER_H

#include "UserHandler.h"

class StudentHandler : public UserHandler {
public:
  mongocxx::cursor getStudentsList();
};

#endif  // STUDENT_HANDLER_H
