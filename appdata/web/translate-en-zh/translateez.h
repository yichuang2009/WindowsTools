#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

namespace trans_en_zh {
	void FanyiBaidu_ez (string str){
		str = "fanyibaidu-ez.bat " + str;
		const char* cmd = str.c_str();
		system (cmd);
	}
	void Google_ez (string str){
		str = "translategoogle-ez.bat " + str;
		const char* cmd = str.c_str();
		system (cmd);
	}
}
