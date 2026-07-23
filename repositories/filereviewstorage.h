#pragma once
#include "filerepository.h"
#include "ireviewstorage.h"
#include "../models/review.h"

class FileReviewStorage : public FileRepository<Review>, public IReviewStorage {
public:
    explicit FileReviewStorage(const QString& path);

    QVector<Review> getByBookId(int bookId) override;
    QVector<Review> getByUserId(int userId) override;
};