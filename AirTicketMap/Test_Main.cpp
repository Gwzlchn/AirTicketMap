#include "include\AirTicSystem.hpp"
#include<iostream>

const char* File_Name = "..\\RawData\\AirlineDataRAW_GBK.csv";
using namespace std;

int main() {
	AirTicSystem test(File_Name);
	string ID = "CA4188";
	Serials_Vec_Type Serials;
	test.Search_Flight_ByID(ID, Serials);
	//test.Search_Flight()
	cout << Serials[0] << endl;
	cout << Serials[1] << endl;
	Flight Ans_Flight;
	
	cout << endl;
	test.Print_Flight_Serials_Vec_To_Terminal(Serials);


	return 0;
}