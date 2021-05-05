//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "basicgamerules.h"
#include "entity.h"
#include "position.h"
#include "tile.h"
#include "maze.h"
#include "entitycontroller.h"

BasicGameRules::BasicGameRules() {
}

BasicGameRules::~BasicGameRules() {
}

bool BasicGameRules::allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const {
    int distance = dest.distanceFrom(source);
    if (distance > 1) {
        return false;
    }
    if (!dest.inBounds(game->getMaze()->getWidth(), game->getMaze()->getHeight())) {
        return false;
    }
    // if the adjacent Tile is unoccupied
    if(!game->getEntityAt(dest)) {
        if(!((int)game->getMaze()->getTile(dest)->checkMoveOnto(actor, source, dest))) {
            return true;
        }
        return false;
    }
    // if it is occupied
    std::string propAtDest = game->getEntityAt(dest)->getProperties();
    std::string actorProp = actor->getProperties();
    // if the Entity at dest is movable
    if(propAtDest == "v") {
        // new position for "v" to move
        Position newdest = dest.displace(actor->getController()->getMoveDirection(game, actor));
        if (!newdest.inBounds(game->getMaze()->getWidth(), game->getMaze()->getHeight())) {
            return false;
        }
        // if tile is occupied
        if(!game->getEntityAt(newdest)) {
            return false;
        }
        if(!((int)game->getMaze()->getTile(newdest)->checkMoveOnto(game->getEntityAt(dest), dest, newdest))) {
            return true;
        }
    }
    if(propAtDest == "m" && actorProp == "h") {
        return true;
    }
    if(propAtDest == "h" && actorProp == "m") {
        return true;
    }
    return false;
}

void BasicGameRules::enactMove(Game *game, Entity *actor, const Position &dest) const {
    if(game->getEntityAt(dest) && game->getEntityAt(dest)->getProperties() == "v") {
        Position newdest = dest.displace(actor->getController()->getMoveDirection(game, actor));
        game->getEntityAt(dest)->setPosition(newdest);
    }
    actor->setPosition(dest);
}

GameResult BasicGameRules::checkGameResult(Game *game) const {
    Game::EntityVec hero = game->getEntitiesWithProperty('h');
    Game::EntityVec minotaur = game->getEntitiesWithProperty('m');
    for(Game::EntityVec::const_iterator it1 = hero.cbegin(); it1 != hero.cend(); ++it1) {
        Position hpos = (*it1)->getPosition();
        if(game->getMaze()->getTile(hpos)->isGoal()){
            return GameResult::HERO_WINS;
        }
        for(Game::EntityVec::const_iterator it2 = minotaur.cbegin(); it2 != minotaur.cend(); ++it2) {
            Position mpos = (*it2)->getPosition();
            if (hpos == mpos) {
                return GameResult::HERO_LOSES;
            }
        }
    }
    return GameResult::UNKNOWN;
}

