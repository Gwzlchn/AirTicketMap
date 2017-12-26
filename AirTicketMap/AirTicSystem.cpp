#pragma warning(disable:4996)
#include"AirTicSystem.hpp"
#include"Common.hpp"
#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;





//分离流水号
void AirTicSystem::Split_Seq_Info(string Seq, vector<string> &Seq_Vec) {
	Seq_Vec.push_back(Seq.substr(0, 3));
	Seq_Vec.push_back(Seq.substr(3, 3));
	Seq_Vec.push_back(Seq.substr(6, 6));
	Seq_Vec.push_back(Seq.substr(12, 12));
}


//从一行数据 新建航班数据
Flight Create_New_Flight(vector<string> Line_Data) {
	Flight New_Flight;

	strcpy(New_Flight.T_City, Line_Data[0].c_str());
	strcpy(New_Flight.L_City, Line_Data[1].c_str());
	strcpy(New_Flight.Flight_CO, Line_Data[2].c_str());
	strcpy(New_Flight.Flight_ID, Line_Data[3].c_str());
	strcpy(New_Flight.T_Airport, Line_Data[4].c_str());
	strcpy(New_Flight.T_Airport_Short, Line_Data[5].c_str());
	strcpy(New_Flight.L_Airport, Line_Data[6].c_str());
	strcpy(New_Flight.L_Airport_Short, Line_Data[7].c_str());
	strcpy(New_Flight.T_Time, Line_Data[8].c_str());
	strcpy(New_Flight.T_Time_Stamp, Line_Data[9].c_str());
	strcpy(New_Flight.L_Time, Line_Data[10].c_str());
	strcpy(New_Flight.L_Time_Stamp, Line_Data[11].c_str());
	strcpy(New_Flight.Aircraft_Type, Line_Data[12].c_str());
	strcpy(New_Flight.Date, Line_Data[13].c_str());
	
	New_Flight.Tic_Price = stof(Line_Data[14]);
	New_Flight.M_Discount = stof(Line_Data[17]);

	New_Flight.Max_Seats = stoi(Line_Data[16]);
	New_Flight.Cur_Order = stoi(Line_Data[17]);

	
	New_Flight.Sequence = Line_Data[5]+Line_Data[7]+Line_Data[3] + Line_Data[9];
	

	return New_Flight;
}




//构造函数
AirTicSystem::AirTicSystem(const char* File_Name)
{
	Airline_From_One_Count = 0;
	Airline_Total_Count = 0;
	ReadIn_From_CSV(File_Name);

}


void AirTicSystem::Print_Flight_Vec_To_Terminal(vector<Flight> Flight_Vec)
{
	for (auto F_Iter = Flight_Vec.begin();
		F_Iter != Flight_Vec.end(); F_Iter++)
		Print_Flight_To_Terminal(*F_Iter);
	
	return;
}

void AirTicSystem::Print_Flight_To_Terminal(Flight& One_Flight)
{
	cout << endl
		<< "  " << One_Flight.T_Airport_Short
		<< "  " << One_Flight.L_Airport_Short
		<< "  " << One_Flight.Flight_ID
		<< "  " << One_Flight.Aircraft_Type << endl
		<< "  " << One_Flight.Max_Seats << " / " << One_Flight.Cur_Order
		<< "  " << One_Flight.Date
		<< "  " << One_Flight.T_Time
		<< "  " << One_Flight.L_Time;

	return;
}


bool AirTicSystem::Insert_Flight(T_Airport* T_Air, L_Airport* L_Air, Flight New_Flight)
{
	int T_Index = Index_OF_T_City_Vec(T_Air);


	//flag==0说明该城市起飞顶点中存在
	if (T_Index>= 0) {
		T_Airport Temp_T_AP = T_City_Vec[T_Index];
		L_Airport* L_Ptr = Temp_T_AP.L_City_Head;

		int L_Flag = 1;
		for (; L_Ptr != NULL; L_Ptr = L_Ptr->Next_City) {
			L_Flag = strcmp(L_Ptr->L_Airport_Short, New_Flight.L_Airport_Short);
			if (L_Flag == 0) break;
		}

		//该降落顶点存在
		if (L_Flag == 0)
			L_Ptr->Flight_Info.push_back(New_Flight);

		//该降落顶点不存在
		else if (L_Flag != 0) {
			L_Airport* Temp_L_Ptr = Temp_T_AP.L_City_Head;
			while (Temp_L_Ptr->Next_City != NULL)
				Temp_L_Ptr = Temp_L_Ptr->Next_City;
			Temp_L_Ptr->Next_City = L_Air;
		}

	}
	//flag！=0说明一个新出发城市顶点
	else {
		T_Air->L_City_Head = L_Air;
		T_City_Vec.push_back((*T_Air));
	}

	return true;
}


