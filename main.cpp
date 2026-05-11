#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "Exam.h"
#include "GradedItem.h"
#include "Homework.h"
#include "Quiz.h"
#include "greeting.h"

/*
 * Grade Calculator (OOP Edition) — Final Project
 * Author: Frank Nava
 * Course: COSC 1437, Spring 2026
 *
 * Concepts Demonstrated (Chapters 11-18 + Sprints 19-22)
 * ------------------------------------------------------
 * Ch 11 - Foundation from COSC 1436: std::vector, control flow, modular code
 * Ch 12 - <algorithm>: std::min_element, std::max_element, std::sort
 * Ch 13 - <fstream> file I/O: saveGrades() / loadGrades() to "grades.txt"
 * Ch 14 - User-defined class: GradedItem with private fields + getters/setters
 * Ch 15 - Object refinement: parameterized constructors, getPercentage(), encapsulation
 * Ch 16 - Menu-driven UI: switch statement, <iomanip> formatting, helper functions
 * Ch 17 - Inheritance + polymorphism: Homework / Quiz / Exam derive from GradedItem
 * Ch 18 - Smart pointers: std::vector<std::unique_ptr<GradedItem>>; GradingScheme struct
 *
 * Sprint 19 - Input validation: rejects bad numbers and out-of-range choices
 * Sprint 20 - Save/load to file: persists grading scheme and graded items
 * Sprint 21 - Display polish: aligned table and colored letter grades
 * Sprint 22 - Final polish: sorting, search, statistics, and GPA conversion
 */

struct GradingScheme {
    float homework_weight = 20.0f;
    float quiz_weight = 30.0f;
    float exam_weight = 50.0f;

    float A_cutoff = 90.0f;
    float B_cutoff = 80.0f;
    float C_cutoff = 70.0f;
    float D_cutoff = 60.0f;
};

int getIntInput(const std::string& prompt, int minValue, int maxValue);
float getFloatInput(const std::string& prompt, float minValue, float maxValue);
char getYesNo(const std::string& prompt);
void displayMenu();
void setGradingScheme(GradingScheme& scheme);
void addItem(std::vector<std::unique_ptr<GradedItem>>& items);
void viewItems(const std::vector<std::unique_ptr<GradedItem>>& items);
void removeItem(std::vector<std::unique_ptr<GradedItem>>& items);
void calculatePointsBasedGrade(const std::vector<std::unique_ptr<GradedItem>>& items, const GradingScheme& scheme);
void calculateWeightedGrade(const std::vector<std::unique_ptr<GradedItem>>& items, const GradingScheme& scheme);
void saveGrades(const std::string& filename, const GradingScheme& scheme, const std::vector<std::unique_ptr<GradedItem>>& items);
bool loadGrades(const std::string& filename, GradingScheme& scheme, std::vector<std::unique_ptr<GradedItem>>& items);
void sortItemsByPercentage(std::vector<std::unique_ptr<GradedItem>>& items);
void searchItems(const std::vector<std::unique_ptr<GradedItem>>& items);
void showStatistics(const std::vector<std::unique_ptr<GradedItem>>& items);
char getLetterGrade(float percentage, const GradingScheme& scheme);
float getGpaPoints(char letterGrade);
std::string getColoredGrade(char letterGrade);
std::unique_ptr<GradedItem> createItem(const std::string& category, const std::string& name, float earned, float possible);
bool compareByPercentage(const std::unique_ptr<GradedItem>& left, const std::unique_ptr<GradedItem>& right);

int main() {
    std::vector<std::unique_ptr<GradedItem>> items;
    GradingScheme scheme;
    int choice = -1;

    displayGreeting();
    std::cout << "Welcome to the COSC 1437 Grade Calculator\n\n";

    do {
        displayMenu();
        choice = getIntInput("Enter your choice: ", 0, 11);

        switch (choice) {
            case 1:
                setGradingScheme(scheme);
                break;
            case 2:
                addItem(items);
                break;
            case 3:
                viewItems(items);
                break;
            case 4:
                removeItem(items);
                break;
            case 5:
                calculatePointsBasedGrade(items, scheme);
                break;
            case 6:
                calculateWeightedGrade(items, scheme);
                break;
            case 7:
                saveGrades("grades.txt", scheme, items);
                break;
            case 8:
                loadGrades("grades.txt", scheme, items);
                break;
            case 9:
                sortItemsByPercentage(items);
                break;
            case 10:
                searchItems(items);
                break;
            case 11:
                showStatistics(items);
                break;
            case 0:
                std::cout << "Thank you for using Grade Calculator!\n";
                break;
        }
    } while (choice != 0);

    return 0;
}

