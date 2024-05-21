//
//  GameObject.hpp
//  project3
//
//  Created by User on 5/12/24.
//

#ifndef GameObject_h
#define GameObject_h

#include <stdio.h>
#include <string>
using namespace std;
class Player;
class GameObject
{
public:
    GameObject(const string& name, char icon, const std::string& action): m_name(name), m_icon(icon), m_onMap(false), m_row(-1), m_col(-1), m_action(action) {} // every object has a name)
    GameObject(int row, int col, const string& name, char icon, const std::string& action): m_name(name), m_icon(icon), m_onMap(true), m_row(row), m_col(col), m_action(action) {} // every object has a name
    virtual ~GameObject() {};
    bool isOnMap() const { return m_onMap; }
    int row() const { return m_row; }
    int col() const { return m_col; }
    char icon() const { return m_icon; }
    virtual std::string name()  { return m_name; }
    std::string& action()  { return m_action; }

    void placeOnMap(int row, int col) {
            m_row = row;
            m_col = col;
            m_onMap = true;
        }

        void removeFromMap() {
            m_row = -1;
            m_col = -1;
            m_onMap = false;
        }
private:
    string m_name;
    string m_action;
    bool m_onMap; // check if the object is on a map or not
    char m_icon;
    int m_row;
    int m_col;

};
class Weapon : public GameObject
{
public:
    Weapon(const std::string& name, char icon, int dextBonus, int damageAmt, const std::string& action)
        : GameObject(name, icon, action), m_dextBonus(dextBonus), m_damageAmt(damageAmt), m_action(action) {}

    Weapon(int row, int col, const std::string& name, char icon, int dextBonus, int damageAmt, const std::string& action) : GameObject(row, col, name, icon, action), m_dextBonus(dextBonus), m_damageAmt(damageAmt), m_action(action) {}
    int dextBonus() const { return m_dextBonus; }
    int damageAmt() const { return m_damageAmt; }
    std::string action() const { return m_action; }
    virtual ~Weapon(){}
private:
    int m_dextBonus;
    int m_damageAmt;
    string m_action;
    
};
class Mace : public Weapon
{
public:
    Mace() : Weapon("mace", ')', 0, 2, "swings mace at") {}
    Mace(int row, int col) : Weapon(row, col, "mace", ')', 0, 2, "swings mace at") {}
 //   Mace(int row, int col) : Weapon(row, col, "mace", 0, 2, "swings mace at") {}
    
};
class shortSword : public Weapon
{
public:
    shortSword() : Weapon("short sword", ')', 0, 2, "slashes short sword") {}
    shortSword(int row, int col) : Weapon(row, col, "short sword", ')', 0, 2, "slashes short sword") {}
//    shortSword() : Weapon ( "short sword", 0, 2, "slashes short sword") {}
//    shortSword(int row, int col) : Weapon(row, col, "short sword", 0, 2, "slashes short sword at") {}
};
class longSword : public Weapon
{
public:
    longSword() : Weapon("long sword", ')', 2, 4, "swings long sword") {}
    longSword(int row, int col) : Weapon(row, col, "long sword", ')', 2, 4, "swings long sword") {}
  //  longSword(int row, int col) : Weapon(row, col, "long sword", 2, 4, "swings long sword at ") {}
};
class magicAxe : public Weapon
{
public:
    magicAxe() : Weapon("magic axe", ')', 5, 5, "chops magic axe at") {}
    magicAxe(int row, int col) : Weapon(row, col, "magic axe", ')', 5, 5, "chops magic axe at") {}
  //  magicAxe(int row, int col) : Weapon(row, col, "magic axe", 5, 5, "chops magic axe at") {}
};
class magicFang : public Weapon
{
public:
    magicFang() : Weapon("magic fang", ')', 3, 2, "strikes magic fangs at") {}
    magicFang(int row, int col) : Weapon(row, col, "magic fang", ')', 3, 2, "strikes magic fangs at") {}
  //  magicFang(int row, int col) : Weapon(row, col, "magic fang", 0, 2, "strikes magic fangs at") {}
};
class Scroll : public GameObject
{
public:
    Scroll(const std::string& name, char icon, const std::string& action) : GameObject(name, icon, action) {}
    Scroll(int row, int col, const std::string& name, char icon, const std::string& action) : GameObject(row, col, name, icon, action) {}
    std::string name()  {
        return "a scroll called " + GameObject::name();
    }
//    virtual string readScroll(); // pure virtual since u can't perform on just a scroll
//    virtual void performEffect(Player& player);
//    virtual void selfDestruct();
    virtual ~Scroll(){}
private:
    
};
class teleportationScroll : public Scroll
{
public:
    teleportationScroll() : Scroll("scroll of teleportation", '?', "You feel your body wrenched in space and time.") {}
    teleportationScroll(int row, int col) : Scroll(row, col, "scroll of teleportation", '?', "You feel your body wrenched in space and time.") {}
//    teleportationScroll(int row, int col) : Scroll(row, col, "teleportation scroll", "You feel your body wrenched in space and time") {}
//   virtual void performEffect(Player&player){
//    }
};
class enhanceArmorScroll : public Scroll
{
public:
    enhanceArmorScroll() : Scroll("scroll of enhance armor", '?', "Your armor glows blue.") {}
    enhanceArmorScroll(int row, int col) : Scroll(row, col, "scroll of enhance armor", '?', "Your armor glows blue.") {}
//    virtual void performEffect(Player&player){
//     }
};
class enhanceStrengthScroll : public Scroll
{
public:
    enhanceStrengthScroll() : Scroll("scroll of strength", '?', "Your muscles bulge.") {}
    enhanceStrengthScroll(int row, int col) : Scroll(row, col, "scroll of strength", '?', "Your muscles bulge.") {}
//    virtual void performEffect(Player&player){
//     }
};
class enhanceHealthScroll : public Scroll
{
public:
    enhanceHealthScroll() : Scroll("scroll of enhance health", '?', "You feel your heart beating stronger.") {}
    enhanceHealthScroll(int row, int col) : Scroll(row, col, "scroll of enhance health", '?', "You feel your heart beating stronger.") {}
//    virtual void performEffect(Player&player){
//     }
};

class enhanceDexterityScroll : public Scroll
{
public:
    enhanceDexterityScroll() : Scroll("scroll of enhance dexterity", '?',  "You feel like less of a klutz.") {}
    enhanceDexterityScroll(int row, int col) : Scroll(row, col, "scroll of enhance dexterity", '?',  "You feel like less of a klutz."
) {}
//    virtual void performEffect(Player&player){
//     }
};
#endif /* GameObject_h */
