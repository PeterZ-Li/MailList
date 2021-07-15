#pragma once
#include<iostream>
#include<string>
#include<vector>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"mysql.h"
#include"User.h"
#include"Person.h"
class DBUtil
{
public:
	DBUtil();
	~DBUtil();
	bool OpenDB();//打开数据库
	bool CloseDB();//关闭数据库
	User ReadUser(string Name, string PassWord);//读取账户，密码
	void SignUser(string mName, string mpassword);//注册账户，管理权限为默认为普通用户
	bool AddPerson(Person person,int id); //增加联系人 
	int SelectAllPerson(vector<Person>& persons,int id);//选取所有联系人
	int SelectPersonByName(string Name, int id, vector<Person>& p);//通过人名选人
	//bool SelectPersonByID(string ID, vector<Person>& persons);//通过电话号码选人
	int DeletePersonByName(string Name, int id);//通过人名删人
	bool RevisePersonByName(Person& person, int id);//通过人名查找，然后修改信息
	//人名可能会重复，所以只有电话号码删人这种手段//已限制人名唯一
public:
	string Username;//账户名
	string Password;//密码
	string Host;//主机名
	string Database;//数据库
	int nPort;//端口号
	MYSQL myCont;
	MYSQL_RES* result;
	MYSQL_ROW sql_row;
	MYSQL_FIELD* fd;
	bool isOpen;
};