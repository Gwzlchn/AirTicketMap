#ifndef COMMON_HPP
#define COMMON_HPP
#include<string>
#include<vector>

using std::string;
using std::vector;

bool All_Is_Alpha(string str);
bool All_Is_Num(string str);

void Split_Row(string str, string separator, vector<string> &result);


#endif // !COMMON_HPP






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