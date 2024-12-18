#include <iostream> // this
#include <string>
#include "player.h"
#include "inventory.h"
#include "combat.h"
#include "save.h"


const int MAX_ITEMS = 10; // Maximum number of items in the inventory
const int TOTAL_ITEMS = 10; // Total items available in the game

// Item structure representing an item in the game
struct Item {
    std::string name;
    std::string description;
    int trait; // Trait associated with the item (e.g., +5 magic)
};

// Player class representing the player profile
class Player {
public:
    std::string name;
    int magic;
    int strength;
    Item inventory[MAX_ITEMS]; // Array to store items
    int itemCount = 0; // Current number of items in inventory

    Player(std::string playerName, int playerMagic, int playerStrength)
        : name(playerName), magic(playerMagic), strength(playerStrength) {}

    void addItem(const Item& item) {
        if (itemCount < MAX_ITEMS) {
            inventory[itemCount++] = item;
            std::cout << item.name << " has been added to your inventory!\n";
        } else {
            std::cout << "Your inventory is full!\n";
        }
    }

    void showInventory() {
        if (itemCount == 0) {
            std::cout << "Your inventory is empty.\n";
            return;
        }
        std::cout << "Inventory:\n";
        for (int i = 0; i < itemCount; ++i) {
            std::cout << "- " << inventory[i].name << ": " << inventory[i].description << " (Trait: +" << inventory[i].trait << ")\n";
        }
    }

    void showStatus() {
        std::cout << "Player: " << name << "\n";
        std::cout << "Magic: " << magic << "\n";
        std::cout << "Strength: " << strength << "\n";
    }
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
void createItems(Item items[]) {
    items[0] = {"Wand", "A magical wand that boosts your magic.", 5};
    items[1] = {"Sword", "A sharp sword for close combat.", 3};
    items[2] = {"Shield", "A sturdy shield for defense.", 2};
    items[3] = {"Potion", "Restores health.", 0};
    items[4] = {"Ring", "A ring that enhances magic.", 4};
    items[5] = {"Armor", "Protective armor that increases strength.", 2};
    items[6] = {"Staff", "A long staff for casting spells.", 6};
    items[7] = {"Bow", "A bow for ranged attacks.", 2};
    items[8] = {"Gem", "A mystical gem that holds ancient power.", 7};
    items[9] = {"Amulet", "An amulet that protects against dark magic.", 5};
}

int main() {
    Player player = createPlayer();
    Item items[TOTAL_ITEMS];
    createItems(items);
    std::string command;

    std::cout << "Welcome, " << player.name << "!\n";
    player.showStatus();

    // Game loop
    while (true) {
        std::cout << "\nEnter a command (add item, inventory, status, quit): ";
        std::getline(std::cin, command);

        if (command == "add item") {
            std::cout << "Choose an item to add (1-10):\n";
            for (int i = 0; i < TOTAL_ITEMS; ++i) {
                std::cout << i + 1 << ". " << items[i].name << ": " << items[i].description << "\n";
            }
            int itemChoice;
            std::cin >> itemChoice;
            std::cin.ignore();

            if (itemChoice > 0 && itemChoice <= TOTAL_ITEMS) {
                player.addItem(items[itemChoice - 1]);
            } else {
                std::cout << "Invalid choice. Try again.\n";
            }
        } else if (command == "inventory") {
            player.showInventory();
        } else if (command == "status") {
            player.showStatus();
        } else if (command == "quit") {
            std::cout << "Goodbye, " << player.name << "!\n";
            break;
        } else {
            std::cout << "Unknown command. Try again.\n";
        }
    }

    return 0;
}
