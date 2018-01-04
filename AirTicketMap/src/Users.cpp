#include "..\include\Users.hpp"
#include"..\include\Common.hpp"
#include<fstream>
#include<iostream>
#include<algorithm>
#include<iterator>
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
	if (A_Iter == Admin_Map.end())
		return false;
	else
		return true;
}

bool Admin_System::Is_Customer(string C_Name)
{
	auto A_Iter = Customer_Map.find(C_Name);
	if (A_Iter == Customer_Map.end())
		return false;
	else
		return true;
}



void Admin_System::Admin_Identity(AirTicSystem & Air_Tic_Data) {
	cout << "请输入管理员名" << endl;
	string A_Name;
	cin >> A_Name;
	if (Is_Admin(A_Name)) {
		cout << "请输入 " << A_Name << " 的密码" << endl;
		string A_Pwd;
		cin >> A_Pwd;
		if (Is_Admin_Pwd_Correct(A_Name, A_Pwd)) {
			cout << "登陆成功" << endl;
			Admin_Manage(Air_Tic_Data);
		}
		else
			cout << "密码有误，请重新登陆" << endl;
	}
	else
	{
		cout << "用户不存在，请重新登陆" << endl;
	}
	return;
}

void Admin_System::Admin_Manage(AirTicSystem & Air_Tic_Data)
{
	cout << "选择管理员可用功能" << endl;
	int A_Choose = Admin_Choose_Func();
	string ID;
	Serials_Vec_Type Same_ID;
	Flight New_Fl;

	for (; A_Choose != 0; A_Choose = Admin_Choose_Func()) {
		switch (A_Choose)
		{
		case 1:
			Air_Tic_Data.Print_Flight_All_In_Sys_To_Terminal();
			break;
		case 2:
			cout << "请输入欲查询的航班号" << endl;
			
			cin >> ID;
			
			Air_Tic_Data.Search_Flight_ByID(ID, Same_ID);
			Air_Tic_Data.Print_Flight_Serials_Vec_To_Terminal(Same_ID);
			break;
		case 3:
			
			New_Fl = Create_New_Flight();
			if (Air_Tic_Data.Insert_Flight_To_All(New_Fl)) {
				cout << "成功插入" << endl;
			}
			else
			{
				cout << "已有相同(同时间)航班" << endl;
			}
			Air_Tic_Data.Print_Flight_All_In_Sys_To_Terminal();
			break;
		}

	}
	if (A_Choose == 0) {
		cout << "退出管理员通道~" << endl;
		return;
	}
}

int Admin_System::Admin_Choose_Func()
{
	int choice;
	
	cout<< "1. 预览系统中所有航班" << endl
		<< "2. 按航班号查询所有航班" << endl
		<< "3. 插入一趟航班" << endl
		<< "0. 退出管理员通道" << endl;
	// >> choice;
	choice = For_All_Check(Check_Admin_Choose);
	
	return choice;
}

int Admin_System::Check_Admin_Choose(int Choice) {
	return (Choice == 1 || Choice == 2 || Choice == 0 || Choice==3) ? 1 : 0;
}





void Admin_System::Customer_Identity(AirTicSystem & Air_Tic_Data) {
	cout << "请输入用户名" << endl;
	string C_Name;
	cin >> C_Name;
	if (Is_Customer(C_Name)) {
		cout << "请输入 " << C_Name << " 的密码" << endl;
		string C_Pwd;
		cin >> C_Pwd;
		if (Is_Cus_Pwd_Correct(C_Name, C_Pwd)) {
			cout << "登陆成功" << endl;
			Customers_Manage(C_Name,Air_Tic_Data);
		}
		else
			cout << "密码有误，请重新登陆" << endl;
	}
	else {
		cout << "用户不存在，请重新登陆" << endl;
	}
	return;
}



string Admin_System::Merge_Cus_Info_To_One_String(Customer One_Cus) {
	string One_Line(One_Cus.Cus_Name);
	One_Line += ",";
	One_Line += One_Cus.Cus_Pwd;
	One_Line += ",";
	One_Line += to_string(One_Cus.Flight_Serials.size());
	One_Line += ",";
	for (auto V_Iter = One_Cus.Flight_Serials.begin();
		V_Iter != One_Cus.Flight_Serials.end(); V_Iter++) {
		One_Line += (*V_Iter);
		One_Line += ",";
	}
	return One_Line;

}

void Admin_System::Store_Cus_Data(const char* File_Name) {
	ofstream Save_Cus(File_Name);
	if (!Save_Cus) {
		cerr << "打开文件失败" << endl;
		system("pause");
	}
	Save_Cus << "用户名,密码,数量,流水号" << endl;
	for (auto C_Iter = Customer_Map.begin(); C_Iter != Customer_Map.end(); C_Iter++) {
		string temp = Merge_Cus_Info_To_One_String(C_Iter->second);
		Save_Cus << temp << endl;
	}
	return;
}



