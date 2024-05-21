//
//  Actor.hpp
//  project3
//
//  Created by User on 5/12/24.
//

#ifndef Actor_h
#define Actor_h

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
class GameObject;
class Weapon;
class Scroll;
class Temple;
class Actor
{
public:
    Actor (int row, int col, int hp, int maxhp, int armor, int strength, int dext, int sleep, Weapon* weapon, char icon);
    virtual ~Actor();
    void resultofAttack();
    void moveTo(int row, int col);
    // accessor functions
    int row() const;
    int col() const;
    int hp() const;
    int maxhp() const;
    int armorpts() const;
    int strengthpts() const;
    int dextpts() const;
    int sleeptime() const;
    char icon() const;
    void updatePosition ();
    Weapon* getWeapon();
    void setWeapon(Weapon* weapon);
    void incrementRow();
    void incrementCol();
    void decrementRow();
    void decrementCol();
    // setter functions?

    
private:
    int m_row;
    int m_col;
    int m_hp;
    int m_maxhp;
    int m_armorpoints;
    int m_strengthpoints;
    int m_dextpoints;
    int m_sleeptime;
    Weapon* m_weapon; // current weapon
    Temple* m_temple; 
    char m_icon; // represent the actor on the map
    
};
class Player :  public Actor
{
public:
    Player(int row, int col);
//    Player (int row, int col, int hp, int maxhp, int armor, GameObject object, int strength, int dext, int sleep, Weapon weapon, char icon, GameObject* inventory[], int invensize);
    virtual ~Player();
    void attack();
    void wieldWeapon();
    void addtoInventory(GameObject* obj);
    void showInventory();
    bool descendStairway();
    void cheat();
    void pickUpObject(GameObject* object);
    void readScroll();
    void quitGame();
    void setMessage(const std::string& message) { m_message = message; }
    string getMessage() const {
        return m_message;
    }
    void clearMessage() { m_message.clear(); }
private:
    GameObject* m_inventory[25]; // pointers to inventory of GameObjects
    int m_invenSize;
    string m_message;
};

class Monster : public Actor
{
public:
    Monster(int row, int col, int hp, int maxhp, int armor, int strength, int dext, int sleep, Weapon* weapon, char icon);
    virtual ~Monster(){}
    virtual void doTurn(int playerRow, int playerCol, Temple* temple) = 0; // turn changes depending on location of monster
    virtual void attack() = 0;
    virtual bool doNothing() = 0 ;
    virtual void dropItem() = 0;
    virtual bool isDead() = 0;//
private:
    
};
class Bogeyman : public Monster
{
public:
    Bogeyman(int row, int col);
 //   virtual void doTurn(Player*player);
    virtual void doTurn(int playerRow, int playerCol, Temple* temple);
    bool canSmell(int startRow, int startCol, int targetRow, int targetCol);
    virtual void attack();
    virtual bool doNothing();
    virtual void dropItem();
     bool isDead();
    virtual ~Bogeyman(){}
private:
};
class SnakeWoman : public Monster
{
public:
    SnakeWoman(int row, int col);
    virtual void doTurn(int playerRow, int playerCol, Temple* temple);// turn changes depending on location of monster
    virtual void attack();
    bool canSmell(int startRow, int startCol, int targetRow, int targetCol);
    virtual bool doNothing();
    virtual void dropItem();
    virtual bool isDead(); //
    virtual ~SnakeWoman(){}
private:
};
class Dragon : public Monster
{
public:
    Dragon(int row, int col);
    virtual void doTurn(int playerRow, int playerCol, Temple* temple);// turn changes depending on location of monster
    virtual void attack();
    virtual bool doNothing();
    virtual void dropItem();
    virtual bool isDead();//
    void heal();
    virtual ~Dragon(){}
private:
};
class Goblin : public Monster
{
public:
    Goblin(int row, int col);
    virtual void doTurn(int playerRow, int playerCol, Temple* temple); // turn changes depending on location of monster
    virtual void attack();
    virtual bool doNothing();
    virtual void dropItem();
    virtual bool isDead(); //
    virtual ~Goblin(){}
private:
};
#endif /* Actor_h */
