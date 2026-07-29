#pragma once
#include <QWidget>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
class SearchBookPage;
}

class NetworkClient;

class SearchBookPage : public QWidget {
    Q_OBJECT

public:
    explicit SearchBookPage(NetworkClient* networkClient, QWidget* parent = nullptr);
    ~SearchBookPage();

signals:
    void backRequested();
    void showResultsRequested(const QJsonArray& books);

private slots:
    void onSearchClicked();
    void onShowAllClicked();
    void onBackClicked();
    void onResponseReceived(const QJsonObject& response);

private:
    Ui::SearchBookPage* ui;
    NetworkClient* networkClient;

    void requestSearch(const QString& searchBy, const QString& query);
    void requestAllBooks();
};