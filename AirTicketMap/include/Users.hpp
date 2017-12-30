#ifndef USERS_HPP
#define USERS_HPP

#include"Flight.hpp"
#include"AirTicSystem.hpp"




struct Customer								//顾客信息
{
	Serials_Vec_Type Flight_Serials;	//购买的所有机票（保存流水号）
	string Cus_Name;					//顾客姓名
	string Cus_Pwd;						//顾客密码
	size_t Tic_Bought;						//该顾客名下所购机票数
};
struct Admin
{
	string Admin_Name;
	string Admin_Pwd;
};


class Admin_System {
private:
	map<string, Customer> Customer_Map;
	map<string, Admin> Admin_Map;
public:

	Admin_System(const char * Admin_File,const char * Cus_File_Name);

	bool Is_Admin(string A_Name);

	bool Is_Customer(string C_Name);

	void Admin_Manage(AirTicSystem& Air_Tic_Data);
	int Admin_Choose_Func();

	void Users_Mange(const AirTicSystem& Air_Tic_Data);
	int Users_Choose_Func();

	

	

};




#endif // !USERS_HPP
