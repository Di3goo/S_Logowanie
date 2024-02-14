#ifndef TEACHER_DASHBOARD_H
#define TEACHER_DASHBOARD_H

#include <memory>
#include <string>

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/util/ref.hpp>

#include <includes/StudentHandler.h>
#include <includes/UserHandler.h>
#include <includes/UserModel.h>

using namespace ftxui;

typedef void (*CallbackFunction)(std::string username, std::string password);

class TeacherDashboard {
 private:
  ftxui::MenuOption getStudentsMenuOptions(ScreenInteractive &screen);
  std::vector<std::string> prepareStudentsList();
  auto getCreateStudentFormRenderer();
  auto getStudentsListRenderer();
  auto getFormRenderer();

  std::vector<std::string> students_list;
  std::string fullname_;
  std::string new_student_username;
  std::string new_student_fullname;
  Component new_student_username_input;
  Component new_student_fullname_input;
  Component new_student_submit_button;
  int selected_student_index;
  int selected_tab_index;

 public:
  TeacherDashboard(std::string fullname);

  void render();
};

#endif  // TEACHER_DASHBOARD_H
