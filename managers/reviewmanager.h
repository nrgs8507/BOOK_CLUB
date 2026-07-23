#pragma once
#include "../repositories/ireviewstorage.h"
#include "bookmanager.h"
#include <QVector>
#include <QString>

class NotificationManager;
class ReviewManager {
private:
    IReviewStorage* storage;
    BookManager* bookManager;
    NotificationManager* notificationManager;

    int generateNewId() const;
    void recalculateAverageRating(int bookId);

public:
    ReviewManager(IReviewStorage* storage, BookManager* bookManager,
                  NotificationManager* notificationManager);

    int addReview(int userId, int bookId, const QString& comment, int rating);
    void editReview(int reviewId, const QString& newComment, int newRating);
    void deleteReview(int reviewId);

    QVector<Review> getReviewsForBook(int bookId);
    QVector<Review> getReviewsByUser(int userId);
};