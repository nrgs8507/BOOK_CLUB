#include "percentdiscount.h"
#include <algorithm>

PercentDiscount::PercentDiscount(double percent)
    : percent(std::clamp(percent, 0.0, 100.0)) {}

double PercentDiscount::getDiscountedPrice(double price) const {
    return price - (price * percent / 100.0);
}

bool PercentDiscount::isActive() const {
    return true;
}

double PercentDiscount::getPercent() const {
    return percent;
}

void PercentDiscount::setPercent(double newPercent) {
    percent = std::clamp(newPercent, 0.0, 100.0);
}