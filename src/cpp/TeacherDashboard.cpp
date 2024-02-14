#include <includes/TeacherDashboard.h>

TeacherDashboard::TeacherDashboard(std::string fullname) {
  fullname_ = fullname;
  selected_student_index = 0;
  selected_tab_index = 0;
  students_list = prepareStudentsList();
}

std::vector<std::string> TeacherDashboard::prepareStudentsList() {
  std::vector<std::string> entries = {};

  StudentHandler studentHandler;
  auto list = studentHandler.getStudentsList();

  for (const auto& doc : list) {
    const auto& view = doc[FULLNAME_FIELD_KEY];
    if (view) {
      std::string data(view.get_utf8().value);
      entries.push_back(data);
    }
  }

  return entries;
}

MenuOption TeacherDashboard::getStudentsMenuOptions(ScreenInteractive& screen) {
  MenuOption option;
  option.on_enter = screen.ExitLoopClosure();

  return option;
}

auto TeacherDashboard::getStudentsListRenderer() {
  auto students_list_component = Menu(&students_list, &selected_student_index);

  return students_list_component;
}

auto TeacherDashboard::getCreateStudentFormRenderer() {
  new_student_username_input = Input(&new_student_username, "...");
  new_student_fullname_input = Input(&new_student_fullname, "...");
  new_student_submit_button = Button("Dodaj ucznia", [&] { 
    std::string generated_password = UserHandler::Password::generateRandom();
    UserModel newStudent(new_student_username, new_student_fullname, generated_password, "student");
    UserHandler users;
    users.addUser(newStudent);
    students_list = prepareStudentsList();
  });

  auto formElements = Container::Vertical({
      new_student_username_input,
      new_student_fullname_input,
      new_student_submit_button
  });

  auto renderer = Renderer(formElements, [&] {
    return vbox({
               text("Nowy uczen dla nauczyciela: " + fullname_),
               separator(),
               hbox(text("Nazwa użytkownika: "), new_student_username_input->Render()),
               hbox(text("Imię i nazwisko: "), new_student_fullname_input->Render()),
               new_student_submit_button->Render()
           }) |
           border;
  });

  return renderer;
}

void TeacherDashboard::render() {
  auto screen = ScreenInteractive::TerminalOutput();
  // auto menu_options = getStudentsMenuOptions(&screen);
  auto students_list_component = getStudentsListRenderer();
  auto student_create_form_component = getCreateStudentFormRenderer();
  auto your_account_component = Button(fullname_ + " - wyloguj się ", [&] { exit(EXIT_SUCCESS); });

  std::vector<std::string> tab_values{"Lista uczniów", "Dodaj ucznia", "Twoje konto"};
  auto tab_toggle = Toggle(&tab_values, &selected_tab_index);

  auto tab_container =
      Container::Tab({students_list_component, student_create_form_component, your_account_component}, &selected_tab_index);

  auto container = Container::Vertical({
      tab_toggle,
      tab_container,
  });

  auto renderer = Renderer(container, [&] {
    return vbox({
               tab_toggle->Render(),
               separator(),
               tab_container->Render(),
           }) |
           border;
  });

  screen.Loop(renderer);
}