#include "..\include\Flight.hpp"
#include "..\include\Common.hpp"
#include<iostream>
using std::cin;
using std::endl;
using std::cout;


Flight Create_New_Flight(vector<string> Line_Data) {
	Flight New_Flight;
	auto Str_Iter = Line_Data.begin();

	strcpy(New_Flight.T_City,			(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.T_City_Short,		(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.L_City,			(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.L_City_Short,		(*Str_Iter).c_str());	Str_Iter++;

	strcpy(New_Flight.Flight_CO,		(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.Flight_ID,		(*Str_Iter).c_str());	Str_Iter++;

	strcpy(New_Flight.T_Airport,		(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.L_Airport,		(*Str_Iter).c_str());	Str_Iter++;
	
	strcpy(New_Flight.T_Time,			(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.T_Time_Stamp,		(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.L_Time,			(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.L_Time_Stamp,		(*Str_Iter).c_str());	Str_Iter++;
	
	strcpy(New_Flight.Aircraft_Type,	(*Str_Iter).c_str());	Str_Iter++;
	
	strcpy(New_Flight.Date,				(*Str_Iter).c_str());	Str_Iter++;

	New_Flight.Tic_Price =	stof((*Str_Iter)); Str_Iter++;
	New_Flight.M_Discount = stof((*Str_Iter)); Str_Iter++;

	New_Flight.Max_Seats =	stoi((*Str_Iter)); Str_Iter++;
	New_Flight.Cur_Order =	stoi((*Str_Iter));

	string L_Time(New_Flight.L_Time_Stamp);
	New_Flight.Serial_NO = Line_Data[1] + Line_Data[3] + Line_Data[5] + Line_Data[9] + L_Time.substr(8,4);


	return New_Flight;
}


Flight Create_New_Flight()
{
	string Line;
	cout << "起始城市0,起始城市缩写1,到达城市2,到达城市缩写3,公司4,航班号5,起飞机场6,到达机场7,起飞时间8,"
		<< "到达时间10,机型12,日期13,价格14,最大折扣15,满载16,当前人数17" << endl
		<< "中间用逗号分隔" << endl;
	cin >> Line;
	vector<string> Line_Vec, Date_Vec, Time_Vec;
	string sep = ",";
	Split_Row(Line, sep, Line_Vec);


	//日期
	sep = "/";
	Split_Row(Line_Vec[11], sep, Date_Vec);

	string T_Stamp, L_Stamp;
	sep = ":";
	Split_Row(Line_Vec[8], sep, Time_Vec);
	T_Stamp = Date_Vec[0] + Date_Vec[1] + Date_Vec[2] + Time_Vec[0] + Time_Vec[1];

	Split_Row(Line_Vec[9], sep, Time_Vec);
	L_Stamp = Date_Vec[0] + Date_Vec[1] + Date_Vec[2] + Time_Vec[0] + Time_Vec[1];


	Line_Vec.insert(Line_Vec.begin() + 9, T_Stamp);
	Line_Vec.insert(Line_Vec.begin() + 11, L_Stamp);



	Flight NN = Create_New_Flight(Line_Vec);
	return NN;
}



