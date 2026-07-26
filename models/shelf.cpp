#include "shelf.h"

Shelf::Shelf() : shelfId(-1) {}

Shelf::Shelf(int shelfId, const QString& name) : shelfId(shelfId), name(name) {}

int Shelf::getId() const { return shelfId; }
int Shelf::getShelfId() const { return shelfId; }
QString Shelf::getName() const { return name; }
QVector<int> Shelf::getBookIds() const { return bookIds; }

void Shelf::setName(const QString& newName) { name = newName; }

void Shelf::addBook(int bookId) {
    if (!bookIds.contains(bookId)) {
        bookIds.append(bookId);
    }
}

void Shelf::removeBook(int bookId) {
    bookIds.removeAll(bookId);
}

bool Shelf::containsBook(int bookId) const {
    return bookIds.contains(bookId);
}

QJsonObject Shelf::toJson() const {
    QJsonObject obj;
    obj["shelfId"] = shelfId;
    obj["name"] = name;

    QJsonArray idsArray;
    for (int id : bookIds) {
        idsArray.append(id);
    }
    obj["bookIds"] = idsArray;

    return obj;
}

Shelf Shelf::fromJson(const QJsonObject& obj) {
    Shelf shelf(obj["shelfId"].toInt(), obj["name"].toString());

    QJsonArray idsArray = obj["bookIds"].toArray();
    for (const QJsonValue& val : idsArray) {
        shelf.addBook(val.toInt());
    }

    return shelf;
}