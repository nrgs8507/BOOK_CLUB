#include "cart.h"

Cart::Cart() : cartId(-1), userId(-1) {}

Cart::Cart(int cartId, int userId) : cartId(cartId), userId(userId) {}

int Cart::getId() const { return cartId; }
int Cart::getCartId() const { return cartId; }
int Cart::getUserId() const { return userId; }
QVector<int> Cart::getBookIds() const { return bookIds; }

void Cart::addBook(int bookId) {
    if (!bookIds.contains(bookId)) {
        bookIds.append(bookId);
    }
}

void Cart::removeBook(int bookId) {
    bookIds.removeAll(bookId);
}

bool Cart::containsBook(int bookId) const {
    return bookIds.contains(bookId);
}

int Cart::itemCount() const {
    return bookIds.size();
}

void Cart::clear() {
    bookIds.clear();
}

QJsonObject Cart::toJson() const {
    QJsonObject obj;
    obj["cartId"] = cartId;
    obj["userId"] = userId;

    QJsonArray idsArray;
    for (int id : bookIds) {
        idsArray.append(id);
    }
    obj["bookIds"] = idsArray;

    return obj;
}

Cart Cart::fromJson(const QJsonObject& obj) {
    Cart cart(obj["cartId"].toInt(), obj["userId"].toInt());

    QJsonArray idsArray = obj["bookIds"].toArray();
    for (const QJsonValue& val : idsArray) {
        cart.addBook(val.toInt());
    }

    return cart;
}