#include "reviewmanager.h"
#include <algorithm>

ReviewManager::ReviewManager(IReviewStorage* storage, BookManager* bookManager,
                             NotificationManager* notificationManager)
    : storage(storage), bookManager(bookManager), notificationManager(notificationManager) {}

int ReviewManager::generateNewId() const {
    QVector<Review> all = storage->getAll();
    int maxId = 0;
    for (const Review& r : all) {
        maxId = std::max(maxId, r.getId());
    }
    return maxId + 1;
}

void ReviewManager::recalculateAverageRating(int bookId) {
    QVector<Review> reviews = storage->getByBookId(bookId);
    if (reviews.isEmpty()) {
        bookManager->updateAverageRating(bookId, -1.0);
        return;
    }

    int sum = 0;
    for (const Review& r : reviews) {
        sum += r.getRating();
    }
    double average = static_cast<double>(sum) / reviews.size();
    bookManager->updateAverageRating(bookId, average);
}

int ReviewManager::addReview(int userId, int bookId, const QString& comment, int rating) {
    int newId = generateNewId();
    Review newReview(newId, userId, bookId, comment, rating);
    storage->save(newReview);

    recalculateAverageRating(bookId);


    //notificationManager->notifyNewReview(bookManager->getBookById(bookId).getPublisherId(), bookId);

    return newId;
}

void ReviewManager::editReview(int reviewId, const QString& newComment, int newRating) {
    Review review = storage->getById(reviewId);
    review.setComment(newComment);
    review.setRating(newRating);
    storage->save(review);

    recalculateAverageRating(review.getBookId());
}

void ReviewManager::deleteReview(int reviewId) {
    Review review = storage->getById(reviewId);
    int bookId = review.getBookId();

    storage->remove(reviewId);

    recalculateAverageRating(bookId);
}

QVector<Review> ReviewManager::getReviewsForBook(int bookId) {
    return storage->getByBookId(bookId);
}

QVector<Review> ReviewManager::getReviewsByUser(int userId) {
    return storage->getByUserId(userId);
}