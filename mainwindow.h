#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_create_user_clicked();

    void on_set_information_clicked();

    void on_withdraw_clicked();

    void on_charge_clicked();

    void on_buy_stock_clicked();

    void on_sell_stock_clicked();

    void on_bascket_clicked();

    void on_stock_list_clicked();

    void load_csv();

    void load_file();

    void on_actionsave_triggered();

    void on_actionsave_and_exit_triggered();

    void save();
private:
    Ui::MainWindow *ui;
    QString currentfile;
};
#endif // MAINWINDOW_H
