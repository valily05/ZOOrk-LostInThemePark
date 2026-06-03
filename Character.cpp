#include "Character.h"
#include <iostream>

Character::Character(const std::string &n, const std::string &d)
        : GameObject(n, d) {
}

void Character::addItem(Item* item) {
    inventory.push_back(item);
}

Item* Character::getItem(const std::string& name) {
    for (auto item : inventory) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

Item* Character::removeItem(const std::string& name) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == name) {
            Item* temp = *it;
            inventory.erase(it);
            return temp;
        }
    }
    return nullptr;
}

void Character::showInventory() {
    if (inventory.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    std::cout << "Inventory:\n";

    for (auto item : inventory) {
        std::cout << "- " << item->getName() << "\n";
    }
}