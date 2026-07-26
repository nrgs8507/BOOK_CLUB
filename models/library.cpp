#include "library.h"
#include <algorithm>

Library::Library() : libraryId(-1), userId(-1) {}

Library::Library(int libraryId, int userId) : libraryId(libraryId), userId(userId) {}

void Library::restoreShelf(const Shelf& shelf) {
    shelves.append(shelf);
}

int Library::getId() const { return libraryId; }
int Library::getLibraryId() const { return libraryId; }
int Library::getUserId() const { return userId; }
QVector<int> Library::getPurchasedBookIds() const { return purchasedBookIds; }
QVector<int> Library::getSavedBookIds() const { return savedBookIds; }
QVector<Shelf> Library::getShelves() const { return shelves; }

void Library::addPurchasedBook(int bookId) {
    if (!purchasedBookIds.contains(bookId)) {
        purchasedBookIds.append(bookId);
    }
}

bool Library::hasPurchasedBook(int bookId) const {
    return purchasedBookIds.contains(bookId);
}

void Library::saveBook(int bookId) {
    if (!savedBookIds.contains(bookId)) {
        savedBookIds.append(bookId);
    }
}

void Library::unsaveBook(int bookId) {
    savedBookIds.removeAll(bookId);
}

bool Library::hasSavedBook(int bookId) const {
    return savedBookIds.contains(bookId);
}

int Library::generateNewShelfId() const {
    int maxId = 0;
    for (const Shelf& s : shelves) {
        maxId = std::max(maxId, s.getId());
    }
    return maxId + 1;
}

int Library::createShelf(const QString& name) {
    int newId = generateNewShelfId();
    shelves.append(Shelf(newId, name));
    return newId;
}

void Library::deleteShelf(int shelfId) {
    for (int i = 0; i < shelves.size(); ++i) {
        if (shelves[i].getId() == shelfId) {
            shelves.removeAt(i);
            break;
        }
    }
}

void Library::addBookToShelf(int shelfId, int bookId) {
    for (int i = 0; i < shelves.size(); ++i) {
        if (shelves[i].getId() == shelfId) {
            shelves[i].addBook(bookId);
            break;
        }
    }
}

void Library::removeBookFromShelf(int shelfId, int bookId) {
    for (int i = 0; i < shelves.size(); ++i) {
        if (shelves[i].getId() == shelfId) {
            shelves[i].removeBook(bookId);
            break;
        }
    }
}

QJsonObject Library::toJson() const {
    QJsonObject obj;
    obj["libraryId"] = libraryId;
    obj["userId"] = userId;

    QJsonArray purchasedArray;
    for (int id : purchasedBookIds) purchasedArray.append(id);
    obj["purchasedBookIds"] = purchasedArray;

    QJsonArray savedArray;
    for (int id : savedBookIds) savedArray.append(id);
    obj["savedBookIds"] = savedArray;

    QJsonArray shelvesArray;
    for (const Shelf& s : shelves) shelvesArray.append(s.toJson());
    obj["shelves"] = shelvesArray;

    return obj;
}

Library Library::fromJson(const QJsonObject& obj) {
    Library library(obj["libraryId"].toInt(), obj["userId"].toInt());

    QJsonArray purchasedArray = obj["purchasedBookIds"].toArray();
    for (const QJsonValue& val : purchasedArray) {
        library.addPurchasedBook(val.toInt());
    }

    QJsonArray savedArray = obj["savedBookIds"].toArray();
    for (const QJsonValue& val : savedArray) {
        library.saveBook(val.toInt());
    }

    QJsonArray shelvesArray = obj["shelves"].toArray();
    for (const QJsonValue& val : shelvesArray) {
        library.restoreShelf(Shelf::fromJson(val.toObject()));
    }

    return library;
}
