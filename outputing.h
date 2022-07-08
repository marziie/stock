#ifndef OUTPUTING_H
#define OUTPUTING_H

#include <QDialog>

namespace Ui {
class Outputing;
}

class Outputing : public QDialog
{
    Q_OBJECT

public:
    explicit Outputing(QWidget *parent = nullptr);
    ~Outputing();

    void set_label(QString label);

    void set_text(QString text);

    static int show_outputing(QString label, QString text)
    {
        Outputing i;
        i.set_label(label);
        i.set_text(text);
        i.show();
        return i.exec();
    }

private:
    Ui::Outputing *ui;
};

#endif // OUTPUTING_H
