# ZOOrk-LostInThemePark

## Overview

Lost in the Theme Park is a text-based adventure game developed in C++ using object-oriented programming principles.

The player is trapped inside a theme park after a sudden power outage. To escape, the player must explore different locations, collect batteries and fuses, restore power, and survive the hunger system.

---

## Objective

Collect:

* 3 Batteries
* 2 Fuses

Once all required components have been collected, use the `repair` command to restore power and escape the theme park.

Be careful — hunger decreases as you explore. If hunger reaches zero, the game ends.

---

## Features

* Room Navigation System
* Inventory Management
* Item Collection and Dropping
* Mission Progress Tracker
* Hunger Survival System
* Food Items (Burger and Pizza)
* Theme Park Map
* Win and Lose Conditions
* Command Help Menu

---

## Commands

| Command        | Description                |
| -------------- | -------------------------- |
| go [direction] | Move between rooms         |
| look           | Examine the current room   |
| take [item]    | Pick up an item            |
| drop [item]    | Drop an item               |
| inventory      | View inventory             |
| status         | View mission progress      |
| hunger         | Check hunger level         |
| eat [food]     | Consume food               |
| map            | Display the theme park map |
| repair         | Restore power              |
| help           | Show available commands    |
| quit           | Exit the game              |

---

## Winning the Game

Collect all required batteries and fuses, then use:

repair

to restore power and escape the theme park.

---

## Losing the Game

The player loses if hunger reaches 0.

---


Valencia Hartono
