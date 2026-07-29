#include "bookcardwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPixmap>
#include <QByteArray>
#include <QMouseEvent>

BookCardWidget::BookCardWidget(const QJsonObject& book, QWidget* parent)
    : QWidget(parent), bookData(book), expanded(false) {

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // ردیف بالا: عکس + عنوان
    QHBoxLayout* headerLayout = new QHBoxLayout();

    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(70, 100);
    coverLabel->setScaledContents(true);

    QByteArray imgData = QByteArray::fromBase64(book["coverImageBase64"].toString().toUtf8());
    QPixmap pixmap;
    if (!imgData.isEmpty() && pixmap.loadFromData(imgData)) {
        coverLabel->setPixmap(pixmap);
    } else {
        coverLabel->setText("بدون تصویر");
        coverLabel->setAlignment(Qt::AlignCenter);
        coverLabel->setStyleSheet("border: 1px solid gray;");
    }

    titleLabel = new QLabel(book["title"].toString(), this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 12pt;");
    titleLabel->setWordWrap(true);

    headerLayout->addWidget(coverLabel);
    headerLayout->addWidget(titleLabel, 1);

    // بخش جزئیات - در ابتدا مخفی
    detailsFrame = new QFrame(this);
    detailsFrame->setStyleSheet("background-color: #f5f5f5; border-radius: 8px; padding: 8px;");
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsFrame);

    double price = book["price"].toDouble();
    double finalPrice = book["finalPrice"].toDouble();
    double rating = book["averageRating"].toDouble();

    QLabel* priceLabel = new QLabel(detailsFrame);
    if (finalPrice < price) {
        priceLabel->setText(QString("قیمت: %1 (با تخفیف: %2)").arg(price).arg(finalPrice));
    } else {
        priceLabel->setText(QString("قیمت: %1").arg(price));
    }
    detailsLayout->addWidget(priceLabel);

    QLabel* ratingLabel = new QLabel(detailsFrame);
    if (rating >= 0) {
        ratingLabel->setText(QString("امتیاز: %1 از ۵").arg(rating, 0, 'f', 1));
    } else {
        ratingLabel->setText("بدون امتیاز");
    }
    detailsLayout->addWidget(ratingLabel);

    detailsFrame->setVisible(false);

    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(detailsFrame);

    setCursor(Qt::PointingHandCursor);
}

void BookCardWidget::mousePressEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    toggleDetails();
}

void BookCardWidget::toggleDetails() {
    expanded = !expanded;
    detailsFrame->setVisible(expanded);
}