//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "textui.h"
#include "game.h"
#include "maze.h"
#include "entity.h"
#include "tile.h"
#include <iostream>

TextUI::TextUI() {
  m_msg.clear();
}

TextUI::~TextUI() {
}

Direction TextUI::getMoveDirection() {
  bool validDirection = false;
  while(!validDirection) {
    std::cout << "Your move (u/d/l/r): ";
    char move;
    std::cin >> move;
    switch(move) {
    case 'u': return Direction::UP;
    case 'd': return Direction::DOWN;
    case 'l': return Direction::LEFT;
    case 'r': return Direction::RIGHT;
    default:
      std::cout << "Unknown direction" << std::endl;
    }
  }
  return Direction::NONE;
}

void TextUI::displayMessage(const std::string &msg, bool endgame) {
  // avoid compiler warning
  endgame = true;
  if(endgame) {
    m_msg = msg;
  }
}

void TextUI::render(Game *game) {
  Maze * m = game->getMaze();
  int width = m->getWidth();
  int height = m->getHeight();
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      Position cur_pos(j, i);
      Entity * ent_atPos = game->getEntityAt(cur_pos);
      if(ent_atPos) {
	std::cout << ent_atPos->getGlyph();
      }
      else {
	std::cout << m->getTile(cur_pos)->getGlyph();
      }
      
    }
    std::cout << "\n";
  }  
  if(!m_msg.empty()) {
    std::cout << ": " << m_msg << std::endl;
    m_msg.clear();
  }
}
