#include "Game.h"

Game::Game(int maxPlayer) : maxPlayer(maxPlayer), numPlayers(0) {
  players = new Player*[maxPlayer]();
}
Game::~Game() {
    for (int i = 0; i < numPlayers; i++) {
        delete players[i];
    }
    delete[] players;
}
Game::Game(const Game& game) {
    maxPlayer = game.maxPlayer;
    players = new Player*[maxPlayer]();
    for (int i = 0; i < game.numPlayers; i++) {
        players[i] = new Player(*game.players[i]);
    }
    numPlayers = game.numPlayers;
}
GameStatus Game::addPlayer(const char* playerName, const char* weaponName, 
    Target target, int hitStrength) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            return NAME_ALREADY_EXISTS;
        }
    }
    if (numPlayers == maxPlayer) {
        return GAME_FULL;
    }
    players[numPlayers] = new Player(playerName, Weapon(weaponName, target, 
        hitStrength));
    int i = numPlayers;
    while (i > 0) {
        Player& newPlayer = *(players[i]);
        Player& oldPlayer = *(players[i-1]);
        if (newPlayer < oldPlayer) {
            Player* temp = players[i];
            players[i] = players[i-1];
            players[i-1] = temp;
        }
        i--;
    }
    numPlayers++;
    return SUCCESS;
}
GameStatus Game::nextLevel(const char* playerName) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            players[i]->nextLevel();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}
GameStatus Game::makeStep(const char* playerName) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            players[i]->makeStep();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}
GameStatus Game::addLife(const char* playerName) {
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            players[i]->addLife();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}
GameStatus Game::addStrength(const char* playerName, int strengthToAdd) {
    if (strengthToAdd < 0) {
        return INVALID_PARAM;
    }
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName)) {
            players[i]->addStrength(strengthToAdd);
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}
bool Game::removeAllPlayersWithWeakWeapon(int weaponStrength) {
    int newNumPlayers = 0;
    Player** newPlayers = new Player*[maxPlayer]();
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->weaponIsWeak(weaponStrength)) {
            delete players[i];
            continue;
        }
        newPlayers[newNumPlayers++] = players[i];
    }
    delete[] players;
    players = newPlayers;
    int temp = numPlayers;
    numPlayers = newNumPlayers;
    return numPlayers != temp;
}
void Game::deletePlayer(int playerNum) {
    int newNumPlayers = 0;
    Player** newPlayers = new Player*[maxPlayer]();
    for (int i = 0; i < numPlayers; i++) {
        if (i != playerNum) {
            newPlayers[newNumPlayers++] = players[i];
        } else {
            delete players[i];
        }
    }
    delete[] players;
    numPlayers = newNumPlayers;
    players = newPlayers;
}
GameStatus Game::fight(const char* playerName1, const char* playerName2) {
    int playerCount = 0;
    int playerIndices[2];
    for (int i = 0; i < numPlayers; i++) {
        if (players[i]->isPlayer(playerName1) || 
            players[i]->isPlayer(playerName2)) {
            playerIndices[playerCount++] = i;
        }
    }
    if (playerCount != 2) {
        return NAME_DOES_NOT_EXIST;
    }
    if (!players[playerIndices[0]]->fight(*(players[playerIndices[1]]))) {
        return FIGHT_FAILED;
    }
    for (int i = 0; i < 2; ++i) {
        if (!players[playerIndices[i]]->isAlive()) {
            deletePlayer(playerIndices[i]);
        }
    }
    return SUCCESS;
}
std::ostream& operator<<(std::ostream& os, Game& game) {
    for (int i = 0; i < game.numPlayers; ++i) {
        os << "player " << i << ": " << *game.players[i] << "," << std::endl;
    }
    return os;
}
Game& Game::operator=(const Game& game) {
    if (this != &game) {
        for (int i = 0; i < numPlayers; i++) {
            delete players[i];
        }
        delete[] players;
        maxPlayer = game.maxPlayer;
        players = new Player*[maxPlayer]();
        for (int i = 0; i < game.numPlayers; i++) {
            players[i] = new Player(*game.players[i]);
        }
        numPlayers = game.numPlayers;
    }
    return *this;
}
