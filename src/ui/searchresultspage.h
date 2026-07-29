#pragma once
#include <QWidget>
#include <QJsonArray>

class QVBoxLayout;

class SearchResultsPage : public QWidget {
    Q_OBJECT

public:
    explicit SearchResultsPage(QWidget* parent = nullptr);
    void setBooks(const QJsonArray& books);

signals:
    void backRequested();

private:
    QVBoxLayout* contentLayout;
    void clearBooks();
};