#include "..\include\Flight.hpp"
#include "..\include\Common.hpp"
#include<iostream>
using std::cin;
using std::endl;
using std::cout;
using std::to_string;

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
	
	strcpy(New_Flight.T_Date, (*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.T_Time,			(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.T_Time_Stamp,		(*Str_Iter).c_str());	Str_Iter++;

	strcpy(New_Flight.L_Date, (*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.L_Time,			(*Str_Iter).c_str());	Str_Iter++;
	strcpy(New_Flight.L_Time_Stamp,		(*Str_Iter).c_str());	Str_Iter++;
	

	strcpy(New_Flight.Aircraft_Type,	(*Str_Iter).c_str());	Str_Iter++;
	New_Flight.Tic_Price =	stof((*Str_Iter)); Str_Iter++;
	New_Flight.M_Discount = stof((*Str_Iter)); Str_Iter++;

	New_Flight.Max_Seats =	stoi((*Str_Iter)); Str_Iter++;
	New_Flight.Cur_Order =	stoi((*Str_Iter));


	string L_Time(New_Flight.L_Time_Stamp);
	New_Flight.Serial_NO = Line_Data[1] + Line_Data[3] + Line_Data[5]+Line_Data[10] + Line_Data[13];


	return New_Flight;
}


Flight Create_New_Flight()
{
	string Line;

	//起始城市0, 起始城市缩写1, 到达城市2, 到达城市缩写3, 公司4, 航班号5, 起飞机场6, 到达机场7, 起飞日期8, 起飞时间9, 起飞时间戳10, 到达日期11, 到达时间12, 到达时间戳13, 机型14, 价格15, 最大折扣16, 满载17, 当前人数18
	cout << "起始城市0,起始城市缩写1,到达城市2,到达城市缩写3,公司4,航班号5,起飞机场6,到达机场7,起飞日期8,"
		<< "起飞时间9，到达日期11，到达时间12,机型14,价格15,最大折扣16,满载17,当前人数18" << endl
		<< "中间用逗号分隔" << endl;
	cin >> Line;
	vector<string> Line_Vec, T_Date_Vec,L_Date_Vec, Time_Vec;
	string sep = ",";
	Split_Row(Line, sep, Line_Vec);
	while (Line_Vec.size() != 17) {
		cout << "输入数据有误" << endl
			<< "重新输入航班数据" << endl;
		cin >> Line;
		Split_Row(Line, sep, Line_Vec);

	}

	//日期
	string T_Date,L_Date;
	sep = "/";
	Split_Row(Line_Vec[8], sep, T_Date_Vec);
	Split_Row(Line_Vec[10], sep, L_Date_Vec);

	string T_Stamp, L_Stamp;
	sep = ":";
	Split_Row(Line_Vec[9], sep, Time_Vec);
	T_Stamp = T_Date_Vec[0] + T_Date_Vec[1] + T_Date_Vec[2] + Time_Vec[0] + Time_Vec[1];
	
	//Time_Vec.clear();
	Split_Row(Line_Vec[11], sep, Time_Vec);
	L_Stamp = L_Date_Vec[0] + L_Date_Vec[1] + L_Date_Vec[2] + Time_Vec[0] + Time_Vec[1];


	Line_Vec.insert(Line_Vec.begin() + 10, T_Stamp);
	Line_Vec.insert(Line_Vec.begin() + 13, L_Stamp);



	Flight NN = Create_New_Flight(Line_Vec);
	return NN;
}

string Merge_Flight_To_One_Str(Flight & One_Filght)
{
	
	string temp = One_Filght.T_City;
	temp += ",";
	temp += One_Filght.T_City_Short;
	temp += ",";
	temp += One_Filght.L_City;
	temp += ",";
	temp += One_Filght.L_City_Short;
	temp += ",";
	temp += One_Filght.Flight_CO;
	temp += ",";
	temp += One_Filght.Flight_ID;
	temp += ",";
	temp += One_Filght.T_Airport;
	temp += ",";
	temp += One_Filght.L_Airport;
	temp += ",";
	temp += One_Filght.T_Date;
	temp += ",";
	temp += One_Filght.T_Time;
	temp += ",";
	temp += One_Filght.T_Time_Stamp;
	temp += ",";
	temp += One_Filght.L_Date;
	temp += ",";
	temp += One_Filght.L_Time;
	temp += ",";
	temp += One_Filght.L_Time_Stamp;
	temp += ",";
	temp += One_Filght.Aircraft_Type;
	temp += ",";
	temp += to_string(One_Filght.M_Discount);
	temp += ",";
	temp += to_string(One_Filght.Tic_Price);
	temp += ",";
	temp += to_string(One_Filght.Max_Seats);
	temp += ",";
	temp += to_string(One_Filght.Cur_Order);

	
	
	return temp;
}



