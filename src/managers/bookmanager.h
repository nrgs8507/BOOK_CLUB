#pragma once
#include "../repository/ibookstorage.h"
#include "../models/book.h"
#include <QVector>
#include <QString>

class BookManager {
private:
    IBookStorage* storage;

    int generateNewId() const;

public:
    explicit BookManager(IBookStorage* storage);

    Book getBookById(int bookId);
    QVector<Book> getAllBooks();
    QVector<Book> getActiveBooks();

    QVector<Book> searchByGenre(const QString& genre);
    QVector<Book> searchByTitle(const QString& title);
    QVector<Book> searchByAuthor(const QString& author);

    int addBook(Book book);
    void updateBook(const Book& book);

    void activateBook(int bookId);
    void deactivateBook(int bookId);
    void deleteBook(int bookId);

    void incrementSalesCount(int bookId);
    void updateAverageRating(int bookId, double newAverage);
};