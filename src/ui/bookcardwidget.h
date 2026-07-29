#pragma once
#include <QWidget>
#include <QJsonObject>

class QLabel;
class QFrame;

class BookCardWidget : public QWidget {
    Q_OBJECT

public:
    explicit BookCardWidget(const QJsonObject& book, QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QJsonObject bookData;
    QLabel* coverLabel;
    QLabel* titleLabel;
    QFrame* detailsFrame;
    bool expanded;

    void toggleDetails();
};