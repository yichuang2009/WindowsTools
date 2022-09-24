#include <bits/stdc++.h>
#include <windows.h>
#include <winbase.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
#include <winnt.h>
//#include <Netlistmgr.h>

using namespace std;

bool IsAdminProcess(int PID) { //判断管理员权限
    if (PID <= 0)
        PID = GetCurrentProcessId();
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, PID);
    if (hProcess == NULL) {//要么没这个进程，要么也有可能是ADMIN权限无法打开
        return TRUE;
    }
    HANDLE hToken;
    DWORD dwAttributes;
    DWORD isAdmin(0);
    if (OpenProcessToken(hProcess, TOKEN_QUERY, &hToken)){
        SID_IDENTIFIER_AUTHORITY Authority;
        Authority.Value[5] = 5;

        PSID psidAdmin = NULL;
        if (AllocateAndInitializeSid(&Authority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &psidAdmin)){
            DWORD dwCount = 0;
            GetTokenInformation(hToken, TokenGroups, NULL, 0, &dwCount);
            TOKEN_GROUPS *pTokenGroups = (TOKEN_GROUPS *)new BYTE[dwCount];
            GetTokenInformation(hToken, TokenGroups, pTokenGroups, dwCount, &dwCount);
            DWORD dwGroupCount = pTokenGroups->GroupCount;
            for (DWORD i = 0; i < dwGroupCount; i++)
                if (EqualSid(psidAdmin, pTokenGroups->Groups[i].Sid)){
                    dwAttributes = pTokenGroups->Groups[i].Attributes;
                    isAdmin = (dwAttributes & SE_GROUP_USE_FOR_DENY_ONLY) != SE_GROUP_USE_FOR_DENY_ONLY;
                    break;
                }
            delete[] pTokenGroups;
            FreeSid(psidAdmin);
        }
        CloseHandle(hToken);
    }
    CloseHandle(hProcess);
    return isAdmin;
}

