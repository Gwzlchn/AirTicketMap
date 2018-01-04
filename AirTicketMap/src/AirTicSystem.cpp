#include "..\include\AirTicSystem.hpp"
#include "..\include\Common.hpp"

#include<iostream>
#include<fstream>
#include<algorithm>
#include<iterator>
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

			City_Short_Map.insert({ New_Flight.L_City_Short,New_Flight.L_City });
			City_Short_Map.insert({ New_Flight.T_City_Short,New_Flight.T_City });
		}
	}

	return;
}





//Vec_choose == 1 找正图 ==2 找反图
//返回值>=0 出发城市在T_City_Vec中，值为索引，留给插入航班函数用
//返回-2 不存在该顶点

int AirTicSystem::Index_OF_Pos_OR_Neg_City_Vec(char V_City[], int Vec_Choose)
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
	Serials_Vec.clear();
	auto Sers_Entries = FlightID_Ser_Map.count(Flight_ID);
	size_t Sers_Cnt = Sers_Entries;
	auto S_Iter = FlightID_Ser_Map.find(Flight_ID);
	if (S_Iter == FlightID_Ser_Map.end()) {
		cout << "无此航班" << endl;
		return 0;
	}
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
	A_Ser_Vec.clear();
	A_Ser_Vec.push_back(Serial.substr(0, 3));	//起飞机场 0
	A_Ser_Vec.push_back(Serial.substr(3, 3));	//到达机场 1
	A_Ser_Vec.push_back(Serial.substr(6, 6));	//航班号   2
	A_Ser_Vec.push_back(Serial.substr(12, 8));	//起飞日期 3
	A_Ser_Vec.push_back(Serial.substr(20, 4));	//起飞时刻 4
	A_Ser_Vec.push_back(Serial.substr(24, 8));	//到达日期 5
	A_Ser_Vec.push_back(Serial.substr(32, 4));	//到达时刻 6
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
	cout << "" << One_Flight.T_City
		<< "\t" << One_Flight.L_City
		<< "\t\t" << One_Flight.Flight_ID
		<< "  " << One_Flight.T_Date
		<< "  " << One_Flight.T_Time
		<< "  " << One_Flight.L_Date
		<< "  " << One_Flight.L_Time
		<< "  " << One_Flight.Aircraft_Type
		<< "  " << One_Flight.Tic_Price
		<< "  " << One_Flight.Max_Seats
		<< "  " << One_Flight.Cur_Order;
	if (One_Flight.Max_Seats > One_Flight.Cur_Order)
		cout << "  未满仓" << endl;
	else
		cout << "  已满仓" << endl;
}


void AirTicSystem::Print_Flight_To_Termimal_In_Ser(Serial_Type One_Ser)
{
	Flight Temp_Flight;
	Search_Flight(One_Ser, Temp_Flight);
	Print_Flight_To_Termimal(Temp_Flight);
}


void AirTicSystem::Print_Flight_All_In_Sys_To_Terminal()
{
	for (auto M_Iter = Ser_Flight_Map.begin();
		M_Iter != Ser_Flight_Map.end(); M_Iter++) {
		Print_Flight_To_Termimal_In_Ser((M_Iter->first));
	}
	return;
}

void AirTicSystem::Print_Flight_Serials_Vec_To_Terminal(Serials_Vec_Type& Serials_Vec)
{
	for (auto S_Iter = Serials_Vec.begin();
		S_Iter != Serials_Vec.end(); S_Iter++) {
		auto F_Iter = Ser_Flight_Map.find((*S_Iter));
		if (F_Iter == Ser_Flight_Map.end()) {
			cout << "未找到该航班  ";
			cout << (*S_Iter) << endl;
			continue;
		}
		else
			Print_Flight_To_Termimal((*F_Iter).second);
	}
	return;
}



