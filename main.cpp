#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

#include <memory>

int main() {

    auto entrance = std::make_shared<Room>(
        "entrance-plaza",
        "You are standing in the Entrance Plaza. The theme park is dark and silent. "
        "The rides have stopped and the exit gates are locked."
    );

    auto ferrisWheel = std::make_shared<Room>(
        "ferris-wheel",
        "The giant Ferris Wheel towers above you. Its cabins sway gently in the wind."
    );

    auto hauntedHouse = std::make_shared<Room>(
        "haunted-house",
        "An abandoned haunted house creaks in the darkness. Strange sounds echo inside."
    );

    auto arcade = std::make_shared<Room>(
        "arcade",
        "Rows of arcade machines flicker weakly. Most have lost power."
    );

    auto foodCourt = std::make_shared<Room>(
        "food-court",
        "Empty tables and chairs fill the food court. A few lights still glow."
    );

    auto waterRide = std::make_shared<Room>(
        "water-ride",
        "The water ride sits motionless. The water is completely still."
    );

    auto rollerCoaster = std::make_shared<Room>(
        "roller-coaster-station",
        "The roller coaster station is deserted. The tracks disappear into the darkness."
    );

    auto maintenance = std::make_shared<Room>(
        "maintenance-room",
        "Tools, spare parts, and electrical equipment are scattered everywhere."
    );

    auto controlCenter = std::make_shared<Room>(
        "control-center",
        "This room controls the entire theme park. The main power system is offline."
    );

    auto souvenirShop = std::make_shared<Room>(
        "souvenir-shop",
        "Dust-covered souvenirs line the shelves."
    );

    auto exitGate = std::make_shared<Room>(
        "exit-gate",
        "A massive locked gate blocks your escape from the theme park."
    );

    Item* battery1 = new Item(
    "battery1",
    "A rechargeable battery."
);

Item* battery2 = new Item(
    "battery2",
    "A rechargeable battery."
);

Item* battery3 = new Item(
    "battery3",
    "A rechargeable battery."
);

Item* fuse1 = new Item(
    "fuse1",
    "An electrical fuse."
);

Item* fuse2 = new Item(
    "fuse2",
    "An electrical fuse."
);
Item* burger = new Item(
    "burger",
    "A juicy cheeseburger from the Food Court."
);

Item* pizza = new Item(
    "pizza",
    "A large slice of pepperoni pizza."
);

    // Main paths

    Passage::createBasicPassage(
        entrance.get(),
        ferrisWheel.get(),
        "north",
        true
    );

    Passage::createBasicPassage(
        entrance.get(),
        arcade.get(),
        "east",
        true
    );

    Passage::createBasicPassage(
        entrance.get(),
        hauntedHouse.get(),
        "west",
        true
    );

    Passage::createBasicPassage(
        arcade.get(),
        foodCourt.get(),
        "east",
        true
    );

    Passage::createBasicPassage(
        foodCourt.get(),
        maintenance.get(),
        "north",
        true
    );

    Passage::createBasicPassage(
        maintenance.get(),
        controlCenter.get(),
        "north",
        true
    );

    Passage::createBasicPassage(
        ferrisWheel.get(),
        waterRide.get(),
        "north",
        true
    );

    Passage::createBasicPassage(
        waterRide.get(),
        rollerCoaster.get(),
        "east",
        true
    );

    Passage::createBasicPassage(
        rollerCoaster.get(),
        souvenirShop.get(),
        "south",
        true
    );

    Passage::createBasicPassage(
        souvenirShop.get(),
        exitGate.get(),
        "south",
        true
    );

    // Extra connections

    Passage::createBasicPassage(
        hauntedHouse.get(),
        foodCourt.get(),
        "north",
        true
    );

    Passage::createBasicPassage(
        arcade.get(),
        ferrisWheel.get(),
        "north",
        true
    );
ferrisWheel->addItem(battery1);

arcade->addItem(battery2);

hauntedHouse->addItem(battery3);

maintenance->addItem(fuse1);

rollerCoaster->addItem(fuse2);
foodCourt->addItem(burger);
foodCourt->addItem(pizza);
    ZOOrkEngine zoork(entrance);

    zoork.run();

    return 0;
}