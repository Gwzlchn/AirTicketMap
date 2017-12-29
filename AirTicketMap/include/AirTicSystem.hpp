
#ifndef AIRTICSYSTEM_HPP
#define AIRTICSYSTEM_HPP

#include"Flight.hpp"
#include<map>
#include<unordered_map>



using	std::multimap;
using	std::map;





//正图、反图统一
//正图选1 反图选2

//边城市
struct Edge_City	
{
	friend class AirTicSystem;
	char Edge_City_Short[SHSIZE];
	Serials_Vec_Type Flight_Serials;			//只保存流水号
	Edge_City* Next_Edge_City;
};



//顶点城市
struct Vertex_City   
{
	friend class AirTicSystem;
	char Vertex_City_Short[SHSIZE];
	Edge_City *Edge_City_Head;
};






class AirTicSystem
{
protected:
	vector<Vertex_City>			Pos_T_City_Vec;			//正图，以出发地做顶点
	vector<Vertex_City>			Neg_L_City_Vec;			//反图，以目的地做顶点
private:
	//vector<Customer>			Customer_Vec;
	int Flight_Total_Count;								//总航线数
	int Flight_From_One_Count;							//一个机场出发总航线数

	//映射结构
	map<Serial_Type, Flight>				Ser_Flight_Map;		//流水号到航班信息的映射
	multimap<string ,Serial_Type>		FlightID_Ser_Map;	//航班号到流水号的映射
public:
	//构造，读写文件，输出函数
	AirTicSystem(const char* File_Name);
	
	void Create_Map_From_CSV(const char* File_Name);
	void Create_Pos_Neg_From_Map();

	void Print_ALL_To_Terminal();
	void Print_ALL_To_File(const char* File_Name);
	void Print_Flight_To_Termimal(Flight& One_Flight);
	void Print_Flight_Vec_To_Terminal(vector<Flight>& Flight_Vec);
	void Print_Flight_Serials_Vec_To_Terminal(Serials_Vec_Type& Serials_Vec);

	//插入到边链表 正图+反图
	bool Insert_Flight_To_Pos_OR_Neg_Graph(Vertex_City* V_City, Edge_City* E_City, const vector<string>& New_Ser_Vec,int Vec_Choose);
	bool Insert_Flight_To_Pos_OR_Neg_Graph(Vertex_City* V_City, Edge_City* E_City, const string New_Ser_Str, int Vec_Choose);
	bool Insert_Flight_To_Pos_OR_Neg_Graph(Flight& NewFlight);

	bool Insert_Flight_To_All(Flight& New_Flight);
	bool Insert_Flight_To_All(vector<string>& Whole_Line_Data);
	bool Insert_Flight_To_All(string Whole_Line_Raw);
	


	//查询航班函数，依据航班流水号（map find）
	int  Search_Flight(Serial_Type Flight_Seq, Flight& Ans_Flight);
	//通过航班 号查询，可能返回多个航班
	int Search_Flight_ByID(string Flight_ID, Serials_Vec_Type& Serials_Vec);
	
	
	

	//查询起飞城市是否存在 返回索引 负值不存在
	//int Index_OF_T_City_Vec(Flight_Serial_Type& Flight_Ser);
	//int Index_OF_T_City_Vec(vector<string>& Ser_Info);
	int Index_OF_Pos_OR_Neg_City_Vec(Vertex_City* V_City, int Vector_Choose);
	int Index_OF_Pos_OR_Neg_City_Vec(char V_City[3], int Vec_Choose);


	//分离流水号
	void Split_Ser_Info(Serial_Type Serial, vector<string>& A_Ser_Vec);
	void Merge_Ser_Info(Serial_Type& Serial, vector<string> A_Ser_Vec);
	//检查时间戳是否有效
	bool Check_Stamp(string& Stamp_To_Check) const;
	//检查流水号是否有效
	int  Check_Seq_Info(vector<string>& A_Ser_Vec) const;
};



#endif // !AIRTICSYSTEM_HPP



