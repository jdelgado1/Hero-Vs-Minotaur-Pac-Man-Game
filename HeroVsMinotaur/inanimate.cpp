//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "inanimate.h"

Inanimate::Inanimate() {
}

Inanimate::~Inanimate() {
}

Direction Inanimate::getMoveDirection(Game *, Entity *) {
  return Direction::NONE;
}

bool Inanimate::isUser() const {
  return false;
}
