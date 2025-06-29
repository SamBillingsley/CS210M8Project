#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

class ItemTracker {
private:
    std::map<std::string, int> itemFrequencies;
    std::string inputFileName;

public:
    // Constructor
    ItemTracker(const std::string& fileName) {
        inputFileName = fileName;
        LoadItems();
        WriteFrequencyToFile("frequency.dat");
    }

    // Load items from file and count them
    void LoadItems() {
        std::ifstream inFile(inputFileName);
        std::string item;
        while (inFile >> item) {
            itemFrequencies[item]++;
        }
        inFile.close();
    }

    // Return frequency of a specific item
    int GetItemFrequency(const std::string& item) {
        if (itemFrequencies.find(item) != itemFrequencies.end()) {
            return itemFrequencies[item];
        } else {
            return 0;
        }
    }

    // Print all item frequencies
    void PrintAllFrequencies() {
        for (const auto& pair : itemFrequencies) {
            std::cout << std::left << std::setw(12) << pair.first << " " << pair.second << std::endl;
        }
    }

    // Print histogram
    void PrintHistogram() {
        for (const auto& pair : itemFrequencies) {
            std::cout << std::left << std::setw(12) << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }

    // Save frequencies to a file
    void WriteFrequencyToFile(const std::string& outputFileName) {
        std::ofstream outFile(outputFileName);
        for (const auto& pair : itemFrequencies) {
            outFile << pair.first << " " << pair.second << std::endl;
        }
        outFile.close();
    }
};

void DisplayMenu() {
    std::cout << "\n===== Corner Grocer Menu =====" << std::endl;
    std::cout << "1. Search for item frequency" << std::endl;
    std::cout << "2. Print all item frequencies" << std::endl;
    std::cout << "3. Print histogram of items" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Choose an option: ";
}

int main() {
    ItemTracker tracker("p3.txt");
    int choice;
    std::string item;

    do {
        DisplayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter item to search: ";
                std::cin >> item;
                std::cout << item << " was purchased " << tracker.GetItemFrequency(item) << " times.\n";
                break;
            case 2:
                tracker.PrintAllFrequencies();
                break;
            case 3:
                tracker.PrintHistogram();
                break;
            case 4:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter 1-4." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