//检查时间戳是否在时间范围内
//留坑待填 20171224-wzl
bool AirTicSystem::Check_Stamp(string & Stamp_To_Check) const
{
	return All_Is_Num(Stamp_To_Check);
}

//返回1 有效 : 流水号前六位为字母　最后起飞时间戳满足范围
//返回0 无效
//小坑……可以返回更多的值
int AirTicSystem::Check_Seq_Info(vector<string>& Info) const
{
	bool valid = All_Is_Alpha(Info[0]) && All_Is_Alpha(Info[1])
		&& Check_Stamp(Info[3]);
	
	return (valid == true)? 1 :0;

}


//返回值>=0 出发城市在T_City_Vec中，值为索引，留给插入航班函数用
//返回值-1 输入参数Flight_Seq 有误(不符合上述格式)
//返回-2 不存在出发地,
int AirTicSystem::Index_OF_T_City_Vec(vector<string>& Seq_Info)
{
	int Seq_Valid = Check_Seq_Info(Seq_Info);
	if (Seq_Valid) {
		return Index_OF_T_City_Vec(const_cast<char*>(Seq_Info[0].c_str()));
	}

	return -1; //if (Seq_Valid == 0) 形参字符串有误
}



int AirTicSystem::Index_OF_T_City_Vec(string & Flight_Seq)
{
	vector<string> Seq_Info;
	Split_Seq_Info(Flight_Seq, Seq_Info);
	return Index_OF_T_City_Vec(Seq_Info);
}

int AirTicSystem::Index_OF_T_City_Vec(T_Airport* T_AP)
{
	return Index_OF_T_City_Vec(T_AP->T_Airport_Short);
}

