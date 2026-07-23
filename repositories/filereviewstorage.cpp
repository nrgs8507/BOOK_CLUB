#include "filereviewstorage.h"

FileReviewStorage::FileReviewStorage(const QString& path)
    : FileRepository<Review>(path) {}

QVector<Review> FileReviewStorage::getByBookId(int bookId) {
    QVector<Review> result;
    for (const Review& r : getAll()) {
        if (r.getBookId() == bookId) {
            result.append(r);
        }
    }
    return result;
}

QVector<Review> FileReviewStorage::getByUserId(int userId) {
    QVector<Review> result;
    for (const Review& r : getAll()) {
        if (r.getUserId() == userId) {
            result.append(r);
        }
    }
    return result;
}