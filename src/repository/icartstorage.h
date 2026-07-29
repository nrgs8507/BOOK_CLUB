#pragma once
#include "irepository.h"
#include "../models/cart.h"
#include <QVector>

class ICartStorage : public virtual IRepository<Cart> {
public:
    virtual ~ICartStorage() = default;

    virtual Cart getByUserId(int userId) = 0;
};