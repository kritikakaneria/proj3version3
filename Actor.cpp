//
//  Actor.cpp
//  project3
//
//  Created by User on 5/12/24.
//

#include "Actor.h"
#include "GameObject.h"
#include "Temple.h"
#include "utilities.h"
#include <iostream>

// Actor implementation //
Actor::Actor (int row, int col, int hp, int maxhp, int armor, int strength, int dext, int sleep, Weapon* weapon, char icon):m_row(row), m_col(col), m_hp(hp), m_maxhp(maxhp), m_armorpoints(armor), m_strengthpoints(strength), m_dextpoints(dext), m_sleeptime(sleep), m_weapon(weapon), m_icon(icon) {}
 Actor:: ~Actor() {}
void Actor::resultofAttack() {}
// getter functions
int Actor::row() const {
    return m_row;
}
int Actor::col() const {
    return m_col;
}
int Actor::hp() const {
    return m_hp;
}
int Actor::maxhp() const {
    return m_maxhp;
}
int Actor::armorpts() const {
    return m_armorpoints;
}
int Actor::strengthpts() const {
    return m_strengthpoints;
}
int Actor::dextpts() const {
    return m_dextpoints;
}
int Actor::sleeptime() const {
    return m_sleeptime;
}
Weapon* Actor::getWeapon()  {
    return m_weapon;
}
void Actor::setWeapon(Weapon* weapon){
    m_weapon = weapon;
}
char Actor::icon() const {
    return m_icon;
}
void Actor::moveTo(int row, int col)
{
    m_row = row;
    m_col = col;
}
void Actor::incrementRow()
{
    m_row++;
}
void Actor::incrementCol()
{
    m_col++;
}
void Actor::decrementRow()
{
    m_row--;
}
void Actor::decrementCol()
{
    m_col--;
}


// player implementation //
//Player::Player (int row, int col, int hp, int maxhp, int armor, GameObject object, int strength, int dext, int sleep, Weapon weapon, char icon, GameObject* inventory[], int invensize): Actor (row, col, hp, maxhp, armor, strength, dext, sleep, weapon, icon), m_object(object), m_invenSize(invensize) {
//Actor (int row, int col, int hp, int maxhp, int armor, int strength, int dext, int sleep, Weapon weapon, char icon)
    Player::Player(int row, int col): Actor(row, col, 20, 20, 2, 2, 2, 0, new shortSword(row, col), '@'), m_invenSize(0) {


    // Initialize inventory with nullptrs
       for (int i = 0; i < 25; ++i) {
           m_inventory[i] = nullptr;
       }

//       if (inventory != nullptr) {
//           for (int i = 0; i < invensize; ++i) {
//               m_inventory[i] = inventory[i]; // copy inventory to m_inventory
//           }
//       }

    m_inventory[m_invenSize] = new shortSword();
       m_invenSize++; // every player starts out with a short sword in their inventory
   }
 Player::~Player(){
    for (int i = 0; i < m_invenSize; ++i) {
            delete m_inventory[i];
        }
}

void Player::addtoInventory(GameObject* obj){
//    if (m_inventory.size() < 25) {
//            m_inventory.push_back(obj);
}
void Player::pickUpObject(GameObject* object){
    if (m_invenSize < 25) {
          m_inventory[m_invenSize] = object;
          m_invenSize++;
          if (object->name() == "golden idol") {
              m_message = "Congratulations, you won!";
              // Handle game win logic here
          } else {
              m_message = "You pick up " + object->name() + ".";
          }
      } else {
          m_message = "Your knapsack is full; you can't pick that up.";
      }
}
    
void Player::showInventory()
{
    cout << "Inventory:" << endl;
      for (int i = 0; i < m_invenSize; ++i) {
          cout << static_cast<char>('a' + i) << ". " << m_inventory[i]->name() << endl;
      }
}
void Player::wieldWeapon(){
//    clearScreen(); // Clear the screen to display the inventory
//        showInventory();
//
//        cout << "Select a weapon to wield: ";
//        char choice;
//        cin >> choice;
//
//        int index = choice - 'a';
//        if (index >= 0 && index < m_invenSize && dynamic_cast<Weapon*>(m_inventory[index])) {
//            setWeapon(dynamic_cast<Weapon*>(m_inventory[index]));
//            m_message = "You are now wielding " + getWeapon()->name() + ".";
//        } else {
//            m_message = "Invalid selection or not a weapon.";
//        }
    clearScreen(); // Clear the screen to display the inventory
    showInventory();

    cout << "Select a weapon to wield: ";
    char choice;
    cin >> choice;

    int index = choice - 'a';
    if (index >= 0 && index < m_invenSize && dynamic_cast<Weapon*>(m_inventory[index])) {
        Weapon* newWeapon = dynamic_cast<Weapon*>(m_inventory[index]);
        if (newWeapon != getWeapon()) { // Check if the new weapon is different from the current one
            // Find a place in the inventory for the current weapon if it's not nullptr
            if (getWeapon() != nullptr) {
                bool addedToInventory = false;
                for (int i = 0; i < m_invenSize; ++i) {
                    if (m_inventory[i] == nullptr) {
                        m_inventory[i] = getWeapon();
                        addedToInventory = true;
                        break;
                    }
                }
                if (!addedToInventory && m_invenSize < 25) {
                    m_inventory[m_invenSize++] = getWeapon();
                }
            }
            // Set the new weapon
            setWeapon(newWeapon);
            // Remove the new weapon from the inventory
            m_inventory[index] = nullptr;
            m_message = "You are now wielding " + getWeapon()->name() + ".";
        } else {
            m_message = "You are already wielding " + getWeapon()->name() + ".";
        }
    } else {
        m_message = "Invalid selection or not a weapon.";
    }
}

