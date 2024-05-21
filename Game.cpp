// Game.cpp

#include "Game.h"
#include "Temple.h"
#include "Actor.h"
#include "utilities.h"
#include "GameObject.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{

    m_player = new Player(0, 0); // create a player with dummy coordinates
    m_temple =  new Temple(m_player, 0); // initialize temple at level 0
    m_temple->initializeLevel(); // initialize base level
  //  m_temple -> placeMonsters(m_temple->level());
    
}
void Game::play()
{
    clearScreen();
    m_temple->display();
    Player* p = m_temple->player();
    if (p == nullptr)
        return;
    cout << "Press q to exit game." << endl;

    while (true)
    {
        char command = getCharacter();
        if (command == 'q')
            break;
        
        int playerRow = p->row();
        int playerCol = p->col();
        bool validMove = false;
        
        switch(command)
        {
            case 'h':
                if (!m_temple->isWall(playerRow, playerCol - 1)) {
                    p->moveTo(playerRow, playerCol - 1);
                    validMove = true;
                }
                break;
            case 'l':
                if (!m_temple->isWall(playerRow, playerCol + 1)) {
                    p->moveTo(playerRow, playerCol + 1);
                    validMove = true;
                }
                break;
            case 'k':
                if (!m_temple->isWall(playerRow - 1, playerCol)) {
                    p->moveTo(playerRow - 1, playerCol);
                    validMove = true;
                }
                break;
            case 'j':
                if (!m_temple->isWall(playerRow + 1, playerCol)) {
                    p->moveTo(playerRow + 1, playerCol);
                    validMove = true;
                }
                break;
            case 'w':
               p->wieldWeapon();
                validMove = true;
                break;
            case 'r':
                p->readScroll();
                validMove = true;
                break;
            case 'i':
                p->showInventory();
                getCharacter();  // pause to allow player to view inventory, exit out by clicking random key
                validMove = true;
                break;
            case 'g': {
                            GameObject* object = m_temple->removeObjectAt(playerRow, playerCol);
                            if (object != nullptr) {
                                p->pickUpObject(object);
                            } else {
                                p->setMessage("There's nothing here to pick up.");
                            }
                            validMove = true;
                            break;
                        }
            case '>':
                if(m_temple->isStairwayAt(playerRow, playerCol)== true)
                {
                    nextLevel();
                //    m_player->descendStairway();
                    validMove = true;
                }
                break;
            default:
                validMove = true;
                
        }
        if (validMove) {
                    for (auto& monster : m_temple->getMonsters()) {
                        monster->doTurn(playerRow, playerCol, m_temple);
                    }
                    clearScreen();
                    m_temple->display();
                if (!p->getMessage().empty()) {
                    cout << p->getMessage() << endl;
                    p->clearMessage();
                    }
                }

    }
}
 
        // loop through actors - actors should have a doTurn function that takes in a movement (for the monster, they can either do 3 things. players take in a key and output that. 
void Game::nextLevel(){
    int newLevel = m_temple->level() + 1;
    if (newLevel <= 4) {
        delete m_temple;  // Clean up the current temple
        m_temple = new Temple(m_player, newLevel); // make new temple with same player, initialize
        m_temple->initializeLevel();
        clearScreen();
        m_temple->display();
    }
    else
        return; // you can't go down if you are on the last level
}

Game::~Game(){
    delete m_temple;
    delete m_player;
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons,
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.

