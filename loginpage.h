#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class loginpage;
}
QT_END_NAMESPACE

class loginpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginpage(QWidget *parent = nullptr);
    ~loginpage() override;

private:
    Ui::loginpage *ui;
};
#endif // LOGINPAGE_H
