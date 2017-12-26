#pragma once
#ifndef AIRTICSYSTEM_HPP
#define AIRTICSYSTEM_HPP

#include"Flight.hpp"
#include<map>
#include<unordered_map>

typedef vector<Flight> Flight_Vector;
using	std::vector;
using	std::string;
using	std::multimap;
using	std::map;


//正图
struct Pos_Land_City
{
	friend class AirTicSystem;
	char L_City_Short[SHSIZE];
	vector<Flight_Serial_Type> Flight_Serials;			//只保存流水号
	Pos_Land_City* Next_Pos_L_City;
};


//出发城市做顶点
struct  Pos_TakeOff_City										
{
	friend class AirTicSystem;
	char T_City_Short[SHSIZE];
	Pos_Land_City *Pos_L_City_Head;
};



struct Neg_TakeOff_City
{
	friend class AirTicSystem;
	char T_City_Short[SHSIZE];
	vector<Flight_Serial_Type> Flight_Serials;			//只保存流水号
	Neg_TakeOff_City* Next_Neg_T_City;
};


//反图
struct Neg_Land_City
{
	friend class AirTicSystem;
	char L_City_Short[SHSIZE];
	Neg_TakeOff_City* Neg_T_City_Head;
};





class AirTicSystem
{
private:
	vector<Pos_TakeOff_City>		Pos_T_City_Vec;						//边链表中顶点
	vector<Customer>			Customer_Vec;
	int Flight_Total_Count;								//总航线数
	int Flight_From_One_Count;							//一个机场出发总航线数


	//保存结构
	map<Flight_Serial_Type, Flight>				Ser_Flight_Map;		//流水号到航班信息的映射
	multimap<string ,Flight_Serial_Type>		FlightID_Ser_Map;	//航班号到流水号的映射
public:
	//构造，读写文件，输出函数
	AirTicSystem(const char* File_Name);
	
	void Create_Map_From_CSV(const char* File_Name);
	void ReadIn_From_Map();
	
	
	void Print_ALL_To_Terminal();
	void Print_ALL_To_File(const char* File_Name);
	void Print_Flight_To_Termimal(Flight& One_Flight);
	void Print_Flight_Vec_To_Terminal(Flight_Vector& Flight_Vec);

	//插入
	bool Insert_Flight(Pos_TakeOff_City* T_City, Pos_Land_City* L_Air, const Flight& NewFlight);

	//流水号内部全用vector<string>
	//其余均为包装形式
	//查询航班主函数，依据Ser_vec
	int Search_Flight(vector<string>& A_Ser_Vec, Flight& Ans_Flight);
	//查询航班函数，依据Flght_Seq字符串（调用上一个函数）
	int  Search_Flight(Flight_Serial_Type Flight_Seq, Flight& Ans_Flight);
	
	
	//通过航班 号查询，可能返回多个航班
	int  Search_Flight(string Flight_ID, vector<Flight> &All_Flight);

	//查询起飞城市是否存在 返回索引 负值不存在
	int Index_OF_T_City_Vec(Flight_Serial_Type& Flight_Ser);
	int Index_OF_T_City_Vec(vector<string>& Ser_Info);
	int Index_OF_T_City_Vec(Pos_TakeOff_City* T_AP);
	int Index_OF_T_City_Vec(char T_City[3]);


	//检查时间戳是否有效
	bool Check_Stamp(string& Stamp_To_Check) const;

	//分离流水号
	void Split_Ser_Info(Flight_Serial_Type Serial, vector<string>& A_Ser_Vec);
	//检查流水号是否有效
	int  Check_Seq_Info(vector<string>& A_Ser_Vec) const;
	
	



	

	

	
	
	
	
	

};



#endif // !AIRTICSYSTEM_HPP



