//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"

#include <utility>

Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c)
        : Location(n, d, std::move(c)) {
}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.find(direction) != passageMap.end()) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.find(direction) != passageMap.end()) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

// ==========================
// Inventory Functions
// ==========================

void Room::addItem(Item* item) {
    items.push_back(item);
}

Item* Room::getItem(const std::string& name) {
    for (auto item : items) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

Item* Room::removeItem(const std::string& name) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == name) {
            Item* temp = *it;
            items.erase(it);
            return temp;
        }
    }
    return nullptr;
}

std::vector<Item*> Room::getItems() {
    return items;
}