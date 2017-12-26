#include "..\include\Flight.hpp"

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






