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
	Create_Pos_From_Map();
}

void AirTicSystem::Create_Pos_From_Map()
{
	for (auto M_Iter = Ser_Flight_Map.begin();
		M_Iter != Ser_Flight_Map.end(); M_Iter++) {
		
		Pos_TakeOff_City* New_Pos_T_Cy = new Pos_TakeOff_City;
		New_Pos_T_Cy->Pos_L_City_Head = NULL;
		strcpy(New_Pos_T_Cy->T_City_Short, M_Iter->second.T_City_Short);
		
		Pos_Land_City* New_Pos_L_Cy = new Pos_Land_City;
		New_Pos_L_Cy->Next_Pos_L_City = NULL;
		New_Pos_L_Cy->Flight_Serials.push_back(M_Iter->first);
		strcpy(New_Pos_L_Cy->L_City_Short, M_Iter->second.L_City_Short);

		Insert_Flight_To_Graph(New_Pos_T_Cy, New_Pos_L_Cy, M_Iter->first);
	}
		
	

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
			
			//序列号 航班信息的映射
			Ser_Flight_Map.insert({ New_Flight.Serial_NO ,New_Flight });
			//航班号 序列号的映射
			FlightID_Ser_Map.insert({ New_Flight.Flight_ID,New_Flight.Serial_NO });
		}
	}

	return;
}




//返回值>=0 出发城市在T_City_Vec中，值为索引，留给插入航班函数用
//返回-2 不存在出发地,
int AirTicSystem::Index_OF_T_City_Vec(char T_City[3])
{
	int T_Flag = 1, T_Index = -1;
	for (auto T_Iter = Pos_T_City_Vec.begin();
		T_Iter != Pos_T_City_Vec.end(); T_Iter++) {
		T_Flag = strcmp((*T_Iter).T_City_Short, T_City);
		T_Index++;
		if (T_Flag == 0) break;
	}
	T_Index = (T_Index == -1) ? 0 : T_Index;

	//T_Flag==0说明该城市起飞顶点中存在
	//T_Flag！=0说明一个新出发城市顶点
	if (T_Flag)
		return -2;
	else
		return T_Index;
}

//查询流水号是否在map中
//在 返回1 ans_flight
//不在 返回 -1
int AirTicSystem::Search_Flight(Flight_Serial_Type Flight_Seq, Flight & Ans_Flight)
{
	auto F_Iter = Ser_Flight_Map.find(Flight_Seq);
	if (F_Iter == Ser_Flight_Map.end())
		return -1;
	else {
		Ans_Flight = F_Iter->second;
		return 1;
	}
}

int AirTicSystem::Search_Flight_ByID(string Flight_ID, vector<Flight_Serial_Type>& Serials_Vec)
{
	auto Sers_Entries = FlightID_Ser_Map.count(Flight_ID);
	auto Sers_Cnt = Sers_Entries;
	auto S_Iter = FlightID_Ser_Map.find(Flight_ID);
	while (Sers_Entries) {
		Serials_Vec.push_back(S_Iter->second);
		++S_Iter;
		--Sers_Entries;
	}
	return Sers_Cnt;
}

int AirTicSystem::Index_OF_T_City_Vec(Pos_TakeOff_City* T_AP)
{
	return Index_OF_T_City_Vec(T_AP->T_City_Short);
}






void AirTicSystem::Split_Ser_Info(Flight_Serial_Type Serial, vector<string>& A_Ser_Vec)
{
	A_Ser_Vec.push_back(Serial.substr(0, 3));
	A_Ser_Vec.push_back(Serial.substr(3, 3));
	A_Ser_Vec.push_back(Serial.substr(6, 6));
	A_Ser_Vec.push_back(Serial.substr(12, 12));
	A_Ser_Vec.push_back(Serial.substr(24, 4));
}

void AirTicSystem::Merge_Ser_Info(Flight_Serial_Type & Serial, vector<string> A_Ser_Vec)
{
	for (auto S_Iter = A_Ser_Vec.begin();
		S_Iter != A_Ser_Vec.end(); S_Iter++)
		Serial += (*S_Iter);
	return;
}




void AirTicSystem::Print_Flight_To_Termimal(Flight& One_Flight)
{
	cout << " " << One_Flight.T_City
		<< "  " << One_Flight.L_City
		<< "  " << One_Flight.Flight_ID
		<< "  " << One_Flight.Date
		<< "  " << One_Flight.T_Time
		<< "  " << One_Flight.L_Time
		<< "  " << One_Flight.Aircraft_Type
		<< "  " << One_Flight.Tic_Price
		<< "  " << One_Flight.Max_Seats
		<< "  " << One_Flight.Cur_Order
		<< endl;
}

void AirTicSystem::Print_Flight_Vec_To_Terminal(vector<Flight>& Flight_Vec)
{
	for (auto F_Iter = Flight_Vec.begin();
		F_Iter != Flight_Vec.end(); F_Iter++)
		Print_Flight_To_Termimal((*F_Iter));
	return;
}

bool AirTicSystem::Insert_Flight_To_Graph(Pos_TakeOff_City * Pos_T_City, Pos_Land_City * Pos_L_City, const vector<string>& New_Ser_Vec)
{
	int T_Index = Index_OF_T_City_Vec(Pos_T_City);

	string New_Ser;
	Merge_Ser_Info(New_Ser, New_Ser_Vec);
	//flag==0说明该城市起飞顶点中存在
	if (T_Index >= 0) {
		Pos_TakeOff_City Temp_T_Cy = Pos_T_City_Vec[T_Index];
		Pos_Land_City* L_Ptr = Temp_T_Cy.Pos_L_City_Head;

		int L_Flag = 1;
		for (; L_Ptr != NULL; L_Ptr = L_Ptr->Next_Pos_L_City) {
			L_Flag = strcmp(L_Ptr->L_City_Short,New_Ser_Vec[1].c_str());
			if (L_Flag == 0) break;
		}

		//该降落顶点存在
		if (L_Flag == 0)
			L_Ptr->Flight_Serials.push_back(New_Ser);

		//该降落顶点不存在
		else if (L_Flag != 0) {
			Pos_Land_City* Temp_L_Ptr = Temp_T_Cy.Pos_L_City_Head;
			while (Temp_L_Ptr->Next_Pos_L_City != NULL)
				Temp_L_Ptr = Temp_L_Ptr->Next_Pos_L_City;
			Temp_L_Ptr->Next_Pos_L_City = Pos_L_City;
		}

	}
	//T_Index！=0说明一个新出发城市顶点
	else {
		Pos_T_City->Pos_L_City_Head = Pos_L_City;
		Pos_T_City_Vec.push_back((*Pos_T_City));
	}

	return true;
}

bool AirTicSystem::Insert_Flight_To_Graph(Pos_TakeOff_City * Pos_T_City, Pos_Land_City * Pos_L_City, const string New_Ser_Str)
{
	vector<string> New_Ser_Vec;
	Split_Ser_Info(New_Ser_Str, New_Ser_Vec);
	return Insert_Flight_To_Graph(Pos_T_City, Pos_L_City, New_Ser_Vec);
}