void Player::readScroll(){
    clearScreen(); // Clear the screen to display the inventory
    showInventory();

//       cout << "Select a scroll to read: ";
//       char choice;
//       cin >> choice;
//
//       int index = choice - 'a';
//    if (index >= 0 && index < m_invenSize && dynamic_cast<Scroll*>(m_inventory[index])) {
//        dynamic_cast<Scroll*>(m_inventory[index])->performEffect(*this);
//        cout << "You read the " << m_inventory[index]->name() << "." << endl;
//
//           // Remove the scroll from the inventory
//           delete m_inventory[index];
//           for (int i = index; i < m_invenSize - 1; ++i) {
//               m_inventory[i] = m_inventory[i + 1];
//           }
//           m_invenSize--;
//       }
//            else {
//           cout << "Invalid selection or not a scroll." << endl;
//       }
 }

bool Player::descendStairway(){
    return true;
}
// monster implementations
Monster::Monster(int row, int col, int hp, int maxhp, int armor, int strength, int dext, int sleep, Weapon* weapon, char icon) : Actor(row, col, hp, maxhp, armor, strength, dext, sleep, weapon, icon) {}


// bogeyman implementations
Bogeyman::Bogeyman(int row, int col)
    : Monster(row, col, randInt(5, 10), 10, 2, randInt(2, 3), randInt(2, 3), 0, new shortSword(row,col), 'B') {}

bool Bogeyman::canSmell(int startRow, int startCol, int targetRow, int targetCol)
{
    return std::abs(startRow - targetRow) + std::abs(startCol - targetCol) <= 5;
}
void Bogeyman::doTurn(int playerRow, int playerCol, Temple* temple)
{
    if (std::abs(this->row() - playerRow) <= 1 && std::abs(this->col() - playerCol) <= 1) {
           this->attack();
           return; // if it's right next to the player, call the attack function
       }
    if (canSmell(this->row(), this->col(), playerRow, playerCol)) {
        // Move one step closer to the player's row or column
        int dRow = playerRow > this->row() ? 1 : (playerRow < this->row() ? -1 : 0);
        int dCol = playerCol > this->col() ? 1 : (playerCol < this->col() ? -1 : 0);
        
        // Attempt to move vertically or horizontally towards the player
        if (dRow != 0 && !temple->isWall(this->row() + dRow, this->col())) {
            this->moveTo(this->row() + dRow, this->col());
        } else if (dCol != 0 && !temple->isWall(this->row(), this->col() + dCol)) {
            this->moveTo(this->row(), this->col() + dCol);
        } else {
            // If neither movement is possible, do nothing
            this->doNothing();
        }
    }
}
void Bogeyman::attack(){
    
}
bool Bogeyman::isDead(){
    return false;
}
void Bogeyman::dropItem(){
    
}
bool Bogeyman::doNothing(){
    return true;
}


// Monster(int row, int col, int hp, int maxhp, int armor, int strength, int dext, int sleep, Weapon weapon, char icon);
// snakewoman implementations
SnakeWoman::SnakeWoman(int row, int col)
    : Monster(row, col, randInt(3, 6), 6, 2, 3, 3, 0, new magicFang(row,col), 'S') {}
bool SnakeWoman::canSmell(int startRow, int startCol, int targetRow, int targetCol)
{
    return std::abs(startRow - targetRow) + std::abs(startCol - targetCol) <= 3;
}
void SnakeWoman::doTurn(int playerRow, int playerCol, Temple* temple)
{
    if (std::abs(this->row() - playerRow) <= 1 && std::abs(this->col() - playerCol) <= 1) {
           this->attack();
           return; // if it's right next to the player, call the attack function
       }
    if (canSmell(this->row(), this->col(), playerRow, playerCol)) {
        // Move one step closer to the player's row or column
        int dRow = playerRow > this->row() ? 1 : (playerRow < this->row() ? -1 : 0);
        int dCol = playerCol > this->col() ? 1 : (playerCol < this->col() ? -1 : 0);
        
        // Attempt to move vertically or horizontally towards the player
        if (dRow != 0 && !temple->isWall(this->row() + dRow, this->col())) {
            this->moveTo(this->row() + dRow, this->col());
        } else if (dCol != 0 && !temple->isWall(this->row(), this->col() + dCol)) {
            this->moveTo(this->row(), this->col() + dCol);
        } else {
            // If neither movement is possible, do nothing
            this->doNothing();
        }
    }
}
void SnakeWoman::attack(){
    
}
bool SnakeWoman::doNothing(){
    return true; // base code for rn pls change
}
bool SnakeWoman::isDead(){
    return true;
}
void SnakeWoman::dropItem(){
    
}
// dragon implementations
Dragon::Dragon(int row, int col)
    : Monster(row, col, randInt(20, 25), 25, 4, 4, 4, 0, new longSword(row,col), 'D') {}
void Dragon::doTurn(int playerRow, int playerCol, Temple* temple){
    
}
void Dragon::attack(){
    
}
bool Dragon::doNothing(){
    return true; // base code for rn pls change
}
bool Dragon::isDead(){
    return true;
}
void Dragon::dropItem(){
    
}
// goblin implementations
Goblin::Goblin(int row, int col)
    : Monster(row, col, randInt(15, 20), 20, 2, 3, 3, 0, new magicFang(row,col), 'G') {}
void Goblin::doTurn(int playerRow, int playerCol, Temple* temple){
    
}
void Goblin::attack(){
    
}
bool Goblin::doNothing(){
    return true; // base code for rn pls change
}
bool Goblin::isDead(){
    return true;
}
void Goblin::dropItem(){
    
}
