//
//  Temple.cpp
//  project3
//
//  Created by User on 5/13/24.
//
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Temple.h"
#include "Actor.h"
#include "utilities.h"
#include "GameObject.h"
Temple::Temple(Player* player, int level):m_player(player), m_level(level) {
    initializeLevel();
}

int Temple::rows() const
{
    return m_rows;
}
int Temple::cols() const
{
    return m_cols;
}
Player* Temple::player() const
{
    return m_player;
}
void Temple::initializeLevel()
{
    // Fill the entire layout with walls
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH -1)
                m_grid[i][j] = '#';
            else
                m_grid[i][j] = ' ';
            
        }
    // Place the stairway (only if it's not the last level)
     if (m_level < 4) {
         int stairRow, stairCol;
         do {
             stairRow = randInt(1, HEIGHT - 2);
             stairCol = randInt(1, WIDTH - 2);
         } while (m_grid[stairRow][stairCol] != ' ');
         m_grid[stairRow][stairCol] = '>';
     }
    placeObjects();
    placePlayer();
    placeMonsters(level());
  
}

void Temple::display()
{
   // initializeLevel();
    // display objects
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || j == 0 || i == HEIGHT - 1 || j == WIDTH -1)
                m_grid[i][j] = '#';
            else
                m_grid[i][j] = ' ';
            
        }
    for (const auto& obj : m_objects) {
            if (m_grid[obj->row()][obj->col()] != '#') {
                m_grid[obj->row()][obj->col()] = obj->icon();
            }
        }
    // display player
    if (m_grid[m_player->row()][m_player->col()] != '#')
    { 
        m_grid[m_player->row()][m_player->col()] = m_player->icon();
    }
    // display monsters
    for (const auto& monster : m_monsters) {
        if (m_grid[monster->row()][monster->col()] != '#' && m_grid[monster->row()][monster->col()] != '@') {
            m_grid[monster->row()][monster->col()] = monster->icon();
        }
    }
    // display entire grid 
        for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << m_grid[i][j];
        }
        cout << "\n";
    }
    cout << endl;
    cout << "Level: " << level() << ", " << "Hit points: " << m_player->hp() << ", " << "Armor: " << m_player->armorpts() << ", " << "Strength: " << m_player->strengthpts() << ", " << "Dexterity: " << m_player->dextpts() << endl;
    cout << "\n" << endl;
}

bool Temple::isWall(int row, int col)
{
    return m_grid[row][col] == '#'; // checking if a wall

}
bool Temple::isItemat(int row, int col) const
{
    if (m_grid[row][col] == ')' || m_grid[row][col] == '?')
        return true;
    else
        return false; // check if a gameobject is at given position
}

bool Temple::isStairwayAt(int row, int col) const{
    return m_grid[m_player->row()][m_player->col()] == '>'; // for '>' command
}

void Temple::placeObjects(){
    int numObjects = randInt(2, 3);  // Either 2 or 3 objects
    int placedObjects = 0;

    while (placedObjects < numObjects) {
        int objectType = randInt(1, 2);  // 1 for scroll, 2 for weapon
        int row, col;
        
        // Generate random coordinates until a free position is found
        do {
            row = randInt(1, HEIGHT - 2);
            col = randInt(1, WIDTH - 2);
        } while (!isPositionFree(row, col));  // Check only for walls, not actors

        GameObject* object = nullptr;

        // Create the appropriate object based on the random type
        if (objectType == 1) {  // Scroll
            int scrollType = randInt(1, 4);  // Different scroll types, excluding teleportation
            switch (scrollType) {
                case 1:
                    object = new enhanceArmorScroll(row, col);
                    break;
                case 2:
                    object = new enhanceHealthScroll(row, col);
                    break;
                case 3:
                    object = new enhanceDexterityScroll(row, col);
                    break;
                case 4:
                    object = new enhanceStrengthScroll(row, col);
                    break;
            }
        } else if (objectType == 2) {  // Weapon
            int weaponType = randInt(1, 3);  // Different regular weapon types
            switch (weaponType) {
                case 1:
                    object = new Mace(row, col);  // Assume Mace class is defined
                    break;
                case 2:
                    object = new shortSword(row, col);  // Use the new constructor
                    break;
                case 3:
                    object = new longSword(row, col);  // Assume LongSword class is defined
                    break;
            }
        }

        if (object != nullptr) {
            m_objects.push_back(object);
            m_grid[row][col] = object->icon();
            placedObjects++;
        }
    }
}
void Temple::placePlayer(){
    int row, col;
        int maxAttempts = 100;
        int attempts = 0;

        while (attempts < maxAttempts) {
            row = randInt(1, HEIGHT - 2);
            col = randInt(1, WIDTH - 2);

            if (isPositionFree(row, col)) {
                m_player->moveTo(row, col);
                break;
            }
            ++attempts;
        }
}
void Temple::placeMonsters(int level){

    int numMonsters = randInt(2, 5*(level+1)+1);
    int placedMonsters = 0;

    while (placedMonsters < numMonsters) {
        int monsterType = randInt(1, 4);  // 1 for Bogeyman, 2 for Snakewoman, 3 for Dragon, 4 for Goblin
        int row, col;
        
        do {
            row = randInt(1, HEIGHT - 2);
            col = randInt(1, WIDTH - 2);
        } while (!isPositionFree(row, col)); // make sure it's not on a position of a wall or actor

        Monster* monster = nullptr;

        switch (monsterType) {
            case 1:
                if (level >= 2) {
                    monster = new Bogeyman(row, col);
                }
                break;
            case 2:
                monster = new SnakeWoman(row, col);
                break;
            case 3:
                if (level >= 3) {
                    monster = new Dragon(row, col);
                }
                break;
            case 4:
                monster = new Goblin(row, col);
                break;
        }

        if (monster != nullptr) {
            m_monsters.push_back(monster);
            m_grid[row][col] = monster->icon();
            placedMonsters++;
        }
    }
}

bool Temple::isPositionFree(int row, int col){
    if (m_grid[row][col] == '#') // position is free for a monster to spawn if there is no actor or wall
        return false;

    for (const auto& monster : m_monsters) {
        if (monster->row() == row && monster->col() == col)
            return false;
    }

    if (m_player->row() == row && m_player->col() == col)
        return false;

    return true;
}
GameObject* Temple::removeObjectAt(int row, int col) {
    for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
        if ((*it)->row() == row && (*it)->col() == col) {
            GameObject* object = *it;
            m_objects.erase(it);
            m_grid[row][col] = ' ';  // Clear the object's position on the grid
            return object;
        }
    }
    return nullptr; // No object found at the position
}

Temple::~Temple(){
    for (auto obj : m_objects) {
        delete obj;
    }
    for (auto monster : m_monsters) {
        delete monster;
    }
}
