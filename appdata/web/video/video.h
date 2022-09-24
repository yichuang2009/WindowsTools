#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

namespace video {
	void HeiMa (string str){
		str = "heima.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void Tencent (string str){
		str = "tencent.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void WangYi (string str){
		str = "wangyi.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void XueTang (string str){
		str = "xuetang.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
}
