#include <bits/stdc++.h>
#include <windows.h>
#include <winbase.h>
#include <unistd.h>
#include <stdlib.h>
#include <conio.h>
#include <winnt.h>
//#include <Netlistmgr.h>

using namespace std;

bool IsAdminProcess(int PID) { //�жϹ���ԱȨ��
    if (PID <= 0)
        PID = GetCurrentProcessId();
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, PID);
    if (hProcess == NULL) {//Ҫôû������̣�ҪôҲ�п�����ADMINȨ���޷���
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
	puts ("�û���֪");
	puts ("1. �����򽫻����ϵͳ��Ҫ�ļ���");
	puts ("2. �����򽫻�ʹ�õ�����ԱȨ�ޡ�");
	puts ("3. ��������ܻ���ı�ϵͳ�ļ��������");
	puts ("4. �������õ�dism����Ҫ����ʳ�á�");
	puts ("�Ƿ�ͬ�Ȿ�����ڱ����������У�");
	puts ("ͬ������Y, ��ͬ�����������ַ�");
	puts ("");

	char input = getch ();
	
	return (input == 'Y' || input == 'y');
}

void System_optimization (){
    puts ("��ʼ�����Ż�ϵͳ");
    puts ("������......");
    system ("@chkdsk /v");
    puts ("�Ż�����......");
    system ("sc stop sysmain");
    system ("sc config sysmain start= disabled");
//    puts ("�Ż���ϣ�");
//    Sleep (1000);
//    system ("cls");
}

void System_activation (){
	puts ("׼������......");
	Sleep (2000);
	puts ("��ʼ����������Ի���ʱ����ȷ�ϡ�");
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
	puts ("���ӳ���Ƿ���޸�......");
	system ("Dism /Online /Cleanup-Image /ScanHealth");
	system ("Dism /Online /Cleanup-Image /CheckHealth");
	puts ("�����޸�ӳ��......");
	system ("DISM /Online /Cleanup-image /RestoreHealth");
	system ("����������沢����......");
	system ("Dism.exe /Online /Cleanup-Image /AnalyzeComponentStore");
}

int main (int argc, char *argv[]){
	if (argc == 1){
		
		bool success = Notice_to_users ();
		if (success){
			puts ("�õģ���л��ʹ�ñ�����");
			Sleep (2000);
			system ("cls");
		}
		else exit (0);
		
		puts ("���Ի�ȡ����ԱȨ��......");
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
//			puts ("���Թ���Ա�������!");
//			puts ("�˳�����3��������");
//			Sleep (3000);
//			exit (0);
//		}
		
		hideCursor ();
		
		while (true){
			system ("cls");
			
			puts ("1.�����Ż�ϵͳ");
			puts ("2.�Զ�ϵͳ�����ֻ֧��Windows10��Windows11ϵͳ��");
			puts ("3.ϵͳ�޸�����������״����ʹ�ã�");
			puts ("4.�˳�");
			puts ("");
			puts ("�����룺");
			
			char input = getch ();
			
			system ("cls");
			
			if (input == '1') {
				System_optimization ();
				system ("@sfc /SCANNOW");
				puts ("�Ż���ϣ�");
				Sleep (2000);
				system ("cls");
			}
 		    else if (input == '2') {
 		    	System_activation ();
 		    	puts ("������ϣ�");
 		    	Sleep (1000);
 		    	puts ("�Ƿ�Ҫ�Զ�������(Yȷ��/�����ַ��ر�)");
 		    	char check = getch ();
 		    	if (check == 'Y') system ("shutdown -r -t 10");
 		    }
// 		    else if (input == '3') {
// 		    	string SecretKey = NULL;
// 		    	puts ("��������Կ");
// 		    	cin >> SecretKey;
// 		    	
// 		    	bool KeySuccess = true;
// 		    	if (SecretKet.size () != 29){
// 		    		KeySuccess = false;
// 		    		puts ("�Բ���������Կ���Ϸ���");
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
// 		    		puts ("�Բ���������Կ���Ϸ���");
// 		    		Sleep (2000);
// 		    		continue;
// 		    	}
// 		    	
// 		    	System_activation (SecretKey, true);
// 		    }
// 		    else if (input == '3') {
// 		    	puts ("�Բ��𣬴˹�����δ���ţ�");
// 		    	Sleep (2000);
// 		    }
			else if (input == '3') {
				DismTools ();
				puts ("�����޸���ϣ�");
				Sleep (2000);
			}
 		    else if (input == '4') exit (0);
 		    else {
 		    	puts ("�Բ���������������Ч�����������롣");
 		    	Sleep (2000);
 		    }
		}
	}
	return 0;
}
