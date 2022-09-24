#include <windows.h>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

namespace library {
	void BaiduWenku (string str){
		str = "baiduwenku.bat " + str;
		const char* cmd = str.c_str();
		system (cmd);
	}
	void DouCin (string str) {
		str = "doucin.bat " + str;
		const char* cmd = str.c_str();
		system (cmd);
	}
}
