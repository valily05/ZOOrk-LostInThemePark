//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"
#include <algorithm>
#include <utility>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
std::cout << "========================================================\n";
std::cout << "             LOST IN THE THEME PARK\n";
std::cout << "========================================================\n";
std::cout << "A sudden power outage has trapped you inside a theme park.\n";
std::cout << "Collect 3 batteries and 2 fuses to restore power.\n";
std::cout << "Find the exit before hunger overwhelms you.\n";
std::cout << "Hint: Food can be found in the Food Court.\n";
std::cout << "Eating food restores your hunger to 10/10.\n";
std::cout << "Use it wisely.\n";
std::cout << "Type HELP for available commands.\n";
std::cout << "========================================================\n\n";
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);
        
std::vector<std::string> words = tokenizeString(input);

if (words.empty()) {
    continue;
}

std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());
if (command == "go") {
    handleGoCommand(arguments);
}
else if ((command == "look") || (command == "inspect")) {
    handleLookCommand(arguments);
}
else if ((command == "take") || (command == "get")) {
    handleTakeCommand(arguments);
}else if (command == "drop") {
    handleDropCommand(arguments);
}
else if (command == "inventory") {
    player->showInventory();
}
else if (command == "status") {
    handleStatusCommand();
}
else if (command == "map") {
    handleMapCommand();
}
else if (command == "eat") {
    handleEatCommand(arguments);
}
else if (command == "help") {
    std::cout << "\n--------------------------------------------------------\n";
    std::cout << "                 COMMAND JOURNAL                  \n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "  go [direction]  - Move to an another room.\n";
    std::cout << "  look            - Examine your current surroundings.\n";
    std::cout << "  take [item]     - Pick up an object.\n";
    std::cout << "  drop [item]     - Remove an item from your inventory.\n";
    std::cout << "  inventory       - Check your current belongings.\n";
    std::cout << "  status          - View mission progress.\n";
    std::cout << "  hunger          - View your hunger level.\n";
    std::cout << "  map             - Display the theme park map.\n";
    std::cout << "  repair          - Attempt to restore electrical power.\n";
    std::cout << "  quit            - Abandon your journey.\n";
    std::cout << "---------------------------------------------------------\n\n";
}
else if (command == "repair") {
    handleRepairCommand();
}
else if (command == "quit") {
    handleQuitCommand(arguments);
}else if (command == "hunger") {
    std::cout << "Current Hunger: "
              << player->getHunger()
              << "/10\n";
}
else {
    std::cout << "I don't understand that command.\n";
}
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {

    if (arguments.empty()) {
        std::cout << "Go where?\n";
        return;
    }

    std::string direction;

    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    }
    else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    }
    else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    }
    else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    }
    else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    }
    else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    }
    else {
        direction = arguments[0];
    }
Room* currentRoom = player->getCurrentRoom();
auto passage = currentRoom->getPassage(direction);

player->setCurrentRoom(passage->getTo());
passage->enter();

// Only lose hunger if player actually moved
if (player->getCurrentRoom() != currentRoom) {
player->decreaseHunger();

if (player->getHunger() == 3) {
    std::cout << "\nHunger: 3/10\n";
    std::cout << "Your stomach growls loudly...\n";
}

if (player->getHunger() == 2) {
    std::cout << "\nHunger: 2/10\n";
    std::cout << "You are getting very hungry.\n";
}

if (player->getHunger() == 1) {
    std::cout << "\nHunger: 1/10\n";
    std::cout << "You feel weak from hunger.\n";
}

    if (player->getHunger() <= 0) {

        std::cout << "\n";
        std::cout << "========================================================\n";
        std::cout << "                      GAME OVER\n";
        std::cout << "========================================================\n";
        std::cout << "You collapse from hunger and exhaustion.\n\n";
        std::cout << "The theme park remains trapped in darkness.\n";
        std::cout << "========================================================\n";

        gameOver = true;
    }
}

     
}
void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {

    Room* currentRoom = player->getCurrentRoom();

    if (arguments.empty()) {

        std::cout << currentRoom->getDescription() << std::endl;

        std::vector<Item*> items = currentRoom->getItems();

        for (auto item : items) {

            std::cout
                << "\nItem here: "
                << item->getName()
                << " - "
                << item->getDescription()
                << "\n";
        }

        return;
    }

    std::cout << "You don't see that here." << std::endl;
}
void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {

    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }

    Room* room = player->getCurrentRoom();

    std::string itemName;

for (const auto& arg : arguments) {
    itemName += arg;
}

Item* item = room->removeItem(itemName);

    if (item == nullptr) {
        std::cout << "That item is not here.\n";
        return;
    }

    player->addItem(item);

    std::cout << "Taken.\n";
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {

    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }

    std::string itemName;

