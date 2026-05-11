#ifndef HOMEWORK_H
#define HOMEWORK_H

#include "GradedItem.h"

class Homework : public GradedItem {
public:
    Homework() : GradedItem() {}

    Homework(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}

    std::string getCategory() const override { return "Homework"; }
    float getDefaultWeight() const override { return 20.0f; }
};

#endif
