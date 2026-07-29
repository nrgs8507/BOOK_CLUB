#include "filebookstorage.h"

FileBookStorage::FileBookStorage(const QString& path)
    : FileRepository<Book>(path) {}

QVector<Book> FileBookStorage::searchByGenre(const QString& genre) {
    QVector<Book> result;
    for (const Book& b : getAll()) {
        if (b.getGenre().compare(genre, Qt::CaseInsensitive) == 0) {
            result.append(b);
        }
    }
    return result;
}

QVector<Book> FileBookStorage::searchByTitle(const QString& title) {
    QVector<Book> result;
    for (const Book& b : getAll()) {
        if (b.getTitle().contains(title, Qt::CaseInsensitive)) {
            result.append(b);
        }
    }
    return result;
}

QVector<Book> FileBookStorage::searchByAuthor(const QString& author) {
    QVector<Book> result;
    for (const Book& b : getAll()) {
        if (b.getAuthor().contains(author, Qt::CaseInsensitive)) {
            result.append(b);
        }
    }
    return result;
}