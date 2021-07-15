#include"DButil.h"
#include<iostream>
#include"User.h"
#include"Manager.h"
using namespace std;
int main()
{
	string strUserName = "";
	string strUserPWD = "";
	bool isLogin = false;
	User user;
	DBUtil dbUtil;
	dbUtil.OpenDB();
A:cout << "按y进行注册" << endl;
	cout << "                          请输入用户名：" << endl;
	getline(cin, strUserName);
	if (strUserName == "y")
	{
		dbUtil.SignUser(strUserName, strUserPWD);
		goto A;
	}
	else
	{
		cout << endl;
		cout << "请输入密码:";
		strUserPWD = User::Password();
		user = dbUtil.ReadUser(strUserName, strUserPWD);
	}
	while (user.m_nID == -1)
	{
		cout << "用户名或者密码错误，请重新输入,按任意键继续..." << endl;
		cin.get();
		system("cls");
		cout << "                          请输入用户名：";
		getline(cin,strUserName);
		cout << endl;
		cout << "                          请输入密码：";
		getline(cin, strUserPWD);
		cout << endl;
		user = dbUtil.ReadUser(strUserName, strUserPWD);
	};
	isLogin = true;
	Manager a(user.m_nID);//需使用user的id，以利用数据库的外键，来达到用户和通讯录一一对应的关系。
	int command = -1;		//选择命令
	while (isLogin)
	{
		a.ShowMenu();
		cout << "请选择命令：";
		cin >> command;
		switch (command)
		{
		case 0:
			isLogin = false;
			break;
		case 1:
			a.PrintAllRecode();
			break;
		case 2:
			a.AddPerson();
			break;
		case 3:
			a.SelectPersonByName();
			break;
		case 4:
			a.DeletePerson();
			break;
		case 5:
			a.Revise();
			break;
		default:
			break;
		}
	}
	return 0;
}