#pragma once
#include <QString>
#include <QDate>
#include <QJsonObject>
#include <memory>

class Discount;

class Book {
private:
    int bookId;
    QString title;
    QString author;
    QString genre;
    QString description;
    double price;
    QString coverImagePath;
    QString pdfFilePath;
    int publisherId;
    bool isActive;
    double averageRating;
    int salesCount;
    QDate publishDate;
    std::shared_ptr<Discount> discount;

public:
    // Book();
    Book(int bookId, const QString& title, const QString& author, const QString& genre,
         const QString& description, double price, const QString& coverImagePath,
         const QString& pdfFilePath, int publisherId, const QDate& publishDate = QDate::currentDate());


    int getId() const;
    int getBookId() const;
    QString getTitle() const;
    QString getAuthor() const;
    QString getGenre() const;
    QString getDescription() const;
    double getPrice() const;
    QString getCoverImagePath() const;
    QString getPdfFilePath() const;
    int getPublisherId() const;
    bool getIsActive() const;
    double getAverageRating() const;
    int getSalesCount() const;
    QDate getPublishDate() const;
    std::shared_ptr<Discount> getDiscount() const;
    double getFinalPrice() const;

    void setTitle(const QString& title);
    void setAuthor(const QString& author);
    void setGenre(const QString& genre);
    void setDescription(const QString& description);
    void setPrice(double price);
    void setCoverImagePath(const QString& path);
    void setPdfFilePath(const QString& path);
    void setIsActive(bool active);
    void setAverageRating(double rating);
    void incrementSalesCount();
    void setDiscount(std::shared_ptr<Discount> newDiscount);


    QJsonObject toJson() const;
    static Book fromJson(const QJsonObject& obj);
};