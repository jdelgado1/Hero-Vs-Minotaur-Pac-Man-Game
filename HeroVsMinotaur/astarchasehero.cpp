//Elaine He jhe48
//Shanelle scao15
//Jose Delgado jdelgad9
#include "astarchasehero.h"
#include "game.h"
#include "basicgamerules.h"
#include "entity.h"
#include "position.h"
#include <vector>
AStarChaseHero::AStarChaseHero(){
    
}
AStarChaseHero::~AStarChaseHero(){

}

Direction AStarChaseHero::getMoveDirection(Game *game, Entity *entity){
    
    Game::EntityVec hero = game->getEntitiesWithProperty('h');
    if (hero.empty()){
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
    //initialize the open list and closed list
    std::vector<Node*> openList;
    std::vector<Node*> closedList;
    bool pathFound = false;
    openList.push_back(constructNode(mpos,0, mpos.distanceFrom(hero_pos), mpos.distanceFrom(hero_pos), nullptr));
    while(!openList.empty()){
        Node * cur = findMinF(openList, closedList);
        if(cur->p == hero_pos){
            pathFound = true;
            break;
        }
        for(int i = 0; i < 3; i++){
            Position next = cur->p.displace((Direction)i);
            //Node* neighbour = constructNode(next, next.distanceFrom(mpos), next.distanceFrom(hero_pos),next.distanceFrom(mpos) +  next.distanceFrom(hero_pos), nullptr);
            // if(!game->getGameRules()->allowMove(game, entity,cur->p, next)||findNode(closedList, next) != -1){
            //     continue;
            // }
            // int tentative_g = cur->g_cost + 1;
            // if(tentative_g < neighbour->g_cost || findNode(openList, next) == -1){
            //     neighbour->prev = cur;
            //     neighbour->g_cost = tentative_g;
            //     neighbour->f_cost = neighbour->g_cost + neighbour->h_cost;
            //     if(findNode(openList, next) == -1){
            //         openList.push_back(neighbour);
            //     }
            // }
            // else if(findNode(openList, next) != -1 && tentative_g < neighbour->g_cost ){
            //     int openind = findNode(openList, next);
            //     openList[openind]->g_cost = tentative_g;
            //     openList[openind]->f_cost = tentative_g + openList[openind]->h_cost;
            //     openList[openind]->prev = cur;
            // }
            int openInd = findNode(openList,next);
            if(game->getGameRules()->allowMove(game, entity,cur->p, next) && findNode(closedList, next) == -1){
                if(openInd != -1){
                    int new_g = cur->g_cost + 1;
                    if(new_g < openList[openInd]->g_cost){
                        //cheaper route is found
                        openList[openInd]->g_cost = new_g;
                        openList[openInd]->f_cost = new_g + openList[openInd]->h_cost;
                        openList[openInd]->prev = cur;
                    }
                }
                else{
                    Node* neighbour = constructNode(next,cur->g_cost + 1, next.distanceFrom(hero_pos),
                    cur->g_cost + 1 + next.distanceFrom(hero_pos), cur);
                    openList.push_back(neighbour);
                }
            }
        }       
    }
    if(pathFound){
        Node *temp = closedList.back();
        while(temp->prev->prev != nullptr){
            temp = temp->prev;
        }
        Position start_pos = temp->prev->p;
        Position next_step = temp->p;
        for(int i = 0; i < 3; i++){
            if(start_pos.displace((Direction)i) == next_step){
                return (Direction) i;
            }
        }
    }
    else{
        // if(!openList.empty()){
        //     for(Node* element : openList){
        //         delete element;
        //     }
        // }
        // if(!closedList.empty()){
        //     for(Node* element : closedList){
        //         delete element;
        //     }
        // }
        return Direction::NONE;
    }
    return Direction::NONE;   
}

bool AStarChaseHero::isUser()const{
    return false;
}


Node* AStarChaseHero::constructNode(Position p, int g, int h, int f, Node *previous){
    Node *n = new Node;
    n->p = p;
    n->g_cost = g;
    n->h_cost = h;
    n->f_cost = f;
    n->prev = previous;
    return n;
}

Node* AStarChaseHero::findMinF(std::vector<Node*> &openList, std::vector<Node*> &closedList){
    std::vector<Node*>::iterator min_pos = openList.begin();
    int minf = openList[0]->f_cost;
    Node *minNode = openList[0];
    for (std::vector<Node*>::iterator i = openList.begin(); i != openList.end(); ++i){
        if((*i)->f_cost <= minf){
            minNode = *i;
            minf = (*i)->f_cost;
            min_pos = i;
        }
    }
    openList.erase(min_pos);
    closedList.push_back(*min_pos);
    return minNode;
}

int AStarChaseHero::findNode(std::vector<Node*> list, Position target){
    
    for(int i = 0; i < (int)list.size(); i++){
        if(list[i]->p == target){
            return i;
        }
    }
    return -1; 
}
