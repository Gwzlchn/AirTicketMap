#include "..\include\Users.hpp"
#include"..\include\Common.hpp"
#include<fstream>
#include<iostream>

using namespace std;

void  Admin_System::Read_A_And_C_From_CSV(const char * Admin_File, const char * Cus_File) {
	ifstream A_File(Admin_File, ios::in);
	ifstream C_File(Cus_File, ios::in);

	if (!A_File)
	{
		cerr << "打开文件失败";
		system("PAUSE");
	}
	if (!C_File) {
		cerr << "打开文件失败";
		system("PAUSE");
	}
	string A_Row;
	getline(A_File, A_Row);//剔除首部
	vector<string> infRow;

	while (A_File.good())
	{
		getline(A_File, A_Row);
		Split_Row(A_Row, ",", infRow);
		if (infRow.size())//有效的数据
		{
			Admin* New_Admin = new Admin;
			New_Admin->Admin_Name = infRow[0];
			New_Admin->Admin_Pwd = infRow[1];
			Admin_Map.insert({ infRow[0], (*New_Admin) });
		}
	}

	string C_Row;
	getline(C_File, C_Row);
	infRow.clear();
	while (C_File.good())
	{
		getline(C_File, C_Row);
		Split_Row(C_Row, ",", infRow);
		if (infRow.size())//有效的数据
		{
			Customer* New_Cus = new Customer;
			New_Cus->Cus_Name = infRow[0];
			New_Cus->Cus_Pwd = infRow[1];
			for (auto iter = infRow.begin() + 3;
				iter != infRow.end(); iter++)
				New_Cus->Flight_Serials.push_back((*iter));
			New_Cus->Tic_Bought = New_Cus->Flight_Serials.size();
			Customer_Map.insert({ infRow[0], (*New_Cus) });

		}
	}

	return;
}



Admin_System::Admin_System(const char * Admin_File, const char * Cus_File,const char* Flight_File_Name)
{
	Read_A_And_C_From_CSV(Admin_File, Cus_File);
	AirTicSystem New_Air_System(Flight_File_Name);
	First_Identity(New_Air_System);


}



//管理员 用户密码是否正确
bool Admin_System::Is_Admin_Pwd_Correct(string A_Name, string A_Pwd) {
	auto A_Iter = Admin_Map.find(A_Name);
	if (A_Iter->second.Admin_Pwd == A_Pwd)
		return true;
	else 
		return false;
}


bool Admin_System::Is_Cus_Pwd_Correct(string C_Name, string C_Pwd) {
	auto C_Iter = Customer_Map.find(C_Name);
	if (C_Iter->second.Cus_Pwd == C_Pwd)
		return true;
	else
		return false;
}


//管理员名 用户名 是否存在
bool Admin_System::Is_Admin(string A_Name)
{
	auto A_Iter = Admin_Map.find(A_Name);
	if (A_Iter != Admin_Map.end())
		return false;
	return true;
}

bool Admin_System::Is_Customer(string C_Name)
{
	auto A_Iter = Customer_Map.find(C_Name);
	if (A_Iter != Customer_Map.end())
		return false;
	return true;
}



void Admin_System::Admin_Manage(AirTicSystem & Air_Tic_Data)
{
}

int Admin_System::Admin_Choose_Func()
{
	return 0;
}

void Admin_System::Users_Manage(const AirTicSystem & Air_Tic_Data)
{
	string a;
	cin >> a;
}

int Admin_System::Users_Choose_Func()
{
	return 0;
}


int Admin_System::Check_Choose_All_Num() {
	string Choose;

	cin >> Choose;
	while (!(All_Is_Num(Choose))) {
		cout << "输入有非数字，请重新输入\t";
		cin >> Choose;
	}

	return stoi(Choose);
}


int  Admin_System::A_OR_C_Choose(int Choice) {

	if (!((Choice) == 1 || (Choice) == 2 || Choice == 0))
		return 0;
	else
		return 1;
}


int Admin_System::For_All_Choose(Check_Ptr Ptr) {
	cout << "请输入你的选择\t";
	int Choose = Check_Choose_All_Num();
	while (!Ptr(Choose) ){
		cout << "输入有误，请重新输入\t";
		Choose = Check_Choose_All_Num();
	}
	return (Choose);

}


void Admin_System::First_Identity(AirTicSystem& Air_Tics)
{
	int A_OR_C = 0;
	printf("\n\n\t\t*****************************************************************\n");
	printf("\t\t*\t\t\t欢迎使用飞机订票系统\t\t\t*");
	printf("\n\t\t*****************************************************************\n");
	printf("\t\t*\t\t\t请选择登陆通道：\t\t\t*\n");
	printf("\t\t*\t\t\t1:管理员通道\t\t\t\t*\n");
	printf("\t\t*\t\t\t2:用户通道\t\t\t\t*\n");
	printf("\t\t*\t\t\t0:退出飞机订票系统\t\t\t*\n");
	printf("\t\t*****************************************************************\n");
	
	
	for (A_OR_C = For_All_Choose(&A_OR_C_Choose);
		A_OR_C != 0; A_OR_C = For_All_Choose(&A_OR_C_Choose)) {
		
		switch (A_OR_C)
		{
		case 1:
			cout << "你选择了 1 ，请谨慎修改哦" <<endl;
			Users_Manage(Air_Tics);
			break;
		case 2:
			cout << " 你选择了 2 ，祝旅途愉快" <<endl;
			Admin_Manage(Air_Tics);
			break;

		}

	}

	if (A_OR_C == 0) {
		printf("看来你是铁了心要退出系统啦～欢迎下次使用～");
		exit(0);
	}

	
	
	
	
	return;

}