int getIntInput(const std::string& prompt, int minValue, int maxValue) {
    int value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a whole number.\n";
        } else if (value < minValue || value > maxValue) {
            std::cout << "Invalid choice. Enter a number from " << minValue << " to " << maxValue << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

float getFloatInput(const std::string& prompt, float minValue, float maxValue) {
    float value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        } else if (value < minValue || value > maxValue) {
            std::cout << "Invalid number. Enter a value from " << minValue << " to " << maxValue << ".\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

char getYesNo(const std::string& prompt) {
    char choice;

    while (true) {
        std::cout << prompt;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
            return choice;
        }

        std::cout << "Please enter y or n.\n";
    }
}

void displayMenu() {
    std::cout << "\nGrade Calculator Menu\n";
    std::cout << "=====================\n";
    std::cout << "1. Set grading scheme\n";
    std::cout << "2. Add graded item\n";
    std::cout << "3. View all items\n";
    std::cout << "4. Remove item\n";
    std::cout << "5. Calculate points-based grade\n";
    std::cout << "6. Calculate weighted grade\n";
    std::cout << "7. Save grades to file\n";
    std::cout << "8. Load grades from file\n";
    std::cout << "9. Sort items by percentage\n";
    std::cout << "10. Search item by name\n";
    std::cout << "11. Show statistics\n";
    std::cout << "0. Exit\n";
}

void setGradingScheme(GradingScheme& scheme) {
    std::cout << "\nGrading Scheme Setup\n";
    std::cout << "====================\n";
    std::cout << "Category weights must add up to 100%.\n\n";

    while (true) {
        scheme.homework_weight = getFloatInput("Homework weight percent: ", 0.0f, 100.0f);
        scheme.quiz_weight = getFloatInput("Quiz weight percent: ", 0.0f, 100.0f);
        scheme.exam_weight = getFloatInput("Exam weight percent: ", 0.0f, 100.0f);

        float totalWeight = scheme.homework_weight + scheme.quiz_weight + scheme.exam_weight;

        if (std::fabs(totalWeight - 100.0f) < 0.01f) {
            break;
        }

        std::cout << "The weights add up to " << totalWeight << "%. Please try again.\n\n";
    }

    std::cout << "\nLetter grade cutoffs must be in order: A > B > C > D.\n";

    while (true) {
        scheme.A_cutoff = getFloatInput("Minimum percent for A: ", 0.0f, 100.0f);
        scheme.B_cutoff = getFloatInput("Minimum percent for B: ", 0.0f, 100.0f);
        scheme.C_cutoff = getFloatInput("Minimum percent for C: ", 0.0f, 100.0f);
        scheme.D_cutoff = getFloatInput("Minimum percent for D: ", 0.0f, 100.0f);

        if (scheme.A_cutoff > scheme.B_cutoff &&
            scheme.B_cutoff > scheme.C_cutoff &&
            scheme.C_cutoff > scheme.D_cutoff) {
            break;
        }

        std::cout << "The cutoffs are not in the correct order. Please try again.\n\n";
    }

    std::cout << "Grading scheme updated successfully!\n";
}

void addItem(std::vector<std::unique_ptr<GradedItem>>& items) {
    int categoryChoice;
    std::string name;
    float possible;
    float earned;

    std::cout << "\nAdd Graded Item\n";
    std::cout << "===============\n";
    std::cout << "1. Homework\n";
    std::cout << "2. Quiz\n";
    std::cout << "3. Exam\n";

    categoryChoice = getIntInput("Choose a category: ", 1, 3);

    std::cout << "Enter item name (no spaces): ";
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    possible = getFloatInput("Enter points possible: ", 0.01f, 100000.0f);
    earned = getFloatInput("Enter points earned: ", 0.0f, possible);

    if (categoryChoice == 1) {
        items.push_back(std::make_unique<Homework>(name, earned, possible));
    } else if (categoryChoice == 2) {
        items.push_back(std::make_unique<Quiz>(name, earned, possible));
    } else {
        items.push_back(std::make_unique<Exam>(name, earned, possible));
    }

    std::cout << "Item added successfully!\n";
}

void viewItems(const std::vector<std::unique_ptr<GradedItem>>& items) {
    std::cout << "\nCurrent Graded Items\n";
    std::cout << "====================\n";

    if (items.empty()) {
        std::cout << "No graded items have been added yet.\n";
        return;
    }

    std::cout << std::left << std::setw(6) << "#"
              << std::setw(14) << "Category"
              << std::setw(20) << "Name"
              << std::right << std::setw(12) << "Earned"
              << std::setw(12) << "Possible"
              << std::setw(12) << "Percent" << '\n';

    std::cout << std::string(76, '-') << '\n';

    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << std::left << std::setw(6) << (i + 1)
                  << std::setw(14) << items[i]->getCategory()
                  << std::setw(20) << items[i]->getName()
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2) << items[i]->getPointsEarned()
                  << std::setw(12) << items[i]->getPointsPossible()
                  << std::setw(11) << items[i]->getPercentage() << "%" << '\n';
    }
}

