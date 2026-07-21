#include "bookmanager.h"
#include <algorithm>

BookManager::BookManager(IBookStorage* storage) : storage(storage) {}

int BookManager::generateNewId() const {
    QVector<Book> all = storage->getAll();
    int maxId = 0;
    for (const Book& b : all) {
        maxId = std::max(maxId, b.getBookId());
    }
    return maxId + 1;
}

Book BookManager::getBookById(int bookId) {
    return storage->getById(bookId);
}

QVector<Book> BookManager::getAllBooks() {
    return storage->getAll();
}

QVector<Book> BookManager::getActiveBooks() {
    QVector<Book> result;
    for (const Book& b : storage->getAll()) {
        if (b.getIsActive()) result.append(b);
    }
    return result;
}

QVector<Book> BookManager::searchByGenre(const QString& genre) {
    return storage->searchByGenre(genre);
}

QVector<Book> BookManager::searchByTitle(const QString& title) {
    return storage->searchByTitle(title);
}

QVector<Book> BookManager::searchByAuthor(const QString& author) {
    return storage->searchByAuthor(author);
}

int BookManager::addBook(Book book) {
    int newId = generateNewId();
    Book newBook(newId, book.getTitle(), book.getAuthor(), book.getGenre(),
                 book.getDescription(), book.getPrice(), book.getCoverImagePath(),
                 book.getPdfFilePath(), book.getPublisherId(), book.getPublishDate());
    storage->save(newBook);
    return newId;
}

void BookManager::updateBook(const Book& book) {
    storage->save(book);
}

void BookManager::activateBook(int bookId) {
    Book b = storage->getById(bookId);
    b.setIsActive(true);
    storage->save(b);
}

void BookManager::deactivateBook(int bookId) {
    Book b = storage->getById(bookId);
    b.setIsActive(false);
    storage->save(b);
}

void BookManager::deleteBook(int bookId) {
    storage->remove(bookId);
}

void BookManager::incrementSalesCount(int bookId) {
    Book b = storage->getById(bookId);
    b.incrementSalesCount();
    storage->save(b);
}

void BookManager::updateAverageRating(int bookId, double newAverage) {
    Book b = storage->getById(bookId);
    b.setAverageRating(newAverage);
    storage->save(b);
}