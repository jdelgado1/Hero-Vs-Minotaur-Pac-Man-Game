//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "floor.h"

Floor::Floor() {
}

Floor::~Floor() {
}

MoveResult Floor::checkMoveOnto(Entity *, const Position &, const Position &) const {
  return MoveResult::ALLOW;
}

bool Floor::isGoal() const {
  return false;
}

std::string Floor::getGlyph() const {
  return ".";
}
