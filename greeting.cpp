#include "greeting.h"
#include <iostream>
#include <ctime>

void displayGreeting() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    int hour = localTime->tm_hour;

    std::cout << "\n";
    if (hour >= 5 && hour < 12) {
        std::cout << "Good morning!\n";
    } else if (hour >= 12 && hour < 17) {
        std::cout << "Good afternoon!\n";
    } else if (hour >= 17 && hour < 21) {
        std::cout << "Good evening!\n";
    } else {
        std::cout << "Hello, night owl!\n";
    }
    std::cout << "\n";
}
