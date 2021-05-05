//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9

#ifndef ASTARCHASEHERO_H
#define ASTARCHASEHERO_H

#include "entitycontroller.h"
#include "game.h"
#include "basicgamerules.h"
#include "entity.h"
#include "position.h"
#include <vector>

  struct Node{
    Position p;
    int g_cost;
    int h_cost;
    int f_cost;
     Node* prev;
  };
class AStarChaseHero : public EntityController {
private:
  // copy constructor and assignment operator are disallowed
  AStarChaseHero(const AStarChaseHero &);
  AStarChaseHero &operator=(const AStarChaseHero &);

public:
  AStarChaseHero();
  virtual ~AStarChaseHero();
 
  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;

private:

  static Node* constructNode(Position p, int g, int h, int f, Node* previous);
  static Node* findMinF(std::vector<Node*> &openList, std::vector<Node*> &closedList);
  static int findNode(std::vector<Node*> list, Position target);


};

#endif // ASTARCHASEHERO_H