void ManagerRun (LPCSTR exe, LPCSTR param, int nShow = SW_SHOW){
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof (SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = "runas";
	ShExecInfo.lpFile = exe;
	ShExecInfo.lpParameters = param;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = nShow;
	ShExecInfo.hInstApp = NULL;
	bool ret = ShellExecuteEx (&ShExecInfo);
	CloseHandle (ShExecInfo.hProcess);
	return ;
}

void hideCursor (){
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = 0;
	cursor.dwSize = 1;
	HANDLE hOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo (hOut, &cursor);
}

//bool CheckInternet (){
//	bool InternetSuccess = true;
//	CoInitialize (NULL);
//	IUnknown *pUnknown = NULL;
//	HRESULT Result = CoCresteInstance (CLSID_NetworkListManager, NULL, CLSCTX_ALL, IID_Iunknown, (void **)&pUnknown);
//	if (SUCCEEDED (Result)){
//		INetworkListManager *pNetworkListManager = NULL;
//		if (pUnknown) Result = pUnknown -> QueryInterface (IID_INetworkListManager, (void **)&pNetworkListManager);
//		if (SUCCEEDED (Result)){
//			VARIANT_BOOL IsConnect = VARIANT_FALSE;
//			if (pNetworkListManager) Result = pNetworkListManager -> get_IsConnectedToInternet (&IsConnect);
//			if (SUCCEEDED (Result)) bol = (IsConnect == VARIANT_TURE) ? true : false;
//		}
//	}
//	if (pNetworkListManager) pNetworkListManager -> Release ();
//	CoUninitialize ();
//	return bol;
//}

bool Notice_to_users (){
	puts ("用户须知");
	puts ("1. 本程序将会更改系统重要文件。");
	puts ("2. 本程序将会使用到管理员权限。");
	puts ("3. 本程序可能会更改本系统的激活情况。");
	puts ("4. 本程序将用到dism，需要联网食用。");
	puts ("是否同意本程序在本电脑上运行？");
	puts ("同意输入Y, 不同意输入其他字符");
	puts ("");

	char input = getch ();
	
	return (input == 'Y' || input == 'y');
}

void System_optimization (){
    puts ("开始尝试优化系统");
    puts ("检查分区......");
    system ("@chkdsk /v");
    puts ("优化服务......");
    system ("sc stop sysmain");
    system ("sc config sysmain start= disabled");
//    puts ("优化完毕！");
//    Sleep (1000);
//    system ("cls");
}

void System_activation (){
	puts ("准备激活......");
	Sleep (2000);
	puts ("开始激活。当弹出对话框时，请确认。");
	Sleep (1000);
	system ("slmgr.vbs -upk");
//	system ("slmgr.vbs -ipk ");
	system ("slmgr.vbs -ipk KH2J9-PC326-T44D4-39H6V-TVPBY");
	system ("slmgr.vbs -skms kms.cangshui.net");
	system ("slmgr.vbs -ato");
	system ("slmgr.vbs -dlv");
}

void DismTools (){
//	CheckInternet ();
	puts ("检查映像是否可修复......");
	system ("Dism /Online /Cleanup-Image /ScanHealth");
	system ("Dism /Online /Cleanup-Image /CheckHealth");
	puts ("尝试修复映像......");
	system ("DISM /Online /Cleanup-image /RestoreHealth");
	system ("分析组件储存并清理......");
	system ("Dism.exe /Online /Cleanup-Image /AnalyzeComponentStore");
}

int main (int argc, char *argv[]){
	if (argc == 1){
		
		bool success = Notice_to_users ();
		if (success){
			puts ("好的！感谢您使用本程序。");
			Sleep (2000);
			system ("cls");
		}
		else exit (0);
		
		puts ("尝试获取管理员权限......");
		Sleep (2000);
		ShowWindow (GetConsoleWindow (), SW_HIDE);
		ManagerRun (argv[0], "2");
		return 1;
	}
	else if (argc == 2){
//		puts ("Getting the current program pid......");
//		int PID = getpid ();
//		Sleep (1000);
////		IntToString (PID);
//		if (!IsAdminProcess (PID)){
//			puts ("请以管理员身份运行!");
//			puts ("此程序将在3秒后结束。");
//			Sleep (3000);
//			exit (0);
//		}
		
		hideCursor ();
		
		while (true){
			system ("cls");
			
			puts ("1.快速优化系统");
			puts ("2.自动系统激活（暂只支持Windows10与Windows11系统）");
			puts ("3.系统修复（须在联网状况下使用）");
			puts ("4.退出");
			puts ("");
			puts ("请输入：");
			
			char input = getch ();
			
			system ("cls");
			
			if (input == '1') {
				System_optimization ();
				system ("@sfc /SCANNOW");
				puts ("优化完毕！");
				Sleep (2000);
				system ("cls");
			}
 		    else if (input == '2') {
 		    	System_activation ();
 		    	puts ("激活完毕！");
 		    	Sleep (1000);
 		    	puts ("是否要自动重启？(Y确认/其他字符关闭)");
 		    	char check = getch ();
 		    	if (check == 'Y') system ("shutdown -r -t 10");
 		    }
// 		    else if (input == '3') {
// 		    	string SecretKey = NULL;
// 		    	puts ("请输入密钥");
// 		    	cin >> SecretKey;
// 		    	
// 		    	bool KeySuccess = true;
// 		    	if (SecretKet.size () != 29){
// 		    		KeySuccess = false;
// 		    		puts ("对不起，您的密钥不合法。");
// 		    		Sleep (2000);
// 		    		continue;
// 		    	}
// 		    	for (int i = 0; i < Secret.size (); i ++ ){
// 		    		if ((i == 5 || i == 11 || i == 17 || i == 23) && i != '-'){
// 		    			KeuSuccess = false;
// 		    			break;
// 		    		}
// 		    		else if (!(('0' <= SecretKey[i] && SecretKey[i] <= '9') || ('A' <= SecretKey[i] && SecretKey[i] <= 'Z'))){
// 		    			KeySuccess = false;
// 		    			break;
// 		    		}
// 		    	}
// 		    	if (!KeySuccess){
// 		    		puts ("对不起，您的密钥不合法。");
// 		    		Sleep (2000);
// 		    		continue;
// 		    	}
// 		    	
// 		    	System_activation (SecretKey, true);
// 		    }
// 		    else if (input == '3') {
// 		    	puts ("对不起，此功能暂未开放！");
// 		    	Sleep (2000);
// 		    }
			else if (input == '3') {
				DismTools ();
				puts ("尝试修复完毕！");
				Sleep (2000);
			}
 		    else if (input == '4') exit (0);
 		    else {
 		    	puts ("对不起，您输入的序号无效。请重新输入。");
 		    	Sleep (2000);
 		    }
		}
	}
	return 0;
}
