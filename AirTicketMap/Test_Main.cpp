﻿#include "./include/AirTicSystem.hpp"
#include"./include/Users.hpp"
#include"./include/Common.hpp"
#include<iostream>



//const char* Flight_File_Name = "..\\RawData\\AirlineDataTEST_GBK.csv";
const char* Flight_File_Name = "..\\RawData\\test_transit.csv";
using namespace std;
const char * Admin_File = "..\\RawData\\admin.csv";
const char * Cus_File = "..\\RawData\\Customer.csv";


int main() {


	

	AirTicSystem test(Flight_File_Name);
	
	string New_Line_Data = "阿勒泰,AAT,乌鲁木齐,URC,中国南方航空(集团)公司,CZ6684,阿勒泰机场,地窝堡国际机场,2017/11/01,11:11,201711011111,2017/11/01,12:20,201711011220,AT7,1864,0.27,260,251";
	test.Insert_Flight_To_All(New_Line_Data);
	
	multimap<Serial_Type, Serial_Type> Test_Transit;
	test.Search_Transit("BAV", "CTU", Test_Transit);
	


	/*Flight Ans_Flight;
	Ans_Flight = Create_New_Flight();

	if(!test.Insert_Flight_To_All(Ans_Flight))
		cout<<"FAIL"<<endl;*/
	string ID = "CZ6684";
	Serials_Vec_Type Serials;
	test.Search_Flight_ByID(ID, Serials);
	//test.Search_Flight()
	for (auto iter = Serials.begin(); iter != Serials.end(); iter++)
		cout << (*iter) << endl;

	cout << endl;
	test.Print_Flight_Serials_Vec_To_Terminal(Serials);
	Serials_Vec_Type Sers;
	char Test_V_City[4] = "BAV";
	test.Search_Flight_V_City_All(Test_V_City, Sers, 1);


	

	//Admin_System A_And_C(Admin_File, Cus_File,Flight_File_Name);
	
	char time[6] = "15:60";
	int t = Char_Time_To_Int(time);
	cout << t;

	char date[11] = "2017/01/05";
	long d = Char_Date_To_Long(date);
	cout << d;
	char a;
	cin >> a;
	

	

	

	return 0;
}