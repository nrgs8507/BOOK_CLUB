#include "../models/timeddiscount.h"
#include <algorithm>

TimedDiscount::TimedDiscount(double percent, const QDate& startDate, const QDate& endDate)
    : percent(std::clamp(percent, 0.0, 100.0)), startDate(startDate), endDate(endDate) {}

double TimedDiscount::getDiscountedPrice(double price) const {
    if (!isActive()) return price;
    return price - (price * percent / 100.0);
}

bool TimedDiscount::isActive() const {
    QDate today = QDate::currentDate();
    return today >= startDate && today <= endDate;
}

double TimedDiscount::getPercent() const {
    return percent;
}

QDate TimedDiscount::getStartDate() const {
    return startDate;
}

QDate TimedDiscount::getEndDate() const {
    return endDate;
}