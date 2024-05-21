//
//  Temple.hpp
//  project3
//
//  Created by User on 5/13/24.
//

#ifndef Temple_h
#define Temple_h

#include <stdio.h>
#include "globals.h"
#include <string>
#include <iostream>
using namespace std;

class Monster;
class Player;
class GameObject;
class Temple
{
public:
    Temple(Player *player, int level);
    ~Temple();
    int rows() const;
    int cols () const;
    Player* player() const;
    int level(){
        return m_level;
    }

    void initializeLevel();
    void display();
    bool isWall(int row, int col);
    bool isItemat(int row, int col) const;
    GameObject* pickUpObject(int row, int col);
    bool isStairwayAt(int row, int col) const;
    void placeObjects();
    void placePlayer();
    void placeMonsters(int level);
    bool isPositionFree(int row, int col);
    void moveMonster();
    void movePlayer();
    const std::vector<Monster*>& getMonsters() const {
          return m_monsters;
      }
    GameObject* removeObjectAt(int row, int col);
    
private:
    int  m_level; 
    char m_grid[HEIGHT][WIDTH];
    int m_rows;
    int m_cols;
    Player* m_player;
    std::vector<Monster*> m_monsters;
    std::vector<GameObject*> m_objects;

};

#endif /* Temple_h */
