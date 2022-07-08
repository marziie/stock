#include "inputing.h"
#include "ui_inputing.h"

Inputing::Inputing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inputing)
{
    ui->setupUi(this);
}

Inputing::~Inputing()
{
    delete ui;
}

void Inputing::setLabel(QString s)
{
    ui->label->setText(s);
}

QString Inputing::mytext()
{
    return ui->textEdit->toPlainText();
}
