#pragma once
#include <QString>
#include <QDate>
#include <QJsonObject>

class Review {
private:
    int reviewId;
    int userId;
    int bookId;
    QString comment;
    int rating;
    QDate date;

public:
    Review();
    Review(int reviewId, int userId, int bookId, const QString& comment, int rating,
           const QDate& date = QDate::currentDate());

    int getId() const;

    int getReviewId() const;
    int getUserId() const;
    int getBookId() const;
    QString getComment() const;
    int getRating() const;
    QDate getDate() const;

    void setComment(const QString& newComment);
    void setRating(int newRating);

    QJsonObject toJson() const;
    static Review fromJson(const QJsonObject& obj);
};