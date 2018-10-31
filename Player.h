#ifndef CALLOFDUTY_PLAYER_H
#define CALLOFDUTY_PLAYER_H

#include "Weapon.h"

//Player object fields: name – the name of the player, level – the player's
//level, life – the number of player's lives, strength – the player's current
//strength, location – the current location of the player
class Player {
    char* name;
    int level;
    int life;
    int strength;
    Weapon &weapon;
    int location;
public:
//Player constructor takes the player's name and the name of their weapon
    explicit Player(const char* name, const Weapon& weapon);
//Copy constructor for the player class
    Player(const Player& player);
//When the player is destroyed, their weapon is destroyed too
    ~Player();
//Prints the player's name and their weapon's name
    friend ostream& operator<<(ostream& os, const Player& player);
//Assigns a player to a variable
    Player& operator=(const Player& player);
//Promotes the player to the next level
    void nextLevel();
//Checks if the given string is the player's name
    bool isPlayer(const char* playerName) const;
//Moves the player to the next location
    void makeStep();
//Increments the player's number of lives
    void addLife();
//Increments the player's strength by the given integer
    void addStrength(int strengthToAdd);
//Returns true if the player is in game (life, strength, and level are positive) 
//and false otherwise
    bool isAlive() const;
//Returns true is the player's weapon's strength is less then the given integer
    bool weaponIsWeak(int weaponMinStrength) const;
//Compare two players by name lexicographically
    friend bool operator<(const Player& player1, const Player& player2);
    friend bool operator>(const Player& player1, const Player& player2);
//Returns true if the player can fight with the player that is passed as
//argument and false otherwise (if they are in different location or have
//weapon of the same value)
    bool fight(Player& player);
};

#endif //CALLOFDUTY_PLAYER_H