int AirTicSystem::Index_OF_T_City_Vec(char* T_City)
{
	int T_Flag = 1, T_Index = -1;
	for (vector<T_Airport>::iterator T_Iter = T_City_Vec.begin();
		T_Iter != T_City_Vec.end(); T_Iter++) {
		T_Flag = strcmp((*T_Iter).T_Airport_Short, T_City);
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




//机票流水号= 起飞机场+ 降落机场 + 航班号 +　起飞时间戳


//返回 3 存在该时间的该航班
//返回 2 存在该航班 但不是该时间
//返回  1 存在该出发地 目的地，但是不是该航班

//返回 -3  存在该出发地 无此目的地
//返回 -2 不存在该出发地

//返回-1 输入参数Flight_Seq 有误(不符合上述格式)

int AirTicSystem::Search_Flight(vector<string>& Seq_Info,  vector<Flight> &All_Flight)
{
	int Seq_Valid = Check_Seq_Info(Seq_Info);
	if (Seq_Valid) {
		int T_Index = Index_OF_T_City_Vec(Seq_Info);
		if (T_Index == -2) return -2; //返回 -2 不存在该出发地

		T_Airport Temp_T_AP = T_City_Vec[T_Index];
		L_Airport* L_Ptr = Temp_T_AP.L_City_Head;

		int L_Flag = 1;
		for (; L_Ptr != NULL; L_Ptr = L_Ptr->Next_City) {
			L_Flag = strcmp(L_Ptr->L_Airport_Short, Seq_Info[1].c_str());
			if (L_Flag == 0) break;
		}

		if (L_Flag != 0) 
			return -3; //存在该出发地,不存在该目的地
		else{		//存在该出发地、目的地
			
			int ID_Eq = 1,ID_Com = 1; 
			vector<int> ID_Flag_Vec;//默认不相等 相等置零 strcmp 或 compare 比较
			for(auto F_Iter =  L_Ptr->Flight_Info.begin();
					F_Iter!=L_Ptr->Flight_Info.end();F_Iter++){
				ID_Com = Seq_Info[2].compare((*F_Iter).Flight_ID);
				if(ID_Com == 0)
					All_Flight.push_back((*F_Iter));
			}
			if (All_Flight.size() != 0) {
				ID_Eq = 0;
				if (ID_Eq != 0)
					return 1; //存在该出发地 目的地，但是不是该航班
				else {
					int Time_Eq = 1, Time_Com = 1;
					for (auto F_Iter = L_Ptr->Flight_Info.begin();
						F_Iter != L_Ptr->Flight_Info.end(); F_Iter++) {
						Time_Com = Seq_Info[3].compare((*F_Iter).T_Time_Stamp);

						if (Time_Com == 0) {
							Time_Eq = 0;
							break;
						}
						
					}
					if (Time_Eq == 0)
						return 3;   //存在该时间的该航班
					else if (Time_Eq != 0)
						return 2;    //存在该航班 但不是该时间
				}
			}
		}
	}

	return -1;

}







int AirTicSystem::Search_Flight(string& Flight_Seq, vector<Flight> &All_Flight) {
	
	vector<string> Seq_Info;
	Split_Seq_Info(Flight_Seq, Seq_Info);
	vector<Flight> Flight_Vec;
	return Search_Flight(Seq_Info,Flight_Vec);
	
}


int AirTicSystem::Search_Flight(Flight& Flight_To_Search, vector<Flight> &All_Flight)
{
	vector<Flight> Flight_Vec;
	return Search_Flight(Flight_To_Search.Sequence,Flight_Vec);
}


void AirTicSystem::ReadIn_From_CSV(const char* File_Name)
{
	ifstream file(File_Name, ios::in);
	if (!file)
	{
		cerr << "打开文件失败";
		//system("PAUSE");
		
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
			Airline_Total_Count++;
			Flight New_Flight=Create_New_Flight(infRow);

			T_Airport* New_T_Ptr = new T_Airport;
			New_T_Ptr->L_City_Head = NULL;
			strcpy(New_T_Ptr->T_Airport_Short, New_Flight.T_Airport_Short);

			L_Airport* New_L_Ptr = new L_Airport;
			New_L_Ptr->Flight_Info.push_back(New_Flight);
			strcpy(New_L_Ptr->L_Airport_Short, New_Flight.L_Airport_Short);
			New_L_Ptr->Next_City = NULL;

			Insert_Flight(New_T_Ptr, New_L_Ptr, New_Flight);

		}
	}

}

void AirTicSystem::Print_To_Terminal()
{
	int cnt = 0;
	if (T_City_Vec.size() == 0) return;
	for (auto iter = T_City_Vec.begin();
		iter != T_City_Vec.end(); iter++) {
		cout << "FROM " << (*iter).T_Airport_Short << endl;
		L_Airport* Temp_L_Ptr = (*iter).L_City_Head;
		
		for (; Temp_L_Ptr != NULL; Temp_L_Ptr = Temp_L_Ptr->Next_City) {
			cout<< "\t TO " <<Temp_L_Ptr->L_Airport_Short << endl;

			for (auto Flight_Iter = Temp_L_Ptr->Flight_Info.begin();
				Flight_Iter != Temp_L_Ptr->Flight_Info.end(); Flight_Iter++) {
				cout << "\t" << (*Flight_Iter).T_Airport_Short
					<< " " << (*Flight_Iter).L_Airport_Short << endl
					<< "\tFlight ID " << (*Flight_Iter).Flight_ID << endl
					<< "\tFlight Price " << (*Flight_Iter).Tic_Price << endl
					<< "\tFlight Max Seats " << (*Flight_Iter).Max_Seats << endl
					<< "\tFlight Now Order " << (*Flight_Iter).Cur_Order << endl << endl;
				cnt++;
			}

		}



	}

	cout <<cnt <<endl;


	
}

void AirTicSystem::Print_To_File(const char* File_Name)
{
	ofstream Save_File(File_Name);
	if (!Save_File)
	{
		cerr << "打开文件失败";
		system("PAUSE");

	}
	int cnt = 0;
	if (T_City_Vec.size() == 0) return;
	for (auto iter = T_City_Vec.begin();
		iter != T_City_Vec.end(); iter++) {
		Save_File << "FROM " << (*iter).T_Airport_Short << endl;
		L_Airport* Temp_L_Ptr = (*iter).L_City_Head;

		for (; Temp_L_Ptr != NULL; Temp_L_Ptr = Temp_L_Ptr->Next_City) {
			Save_File << "\t TO " << Temp_L_Ptr->L_Airport_Short << endl;

			for (auto Flight_Iter = Temp_L_Ptr->Flight_Info.begin();
				Flight_Iter != Temp_L_Ptr->Flight_Info.end(); Flight_Iter++) {
				Save_File << "\t" << (*Flight_Iter).T_Airport_Short
					<< " " << (*Flight_Iter).L_Airport_Short << endl
					<< "\tFlight ID " << (*Flight_Iter).Flight_ID << endl
					<< "\tFlight Price " << (*Flight_Iter).Tic_Price << endl
					<< "\tFlight Max Seats " << (*Flight_Iter).Max_Seats << endl
					<< "\tFlight Now Order " << (*Flight_Iter).Cur_Order << endl << endl;
				cnt++;
			}

		}



	}

	Save_File << cnt << endl;
	Save_File.close();
	return;

}
