//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "mysterycontroller.h"

MysteryController::MysteryController() {
}

MysteryController::~MysteryController() {
}

Direction MysteryController::getMoveDirection(Game *, Entity *) {
  return Direction::NONE;
}

bool MysteryController::isUser() const {
  return false;
}
