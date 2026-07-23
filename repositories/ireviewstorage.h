#pragma once
#include "irepository.h"
#include "../models/review.h"
#include <QVector>

class IReviewStorage : public virtual IRepository<Review> {
public:
    virtual ~IReviewStorage() = default;

    virtual QVector<Review> getByBookId(int bookId) = 0;
    virtual QVector<Review> getByUserId(int userId) = 0;
};