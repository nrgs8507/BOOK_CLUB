#pragma once
#include "discount.h"

class PercentDiscount : public Discount {
private:
    double percent;

public:
    explicit PercentDiscount(double percent);

    double getDiscountedPrice(double price) const override;
    bool isActive() const override;

    double getPercent() const;
    void setPercent(double newPercent);
};