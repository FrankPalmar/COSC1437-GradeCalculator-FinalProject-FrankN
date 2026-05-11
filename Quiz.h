#ifndef QUIZ_H
#define QUIZ_H

#include "GradedItem.h"

class Quiz : public GradedItem {
public:
    Quiz() : GradedItem() {}

    Quiz(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}

    std::string getCategory() const override { return "Quiz"; }
    float getDefaultWeight() const override { return 30.0f; }
};

#endif
