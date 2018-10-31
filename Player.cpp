#include "Player.h"

Player::Player(const char* name, const Weapon& weapon): 
weapon(*(new Weapon(weapon))) {
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
    life = 1;
    level = 1;
    strength = 1;
    location = 0;
}
Player::Player(const Player& player): weapon(*(new Weapon(player.weapon))) {
    this->name = new char[strlen(player.name)+1];
    strcpy(this->name, player.name);
    life = player.life;
    level = player.level;
    strength = player.strength;
    location = player.location;
}
Player::~Player() {
    delete[] name;
    delete &weapon;
}
ostream& operator<<(ostream& os, const Player& player) {
    return os << "{player name: " << player.name << ", weapon: " << 
    player.weapon << "}";
}
void Player::nextLevel() {
    level++;
}
bool Player::isPlayer(const char* playerName) const {
    return (strcmp(name, playerName) == 0);
}
void Player::makeStep() {
    location++;
}
void Player::addLife() {
    life++;
}
void Player::addStrength(int strengthToAdd) {
    strength += strengthToAdd;
}
bool Player::isAlive() const {
    return (life > 0) && (level > 0) && (strength > 0);
}
bool Player::weaponIsWeak(int weaponMinStrength) const {
    return weapon.getValue() < weaponMinStrength;
}
bool operator<(const Player& player1, const Player& player2) {
    return strcmp(player1.name, player2.name) < 0;
}
bool operator>(const Player& player1, const Player& player2) {
    return strcmp(player1.name, player2.name) > 0;
}
bool Player::fight(Player& player) {
    if ((this->location != player.location) || (this->weapon == 
        player.weapon)) {
        return false;
    }
    Player& beater = this->weapon > player.weapon ? *this : player;
    Player& beatee = this->weapon < player.weapon ? *this : player;
    int hitStrength = beater.weapon.getHitStrength();
    Target target = beater.weapon.getTarget();
    switch (target) {
    case LEVEL:
        beatee.level -= hitStrength;
        if (beatee.level < 0) {
            beatee.level = 0;
        }
        break;
    case STRENGTH:
        beatee.strength -= hitStrength;
        if (beatee.strength < 0) {
            beatee.strength = 0;
        }
        break;
    case LIFE:
        beatee.life -= hitStrength;
        if (beatee.life < 0) {
            beatee.life = 0;
        }
        break;
    }
    return true;
}
Player& Player::operator=(const Player& player) {
    if (this != &player) {
        char* oldName = name;
        name = new char[strlen(player.name)+1];
        strcpy(name, player.name);
        delete[] oldName;
        this->weapon = Weapon(player.weapon); // Will make a copy
        this->life = player.life;
        this->level = player.level;
        this->strength = player.strength;
        this->location = player.location;
    }
    return *this;
}