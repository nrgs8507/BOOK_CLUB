#include "librarymanager.h"
#include <algorithm>

LibraryManager::LibraryManager(ILibraryStorage* storage, BookManager* bookManager)
    : storage(storage), bookManager(bookManager) {}

int LibraryManager::generateNewId() const {
    QVector<Library> all = storage->getAll();
    int maxId = 0;
    for (const Library& l : all) {
        maxId = std::max(maxId, l.getId());
    }
    return maxId + 1;
}

Library LibraryManager::getOrCreateLibrary(int userId) {
    Library library = storage->getByUserId(userId);
    if (library.getId() == -1) {
        int newId = generateNewId();
        Library newLibrary(newId, userId);
        storage->save(newLibrary);
        return newLibrary;
    }
    return library;
}

void LibraryManager::addBookToLibrary(int userId, int bookId) {
    Library library = getOrCreateLibrary(userId);
    library.addPurchasedBook(bookId);
    library.unsaveBook(bookId);
    storage->save(library);
}

QVector<Book> LibraryManager::getPurchasedBooks(int userId) {
    Library library = getOrCreateLibrary(userId);
    QVector<Book> books;
    for (int bookId : library.getPurchasedBookIds()) {
        books.append(bookManager->getBookById(bookId));
    }
    return books;
}

void LibraryManager::saveBookForLater(int userId, int bookId) {
    Library library = getOrCreateLibrary(userId);
    library.saveBook(bookId);
    storage->save(library);
}

void LibraryManager::unsaveBook(int userId, int bookId) {
    Library library = getOrCreateLibrary(userId);
    library.unsaveBook(bookId);
    storage->save(library);
}

QVector<Book> LibraryManager::getSavedBooks(int userId) {
    Library library = getOrCreateLibrary(userId);
    QVector<Book> books;
    for (int bookId : library.getSavedBookIds()) {
        books.append(bookManager->getBookById(bookId));
    }
    return books;
}

int LibraryManager::createShelf(int userId, const QString& shelfName) {
    Library library = getOrCreateLibrary(userId);
    int shelfId = library.createShelf(shelfName);
    storage->save(library);
    return shelfId;
}

void LibraryManager::deleteShelf(int userId, int shelfId) {
    Library library = getOrCreateLibrary(userId);
    library.deleteShelf(shelfId);
    storage->save(library);
}

void LibraryManager::addBookToShelf(int userId, int shelfId, int bookId) {
    Library library = getOrCreateLibrary(userId);
    library.addBookToShelf(shelfId, bookId);
    storage->save(library);
}

void LibraryManager::removeBookFromShelf(int userId, int shelfId, int bookId) {
    Library library = getOrCreateLibrary(userId);
    library.removeBookFromShelf(shelfId, bookId);
    storage->save(library);
}

QVector<Shelf> LibraryManager::getShelves(int userId) {
    Library library = getOrCreateLibrary(userId);
    return library.getShelves();
}