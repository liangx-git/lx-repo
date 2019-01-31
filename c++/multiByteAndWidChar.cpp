#include<iostream>
#include<locale>
#include<string>
#include<cstring>
using namespace std;

int main()
{
	/*
	locale china("chs");
	wcin.imbue(china);
	wcin.imbue(china);
	
	wstring wstr;
	wchar_t wc = L'。';
	while(getline(wcin, wstr))
	{
		wcout << endl << wstr << endl;
	}
	*/

	string s = "和和阿asd";
	const char *mc = s.c_str();
	wchar_t *wc = new wchar_t[50];
	setlocale(LC_ALL, "zn_CH.UTF-8");
	int count = mbstowcs(wc, mc, 50);
	cout << s.size() << "," << strlen(mc) << endl;
	cout << "一共有" << count << "个字节" << endl;

	return 0;
}

