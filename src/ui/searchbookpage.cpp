#include "searchbookpage.h"
#include "ui_searchbookpage.h"
#include "../network/networkclient.h"

SearchBookPage::SearchBookPage(NetworkClient* networkClient, QWidget* parent)
    : QWidget(parent), ui(new Ui::SearchBookPage), networkClient(networkClient) {
    ui->setupUi(this);

    ui->comboBox->addItem("All");
    ui->comboBox->addItem("Fiction");
    ui->comboBox->addItem("Fantasy");

    connect(ui->search, &QPushButton::clicked, this, &SearchBookPage::onSearchClicked);
    connect(ui->showall, &QPushButton::clicked, this, &SearchBookPage::onShowAllClicked);
    connect(ui->back, &QPushButton::clicked, this, &SearchBookPage::onBackClicked);

    connect(networkClient, &NetworkClient::responseReceived,
            this, &SearchBookPage::onResponseReceived);
}

SearchBookPage::~SearchBookPage() {
    delete ui;
}

void SearchBookPage::onSearchClicked() {
    QString title = ui->linetitle->text().trimmed();
    QString author = ui->lineauthor->text().trimmed();
    QString genre = ui->comboBox->currentText();

    if (!title.isEmpty()) {
        requestSearch("title", title);
    } else if (!author.isEmpty()) {
        requestSearch("author", author);
    } else if (genre != "All") {
        requestSearch("genre", genre);
    } else {
        requestAllBooks();
    }
}

void SearchBookPage::onShowAllClicked() {
    ui->linetitle->clear();
    ui->lineauthor->clear();
    ui->comboBox->setCurrentIndex(0);
    requestAllBooks();
}

void SearchBookPage::onBackClicked() {
    emit backRequested();
}

void SearchBookPage::requestSearch(const QString& searchBy, const QString& query)
{
    QJsonObject request;
    request["action"] = "searchBooks";
    request["searchBy"] = searchBy;
    request["query"] = query;
    networkClient->sendRequest(request);
}

void SearchBookPage::requestAllBooks()
{
    QJsonObject request;
    request["action"] = "getAllBooks";
    networkClient->sendRequest(request);
}

void SearchBookPage::onResponseReceived(const QJsonObject& response) {
    QString action = response["action"].toString();
    if (action != "searchBooks" && action != "getAllBooks") return;
    if (response["status"].toString() != "ok") return;

    emit showResultsRequested(response["books"].toArray());
}