void removeItem(std::vector<std::unique_ptr<GradedItem>>& items) {
    if (items.empty()) {
        std::cout << "\nThere are no items to remove.\n";
        return;
    }

    viewItems(items);
    int itemNumber = getIntInput("Enter the item number to remove: ", 1, static_cast<int>(items.size()));
    char confirm = getYesNo("Are you sure you want to remove this item? (y/n): ");

    if (confirm == 'y' || confirm == 'Y') {
        items.erase(items.begin() + itemNumber - 1);
        std::cout << "Item removed successfully!\n";
    } else {
        std::cout << "Remove canceled.\n";
    }
}

void calculatePointsBasedGrade(const std::vector<std::unique_ptr<GradedItem>>& items, const GradingScheme& scheme) {
    float totalEarned = 0.0f;
    float totalPossible = 0.0f;

    std::cout << "\nPoints-Based Grade\n";
    std::cout << "==================\n";

    if (items.empty()) {
        std::cout << "No items to calculate.\n";
        return;
    }

    for (const auto& item : items) {
        totalEarned += item->getPointsEarned();
        totalPossible += item->getPointsPossible();
    }

    float percentage = 0.0f;
    if (totalPossible > 0) {
        percentage = (totalEarned / totalPossible) * 100;
    }

    char letterGrade = getLetterGrade(percentage, scheme);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Points Earned: " << totalEarned << '\n';
    std::cout << "Total Points Possible: " << totalPossible << '\n';
    std::cout << "Percentage: " << percentage << "%\n";
    std::cout << "Letter Grade: " << getColoredGrade(letterGrade) << '\n';
    std::cout << "GPA Points: " << getGpaPoints(letterGrade) << '\n';
}

