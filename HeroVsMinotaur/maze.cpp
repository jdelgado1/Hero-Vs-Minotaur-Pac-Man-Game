//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "maze.h"
#include "tile.h"
#include "entity.h"
#include "position.h"
#include "tilefactory.h"
#include <string>

Maze::Maze(int width, int height) {
  m_width = width;
  m_height = height;
}

Maze::~Maze() {
  for(std::vector<Tile*>::iterator it = m_tile.begin(); it != m_tile.end(); ++it) {
    delete *it;
  }
}

int Maze::getWidth() const{
  return m_width;
}

int Maze::getHeight() const{
  return m_height;
}

bool Maze::inBounds(const Position &pos) const{
  return pos.inBounds(m_width, m_height);
}

void Maze::setTile(const Position &pos, Tile *tile) {
  m_tile[pos.getY() * m_width + pos.getX()] = tile;
}

const Tile *Maze::getTile(const Position &pos) const {
  return m_tile[pos.getY() * m_width + pos.getX()];
}

Maze *Maze::read(std::istream &in) {
  int width;
  int height;
  in >> width >> height;
  Maze * new_maze = new Maze(width, height);
  for(int i = 0; i < height; i++) {
    std::string s;
    in >> s;
    for(int j = 0; j < width; j++) {
      Tile * new_tile = TileFactory::getInstance()->createFromChar(s[j]);
      if(!new_tile) {
        return nullptr;
      }
    new_maze->m_tile.push_back(new_tile);
    }
  }
  return new_maze;
}
