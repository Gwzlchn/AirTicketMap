#include "..\include\Common.hpp"


bool All_Is_Alpha(string str) {
	for (size_t i = 0; i < str.size(); i++)
	{
		int tmp = (int)str[i];
		if (tmp >= 65 && tmp <= 122)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool All_Is_Num(string str)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		int tmp = (int)str[i];
		if (tmp >= 48 && tmp <= 57)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}




//解析csv文件的一行
void Split_Row(string str, string separator, vector<string> &result)
{//对每一行以逗号为分隔符进行分割
	result.clear();
	size_t cutAt;
	while ((cutAt = str.find_first_of(separator)) != str.npos)
	{
		if (cutAt > 0)
		{
			result.push_back(str.substr(0, cutAt));
		}
		str = str.substr(cutAt + 1);
	}
	if (str.length() > 0)
	{
		result.push_back(str);
	}
}

int Char_Time_To_Int(char C_Time[6])
{
	vector<string> T_Vec;
	string sep = ":";
	string T_Str(C_Time);
	Split_Row(T_Str, sep, T_Vec);
	int hour = stoi(T_Vec[0]);
	int min = stoi(T_Vec[1]);
	return hour * 100 + min;

}

long Char_Date_To_Long(char C_Date[])
{
	vector<string> D_Vec;
	string sep = "/";
	string D_Str(C_Date);
	Split_Row(D_Str, sep, D_Vec);
	int year = stoi(D_Vec[0]);
	int mm = stoi(D_Vec[1]);
	int dd = stoi(D_Vec[2]);

	return year * 10000 + mm * 100 + dd;

}

