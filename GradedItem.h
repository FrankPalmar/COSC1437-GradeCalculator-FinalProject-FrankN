#ifndef GRADEDITEM_H
#define GRADEDITEM_H

#include <string>

class GradedItem {
private:
    std::string name;
    float points_earned;
    float points_possible;

public:
    GradedItem() : name(""), points_earned(0), points_possible(0) {}

    GradedItem(const std::string& n, float earned, float possible)
        : name(n), points_earned(earned), points_possible(possible) {}

    virtual ~GradedItem() {}

    std::string getName() const { return name; }
    float getPointsEarned() const { return points_earned; }
    float getPointsPossible() const { return points_possible; }

    void setName(const std::string& n) { name = n; }

    void setPointsEarned(float earned) {
        if (earned >= 0) {
            points_earned = earned;
        }
    }

    void setPointsPossible(float possible) {
        if (possible > 0) {
            points_possible = possible;
        }
    }

    float getPercentage() const {
        if (points_possible == 0) return 0;
        return (points_earned / points_possible) * 100;
    }

    virtual std::string getCategory() const = 0;
    virtual float getDefaultWeight() const = 0;
};

#endif
