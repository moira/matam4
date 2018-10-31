#ifndef CALLOFDUTY_GAME_H
#define CALLOFDUTY_GAME_H

#include "Player.h"

//Possible errors returned by functions as GameStatus:
//INVALID_PARAM – an invalid parameter was passed to a function,
//NAME_ALREADY_EXISTS – a player already belongs to the game,
//GAME_FULL – the number of the players in the game does not allow to add
//another player,
//FIGHT_FAILED – players cannot fight because they are in different locations
//or their weapon has the same value,
//SUCCESS – no error*/
enum GameStatus {
    INVALID_PARAM,
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    NAME_DOES_NOT_EXIST,
    FIGHT_FAILED,
    SUCCESS
};

//Game fields:
//maxPlayer – the maximal number of players in the game,
//numPlayers – the current number of players in the game,
//players – the array of the pointers to the players currently in game
class Game {
    int maxPlayer;
    int numPlayers;
    Player** players;
/*Given a player's number, deletes the player*/
    void deletePlayer(int playerNum);
public:
//Initializes a game with a given maximal number of players
    explicit Game(int maxPlayer);
//Initializes a game by copying it from another game
    Game(const Game& game);
//Destroys the game and all its contents
    ~Game();
//Adds a player to the game given the player's name and the characteristics of
//their weapon: name, target, strength
    GameStatus addPlayer(const char* playerName, const char* weaponName, 
        Target target, int hitStrength);
//Promotes the player with the given name to the next level
    GameStatus nextLevel(const char* playerName);
//Promotes the player with the given name to the next location
    GameStatus makeStep(const char* playerName);
//Adds life to the given player
    GameStatus addLife(const char* playerName);
//Given a player and a strength to add as an integer, adds the strength to
//the player
    GameStatus addStrength(const char* playerName, int strengthToAdd);
//Removes from the game all players whose weapon's strength is less than
//the passed integer; removes true if at least one player was removed and
//false otherwise
    bool removeAllPlayersWithWeakWeapon(int weaponStrength);
//Makes two players fight if they are in the same location, adjusts the game
//according to the outcome
    GameStatus fight(const char* playerName1, const char* playerName2);
//Prints the players in alphabetic order
    friend ostream& operator<<(ostream& os, Game& game);
    Game& operator=(const Game& game);
};

#endif //CALLOFDUTY_GAME_H
