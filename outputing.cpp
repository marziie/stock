#include "outputing.h"
#include "ui_outputing.h"

Outputing::Outputing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Outputing)
{
    ui->setupUi(this);
}

void Outputing::set_label(QString label)
{
    ui->label->setText(label);
}

void Outputing::set_text(QString text)
{
    ui->textBrowser->setText(text);
}

Outputing::~Outputing()
{
    delete ui;
}


