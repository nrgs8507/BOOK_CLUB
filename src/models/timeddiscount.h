#pragma once
#include "discount.h"
#include <QDate>

class TimedDiscount : public Discount {
private:
    double percent;
    QDate startDate;
    QDate endDate;

public:
    TimedDiscount(double percent, const QDate& startDate, const QDate& endDate);

    double getDiscountedPrice(double price) const override;
    bool isActive() const override;

    double getPercent() const;
    QDate getStartDate() const;
    QDate getEndDate() const;
};