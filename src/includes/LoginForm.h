#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <memory>
#include <string>

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/util/ref.hpp>

using namespace ftxui;

typedef void (*CallbackFunction)(std::string username, std::string password);

class LoginForm {
 private:
  auto prepareFormComponent();
  auto getFormRenderer();
  ftxui::InputOption getPasswordInputOptions();

  std::string username;
  std::string password;
  Component login_submit_button;
  Component input_username;
  Component input_password;
  CallbackFunction submit_callback_function;

 public:
  LoginForm(CallbackFunction successCallbackFuncion);

  void render();
  std::string getProvidedUsername();
  std::string getProvidedPassword();
};

#endif  // LOGINFORM_H
