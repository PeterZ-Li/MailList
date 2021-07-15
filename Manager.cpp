#include"Manager.h"
#include<iomanip>

Manager::Manager(int id) :ID(id)
{}

Manager::~Manager()
{
}

void Manager::ShowMenu()
{
    system("cls");
    cout << "==========================欢迎使用通讯录管理系统：==========================" << endl;
    cout << "                              1.显示全部联系人" << endl;
    cout << "                              2.添加联系人" << endl;
    cout << "                              3.查找联系人" << endl;
    cout << "                              4.删除联系人" << endl;
    cout << "                              5.修改联系人信息" << endl;
    cout << "                              0.退出登录" << endl;
}

void Manager::PrintAllRecode()
{
    DBUtil db;
    if (!db.isOpen)
    {
        db.OpenDB();
    }
    cin.get();
    int resu = db.SelectAllPerson(Allpersons, ID);
    if (resu == 2)
    {
        cout << "数据库连接失败" << endl;
    }
    else if (resu == 1)
    {
        //格式化输出
        cout << setw(15) << setfill(' ') << "NAME" << left;
        cout << setw(15) << setfill(' ') << "Location" << left;
        cout << setw(15) << setfill(' ') << "QQID" << left;
        cout << setw(15) << setfill(' ') << "PHONEID" << left << endl;
        //循环输出名字，电话号码，QQ和地址
        for (int n = 0; n < (int)Allpersons.size(); n++)
        {
            Person person = Allpersons.at(n);//取出第n个元素
            cout << setw(15) << setfill(' ') << person.PName << left;
            cout << setw(15) << setfill(' ') << person.Location << left;
            cout << setw(15) << setfill(' ') << person.QQID << left;
            cout << setw(15) << setfill(' ') << person.PhoneID << left << endl;
        }
        Allpersons.clear();
        //vector <Person>().swap(Allpersons);//清空搜索后储存的信息，以防止后续查找得到的信息与前面的重复。
    }
    else if (resu == 0)
    {
        cout << "暂无联系人" << endl;
    }
    cout << "返回主菜单请按ENTER" << endl;
    cin.get();
    return;
}

void Manager::AddPerson()
{
    DBUtil db;
    if (!db.isOpen)
    {
        db.OpenDB();
    }
    cin.get();
    Person hb;
    hb.setPName();
    //查找，看联系人是否存在，以名字作为唯一依据
    if (db.isOpen) {
        mysql_query(&db.myCont, "SET NAMES GBK");
        string sql = "select * from person where name = '" + hb.getPName() + "' and user_id='" + to_string(ID) + "'";
        int res = mysql_query(&db.myCont, sql.c_str());
        if (res==0)
        {
            MYSQL_RES* result = mysql_store_result(&db.myCont);
            if (result->row_count>0)
            {
                cout << "联系人已存在" << endl;
            }
            else
            {
                hb.setLocation();
                hb.setQQID();
                hb.setPhoneID();
                if (db.AddPerson(hb, ID))
                {
                    cout << "添加成功" << endl;
                }
            }
        }
    }
    cout << "返回主菜单请按ENTER" << endl;
    cin.get();
}

void Manager::SelectPersonByName()
{
    DBUtil db;
    if (!db.isOpen)
    {
        db.OpenDB();
    }
    string na;
    cout << "请输入你想查找的联系人的姓名：";
    cin.get();
    getline(cin, na);
    int resu = db.SelectPersonByName(na, ID, Allpersons);
    if (resu == 2)
    {
        cout << "数据库连接失败！" << endl;
    }
    else if (resu == 1)
    {
        //格式化输出
        cout << setw(15) << setfill(' ') << "Name" << left;
        cout << setw(15) << setfill(' ') << "Location" << left;
        cout << setw(15) << setfill(' ') << "QQID" << left;
        cout << setw(15) << setfill(' ') << "PHONEID" << left << endl;
        //输出名字，电话号码，QQ和地址
        Person person = Allpersons.at(0);//取出第n个元素
        cout << setw(15) << setfill(' ') << person.PName << left;
        cout << setw(15) << setfill(' ') << person.Location << left;
        cout << setw(15) << setfill(' ') << person.QQID << left;
        cout << setw(15) << setfill(' ') << person.PhoneID << left << endl;
        Allpersons.clear();
        //vector <Person>().swap(Allpersons);//清空搜索后储存的信息，以防止后续查找得到的信息与前面的重复。
    }
    else if (resu == 0)
    {
        cout << "该联系人不存在" << endl;
    }
    cout << "返回主菜单请按ENTER" << endl;
    cin.get();
}

