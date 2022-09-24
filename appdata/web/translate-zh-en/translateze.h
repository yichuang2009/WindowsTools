#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

namespace trans_zh_en {
	void FanyiBaidu_ze (string str){
		str = "fanyibaidu-ze.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void Google_ze (string str){
		str = "translategoogle-ze.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
}
