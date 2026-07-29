#pragma once
#include "filerepository.h"
#include "ibookstorage.h"
#include "../models/book.h"
#include <qstring>
class FileBookStorage : public FileRepository<Book>, public IBookStorage {
public:
    explicit FileBookStorage(const QString& path);

    QVector<Book> searchByGenre(const QString& genre) override;
    QVector<Book> searchByTitle(const QString& title) override;
    QVector<Book> searchByAuthor(const QString& author) override;
};