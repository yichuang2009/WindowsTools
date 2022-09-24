#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

namespace talk {
	void DouBan (string str){
		str = "douban.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void WeiBo (string str){
		str = "weibo.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
	void ZhiHu (string str){
		str = "zhihu.bat " + str;
		const char* cmd = str.c_str ();
		system (cmd);
	}
}