void AirTicSystem::Store_All_Data_To_File(const char * Store_Name) {
	ofstream SaveFile(Store_Name);
	if (!SaveFile) {
		cerr << "打开文件失败" << endl;
		system("pause");
	}
	SaveFile << "起始城市,起始城市缩写,到达城市,到达城市缩写,"
		"公司,航班号,起飞机场,到达机场,起飞日期,起飞时间,"
		"起飞时间戳,到达日期,到达时间,到达时间戳,机型,"
		"价格,最大折扣,满载,当前人数" << endl;
	for (auto M_Iter = Ser_Flight_Map.begin();
		M_Iter != Ser_Flight_Map.end(); M_Iter++) {
		string One_Line = Merge_Flight_To_One_Str(M_Iter->second);
		SaveFile << One_Line << endl;
	}
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
				E_Flag = strcmp(E_Cy_Ptr->Edge_City_Short, New_Ser_Vec[1].c_str());
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
		return true;
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










void AirTicSystem::Fliter_Ser_Vec_By_T_Date_Time(char T_Date[], char T_Time[], const Serials_Vec_Type& Raw_Vec, Serials_Vec_Type& Date_Vec)
{
	long T_Date_Long = Char_Date_To_Long(T_Date);
	int T_Time_Int = Char_Date_To_Long(T_Time);
	Fliter_Ser_Vec_By_T_Date_Time(T_Date_Long, T_Time_Int, Raw_Vec, Date_Vec);

	return;
}

//使用该函数之前 流水号已经筛选为确定日期
//出发日期、时间作为过滤器，过滤Raw_Vec中流水号，符合条件压入Date_Vec
void AirTicSystem::Fliter_Ser_Vec_By_T_Date_Time(long T_Date, int T_Time, const Serials_Vec_Type& Raw_Vec, Serials_Vec_Type& Date_Vec) {

	if (Raw_Vec.size() != 0) {
		for (auto R_Iter = Raw_Vec.begin();
			R_Iter != Raw_Vec.end(); R_Iter++) {
			vector<string> Raw_Ser_Vec;
			Split_Ser_Info((*R_Iter), Raw_Ser_Vec);

			long long R_T_Date = stoll(Raw_Ser_Vec[4]);
			long long R_T_Time = stoll(Raw_Ser_Vec[5]);
			if ((R_T_Date >= T_Date) && (R_T_Time <= T_Time))
				Date_Vec.push_back(*R_Iter);

		}
		return;
	}
	return;
}


void AirTicSystem::Fliter_Ser_Vec_By_Date(const char T_Date[], const char L_Date[],  const Serials_Vec_Type& Raw_Vec, Serials_Vec_Type& Date_Vec) {
	Fliter_Ser_Vec_By_Date(const_cast<char*>(T_Date), const_cast<char*>(L_Date), Raw_Vec, Date_Vec);
	return;
}


//两个正常字符串日期作为过滤器，过滤流水号，详细见下面用long的
void AirTicSystem::Fliter_Ser_Vec_By_Date(char T_Date[], char L_Date[], const Serials_Vec_Type& Raw_Vec, Serials_Vec_Type& Date_Vec) {
	long T_Long = Char_Date_To_Long(T_Date);
	long L_Long = Char_Date_To_Long(L_Date);
	Fliter_Ser_Vec_By_Date(T_Long, L_Long, Raw_Vec, Date_Vec);
	return;
}



//两个long int日期作为过滤器，过滤Raw_Vec中流水号，符合条件压入Date_Vec
void AirTicSystem::Fliter_Ser_Vec_By_Date(long T_Date, long L_Date, const Serials_Vec_Type& Raw_Vec, Serials_Vec_Type& Date_Vec) {

	if (Raw_Vec.size() != 0) {
		for (auto R_Iter = Raw_Vec.begin();
			R_Iter != Raw_Vec.end(); R_Iter++) {
			vector<string> Raw_Ser_Vec;
			Split_Ser_Info((*R_Iter), Raw_Ser_Vec);

			long R_T_Date = stol(Raw_Ser_Vec[3]);
			long R_L_Date = stol(Raw_Ser_Vec[5]);
			if ((R_T_Date >= T_Date) && (R_L_Date <= L_Date))
				Date_Vec.push_back(*R_Iter);

		}
		return;
	}
	return;
}
//将流水号 按起飞时间从小到大排序
void AirTicSystem::Rank_Ser_Vec_T_Time(const Serials_Vec_Type& Raw_Vec, Serials_Vec_Type& Rank_Vec) {
	multimap<unsigned long long, Serial_Type>  T_Time_Ser_Map;
	for (auto R_V_Iter = Raw_Vec.begin();
		R_V_Iter != Raw_Vec.end(); R_V_Iter++) {
		vector<string> Ser_Vec;
		Split_Ser_Info((*R_V_Iter), Ser_Vec);

		unsigned long long  T_Time_Stamp = stoi(Ser_Vec[3]) * 10000 + stoi(Ser_Vec[4]);
		T_Time_Ser_Map.insert({ T_Time_Stamp,(*R_V_Iter) });
	}

	for (auto T_Iter = T_Time_Ser_Map.begin();
		T_Iter != T_Time_Ser_Map.end(); T_Iter++) {
		Rank_Vec.push_back(T_Iter->second);
	}
	return;


}
//将流水号 按价格从低到高排序
void AirTicSystem::Rank_Ser_Vec_Price(const Serials_Vec_Type& Raw_Vec, Serials_Vec_Type& Rank_Vec) {
	if (Raw_Vec.size() != 0) {
		//价格 - 流水号的映射（插入是有序的）
		multimap<float, Serial_Type>  Price_Ser_Map;
		for (auto R_V_Iter = Raw_Vec.begin();
			R_V_Iter != Raw_Vec.end(); R_V_Iter++) {
			Flight Temp_Flight;
			Search_Flight((*R_V_Iter), Temp_Flight);
			float Temp_Price = Temp_Flight.Tic_Price;
			Price_Ser_Map.insert({ Temp_Price,(*R_V_Iter) });
		}

		for (auto P_Iter = Price_Ser_Map.begin();
			P_Iter != Price_Ser_Map.end(); P_Iter++) {
			Rank_Vec.push_back(P_Iter->second);
		}
		return;
	}
	return;
}



int AirTicSystem::Search_Flight_V_City_All(const char V_City[], Serials_Vec_Type& Ser_Vec, int Vec_Choose) {
	return Search_Flight_V_City_All(const_cast<char*>(V_City), Ser_Vec, Vec_Choose);
}




//把该顶点城市的所有航班 均压入向量
//正图 1 ： 从V_City出发
//反图　2 ：　到达V_City

//返回-3 选择不对
//返回-2 无顶点城市
//返回 2 成功

int AirTicSystem::Search_Flight_V_City_All(char V_City[], Serials_Vec_Type& Ser_Vec, int Vec_Choose) {
	if (Vec_Choose == 1 || Vec_Choose == 2) {
		vector<Vertex_City>& V_City_Vec = (Vec_Choose == 1) ? Pos_T_City_Vec : Neg_L_City_Vec;

		int V_Index = Index_OF_Pos_OR_Neg_City_Vec(V_City, Vec_Choose);
		if (V_Index < 0)
			return -2;
		else {
			auto  E_Ptr = V_City_Vec[V_Index].Edge_City_Head;
			int E_Flag = 1;
			for (; E_Ptr != NULL; E_Ptr = E_Ptr->Next_Edge_City) {
				Ser_Vec.insert(Ser_Vec.end(), E_Ptr->Flight_Serials.begin(), E_Ptr->Flight_Serials.end());
			}
			return 2;

		}


	}
	return -3;
}






int AirTicSystem::Search_Flight_In_Gragh(const char V_City[],const char E_City[], Serials_Vec_Type& Ser_Vec, int Vec_Choose) {
	return Search_Flight_In_Gragh(const_cast<char*>(V_City), const_cast<char*>(E_City), Ser_Vec, Vec_Choose);
}

//这个函数是搜索直达的
//返回-3 选择不对
//返回-2 无顶点城市
//返回 2 成功
//返回 1 无边城市
int AirTicSystem::Search_Flight_In_Gragh(char V_City[], char E_City[], Serials_Vec_Type& Ser_Vec, int Vec_Choose) {
	if (Vec_Choose == 1 || Vec_Choose == 2) {
		Ser_Vec.clear();
		vector<Vertex_City>& V_City_Vec = (Vec_Choose == 1) ? Pos_T_City_Vec : Neg_L_City_Vec;

		int V_Index = Index_OF_Pos_OR_Neg_City_Vec(V_City, Vec_Choose);
		if (V_Index < 0)
			return -2;
		else {
			auto  E_Ptr = V_City_Vec[V_Index].Edge_City_Head;
			int E_Flag = 1;
			for (; E_Ptr != NULL; E_Ptr = E_Ptr->Next_Edge_City) {
				E_Flag = strcmp(E_Ptr->Edge_City_Short, E_City);
				if (E_Flag == 0) break;
			}
			if (E_Flag == 0) {
				Ser_Vec.assign(E_Ptr->Flight_Serials.begin(), E_Ptr->Flight_Serials.end());
				return 2;
			}
			else
				return 1;

		}


	}
	return -3;

}


//搜索两个城市 之间一次中转

void AirTicSystem::Search_Transit(char T_City[], char L_City[], multimap<Serial_Type, Serial_Type>& Sers_Map) {

	Serials_Vec_Type T_Sers, L_Sers;
	Search_Flight_V_City_All(T_City, T_Sers, 1);
	Search_Flight_V_City_All(L_City, L_Sers, 2);
	vector<string> T_Ser_Vec, L_Ser_Vec;



	if ((T_Sers.size() != 0) && (L_Sers.size() != 0)) {
		Search_Transit(T_Sers, L_Sers, Sers_Map);
	}
	return;

}


//在已筛选的航班流水号之间进行中转

void AirTicSystem::Search_Transit(Serials_Vec_Type T_Sers, Serials_Vec_Type L_Sers, multimap<Serial_Type, Serial_Type>& Sers_Map) {

	vector<string> T_Ser_Vec, L_Ser_Vec;
	if ((T_Sers.size() != 0) && (L_Sers.size() != 0)) {
		for (auto T_Iter = T_Sers.begin();
			T_Iter != T_Sers.end(); T_Iter++) {
			Split_Ser_Info((*T_Iter), T_Ser_Vec);
			for (auto L_Iter = L_Sers.begin();
				L_Iter != L_Sers.end(); L_Iter++) {
				Split_Ser_Info((*L_Iter), L_Ser_Vec);
				unsigned long long T_Stamp = stoll(T_Ser_Vec[5]) * 10000 + stol(T_Ser_Vec[6]);
				unsigned long long L_Stamp = stoll(L_Ser_Vec[3]) * 10000 + stol(L_Ser_Vec[4]);
				if ((T_Ser_Vec[1] == L_Ser_Vec[0] )&&(T_Stamp <= L_Stamp))
					Sers_Map.insert({ (*T_Iter),(*L_Iter) });

			}
		}
	}
}


void AirTicSystem::Rank_Ser_Map_Price(const multimap<Serial_Type, Serial_Type>& Sers_Map, multimap<float, pair<Serial_Type, Serial_Type> >& Sers_Map_In_Price) {
	for (auto S_Iter = Sers_Map.begin();
		S_Iter != Sers_Map.end(); S_Iter++) {
		Flight Fir, Sec;
		Search_Flight(S_Iter->first, Fir);
		Search_Flight(S_Iter->second,Sec);
		float total = Fir.Tic_Price + Sec.Tic_Price;
		Sers_Map_In_Price.insert({ total,{S_Iter->first,S_Iter->second} });

	}
	return;

}

bool AirTicSystem::Is_In_City_Map(string City_Short) {
	auto iter = City_Short_Map.find(City_Short);
	if (iter == City_Short_Map.end())
		return false;
	return true;
}

Serials_Vec_Type AirTicSystem::Search_Flight_In_Condition() {
	Serials_Vec_Type Sers_All_Vec, T_All_Vec, L_All_Vec;
	set<Serial_Type> Sers_Set;
	while (1)
	{
		string T_City, L_City;
		cout << "输入起飞城市三字代码  ";
		cin >> T_City;
		while (!Is_In_City_Map(T_City))
		{
			cout << "输入城市有误" << endl;
			cin >> T_City;
		}

		cout << "输入到达城市三字代码  ";
		cin >> L_City;
		while (!Is_In_City_Map(L_City))
		{
			cout << "输入城市有误" << endl;
			cin >> L_City;
		}


		Serials_Vec_Type Sers_All_Vec, T_All_Vec, L_All_Vec;
		
		Search_Flight_V_City_All(T_City.c_str(), T_All_Vec, 1);
		Search_Flight_V_City_All(L_City.c_str(), L_All_Vec, 2);
		int cor = Search_Flight_In_Gragh(T_City.c_str(), L_City.c_str(), Sers_All_Vec, 1);
		if (Sers_All_Vec.size() != 0) {
			cout << "二者之间的直达航班有：" << endl;
			Print_Flight_Serials_Vec_To_Terminal(Sers_All_Vec);
			cout << "按价格排序后有： " << endl;
			Serials_Vec_Type Ser_Price;
			Rank_Ser_Vec_Price(Sers_All_Vec, Ser_Price);
			Print_Flight_Serials_Vec_To_Terminal(Ser_Price);
			int i; 
			cout << "您要购买第几张？ 1 -- "<<Ser_Price.size() << endl;
			cin >> i;
			for (; i > 0; cin >> i) {
				if (i > Ser_Price.size()) {
					cout << "超过范围,重新输入" << endl;
				}
				else {
					Sers_Set.insert(Ser_Price[i - 1]);
					cout << "还想购买第i张，输入0退出";
				}
			}
			break;
		}
		else {
			cout << "二者之间没有直达航班" << endl;

			string T_Date, L_Date;
			Serials_Vec_Type T_Date_Vec, L_Date_Vec;
			cout << "输入起飞日期（按照yyyy/mm/dd）" << endl;
			cin >> T_Date;
			cout << "输入最晚降落日期，（按照yyyy/mm/dd）" << endl;
			cin >> L_Date;


			Fliter_Ser_Vec_By_Date(T_Date.c_str(), L_Date.c_str(), T_All_Vec, T_Date_Vec);
			Fliter_Ser_Vec_By_Date(T_Date.c_str(), L_Date.c_str(), L_All_Vec, L_Date_Vec);
			Print_Flight_Serials_Vec_To_Terminal(T_Date_Vec);
			Print_Flight_Serials_Vec_To_Terminal(L_Date_Vec);
			multimap<Serial_Type, Serial_Type> transit_map;
			Search_Transit(T_Date_Vec, L_Date_Vec, transit_map);
			multimap<float, pair<Serial_Type, Serial_Type> > trans_map_in_price;
			Rank_Ser_Map_Price(transit_map, trans_map_in_price);


			multimap<int, pair<Serial_Type, Serial_Type> > trans_map_in_price_temp;
			int index = 1;
			if (trans_map_in_price.size() != 0) {
				cout << "总价格\t\t第一个航班流水号为\t\t 第二个航班流水号为" << endl;
				for (auto iter = trans_map_in_price.begin();
					iter != trans_map_in_price.end(); iter++) {
					cout << iter->first << "    ";
					Print_Flight_To_Termimal_In_Ser(iter->second.first);
					cout << "\t";
					Print_Flight_To_Termimal_In_Ser(iter->second.second);
					cout << endl;
					trans_map_in_price_temp.insert({ index,iter->second });
					index++;
				}

				int i;
				cout << "你想要购买哪两个中转航班 1 -- " << transit_map.size() << endl;
				cin >> i;
				for (; i > 0; cin >> i) {
					if (i > transit_map.size()) {
						cout << "超过范围，重新输入" << endl;
					}
					else {
						auto Pair_Iter = trans_map_in_price_temp.find(i);
						if (Pair_Iter == trans_map_in_price_temp.end())
							continue;
						else {
							pair<Serial_Type,Serial_Type> Pair_Vec;
							Pair_Vec = Pair_Iter->second;
							Sers_Set.insert(Pair_Vec.first);
							Sers_Set.insert(Pair_Vec.second);
							cout << "还想购买 输入i，否则输入0退出" << endl;
						}
					}
				}
				break;
			}
			else {
				cout << "这两城市之间无法中转到达" << endl;
			}
		}
			
		
			
	}
	Serials_Vec_Type To_Return;
	insert_iterator<Serials_Vec_Type> V_init(To_Return, To_Return.begin());
	copy(Sers_Set.begin(), Sers_Set.end(), V_init);
	sort(To_Return.begin(), To_Return.end());
	return To_Return;
}



void AirTicSystem::Book_Flight_Tics(const Serials_Vec_Type& To_Book_Vec, const Serials_Vec_Type& Haved_Vec, Serials_Vec_Type& Booked_Vec) {
	Booked_Vec.clear();
	Serials_Vec_Type Real_To_Book = To_Book_Vec;
	auto read_iter = set_difference(To_Book_Vec.begin(), To_Book_Vec.end(), Haved_Vec.begin(), Haved_Vec.end(), Real_To_Book.begin());
	Real_To_Book.resize(read_iter - Real_To_Book.begin());
	for (auto V_Iter = Real_To_Book.begin();
		V_Iter != Real_To_Book.end(); V_Iter++) {
		auto M_Iter = Ser_Flight_Map.find(*V_Iter);
		if (M_Iter == Ser_Flight_Map.end()) {
			cout << "未找到该航班  ";
			cout << (*V_Iter) << endl;
			continue;
		}
		else
		{
			if (M_Iter->second.Cur_Order >= M_Iter->second.Max_Seats){
				cout << "已满员" << endl;
				continue;
			}
			else {
				M_Iter->second.Cur_Order++;
				cout << "订票成功" << endl;
				Booked_Vec.push_back(M_Iter->first);

			}
		}
	}

}





Serials_Vec_Type AirTicSystem::Choose_Tics_To_Cancel(const Serials_Vec_Type& All_In_Cus) {
	if (All_In_Cus.size() != 0) {
		cout << "您一共购买了 " << All_In_Cus.size() << " 张票" << endl;
		int i = 1;
		for (auto V_Iter = All_In_Cus.begin();
			V_Iter != All_In_Cus.end(); V_Iter++) {
			if (Ser_Flight_Map.find(*V_Iter) == Ser_Flight_Map.end()) {
				
				cout << " 第 " << i << " 张 ";
				cout << "无此航班  " << (*V_Iter) << endl;
				i++;
				continue;
			}
			cout << " 第 " << i << " 张 ";
			Print_Flight_To_Termimal_In_Ser(*V_Iter);
			i++;
		}
		Serials_Vec_Type To_Cancel_Vec;
		set<Serial_Type> To_Cancel_Set;
		cout << "输入想退票的标号(0是不需要退票，直接退出)" << endl;
		int choice ;
		cin >> choice;
		while (choice!=0)
		{
			To_Cancel_Set.insert(All_In_Cus[choice-1]);
			cout << "将继续输入(0是退出)" << endl;
			cin >> choice;
		}
		insert_iterator<Serials_Vec_Type> V_init(To_Cancel_Vec, To_Cancel_Vec.begin());
		copy(To_Cancel_Set.begin(), To_Cancel_Set.end(), V_init);



		return To_Cancel_Vec;
	}

}


void AirTicSystem::Cancel_Flight_Tics(const Serials_Vec_Type& To_Cancel_Vec, Serials_Vec_Type& Canceled_Vec){

	for (auto V_Iter = To_Cancel_Vec.begin();
		V_Iter != To_Cancel_Vec.end(); V_Iter++) {
		auto M_Iter = Ser_Flight_Map.find(*V_Iter);
		if (M_Iter == Ser_Flight_Map.end()) {
			cout << "未找到该航班  ";
			cout << (*V_Iter) << endl;
			continue;
		}
		else
		{
			M_Iter->second.Cur_Order--;
			cout << "退票成功" << endl;
			Canceled_Vec.push_back(M_Iter->first);
		}
		
	}

}