void calculateWeightedGrade(const std::vector<std::unique_ptr<GradedItem>>& items, const GradingScheme& scheme) {
    float homeworkEarned = 0.0f, homeworkPossible = 0.0f;
    float quizEarned = 0.0f, quizPossible = 0.0f;
    float examEarned = 0.0f, examPossible = 0.0f;

    std::cout << "\nWeighted Grade\n";
    std::cout << "==============\n";

    if (items.empty()) {
        std::cout << "No items to calculate.\n";
        return;
    }

    for (const auto& item : items) {
        if (item->getCategory() == "Homework") {
            homeworkEarned += item->getPointsEarned();
            homeworkPossible += item->getPointsPossible();
        } else if (item->getCategory() == "Quiz") {
            quizEarned += item->getPointsEarned();
            quizPossible += item->getPointsPossible();
        } else if (item->getCategory() == "Exam") {
            examEarned += item->getPointsEarned();
            examPossible += item->getPointsPossible();
        }
    }

    float homeworkAverage = 0.0f;
    float quizAverage = 0.0f;
    float examAverage = 0.0f;

    if (homeworkPossible > 0) homeworkAverage = (homeworkEarned / homeworkPossible) * 100;
    if (quizPossible > 0) quizAverage = (quizEarned / quizPossible) * 100;
    if (examPossible > 0) examAverage = (examEarned / examPossible) * 100;

    float homeworkContribution = homeworkAverage * (scheme.homework_weight / 100.0f);
    float quizContribution = quizAverage * (scheme.quiz_weight / 100.0f);
    float examContribution = examAverage * (scheme.exam_weight / 100.0f);
    float finalPercentage = homeworkContribution + quizContribution + examContribution;
    char letterGrade = getLetterGrade(finalPercentage, scheme);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(14) << "Category"
              << std::right << std::setw(12) << "Average"
              << std::setw(12) << "Weight"
              << std::setw(16) << "Contribution" << '\n';
    std::cout << std::string(54, '-') << '\n';

    std::cout << std::left << std::setw(14) << "Homework"
              << std::right << std::setw(11) << homeworkAverage << "%"
              << std::setw(11) << scheme.homework_weight << "%"
              << std::setw(15) << homeworkContribution << "%" << '\n';

    std::cout << std::left << std::setw(14) << "Quiz"
              << std::right << std::setw(11) << quizAverage << "%"
              << std::setw(11) << scheme.quiz_weight << "%"
              << std::setw(15) << quizContribution << "%" << '\n';

    std::cout << std::left << std::setw(14) << "Exam"
              << std::right << std::setw(11) << examAverage << "%"
              << std::setw(11) << scheme.exam_weight << "%"
              << std::setw(15) << examContribution << "%" << '\n';

    std::cout << "\nFinal Weighted Percentage: " << finalPercentage << "%\n";
    std::cout << "Letter Grade: " << getColoredGrade(letterGrade) << '\n';
    std::cout << "GPA Points: " << getGpaPoints(letterGrade) << '\n';
}

void saveGrades(const std::string& filename, const GradingScheme& scheme, const std::vector<std::unique_ptr<GradedItem>>& items) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cout << "Error: Could not save to file.\n";
        return;
    }

    outFile << scheme.homework_weight << '\n';
    outFile << scheme.quiz_weight << '\n';
    outFile << scheme.exam_weight << '\n';
    outFile << scheme.A_cutoff << '\n';
    outFile << scheme.B_cutoff << '\n';
    outFile << scheme.C_cutoff << '\n';
    outFile << scheme.D_cutoff << '\n';

    outFile << items.size() << '\n';
    for (const auto& item : items) {
        outFile << item->getCategory() << ' '
                << item->getName() << ' '
                << item->getPointsEarned() << ' '
                << item->getPointsPossible() << '\n';
    }

    outFile.close();
    std::cout << "Grades saved successfully to " << filename << "!\n";
}

bool loadGrades(const std::string& filename, GradingScheme& scheme, std::vector<std::unique_ptr<GradedItem>>& items) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cout << "No saved file was found.\n";
        return false;
    }

    GradingScheme loadedScheme;
    std::vector<std::unique_ptr<GradedItem>> loadedItems;
    size_t count;

    if (!(inFile >> loadedScheme.homework_weight >> loadedScheme.quiz_weight >> loadedScheme.exam_weight
                 >> loadedScheme.A_cutoff >> loadedScheme.B_cutoff >> loadedScheme.C_cutoff >> loadedScheme.D_cutoff)) {
        std::cout << "Error: Could not read the grading scheme from the file.\n";
        return false;
    }

    if (!(inFile >> count)) {
        std::cout << "Error: Could not read the saved item count.\n";
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        std::string category;
        std::string name;
        float earned;
        float possible;

        if (!(inFile >> category >> name >> earned >> possible)) {
            std::cout << "Error: Could not read all saved items.\n";
            return false;
        }

        std::unique_ptr<GradedItem> newItem = createItem(category, name, earned, possible);
        if (newItem == nullptr) {
            std::cout << "Error: Unknown item category in file.\n";
            return false;
        }

        loadedItems.push_back(std::move(newItem));
    }

    scheme = loadedScheme;
    items = std::move(loadedItems);

    inFile.close();
    std::cout << "Grades loaded successfully from " << filename << "!\n";
    return true;
}

