#include"Person.h"

void Person::setPName() {
	cout << "请输入联系人姓名：" ;
	getline(cin, PName);
}
void Person::setPhoneID() {
	cout << "请输入联系人电话号码：" ;
	A:getline(cin, PhoneID);
	if (PhoneID.size() > 11)
	{
		cout << "不能超过11位！请重新输入！" << endl;
		goto A;
	}
}
void Person::setQQID() {
	cout << "请输入联系人QQ号：" ;
	B:getline(cin, QQID);
	if (QQID.size() > 12)
	{
		cout << "不能超过12位！请重新输入！" << endl;
		goto B;
	}
}
void Person::setLocation() {
	cout << "请输入联系人工作场所：" ;
	getline(cin, Location);
}
string Person::getPName() {
	return PName;
}
string Person::getLocation() {
	return Location;
}
string Person::getPhoneID() {
	return PhoneID;
}
string Person::getQQID() {
	return QQID;
}