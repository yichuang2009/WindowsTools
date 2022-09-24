#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

namespace warehouse {
	void Github (string str){
		str = "github.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void Gitee (string str){
		str = "gitee.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
}
