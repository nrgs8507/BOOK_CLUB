#pragma once
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

class Cart {
private:
    int cartId;
    int userId;
    QVector<int> bookIds;


public:
    Cart();
    Cart(int cartId, int userId);

    int getId() const;
    int getCartId() const;
    int getUserId() const;
    QVector<int> getBookIds() const;

    void addBook(int bookId);
    void removeBook(int bookId);
    bool containsBook(int bookId) const;
    int itemCount() const;
    void clear();

    QJsonObject toJson() const;
    static Cart fromJson(const QJsonObject& obj);
};
