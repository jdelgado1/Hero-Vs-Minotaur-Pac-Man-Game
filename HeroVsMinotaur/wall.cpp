//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "wall.h"

Wall::Wall() {
}

Wall::~Wall() {
}
  
MoveResult Wall::checkMoveOnto(Entity *, const Position &, const Position &) const {
  return MoveResult::BLOCK;
}

bool Wall::isGoal() const {
  return false;
}

std::string Wall::getGlyph() const {
  return "#";
}
