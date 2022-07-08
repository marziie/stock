#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputing.h"
#include "outputing.h"
#include "user.h"
#include "stock.h"
#include "inputing.h"

#include <fstream>
#include <string>
#include <QVector>
#include <sstream>
#include <QTextCodec>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    currentfile = Inputing::set_string("enter dir", 100);
    this->load_csv();
    try {
        this->load_file();
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

User u;
QVector<Stock> stocks;
//***********************************************


void MainWindow::load_file()
{
    QFile file(currentfile + "\\Data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw QString("cant load file from Data.txt");
    }

    QTextStream in(&file);
    QString word;
    while (!in.atEnd()) {
        word = in.readLine();
        if (word == "1.")
        {
            word = in.readLine();
            u.username = word;
            word = in.readLine();
            u.password = word;
            u.is_login = true;
        }
        else if (word == "2.")
        {
            word = in.readLine();
            u.fullname = word;
            word = in.readLine();
            u.nationalcode = word;
            word = in.readLine();
            u.shaba = word;
            word = in.readLine();
            u.money = word.toLongLong();
            u.set_inf = true;
        }
        else if (word == "bascket")
        {
            while (!in.atEnd())
            {
                word = in.readLine();
                int andis = word.toInt();
                word = in.readLine();
                stocks[andis].value = word.toLongLong();
            }
        }
    }
    file.close();
}

void MainWindow::save()
{
    QFile file(currentfile + "\\Data.txt");
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream myfile(&file);
        if (u.is_login)
            myfile << "1.\n" << u.username << '\n' << u.password << '\n';
        if (u.set_inf)
            myfile << "2.\n" <<
            u.fullname << '\n' <<
            u.nationalcode << '\n' <<
            u.shaba << '\n' <<
            u.money << '\n';
        myfile << "bascket\n";
        for (int i = 0; i < stocks.size(); i++) {
            if (stocks[i].value > 0) {
                myfile << i << '\n' << stocks[i].value << '\n';
            }
        }
        file.close();
    }
    else
        throw QString("cant save in file Data.txt");
}

void MainWindow::load_csv()
{
    QString ans, string;
    QFile file(currentfile + "\\stock_market_data.csv");
    if (!file.open(QIODevice::ReadOnly))
    {
        throw QString("cant open file");
    }

    QByteArray _line = file.readLine();
    //QStringList wordList;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        //wordList.append(line.split(',').first());
        QTextCodec *codec = QTextCodec::codecForName("KOI8-R");
        string = codec->toUnicode(line);
        ans += string;
        if (string.split(',')[2].count('"') == 0)
        {
            stocks.append(Stock(
                    string.split(',')[1],
                    string.split(',')[2],
                    string.split(',')[3].toLongLong(),
                    string.split(',')[4].toLongLong()
            ));
        }
        else
        {
            stocks.append(Stock(
                    string.split(',')[1],
                    string.split(',')[2] + string.split(',')[3],
                    string.split(',')[4].toLongLong(),
                    string.split(',')[5].toLongLong()
            ));
        }
    }
}

void MainWindow::on_create_user_clicked()
{
    try {
        u.login();
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
}

void MainWindow::on_set_information_clicked()
{
    try {
        if (!u.is_login)
            throw QString("you must create user first");
        u.get_console();
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
}

void MainWindow::on_withdraw_clicked()
{
    try {
        u.is_login_inf();
        u.withraw();
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
}

void MainWindow::on_charge_clicked()
{
    try {
        u.is_login_inf();
        u.charge();
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
}

void MainWindow::on_buy_stock_clicked()
{
    try {
        u.is_login_inf();
        QString symbol = Inputing::set_string("enter symbol", 5);
        long long value = Inputing::set_string("enter value", 9).toLongLong();
        for (int i = 0; i < stocks.size(); i++)
        {
            if (stocks[i].symbol == symbol)
            {
                if (stocks[i].price * value > u.money)
                    throw QString("you have not enough money to buy this stock");
                u.money -= stocks[i].price * value;
                stocks[i].value += value;
                return;
            }
        }
        throw QString("the symbol name is not in stock list");
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
}

void MainWindow::on_sell_stock_clicked()
{
    try {
        u.is_login_inf();
        QString symbol = Inputing::set_string("enter symbol", 5);
        long long value = Inputing::set_string("enter value", 9).toLongLong();
        for (int i = 0; i < stocks.size(); i++)
        {
            if (stocks[i].symbol == symbol)
            {
                if (stocks[i].value < value)
                    throw QString("you have not this value from this stock in bascket");
                stocks[i].value -= value;
                u.money += stocks[i].price * value;
                return;
            }
        }
        throw QString("the symbol name is not in stock list");
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
}

void MainWindow::on_bascket_clicked()
{
    try {
        u.is_login_inf();
        QString ans;
        for (int i = 0; i < stocks.size(); i++) {
            if (stocks[i].value != 0)
                ans += stocks[i].print();
        }
        if (ans.isEmpty())
        {
            ans = "no have stock in your bascket";
        }
        Outputing::show_outputing("stock list", ans);
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
}

void MainWindow::on_stock_list_clicked()
{
    try {
        QString ans;
        for (int i = 0; i < stocks.size(); i++) {

            ans += stocks[i].print();
        }
        Outputing::show_outputing("stock list", ans);
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
}

void MainWindow::on_actionsave_triggered()
{
    try {
        save();
    } catch (QString s) {
        QMessageBox::warning(this, "error", s);
    }
    QMessageBox::warning(this, "save", "save successfully !");
}

void MainWindow::on_actionsave_and_exit_triggered()
{
    save();
    QApplication::quit();
}
