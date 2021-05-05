//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "goal.h"

Goal::Goal() {
}

Goal::~Goal() {
}

MoveResult Goal::checkMoveOnto(Entity *, const Position &, const Position &) const {
  return MoveResult::ALLOW;
}

bool Goal::isGoal() const {
  return true;
}

std::string Goal::getGlyph() const {
  return "<";
}
