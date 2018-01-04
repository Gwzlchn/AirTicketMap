#include "..\include\Common.hpp"
#include<windows.h>
#include<cstdio>
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


int is_number(char c)                 ///判断数字
{
	return (c >= '0' && c <= '9') ? 1 : 0;
}


int check_time_fomart(char time[])    ///检查时间格式
{
	int i = 0;
	unsigned int year = 0, month = 0, day = 0;
	unsigned int m[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (strlen(time) == 0)return 0;
	if (strlen(time) != 10)
	{
		printf("%d", strlen(time));
		MessageBox(NULL, TEXT("       日期格式不正确!\n正确格式:2017/01/01      "), TEXT("Error!"), MB_OK);
		return 0;
	}
	if (time[4] != '/' && time[7] != '/')return 0;
	for (i = 0; i<10; i++)
	{
		if (is_number(time[i])&& i != 4 && i != 7)
		{
			MessageBox(NULL, TEXT("       日期格式不正确!\n正确格式:2017/01/01      "), TEXT("Error!"), MB_OK);
			return 0;
		}
		if (i<4)
			year = 10 * year + (time[i] - '0');
		if (i>4 && i<7)
			month = 10 * month + (time[i] - '0');
		if (i>7)
			day = 10 * day + (time[i] - '0');
	}
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		m[1] = 29;
	if (!(month > 0 && month <= 12 && day > 0 && day <= m[month - 1]))
	{
		MessageBox(NULL, TEXT("        输入日期无效!      "), TEXT("Error!"), MB_OK);
		return 0;
	}
	return 1;
}

