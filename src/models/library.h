#pragma once
#include "shelf.h"
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

class Library {
private:
    int libraryId;
    int userId;
    QVector<int> purchasedBookIds;
    QVector<int> savedBookIds;
    QVector<Shelf> shelves;

    int generateNewShelfId() const;
    void restoreShelf(const Shelf& shelf);

public:
    Library();
    Library(int libraryId, int userId);

    int getId() const;
    int getLibraryId() const;
    int getUserId() const;
    QVector<int> getPurchasedBookIds() const;
    QVector<int> getSavedBookIds() const;
    QVector<Shelf> getShelves() const;

    void addPurchasedBook(int bookId);
    bool hasPurchasedBook(int bookId) const;

    void saveBook(int bookId);
    void unsaveBook(int bookId);
    bool hasSavedBook(int bookId) const;

    int createShelf(const QString& name);
    void deleteShelf(int shelfId);
    void addBookToShelf(int shelfId, int bookId);
    void removeBookFromShelf(int shelfId, int bookId);

    QJsonObject toJson() const;
    static Library fromJson(const QJsonObject& obj);
};