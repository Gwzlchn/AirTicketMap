#ifndef USERS_HPP
#define USERS_HPP

#include"Flight.hpp"
#include"AirTicSystem.hpp"


typedef int(*Check_Ptr)(int);


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


	void Read_A_And_C_From_CSV(const char * Admin_File, const char * Cus_File);

	Admin_System(const char * Admin_File,const char * Cus_File_Name,const char* Flight_File_Name);

	bool Is_Admin_Pwd_Correct(string A_Name, string A_Pwd);

	bool Is_Cus_Pwd_Correct(string C_Name, string C_Pwd);

	bool Is_Admin(string A_Name);

	bool Is_Customer(string C_Name);

	void Admin_Manage(AirTicSystem& Air_Tic_Data);
	int Admin_Choose_Func();

	void Users_Manage(const AirTicSystem & Air_Tic_Data);


	int Users_Choose_Func();

	int Check_Choose_All_Num();

	int A_OR_C_Choose(int Choice);

	int For_All_Choose(Check_Ptr Ptr);



	void First_Identity(AirTicSystem & Air_Tics);

	

	

};




#endif // !USERS_HPP