void Admin_System::Customers_Manage(const string Customer_Name,AirTicSystem & Air_Tic_Data)
{
	//用户个人信息，在map中定位
	auto C_Iter = Customer_Map.find(Customer_Name);
	Serials_Vec_Type& One_Cus_Ser_Vec = C_Iter->second.Flight_Serials;
	sort(One_Cus_Ser_Vec.begin(), One_Cus_Ser_Vec.end());
	cout << "选择用户可用功能" << endl;
	int C_Choose = Customers_Choose_Func();
	string ID;
	Serials_Vec_Type Same_ID;
	Flight New_Fl;
	Serials_Vec_Type To_Book, Booked;
	Serials_Vec_Type To_Cancel,Canceled;
	for (; C_Choose != 0; C_Choose = Customers_Choose_Func()) {
		switch (C_Choose)
		{
		case 1:
			Air_Tic_Data.Print_Flight_All_In_Sys_To_Terminal();
			break;
		case 2:
			cout << "请输入欲查询的航班号" << endl;
			cin >> ID;
			Air_Tic_Data.Search_Flight_ByID(ID, Same_ID);
			Air_Tic_Data.Print_Flight_Serials_Vec_To_Terminal(Same_ID);
			break;
		case 3:
			cout << "欢迎使用购票系统" << endl;
			To_Book = Air_Tic_Data.Search_Flight_In_Condition();
			Air_Tic_Data.Book_Flight_Tics(To_Book, One_Cus_Ser_Vec ,Booked);
			One_Cus_Ser_Vec.insert(One_Cus_Ser_Vec.end(), Booked.begin(), Booked.end());
			Store_Cus_Data("storeusers.csv");
			break;
		case 4:
			cout << "您所购买的机票如下所示" << endl;
			Air_Tic_Data.Print_Flight_Serials_Vec_To_Terminal(One_Cus_Ser_Vec);
			break;
		case 5:
			To_Cancel = Air_Tic_Data.Choose_Tics_To_Cancel(One_Cus_Ser_Vec);
			Vector_Set_Diff(One_Cus_Ser_Vec, To_Cancel);
			Store_Cus_Data("storeusers.csv");
			//Air_Tic_Data.Cancel_Flight_Tics(cancels);
			break;

		
		}
	}
	if (C_Choose == 0) {
		cout << "退出用户通道~" << endl;
		return;
	}

}



void Admin_System::Vector_Set_Diff(Serials_Vec_Type& Ans_Vec,const Serials_Vec_Type To_Diff){
	
Serials_Vec_Type Real_To_Ans = Ans_Vec;
auto read_iter = set_difference(Ans_Vec.begin(), Ans_Vec.end(), To_Diff.begin(), To_Diff.end(), Real_To_Ans.begin());
Real_To_Ans.resize(read_iter - Real_To_Ans.begin());
Ans_Vec = Real_To_Ans;
return;
}


int Admin_System::Customers_Choose_Func()
{
	int choice;

	cout << "1. 预览系统中所有航班" << endl
		<< "2. 按航班号查询所有航班" << endl
		<< "3. 按条件查询所有航班" << endl
		<<" 4. 预览自己所购买的票"<<endl
		<<"5. 退票"<<endl
		
		//<<"5. "
		<< "0. 退出用户通道" << endl;
	

	choice = For_All_Check(Check_Customers_Choose);

	return choice;
}

int Admin_System::Check_Customers_Choose(int Choice) {
	return (Choice == 1 || Choice == 2 || Choice == 3|| 
		Choice == 4 ||Choice==5|| Choice == 6 ||Choice == 0 ) ? 1 : 0;
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


int  Admin_System::Check_A_OR_C_Choose(int Choice) {
	return (Choice == 1 || Choice == 2 || Choice == 0) ? 1 : 0;
}


 int Admin_System::For_All_Check(Check_Ptr Ptr) {
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

	
	
	for (A_OR_C = For_All_Check(Check_A_OR_C_Choose);
		A_OR_C != 0; A_OR_C = For_All_Check(Check_A_OR_C_Choose)) {
		
		switch (A_OR_C)
		{
		case 1:
			cout << "你选择了 1 ，请谨慎修改哦" <<endl;
			Admin_Identity(Air_Tics);
			//Customers_Manage(Air_Tics);
			break;
		case 2:
			cout << " 你选择了 2 ，祝旅途愉快" <<endl;
			Customer_Identity(Air_Tics);
			break;

		}

	}

	if (A_OR_C == 0) {
		printf("看来你是铁了心要退出系统啦～欢迎下次使用～");
		exit(0);
	}

	
	
	
	
	return;

}

