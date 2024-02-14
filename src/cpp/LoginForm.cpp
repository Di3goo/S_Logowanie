
#include <includes/LoginForm.h>

LoginForm::LoginForm(CallbackFunction submitCallbackFuncion) {
  submit_callback_function = submitCallbackFuncion;
}

ftxui::InputOption LoginForm::getPasswordInputOptions() {
  InputOption password_option;
  password_option.password = true;

  return password_option;
}

auto LoginForm::getFormRenderer() {
  input_username = Input(&username, "...");
  input_password = Input(&password, "...", getPasswordInputOptions());
  login_submit_button = Button("Zaloguj się", [&] { submit_callback_function(username, password); });

  auto formElements = Container::Vertical({
      input_username,
      input_password,
      login_submit_button
  });

  auto renderer = Renderer(formElements, [&] {
    return vbox({
               text(username.empty() ? "Zaloguj się" : "Witaj, " + username),
               separator(),
               hbox(text("Nazwa użytkownika: "), input_username->Render()),
               hbox(text("Hasło: "), input_password->Render()),
               login_submit_button->Render()
           }) |
           border;
  });

  return renderer;
}

void LoginForm::render() {
  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(getFormRenderer());
}

std::string LoginForm::getProvidedUsername() {
  return username;
}

std::string LoginForm::getProvidedPassword() {
  return password;
}
