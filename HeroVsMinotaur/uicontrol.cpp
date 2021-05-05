//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "uicontrol.h"
#include "ui.h"

UIControl::UIControl() {
}

UIControl::~UIControl() {
}

Direction UIControl::getMoveDirection(Game *, Entity *) {
  UI *ui = UI::getInstance();
  Direction dir = ui->getMoveDirection();
  return dir; // or Direction::dir
}

bool UIControl::isUser() const {
  return true;
}
