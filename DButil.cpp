#include<iostream>
#include"DButil.h"
using namespace std;

DBUtil::DBUtil()
{
	Username = "root";
	Password = "lipeize20020409";
	Host = "localhost";
	Database = "maillist";
	nPort = 3306;
	isOpen = false;
}

DBUtil::~DBUtil()
{
	CloseDB();
}

bool DBUtil::OpenDB()
{
	mysql_init(&myCont);
	if (!mysql_real_connect(&myCont, Host.c_str(), Username.c_str(), Password.c_str(),
		Database.c_str(), nPort, NULL, 0))
	{
		isOpen = false;
		//cout << "Fail" << endl;
		return false;
	}
	else
	{
		isOpen = true;
		//cout << "Succeed"<<endl;
		return true;
	}
}

bool DBUtil::CloseDB()
{
	mysql_close(&myCont);
	return true;
}

//根据用户名和密码获得用户信息
User  DBUtil::ReadUser(string strUserName, string strUserPWD)
{
	User user;
	int res;
	string sql;
	if (isOpen)
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
		sql += "select * from user where name='" + strUserName + "' and password='" + strUserPWD + "'";
		res = mysql_query(&myCont, sql.c_str());//查询是否有这个用户
		if (!res)//语句正确
		{
			result = mysql_store_result(&myCont);//保存查询到的数据到result
			if (result->row_count > 0)
			{
				sql_row = mysql_fetch_row(result);
				user.m_nID = atoi(sql_row[0]);//字符串转换为数字
				user.m_strName = sql_row[1];
				if (result != NULL)
				{
					mysql_free_result(result);//释放结果资源
				}
				return user;
			}
			else//否则就没有这个用户，或用户名、密码错误。
			{
				user.m_nID = -1;
				if (result != NULL)
				{
					mysql_free_result(result);//释放结果资源
				}
				return user;
			}
		}
	}
	else
	{
		cout << "数据库链接失败！" << endl;
	}
	return user;
}

//注册功能
void DBUtil::SignUser(string mName, string mpassword) {
	string sql;
	if (isOpen) 
	{
	    B:cout << "请输入用户名：" << endl;//重名怎么办
		getline(cin, mName);
		if (mName.size()>20)
		{
			cout << "不能超过20位！请重新输入！" << endl;
			goto B;
		}
		mysql_query(&myCont, "SET NAMES GBK");
		sql = "select * from user where name = '" + mName + "'";
		int res = mysql_query(&myCont, sql.c_str());
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result->row_count > 0)
			{
				cout << "用户名已存在" << endl;
				goto B;
			}
			else
			{
				goto A;
			}
		}
	    A:cout << "请输入密码：" << endl;
		getline(cin, mpassword);
		string p1;
		cout << "请再次输入密码:" << endl;
		getline(cin, p1);
		if (p1 != mpassword) {
			cout << "两次密码不一致，请重新输入。" << endl;
			goto A;
		}
		//int id=1;//id随机生成todo
		mysql_query(&myCont, "SET NAMES GBK");
		//id用null即可自动增加
		sql += "insert into user(id,name,password)values(null,'" + mName + "','" + mpassword + "')";
		mysql_query(&myCont, sql.c_str());
	}
	else
	{
		cout << "数据库连接失败!" << endl;
	}
}

//新增联系人
bool DBUtil::AddPerson(Person person, int id)
{
	string sql;
	if (isOpen)
	{
		mysql_query(&myCont, "SET NAMES GBK");
		sql += "insert into person (name,workplace,QQID,PhoneID,user_id) values('" + person.getPName() + "','" + person.getLocation() + "','" + person.getQQID() + "','" + person.getPhoneID() + "','"+to_string(id)+"')";
		bool res = mysql_query(&myCont, sql.c_str());
		return res;
	}
	return false;
}

