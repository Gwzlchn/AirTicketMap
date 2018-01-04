#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP

#include<string>
#include<vector>

using std::string;
using std::vector;
using std::stoi;

bool All_Is_Alpha(string str);
bool All_Is_Num(string str);

void Split_Row(string str,  string separator, vector<string> &result);


int Char_Time_To_Int(char C_Time[6]);

int is_number(char c);

int check_time_fomart(char time[]);

long Char_Date_To_Long(char C_Date[]);





#endif // !COMMON_HPP






