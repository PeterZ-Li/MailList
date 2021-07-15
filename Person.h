#pragma once
#include "User.h"
class Person :public User {
public:
	string PName;//名字
	string PhoneID;//电话
	string QQID;//QQ
	string Location;//工作单位
public:
	void setPName();
	void setPhoneID();
	void setQQID();
	void setLocation();
	string getPName();
	string getLocation();
	string getQQID();
	string getPhoneID();
};