void Manager::DeletePerson()
{
    DBUtil db;
    if (!db.isOpen)
    {
        db.OpenDB();
    }
    string na;
    cout << "请输入你想删除的联系人的名字：";
    cin.get();
    getline(cin, na);
    if (db.SelectPersonByName(na, ID, Allpersons) == 2)
    {
        cout << "数据库连接失败！" << endl;
    }
    else if (db.SelectPersonByName(na, ID,Allpersons) == 1)
    {
        //格式化输出
        cout << setw(15) << setfill(' ') << "NAME" << left;
        cout << setw(15) << setfill(' ') << "Location" << left;
        cout << setw(15) << setfill(' ') << "QQID" << left;
        cout << setw(15) << setfill(' ') << "PHONEID" << left << endl;
        //输出名字，电话号码，QQ和地址
        Person person = Allpersons.at(0);//取出第n个元素
        cout << setw(15) << setfill(' ') << person.PName << left;
        cout << setw(15) << setfill(' ') << person.Location << left;
        cout << setw(15) << setfill(' ') << person.QQID << left;
        cout << setw(15) << setfill(' ') << person.PhoneID << left << endl;
        Allpersons.clear();
        //vector <Person>().swap(Allpersons);//清空搜索后储存的信息，以防止后续查找得到的信息与前面的重复。
        cout << "你确定要删除吗？（y/n）：";
        string judge;
        cin >> judge;
        if (judge == "y")
        {
            if (db.DeletePersonByName(na,ID)==1)
            {
                cout << "删除成功" << endl;
                cin.get();
            }
            else
            {
                cout << "数据库连接失败" << endl;
            }
        }
    }
    else if (db.SelectPersonByName(na,ID, Allpersons) == 0)
    {
        cout << "该联系人不存在" << endl;
    }
    cout << "返回主菜单请按ENTER" << endl;
    cin.get();
}

void Manager::Revise()
{
    DBUtil db;
    if (!db.isOpen)
    {
        db.OpenDB();
    }
    cout << "请输入你想修改的联系人的名字：";
    cin.get();
    string na;
    getline(cin, na);
    if (db.SelectPersonByName(na,ID, Allpersons) == 2)
    {
        cout << "数据库连接失败！" << endl;
    }
    else if (db.SelectPersonByName(na, ID,Allpersons) == 1)
    {
        //格式化输出
        cout << setw(15) << setfill(' ') << "NAME" << left;
        cout << setw(15) << setfill(' ') << "Location" << left;
        cout << setw(15) << setfill(' ') << "QQID" << left;
        cout << setw(15) << setfill(' ') << "PHONEID" << left << endl;
        //输出名字，电话号码，QQ和地址
        Person person = Allpersons.at(0);//取出第n个元素
        cout << setw(15) << setfill(' ') << person.PName << left;
        cout << setw(15) << setfill(' ') << person.Location << left;
        cout << setw(15) << setfill(' ') << person.QQID << left;
        cout << setw(15) << setfill(' ') << person.PhoneID << left << endl;
        Allpersons.clear();
        vector <Person>().swap(Allpersons);//清空搜索后储存的信息，以防止后续查找得到的信息与前面的重复。
        cout << "你确定要修改吗？（y/n）：";
        string judge;
        cin >> judge;
        if (judge == "y")
        {
            cin.get();
            Person person;
            cout << "请输入修改后的信息：" << endl;
            person.setPName();
            person.setLocation();
            person.setQQID();
            person.setPhoneID();
            if (db.RevisePersonByName(person,ID))
            {
                cout << "修改成功" << endl;
            }
            else
            {
                cout << "数据库连接失败！" << endl;
            }
        }
    }
    else if (db.SelectPersonByName(na,ID, Allpersons) == 0)
    {
        cout << "该联系人不存在" << endl;
    }
    cout << "返回主菜单请按ENTER" << endl;
    cin.get();
}
