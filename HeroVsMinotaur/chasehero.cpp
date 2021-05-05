//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "chasehero.h"
#include "entity.h"
#include "game.h"
#include "basicgamerules.h"

ChaseHero::ChaseHero() {
}

ChaseHero::~ChaseHero() {
}

Direction ChaseHero::getMoveDirection(Game *game, Entity *entity) {
    Game::EntityVec hero = game->getEntitiesWithProperty('h');
    if(hero.empty()){
        return Direction::NONE;
    }
    Position mpos = entity->getPosition();
    std::vector<int> dist;
    //getting the position of all heros
    for(Game::EntityVec::const_iterator it1 = hero.cbegin(); it1 != hero.cend(); ++it1) {
        Position hpos = (*it1)->getPosition();   
        dist.push_back(mpos.distanceFrom(hpos));
    }
    //finding the closest hero
    int min = dist[0];
    int min_hero = 0;
    for(int i = 1; i < (int)dist.size(); i++){
        if(min - dist[i] < 0){
            min = dist[i];
            min_hero = i;
        }
    }
    Entity *closest_hero = hero[min_hero];
    Position hero_pos = closest_hero->getPosition();
    //checking which direction results in shortest movement
    int min_dist = min, cur_dist, index = 4;
    for(int dir = 3; dir >= 0; dir--){
        Position new_pos = mpos.displace((Direction) dir);
        if(game->getGameRules()->allowMove(game, entity, mpos, new_pos)){
            cur_dist = new_pos.distanceFrom(hero_pos);
            if(cur_dist < min_dist) {
                min_dist = cur_dist;
                index = dir;
            }           
        }
    }
    return (Direction) index;
}

bool ChaseHero::isUser()const{
return false;
}
