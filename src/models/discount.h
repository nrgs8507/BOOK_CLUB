#pragma once

class Discount {
public:
    virtual ~Discount() = default;

    virtual double getDiscountedPrice(double price) const = 0;
    virtual bool isActive() const = 0;
};