#include <includes/LoginForm.h>
#include <includes/MongoDBCollection.h>
#include <includes/TeacherHandler.h>
#include <includes/TeacherDashboard.h>

void callback(std::string username, std::string password) {
  TeacherHandler teacher;
  bool doesUserHasPrivalges = teacher.checkTeacherRolePermission(username, password);

  if (!doesUserHasPrivalges) {
    exit(EXIT_FAILURE);
  }
  
  TeacherDashboard dashboard(teacher.getUserFullname(username));
  auto screen = ScreenInteractive::Active();
  
  (*(screen)).ExitLoopClosure();
  dashboard.render();
}

int main() {
  LoginForm loginForm(&callback);
  loginForm.render();

  return 0;
}