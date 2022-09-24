#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

namespace search {
	void _360 (string str){
		str = "360.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void Baidu (string str){
		str = "baidu.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void Bing (string str){
		str = "bing.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void Google (string str){
		str = "google.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void sogou (string str){
		str = "sogou.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
}
