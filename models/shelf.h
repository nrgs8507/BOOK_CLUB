#pragma once
#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

class Shelf {
private:
    int shelfId;
    QString name;
    QVector<int> bookIds;

public:
    Shelf();
    Shelf(int shelfId, const QString& name);

    int getId() const;
    int getShelfId() const;
    QString getName() const;
    QVector<int> getBookIds() const;

    void setName(const QString& newName);
    void addBook(int bookId);
    void removeBook(int bookId);
    bool containsBook(int bookId) const;

    QJsonObject toJson() const;
    static Shelf fromJson(const QJsonObject& obj);
};