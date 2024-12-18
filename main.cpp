include <iostream>
#include <string>
#include "player.hpp"
#include "inventory.hpp"
#include "combat.hpp"
#include "save.hpp"

const int TOTAL_ITEMS = 10; // Total items available in the game

// Item structure representing an item in the game
struct Item {
    std::string name;
    std::string description;
    int trait; // Trait associated with the item (e.g., +5 magic)
};

// Function to choose player type and create a player
Player createPlayer() {
    std::string playerName;
    int playerType;

    std::cout << "Choose your player type:\n";
    std::cout << "1. Wizard (Magic: 10, Strength: 5)\n";
    std::cout << "2. Knight (Magic: 0, Strength: 15)\n";
    std::cout << "Enter the number of your choice: ";
    std::cin >> playerType;
    std::cin.ignore();

    std::cout << "Enter your player's name: ";
    std::getline(std::cin, playerName);

    if (playerType == 1) {
        return Player(playerName, 10, 5);
    } else {
        return Player(playerName, 0, 15);
    }
}

// Function to create items
void createItems(std::vector<Item>& items) {
    items = {
        {"Wand", "A magical wand that boosts your magic.", 5},
        {"Sword", "A sharp sword for close combat.", 3},
        {"Shield", "A sturdy shield for defense.", 2},
        {"Potion", "Restores health.", 0},
        {"Ring", "A ring that enhances magic.", 4},
        {"Armor", "Protective armor that increases strength.", 2},
        {"Staff", "A long staff for casting spells.", 6},
        {"Bow", "A bow for ranged attacks.", 2},
        {"Gem", "A mystical gem that holds ancient power.", 7},
        {"Amulet", "An amulet that protects against dark magic.", 5}
    };
}

int main() {
    // Initialize player and items
    Player player = createPlayer();
    std::vector<Item> items;
    createItems(items);
    std::string command;

    std::cout << "Welcome, " << player.getName() << "!\n";
    player.showStatus();

    // Game loop
    while (true) {
        std::cout << "\nEnter a command (add item, inventory, status, save, load, quit): ";
        std::getline(std::cin, command);

        if (command == "add item") {
            std::cout << "Choose an item to add (1-" << TOTAL_ITEMS << "):\n";
            for (size_t i = 0; i < items.size(); ++i) {
                std::cout << i + 1 << ". " << items[i].name << ": " << items[i].description << "\n";
            }

            int itemChoice;
            std::cin >> itemChoice;
            std::cin.ignore();

            if (itemChoice > 0 && itemChoice <= TOTAL_ITEMS) {
                player.getInventory().addItem(items[itemChoice - 1].name);
            } else {
                std::cout << "Invalid choice. Try again.\n";
            }
        } else if (command == "inventory") {
            player.getInventory().display();
        } else if (command == "status") {
            player.showStatus();
        } else if (command == "save") {
            SaveSystem::savePlayerState(player, "savefile.json");
        } else if (command == "load") {
            SaveSystem::loadPlayerState(player, "savefile.json");
        } else if (command == "quit") {
            std::cout << "Goodbye, " << player.getName() << "!\n";
            break;
        } else {
            std::cout << "Unknown command. Try again.\n";
        }
    }

    return 0;
}
