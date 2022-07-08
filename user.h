#ifndef USER_H
#define USER_H
#include "inputing.h"

class User
{
public:
    User()
    {
        password = "";
        nationalcode = "";
        money = 0;
    }

    void login()
    {
        username = Inputing::set_string("Username", 10);
        password = Inputing::set_string("Password", 20);
        if (password.size() != 0)
            is_login = true;
    }

    void get_console()
    {
        fullname = Inputing::set_string("FirstName and lastName", 50);
        nationalcode = Inputing::set_string("Nationall code", 10);
        shaba = Inputing::set_string("shaba code (must start with 'IR...') :", 12);
        if (shaba.size() < 3 || shaba[0] != 'I' || shaba[1] != 'R')
            throw QString("shaba must start with 'IR...' ");
        money = Inputing::set_string("Enter your money value", 17).toLongLong();
        // todo set money
        set_inf = true;
    }


    void withraw()
    {
        long long money = Inputing::set_string("enter money value you want withraw", 17).toLongLong();
        if (this->money - money < -1000000)
            throw QString("you cant Debit greater than 1 milion");
        this->money -= money;
    }

    void charge()
    {
        long long money = Inputing::set_string("enter money value you want charge", 17).toLongLong();
        this->money += money;
    }

    void is_login_inf()
    {
        if (!is_login)
            throw QString("you must set information first");
        if (!set_inf)
            throw QString("you must create user first");
    }

    QString username;
    QString password;
    QString fullname;
    QString nationalcode;
    QString shaba;

    long long money;
    long long stocks_value;
    bool set_inf = false;
    bool is_login = false;
};


#endif // USER_H
