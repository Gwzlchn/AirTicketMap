#include<iostream>
#include"AirTicSystem.hpp"
using namespace std;


int main() {
	//如果windows系统，打开gbk编码文件
	AirTicSystem test("test_GBK.csv");

	//如果mac系统，打开utf8 without BOM 编码文件
	//AirTicSystem test("test_UTF8.csv");

	vector<Flight> F_Vec;
	//test.Print_To_Terminal();
	test.Print_To_File("testOut.dat");
	
	string sear = "AATURCCZ6684201711011110";
	int a = test.Search_Flight(sear,F_Vec);
	test.Print_Flight_Vec_To_Terminal(F_Vec);
	cout << a;
	return 0;
}