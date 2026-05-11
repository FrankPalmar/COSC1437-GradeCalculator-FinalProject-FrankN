#ifndef EXAM_H
#define EXAM_H

#include "GradedItem.h"

class Exam : public GradedItem {
public:
    Exam() : GradedItem() {}

    Exam(const std::string& n, float earned, float possible)
        : GradedItem(n, earned, possible) {}

    std::string getCategory() const override { return "Exam"; }
    float getDefaultWeight() const override { return 50.0f; }
};

#endif
