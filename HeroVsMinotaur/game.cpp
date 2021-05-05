//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9

#include "game.h"
#include "maze.h"
#include "ui.h"
#include "position.h"
#include "entity.h"
#include "gamerules.h"
#include "entitycontroller.h"
#include "ecfactory.h"
#include <string>

Game::Game() {
}

Game::~Game() {
  delete m_maze;
  delete m_ui;
  delete m_gameRules;
  for(EntityVec::iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
    delete *it;
  }
}

void Game::setMaze(Maze *maze) {
  m_maze = maze;
}

void Game::setUI(UI *ui) {
  m_ui = ui;
}

void Game::setGameRules(GameRules *gameRules) {
  m_gameRules = gameRules;
}

void Game::addEntity(Entity *entity) {
  m_entities.push_back(entity);
}

Entity *Game::getEntityAt(const Position &pos) {
  for(EntityVec::const_reverse_iterator it = m_entities.crbegin(); it != m_entities.crend(); ++it) {
    if((*it)->getPosition() == pos) {
      return *it;
    }
  }
  return nullptr;
}

const Game::EntityVec &Game::getEntities() const {
  return m_entities;
}

std::vector<Entity *> Game::getEntitiesWithProperty(char prop) const {
  std::vector<Entity *> match_prop;
  for(EntityVec::const_iterator it = m_entities.cbegin(); it != m_entities.cend(); ++it) {
    if((*it)->hasProperty(prop)) {
      match_prop.push_back(*it);
    }
  }
  return match_prop;
}

Maze *Game::getMaze() {
  return m_maze;
}

UI *Game::getUI() {
  return m_ui;
}

GameRules *Game::getGameRules() {
  return m_gameRules;
}

void Game::gameLoop() {
  int game_end = (int)m_gameRules->checkGameResult(this);
  while(!game_end) {
    for(EntityVec::const_iterator it = m_entities.cbegin(); it != m_entities.cend(); ++it) {
      if((*it)->getController()->isUser()){
	      m_ui->render(this);
      }
      takeTurn(*it);
      game_end = (int)m_gameRules->checkGameResult(this);
      if(game_end) {
	      break;
      }
    }
  }
  GameResult result = m_gameRules->checkGameResult(this);
  switch(result){
    case GameResult::HERO_WINS:
      m_ui->displayMessage("Hero wins", true);
      m_ui->render(this);
      break;
    case GameResult::HERO_LOSES:
      m_ui->displayMessage("Hero loses", true);
      m_ui->render(this);
    // avoid compiler warning
    case GameResult::UNKNOWN:
      break;
  }
}

void Game::takeTurn(Entity *actor) {
  Position dest = actor->getPosition().displace(actor->getController()->getMoveDirection(this, actor));
  if(m_gameRules->allowMove(this, actor, actor->getPosition(), dest)) {
    m_gameRules->enactMove(this, actor, dest);
  }
  else if(actor->getController()->isUser()) {
    m_ui->displayMessage("Illegal Move", false);
  }
}

Game *Game::loadGame(std::istream &in) {
  Game * new_game = new Game();
  Maze * new_maze = Maze::read(in);
  if(!new_maze) {
    return nullptr;
  }
  new_game->m_maze = new_maze;
  std::string info;
  int x;
  int y;
  while(in >> info >> x >> y) {
    if(info.length() < 2) {
      return nullptr;
    }
    Entity * character = new Entity();
    character->setGlyph(info.substr(0, 1));
    EntityController * con = EntityControllerFactory::getInstance()->createFromChar(info[1]);
    character->setController(con);
    character->setProperties(info.substr(2, info.length() - 2));
    Position pos(x, y);
    if(!pos.inBounds(new_game->m_maze->getWidth(), new_game->m_maze->getHeight())) {
      return nullptr;
    }
    character->setPosition(pos);
    new_game->m_entities.push_back(character);
  }
  if(new_game->m_entities.empty()) {
    return nullptr;
  }
  return new_game;
}
