//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room* room) {
    currentRoom = room;
}

Room* Player::getCurrentRoom() const {
    return currentRoom;
}
void Player::decreaseHunger() {
    hunger--;
}

int Player::getHunger() const {
    return hunger;
}
void Player::restoreHunger(int amount) {

    hunger += amount;

    if (hunger > 10) {
        hunger = 10;
    }
}