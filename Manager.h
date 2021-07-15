#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "Person.h"
#include "DButil.h"
using namespace std;

class Manager :public Person//继承Person
{
public:
    int ID;
    Manager(int id);
    ~Manager();
    void ShowMenu();//显示菜单
    void PrintAllRecode();//显示记录
    void AddPerson();//增加联系人
    void SelectPersonByName();//通过名字选人
    void DeletePerson();//删除联系人
    void Revise();//修改联系人信息
    //void Exit();//退出登录
    vector<Person> Allpersons;
};
