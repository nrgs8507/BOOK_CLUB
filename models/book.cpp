#include "book.h"
#include "discount.h"

Book:://Book()
    //: bookId(-1), price(0.0), publisherId(-1), isActive(true),
    //averageRating(0.0), salesCount(0), publishDate(QDate::currentDate()), discount(nullptr) {}

Book::Book(int bookId, const QString& title, const QString& author, const QString& genre,
           const QString& description, double price, const QString& coverImagePath,
           const QString& pdfFilePath, int publisherId, const QDate& publishDate)
    : bookId(bookId), title(title), author(author), genre(genre), description(description),
    price(price), coverImagePath(coverImagePath), pdfFilePath(pdfFilePath),
    publisherId(publisherId), isActive(true), averageRating(0.0), salesCount(0),
    publishDate(publishDate), discount(nullptr) {}

int Book::getId() const { return bookId; }
int Book::getBookId() const { return bookId; }
QString Book::getTitle() const { return title; }
QString Book::getAuthor() const { return author; }
QString Book::getGenre() const { return genre; }
QString Book::getDescription() const { return description; }
double Book::getPrice() const { return price; }
QString Book::getCoverImagePath() const { return coverImagePath; }
QString Book::getPdfFilePath() const { return pdfFilePath; }
int Book::getPublisherId() const { return publisherId; }
bool Book::getIsActive() const { return isActive; }
double Book::getAverageRating() const { return averageRating; }
int Book::getSalesCount() const { return salesCount; }
QDate Book::getPublishDate() const { return publishDate; }
std::shared_ptr<Discount> Book::getDiscount() const { return discount; }

double Book::getFinalPrice() const {
    if (discount && discount->isActive()) {
        return discount->getDiscountedPrice(price);
    }
    return price;
}

void Book::setTitle(const QString& t) { title = t; }
void Book::setAuthor(const QString& a) { author = a; }
void Book::setGenre(const QString& g) { genre = g; }
void Book::setDescription(const QString& d) { description = d; }
void Book::setPrice(double p) { price = p; }
void Book::setCoverImagePath(const QString& path) { coverImagePath = path; }
void Book::setPdfFilePath(const QString& path) { pdfFilePath = path; }
void Book::setIsActive(bool active) { isActive = active; }
void Book::setAverageRating(double rating) { averageRating = rating; }
void Book::incrementSalesCount() { salesCount++; }
void Book::setDiscount(std::shared_ptr<Discount> newDiscount) { discount = newDiscount; }

QJsonObject Book::toJson() const {
    QJsonObject obj;
    obj["bookId"] = bookId;
    obj["title"] = title;
    obj["author"] = author;
    obj["genre"] = genre;
    obj["description"] = description;
    obj["price"] = price;
    obj["coverImagePath"] = coverImagePath;
    obj["pdfFilePath"] = pdfFilePath;
    obj["publisherId"] = publisherId;
    obj["isActive"] = isActive;
    obj["averageRating"] = averageRating;
    obj["salesCount"] = salesCount;
    obj["publishDate"] = publishDate.toString(Qt::ISODate);

    return obj;
}


Book Book::fromJson(const QJsonObject& obj) {
    Book book(
        obj["bookId"].toInt(),
        obj["title"].toString(),
        obj["author"].toString(),
        obj["genre"].toString(),
        obj["description"].toString(),
        obj["price"].toDouble(),
        obj["coverImagePath"].toString(),
        obj["pdfFilePath"].toString(),
        obj["publisherId"].toInt(),
        QDate::fromString(obj["publishDate"].toString(), Qt::ISODate)
        );
    book.isActive = obj["isActive"].toBool();
    book.averageRating = obj["averageRating"].toDouble();
    book.salesCount = obj["salesCount"].toInt();
    return book;
}