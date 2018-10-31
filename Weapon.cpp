#include "Weapon.h"

Weapon::Weapon(const char* name, Target target, int hitStrength) {
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
    this->target = target;
    this->hitStrength = hitStrength;
}
Weapon::Weapon(const Weapon& weapon) {
    name = new char[strlen(weapon.name)+1];
    strcpy(name, weapon.name);
    target = weapon.target;
    hitStrength = weapon.hitStrength;
}
Weapon::~Weapon() {
    delete[] name;
}
Target Weapon::getTarget() const {
    return target;
}
int Weapon::getHitStrength() const {
    return hitStrength;
}
int Weapon::getValue() const {
    return hitStrength * (target+1);
}
bool operator== (const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() == weapon2.getValue();
}
bool operator!= (const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() != weapon2.getValue();
}
bool operator> (const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() > weapon2.getValue();
}
bool operator< (const Weapon& weapon1, const Weapon& weapon2) {
    return weapon1.getValue() < weapon2.getValue();
}
ostream& operator<<(ostream& os, const Weapon& weapon) {
    return os << "{weapon name: " << weapon.name << ", weapon value:" << 
    weapon.getValue() << "}";
}
Weapon& Weapon::operator=(const Weapon& weapon) {
    if (this != &weapon) {
        char* oldName = name;
        name = new char[strlen(weapon.name)+1];
        strcpy(name, weapon.name);
        delete[] oldName;
        target = weapon.target;
        hitStrength = weapon.hitStrength;
    }
    return *this;
}
