#include "review.h"
#include <algorithm>

Review::Review() : reviewId(-1), userId(-1), bookId(-1), rating(1), date(QDate::currentDate()) {}

Review::Review(int reviewId, int userId, int bookId, const QString& comment, int rating,
               const QDate& date)
    : reviewId(reviewId), userId(userId), bookId(bookId), comment(comment),
    rating(std::clamp(rating, 1, 5)), date(date) {}

int Review::getId() const { return reviewId; }
int Review::getReviewId() const { return reviewId; }
int Review::getUserId() const { return userId; }
int Review::getBookId() const { return bookId; }
QString Review::getComment() const { return comment; }
int Review::getRating() const { return rating; }
QDate Review::getDate() const { return date; }

void Review::setComment(const QString& newComment) { comment = newComment; }
void Review::setRating(int newRating) { rating = std::clamp(newRating, 1, 5); }

QJsonObject Review::toJson() const {
    QJsonObject obj;
    obj["reviewId"] = reviewId;
    obj["userId"] = userId;
    obj["bookId"] = bookId;
    obj["comment"] = comment;
    obj["rating"] = rating;
    obj["date"] = date.toString(Qt::ISODate);
    return obj;
}

Review Review::fromJson(const QJsonObject& obj) {
    return Review(
        obj["reviewId"].toInt(),
        obj["userId"].toInt(),
        obj["bookId"].toInt(),
        obj["comment"].toString(),
        obj["rating"].toInt(),
        QDate::fromString(obj["date"].toString(), Qt::ISODate)
        );
}