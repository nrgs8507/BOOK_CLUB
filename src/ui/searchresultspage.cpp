#include "searchresultspage.h"
#include "bookcardwidget.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>

SearchResultsPage::SearchResultsPage(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* outerLayout = new QVBoxLayout(this);

    QPushButton* backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &SearchResultsPage::backRequested);
    outerLayout->addWidget(backButton);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget* contentWidget = new QWidget();
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->addStretch(); // نگه‌داشتن کارت‌ها بالای صفحه، نه پخش‌شده در کل ارتفاع

    scrollArea->setWidget(contentWidget);
    outerLayout->addWidget(scrollArea);
}

void SearchResultsPage::clearBooks() {
    while (contentLayout->count() > 1) { // آیتم آخر همیشه stretch است، نگهش می‌داریم
        QLayoutItem* item = contentLayout->takeAt(0);
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }
}

void SearchResultsPage::setBooks(const QJsonArray& books) {
    clearBooks();
    for (const QJsonValue& val : books) {
        BookCardWidget* card = new BookCardWidget(val.toObject());
        contentLayout->insertWidget(contentLayout->count() - 1, card);
    }
}
