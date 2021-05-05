//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include <cassert>
#include "ui.h"

UI *UI::s_instance;

UI::UI() {
  // there can be only one instance of UI
  // assert(s_instance == nullptr);
  s_instance = this;
}

UI::~UI() {
}

UI *UI::getInstance() {
  // make sure that the singleton instance exists
  assert(s_instance != nullptr);
  return s_instance;
}