void sortItemsByPercentage(std::vector<std::unique_ptr<GradedItem>>& items) {
    if (items.empty()) {
        std::cout << "\nNo items to sort.\n";
        return;
    }

    std::sort(items.begin(), items.end(), compareByPercentage);
    std::cout << "\nItems sorted from lowest percentage to highest percentage.\n";
    viewItems(items);
}

void searchItems(const std::vector<std::unique_ptr<GradedItem>>& items) {
    if (items.empty()) {
        std::cout << "\nNo items to search.\n";
        return;
    }

    std::string searchName;
    bool found = false;

    std::cout << "\nSearch Item\n";
    std::cout << "===========\n";
    std::cout << "Enter all or part of the item name: ";
    std::cin >> searchName;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\nSearch Results\n";
    std::cout << "==============\n";

    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i]->getName().find(searchName) != std::string::npos) {
            std::cout << (i + 1) << ". "
                      << items[i]->getCategory() << " - "
                      << items[i]->getName() << ": "
                      << items[i]->getPointsEarned() << "/"
                      << items[i]->getPointsPossible() << " ("
                      << std::fixed << std::setprecision(2) << items[i]->getPercentage() << "%)\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching item was found.\n";
    }
}

void showStatistics(const std::vector<std::unique_ptr<GradedItem>>& items) {
    std::cout << "\nStatistics Dashboard\n";
    std::cout << "====================\n";

    if (items.empty()) {
        std::cout << "No items to analyze.\n";
        return;
    }

    float totalEarned = 0.0f;
    float totalPossible = 0.0f;

    for (const auto& item : items) {
        totalEarned += item->getPointsEarned();
        totalPossible += item->getPointsPossible();
    }

    auto lowest = std::min_element(items.begin(), items.end(), compareByPercentage);
    auto highest = std::max_element(items.begin(), items.end(), compareByPercentage);

    float overallPercent = 0.0f;
    if (totalPossible > 0) {
        overallPercent = (totalEarned / totalPossible) * 100;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Number of items: " << items.size() << '\n';
    std::cout << "Total earned: " << totalEarned << '\n';
    std::cout << "Total possible: " << totalPossible << '\n';
    std::cout << "Overall points-based percent: " << overallPercent << "%\n";
    std::cout << "Highest item: " << (*highest)->getName() << " (" << (*highest)->getPercentage() << "%)\n";
    std::cout << "Lowest item: " << (*lowest)->getName() << " (" << (*lowest)->getPercentage() << "%)\n";
}

char getLetterGrade(float percentage, const GradingScheme& scheme) {
    if (percentage >= scheme.A_cutoff) {
        return 'A';
    } else if (percentage >= scheme.B_cutoff) {
        return 'B';
    } else if (percentage >= scheme.C_cutoff) {
        return 'C';
    } else if (percentage >= scheme.D_cutoff) {
        return 'D';
    } else {
        return 'F';
    }
}

float getGpaPoints(char letterGrade) {
    if (letterGrade == 'A') {
        return 4.0f;
    } else if (letterGrade == 'B') {
        return 3.0f;
    } else if (letterGrade == 'C') {
        return 2.0f;
    } else if (letterGrade == 'D') {
        return 1.0f;
    } else {
        return 0.0f;
    }
}

std::string getColoredGrade(char letterGrade) {
    if (letterGrade == 'A' || letterGrade == 'B') {
        return "\033[32m" + std::string(1, letterGrade) + "\033[0m";
    } else if (letterGrade == 'C') {
        return "\033[33m" + std::string(1, letterGrade) + "\033[0m";
    } else {
        return "\033[31m" + std::string(1, letterGrade) + "\033[0m";
    }
}

std::unique_ptr<GradedItem> createItem(const std::string& category, const std::string& name, float earned, float possible) {
    if (category == "Homework") {
        return std::make_unique<Homework>(name, earned, possible);
    } else if (category == "Quiz") {
        return std::make_unique<Quiz>(name, earned, possible);
    } else if (category == "Exam") {
        return std::make_unique<Exam>(name, earned, possible);
    }

    return nullptr;
}

bool compareByPercentage(const std::unique_ptr<GradedItem>& left, const std::unique_ptr<GradedItem>& right) {
    return left->getPercentage() < right->getPercentage();
}
