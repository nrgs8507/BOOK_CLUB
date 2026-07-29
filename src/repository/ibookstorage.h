#pragma once
#include "irepository.h"
#include "../models/book.h"
#include <QVector>
#include <QString>

class IBookStorage : public virtual IRepository<Book> {
public:
    virtual ~IBookStorage() = default;

    virtual QVector<Book> searchByGenre(const QString& genre) = 0;
    virtual QVector<Book> searchByTitle(const QString& title) = 0;
    virtual QVector<Book> searchByAuthor(const QString& author) = 0;
};