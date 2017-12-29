#include "..\include\AirTicSystem.hpp"
#include "..\include\Common.hpp"

#include<iostream>
#include<fstream>

using namespace std;
//非类中函数写到Common.cpp里








AirTicSystem::AirTicSystem(const char * File_Name)
{
	Flight_From_One_Count = 0;
	Flight_Total_Count = 0;
	Create_Map_From_CSV(File_Name);
	Create_Pos_Neg_From_Map();
}

void AirTicSystem::Create_Pos_Neg_From_Map()
{
	for (auto M_Iter = Ser_Flight_Map.begin();
		M_Iter != Ser_Flight_Map.end(); M_Iter++) {


		//正& 反
		Insert_Flight_To_Pos_OR_Neg_Graph(M_Iter->second);


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





//Vec_choose == 1 找正图 ==2 找反图
//返回值>=0 出发城市在T_City_Vec中，值为索引，留给插入航班函数用
//返回-2 不存在该顶点

int AirTicSystem::Index_OF_Pos_OR_Neg_City_Vec(char V_City[3], int Vec_Choose)
{
	if (Vec_Choose == 1 || Vec_Choose == 2) {
		vector<Vertex_City>& V_City_Vec = (Vec_Choose == 1) ? Pos_T_City_Vec : Neg_L_City_Vec;

		int V_Flag = 1, V_Index = -1;

		for (auto V_Iter = V_City_Vec.begin();
			V_Iter != V_City_Vec.end(); V_Iter++) {
			V_Flag = strcmp((*V_Iter).Vertex_City_Short, V_City);
			V_Index++;
			if (V_Flag == 0) break;
		}
		V_Index = (V_Index == -1) ? 0 : V_Index;

		//T_Flag==0说明该城市起飞顶点中存在
		//T_Flag！=0说明一个新出发城市顶点
		if (V_Flag)
			return -2;
		else
			return V_Index;
	}
	else
		return -2;
}

//查询流水号是否在map中
//在 返回1 ans_flight
//不在 返回 -1
int AirTicSystem::Search_Flight(Serial_Type Flight_Seq, Flight & Ans_Flight)
{
	auto F_Iter = Ser_Flight_Map.find(Flight_Seq);
	if (F_Iter == Ser_Flight_Map.end())
		return -1;
	else {
		Ans_Flight = F_Iter->second;
		return 1;
	}
}

int AirTicSystem::Search_Flight_ByID(string Flight_ID, Serials_Vec_Type& Serials_Vec)
{
	auto Sers_Entries = FlightID_Ser_Map.count(Flight_ID);
	int Sers_Cnt = Sers_Entries;
	auto S_Iter = FlightID_Ser_Map.find(Flight_ID);
	while (Sers_Entries) {
		Serials_Vec.push_back(S_Iter->second);
		++S_Iter;
		--Sers_Entries;
	}
	return Sers_Cnt;
}

int AirTicSystem::Index_OF_Pos_OR_Neg_City_Vec(Vertex_City* V_City, int Vector_Choose) {
	return Index_OF_Pos_OR_Neg_City_Vec(V_City->Vertex_City_Short, Vector_Choose);
}






void AirTicSystem::Split_Ser_Info(Serial_Type Serial, vector<string>& A_Ser_Vec)
{
	A_Ser_Vec.push_back(Serial.substr(0, 3));
	A_Ser_Vec.push_back(Serial.substr(3, 3));
	A_Ser_Vec.push_back(Serial.substr(6, 6));
	A_Ser_Vec.push_back(Serial.substr(12, 12));
	A_Ser_Vec.push_back(Serial.substr(24, 4));
}

void AirTicSystem::Merge_Ser_Info(Serial_Type & Serial, vector<string> A_Ser_Vec)
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

void AirTicSystem::Print_Flight_Serials_Vec_To_Terminal(Serials_Vec_Type& Serials_Vec)
{
	for (auto S_Iter = Serials_Vec.begin();
		S_Iter != Serials_Vec.end(); S_Iter++) {
		auto F_Iter = Ser_Flight_Map.find((*S_Iter));
		Print_Flight_To_Termimal((*F_Iter).second);
	}
	return;
}


//Vec_choose == 1 找正图 ==2 找反图
bool AirTicSystem::Insert_Flight_To_Pos_OR_Neg_Graph(Vertex_City* V_City, Edge_City* E_City, const vector<string>& New_Ser_Vec, int Vec_Choose) {


	if (Vec_Choose == 1 || Vec_Choose == 2) {
		vector<Vertex_City>& V_City_Vec = (Vec_Choose == 1) ? Pos_T_City_Vec : Neg_L_City_Vec;

		int V_Index = Index_OF_Pos_OR_Neg_City_Vec(V_City, Vec_Choose);


		Serial_Type New_Ser;
		Merge_Ser_Info(New_Ser, New_Ser_Vec);

		if (V_Index >= 0) {
			Vertex_City Temp_V_Cy = V_City_Vec[V_Index];
			Edge_City* E_Cy_Ptr = Temp_V_Cy.Edge_City_Head;

			int E_Flag = 1;
			for (; E_Cy_Ptr != NULL; E_Cy_Ptr = E_Cy_Ptr->Next_Edge_City) {
				E_Flag = strcmp(E_City->Edge_City_Short, New_Ser_Vec[1].c_str());
				if (E_Flag == 0) break;
			}

			//该降落顶点存在
			if (E_Flag == 0)
				E_Cy_Ptr->Flight_Serials.push_back(New_Ser);

			//该降落顶点不存在
			else if (E_Flag != 0) {
				Edge_City* Temp_E_Ptr = Temp_V_Cy.Edge_City_Head;
				while (Temp_E_Ptr->Next_Edge_City != NULL)
					Temp_E_Ptr = Temp_E_Ptr->Next_Edge_City;
				Temp_E_Ptr->Next_Edge_City = E_City;
			}

		}
		//T_Index！=0说明一个新出发城市顶点
		else {
			V_City->Edge_City_Head = E_City;
			V_City_Vec.push_back((*V_City));
		}
		return true;
	}
	else
		return false;

}





bool AirTicSystem::Insert_Flight_To_Pos_OR_Neg_Graph(Vertex_City* V_City, Edge_City* E_City, const string New_Ser_Str, int Vec_Choose) {

	vector<string> New_Ser_Vec;
	Split_Ser_Info(New_Ser_Str, New_Ser_Vec);
	return Insert_Flight_To_Pos_OR_Neg_Graph(V_City, E_City, New_Ser_Vec, Vec_Choose);
}

bool AirTicSystem::Insert_Flight_To_Pos_OR_Neg_Graph(Flight & New_Flight)
{
	//正图
	Vertex_City*   New_Pos_V_T_Cy = new Vertex_City;
	New_Pos_V_T_Cy->Edge_City_Head = NULL;
	strcpy(New_Pos_V_T_Cy->Vertex_City_Short, New_Flight.T_City_Short);

	Edge_City* New_Pos_E_L_Cy = new Edge_City;
	New_Pos_E_L_Cy->Next_Edge_City = NULL;
	New_Pos_E_L_Cy->Flight_Serials.push_back(New_Flight.Serial_NO);
	strcpy(New_Pos_E_L_Cy->Edge_City_Short, New_Flight.L_City_Short);

	Insert_Flight_To_Pos_OR_Neg_Graph(New_Pos_V_T_Cy, New_Pos_E_L_Cy, New_Flight.Serial_NO, 1);

	//反图
	Vertex_City*   New_Neg_V_L_Cy = new Vertex_City;
	New_Neg_V_L_Cy->Edge_City_Head = NULL;
	strcpy(New_Neg_V_L_Cy->Vertex_City_Short, New_Flight.L_City_Short);

	Edge_City* New_Neg_E_T_Cy = new Edge_City;
	New_Neg_E_T_Cy->Next_Edge_City = NULL;
	New_Neg_E_T_Cy->Flight_Serials.push_back(New_Flight.Serial_NO);
	strcpy(New_Neg_E_T_Cy->Edge_City_Short, New_Flight.T_City_Short);

	Insert_Flight_To_Pos_OR_Neg_Graph(New_Neg_V_L_Cy, New_Neg_E_T_Cy, New_Flight.Serial_NO, 2);


	return true;
}

bool AirTicSystem::Insert_Flight_To_All(Flight& New_Flight)
{
	auto S_M_Iter = Ser_Flight_Map.find(New_Flight.Serial_NO);
	if (S_M_Iter == Ser_Flight_Map.end()) {
		Insert_Flight_To_Pos_OR_Neg_Graph(New_Flight);
		Ser_Flight_Map.insert({ New_Flight.Serial_NO,New_Flight });
		FlightID_Ser_Map.insert({ New_Flight.Flight_ID,New_Flight.Serial_NO });
	}

	//已存在相同航班
	else
		return false;
}

bool AirTicSystem::Insert_Flight_To_All(vector<string>& Whole_Line_Data)
{
	Flight New_Flight = Create_New_Flight(Whole_Line_Data);
	return Insert_Flight_To_All(New_Flight);


}

bool AirTicSystem::Insert_Flight_To_All(string Whole_Line_Raw)
{
	vector<string> Line_Data_Vec;
	string sep = ",";
	Split_Row(Whole_Line_Raw, sep, Line_Data_Vec);
	return Insert_Flight_To_All(Line_Data_Vec);
}







