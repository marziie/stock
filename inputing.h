#ifndef INPUTING_H
#define INPUTING_H

#include <QDialog>

namespace Ui {
class Inputing;
}

class Inputing : public QDialog
{
    Q_OBJECT

public:
    explicit Inputing(QWidget *parent = nullptr);
    ~Inputing();

    QString mytext();

    void setLabel(QString s);

    static int show_inputing(Inputing & i)
    {
        i.show();
        return i.exec();
    }

    static QString get_from_user(QString label)
    {
        Inputing i;
        i.setLabel(label);
        show_inputing(i);
        return i.mytext();
    }

    static QString set_string(QString label, int size)
    {
        QString tmp = Inputing::get_from_user("enter " + label);
        if (tmp.size() > size)
            throw QString("your " + label + " size must be less from" + QString(size));
        return tmp;
    }

private:
    Ui::Inputing *ui;
};

#endif // INPUTING_H
