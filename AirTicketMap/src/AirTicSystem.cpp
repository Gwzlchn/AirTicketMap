#include "..\include\AirTicSystem.hpp"
#include "..\include\Common.hpp"

#include<iostream>
#include<fstream>

using namespace std;
//非类中函数写到Common里





AirTicSystem::AirTicSystem(const char * File_Name)
{
	Flight_From_One_Count = 0;
	Flight_Total_Count = 0;
	Create_Map_From_CSV(File_Name);
	ReadIn_From_Map();
}

void AirTicSystem::ReadIn_From_Map()
{

}

void AirTicSystem::Create_Map_From_CSV(const char * File_Name)
{
	ifstream file(File_Name, ios::in);
	if (!file)
	{
		cerr << "打开文件失败";
		system("PAUSE");

	}
	string row;
	getline(file, row);//剔除首部
	vector<string> infRow;

	while (file.good())
	{

		getline(file, row);
		Split_Row(row, ",", infRow);
		if (infRow.size())//有效的数据
		{
			Flight_Total_Count++;
			Flight New_Flight = Create_New_Flight(infRow);
			
			Ser_Flight_Map.insert({ New_Flight.Serial_NO ,New_Flight });
			FlightID_Ser_Map.insert({ New_Flight.Flight_ID,New_Flight.Serial_NO });


		}
	}

	return;
}


void AirTicSystem::Split_Ser_Info(Flight_Serial_Type Serial, vector<string>& A_Ser_Vec)
{
	A_Ser_Vec.push_back(Serial.substr(0, 3));
	A_Ser_Vec.push_back(Serial.substr(3, 3));
	A_Ser_Vec.push_back(Serial.substr(6, 6));
	A_Ser_Vec.push_back(Serial.substr(12, 12));
}
