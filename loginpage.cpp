#include "loginpage.h"
#include "ui_loginpage.h"

loginpage::loginpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginpage)
{
    ui->setupUi(this);
}

loginpage::~loginpage()
{
    delete ui;
}
