#include"User.h"
using namespace std;
User::User()
{
}


User::~User()
{
}

string User::Password() {
    char c;
    int count = 0;
    string temp;
    while (true)
    {
        c = _getch();
        if (c == '\b')
        {
            if (count != 0)
            {
                cout << '\b';
                cout << ' ';
                cout << '\b';
                count--;
            }
            else;
        }
        else if (c != 13)
        {
            temp = temp + c;
            cout << "";
            count++;
        }
        else break;
    }
    cout << endl;
    return temp;
}