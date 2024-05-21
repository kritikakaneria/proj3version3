// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.
class Temple;
class Player;
class GameObject;
class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
    void nextLevel();
private:
    Temple* m_temple;
    Player* m_player;
};

#endif // GAME_INCLUDED