for (const auto& arg : arguments) {
    itemName += arg;
}

Item* item = player->removeItem(itemName);

    if (item == nullptr) {
        std::cout << "You don't have that item.\n";
        return;
    }

    player->getCurrentRoom()->addItem(item);

    std::cout << "Dropped.\n";
}

void ZOOrkEngine::handleEatCommand(std::vector<std::string> arguments) {

    if (arguments.empty()) {
        std::cout << "Eat what?\n";
        return;
    }

    std::string itemName;

    for (const auto& arg : arguments) {
        itemName += arg;
    }

    Item* food = player->removeItem(itemName);

    if (food == nullptr) {
        std::cout << "You don't have that item.\n";
        return;
    }
if (itemName == "burger") {

    if (player->getHunger() >= 10) {

        player->addItem(food);

        std::cout << "You are already full.\n";

        return;
    }

    player->restoreHunger(10);

    std::cout << "You eat the burger.\n";
    std::cout << "Hunger restored!\n";
}else if (itemName == "pizza") {

    if (player->getHunger() >= 10) {

        player->addItem(food);

        std::cout << "You are already full.\n";

        return;
    }

    player->restoreHunger(10);

    std::cout << "You eat the pizza.\n";
    std::cout << "Hunger restored!\n";
}
    else {

        player->addItem(food);

        std::cout << "You can't eat that!\n";
        return;
    }

    delete food;

    std::cout << "Current Hunger: "
              << player->getHunger()
              << "/10\n";
}
void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}
void ZOOrkEngine::handleRepairCommand() {

    if (
        player->getItem("battery1") &&
        player->getItem("battery2") &&
        player->getItem("battery3") &&
        player->getItem("fuse1") &&
        player->getItem("fuse2")
    ) {
        std::cout << "\nPower restored!\n";
        std::cout << "The Exit Gate has been unlocked!\n";
        std::cout << "You escaped the theme park!\n";

        gameOver = true;
    }
    else {
        std::cout << "You still need more batteries and fuses.\n";
    }
    
}void ZOOrkEngine::handleStatusCommand() {
    int progress = 0;

    bool battery1 = player->getItem("battery1");
    bool battery2 = player->getItem("battery2");
    bool battery3 = player->getItem("battery3");
    bool fuse1 = player->getItem("fuse1");
    bool fuse2 = player->getItem("fuse2");

    if (battery1) progress++;
    if (battery2) progress++;
    if (battery3) progress++;
    if (fuse1) progress++;
    if (fuse2) progress++;

    int percent = progress * 20;

    std::string bar = "[";

    for (int i = 0; i < progress; i++) {
        bar += "====";
    }

    if (progress < 5) {
        bar += "";
        for (int i = progress; i < 5; i++) {
            bar += "....";
        }
    }

    bar += "]";

    std::cout << "\n--------------------------------------------------------\n";
    std::cout << "                     MISSION STATUS                     \n";
    std::cout << "--------------------------------------------------------\n";

    std::cout << "  Battery 1 : "
              << (battery1 ? "FOUND" : "[MISSING]") << "\n";

    std::cout << "  Battery 2 : "
              << (battery2 ? "FOUND" : "[MISSING]") << "\n";

    std::cout << "  Battery 3 : "
              << (battery3 ? "FOUND" : "[MISSING]") << "\n\n";

    std::cout << "  Fuse 1    : "
              << (fuse1 ? "FOUND" : "[MISSING]") << "\n";

    std::cout << "  Fuse 2    : "
              << (fuse2 ? "FOUND" : "[MISSING]") << "\n";

    std::cout << "--------------------------------------------------------\n";

    std::cout << "  Progress  : "
              << bar
              << " "
              << percent
              << "% ("
              << progress
              << " / 5)\n";

    std::cout << "--------------------------------------------------------\n\n";
}

void ZOOrkEngine::handleMapCommand() {
std::cout << "\n";
std::cout << "========================================================\n";
std::cout << "                    THEME PARK MAP\n";
std::cout << "========================================================\n\n";

std::cout << "                         Water Ride ---- Roller Coaster\n";
std::cout << "                              |                  |\n";
std::cout << "                         Ferris Wheel      Souvenir Shop\n";
std::cout << "                              |                  |\n";
std::cout << " Haunted House ---- Entrance ---- Arcade ---- Food Court\n";
std::cout << "       |                                        |\n";
std::cout << "       +----------------------------------------+\n";
std::cout << "                                                |\n";
std::cout << "                                          Maintenance\n";
std::cout << "                                                |\n";
std::cout << "                                          Control Center\n";
std::cout << "                                                \n";
std::cout << "                                            Exit Gate\n\n";

std::cout << "========================================================\n";
}
std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
