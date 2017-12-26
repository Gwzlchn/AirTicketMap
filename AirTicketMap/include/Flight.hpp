
#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include<string>
#include<vector>

using std::string;
using std::vector;
typedef string Serial_Type;			//机票流水号
typedef vector<Serial_Type> Serials_Vec_Type;

#define LSIZE 32
#define MSIZE 8
#define SHSIZE 4

struct Flight							//航班信息
{
	char T_City[MSIZE*2];				//起飞城市		0
	char T_City_Short[SHSIZE];			//起飞城市缩写	1
	char L_City[MSIZE*2];				//到达城市		2
	char L_City_Short[SHSIZE];			//到达城市缩写	3

	char Flight_CO[LSIZE];      		//航空公司		4
	char Flight_ID[MSIZE];				//航班号		5
	
	char T_Airport[LSIZE];				//起飞机场		6
	char L_Airport[LSIZE];				//到达机场		7

	char T_Time[SHSIZE+2];    			//起飞时刻		8
	char T_Time_Stamp[LSIZE];			//起飞时间戳	9

	char L_Time[SHSIZE+2];    			//到达时刻		10
	char L_Time_Stamp[LSIZE];			//到达时间戳	11


	char Aircraft_Type[SHSIZE];			//机型			12

	char Date[MSIZE+3];    				//日期			13

	float M_Discount;    				//最大折扣		14
	float Tic_Price;					//机票单价		15
	
	int Max_Seats;						//满载人员		16
	int Cur_Order;						//当前已定人数	17

	Serial_Type  Serial_NO;			//机票流水号 = 起飞机场 + 降落机场 + 航班号 +　起飞时间戳 +　降落时刻
};
Flight Create_New_Flight(vector<string> Line_Data);
Flight Create_New_Flight();


struct Customer								//顾客信息
{
	Serials_Vec_Type Flight_Serials;	//购买的所有机票（保存流水号）
	char Customer_Name[MSIZE];				//顾客姓名
	char IDcard[LSIZE];						//身份证号
	int Tic_Bought;							//该顾客名下所购机票数
};


#endif // !FLIGHT_HPP
