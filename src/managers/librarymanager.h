#pragma once
#include "../repository/ilibrarystorage.h"
#include "bookmanager.h"
#include <QVector>

class LibraryManager {
private:
    ILibraryStorage* storage;
    BookManager* bookManager;

    int generateNewId() const;
    Library getOrCreateLibrary(int userId);

public:
    LibraryManager(ILibraryStorage* storage, BookManager* bookManager);

    void addBookToLibrary(int userId, int bookId);
    QVector<Book> getPurchasedBooks(int userId);

    void saveBookForLater(int userId, int bookId);
    void unsaveBook(int userId, int bookId);
    QVector<Book> getSavedBooks(int userId);

    int createShelf(int userId, const QString& shelfName);
    void deleteShelf(int userId, int shelfId);
    void addBookToShelf(int userId, int shelfId, int bookId);
    void removeBookFromShelf(int userId, int shelfId, int bookId);
    QVector<Shelf> getShelves(int userId);
};