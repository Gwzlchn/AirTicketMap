#include "..\include\Users.hpp"
#include"..\include\Common.hpp"
#include<fstream>
#include<iostream>

using namespace std;


Admin_System::Admin_System(const char * Admin_File, const char * Cus_File)
{
	ifstream A_File(Admin_File, ios::in);
	ifstream C_File(Cus_File, ios::in);

	if (!A_File )
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

void Admin_System::Users_Mange(const AirTicSystem & Air_Tic_Data)
{
}

int Admin_System::Users_Choose_Func()
{
	return 0;
}