//显示所有联系人
int DBUtil::SelectAllPerson(vector<Person>& persons,int id)
{
	int res;
	string sql;
	if (isOpen)
	{
		mysql_query(&myCont, "SET NAMES GBK");
		sql = "select * from person where user_id = '" + to_string(id) + "'";
		res = mysql_query(&myCont, sql.c_str());
		//cout << res << endl;有数据返回0
		if (res==0)//语句执行正确
		{
			result = mysql_store_result(&myCont);
			if (result->row_count>0)
			{
				while (sql_row = mysql_fetch_row(result))
				{
					Person person;
					person.PName = sql_row[0];
					person.Location = sql_row[1];
					person.QQID = sql_row[2];
					person.PhoneID = sql_row[3];
					persons.push_back(person);
				}
				//cout<<"查询成功"<<endl;
				if (result != NULL)
				{
					mysql_free_result(result);
				}
				return 1;
			}
			else
			{
				//cout<<"暂无联系人"<<endl;
				return 0;
			}
		}
	}
	else
	{
		//cout<<"数据库连接失败"<<endl;
		return 2;
	}
	return 2;
}

//通过名字选人
int DBUtil::SelectPersonByName(string Name,int id ,vector<Person>& p) {
	int res;
	string sql;
	if (isOpen) {
		mysql_query(&myCont, "SET NAMES GBK");
		sql += "select * from person where name = '" + Name + "'"+"and user_id = '"+to_string(id)+"'";
		res = mysql_query(&myCont, sql.c_str());
		if (res==0)
		{
			result = mysql_store_result(&myCont);
			if (result->row_count>0)
			{
				while (sql_row = mysql_fetch_row(result))
				{
					Person pe;
					pe.PName = sql_row[0];
					pe.Location = sql_row[1];
					pe.QQID = sql_row[2];
					pe.PhoneID = sql_row[3];
					p.push_back(pe);
				}
				if (result != NULL)
				{
					mysql_free_result(result);
				}
				return 1;
			}
			else
			{
				//cout<<"联系人不存在！"<<endl;
				return 0;
			}
		}

	}
	else
	{
		//cout << "连接数据库失败！" << endl;
		return 2;
	}
	return 2;
}

/*bool DBUtil::SelectPersonByID(string ID, vector<Person>& persons)
{
	int res;
	string sql;
	if (isOpen)
	{
		mysql_query(&myCont, "SET NAMES GBK");
		sql += "select * from person where PhoneID=";
		sql += ID;
		res = mysql_query(&myCont, sql.c_str());
		if (!res)
		{
			result = mysql_store_result(&myCont);
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))
				{
					Person person;
					person.PName = sql_row[0];
					person.Location = sql_row[1];
					person.QQID = sql_row[2];
					person.PhoneID = sql_row[3];
					persons.push_back(person);
				}
				cout << "查询成功" << endl;
				if (result != NULL)
				{
					mysql_free_result(result);
				}
				return true;
			}
		}
		else
		{
			cout << "查询失败" << endl;
			return false;
		}
	}
	else
	{
		cout << "数据库连接失败" << endl;
		return false;
	}
	return false;
}*/

int DBUtil::DeletePersonByName(string Name,int id)
{
	int res;
	string sql;
	if (isOpen)
	{
		mysql_query(&myCont, "SET NAMES GBK");
		sql = "delete from person where name = '" + Name + "' and user_id = '" + to_string(id) + "'";
		//sql += Name;
		res = mysql_query(&myCont, sql.c_str());
		return 1;
	}
	else
	{
		//cout << "数据库连接失败" << endl;
		return 0;
	}
}

bool DBUtil::RevisePersonByName(Person& person,int id)
{
	bool res;
	string sql;
	if (isOpen)
	{
		mysql_query(&myCont, "SET NAMES GBK");
		sql += "update person set name='" + person.getPName() + "',workplace='" + person.getLocation() +
			"',QQID='" + person.getQQID() + "',PhoneID='" + person.getPhoneID() + "'where name='" + person.getPName() + "'and user_id='" + to_string(id) + "'";
		res = mysql_query(&myCont, sql.c_str());
		return true;
	}
	else
	{
		return false;
	}
}