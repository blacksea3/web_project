// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "TaskInfo.h"

/*************************************TaskInfo*************************************/
TaskInfo* TaskInfo::Instance()
{
	if (_ptaskinfo == NULL)
	{
		_ptaskinfo = new TaskInfo();
	}
	else
	{
		std::cout << "TaskInfo instance already ouucrs" << std::endl;
	}
	return _ptaskinfo;
}

TaskInfo::TaskInfo()
{
	_p_structtaskinfo = new StructTaskInfo[50];	
	_taskinfo_loc = 0;
	std::cout << "TaskInfo created" << std::endl;
}

TaskInfo::~TaskInfo()
{
	delete[] _p_structtaskinfo;
	std::cout << "TaskInfo deleted" << std::endl;
}

//����������Ϣ,
//type:0�ö�,1��ͨ
void TaskInfo::append_structtaskinfo(const CString& classname, const CString& windowtext, 
	const CString& processname, int type)
{
	if (_taskinfo_loc >= _MAX_TASKINFO_LENGTH)
	{
		std::cout << "FATAl ERROR, EXCEED MAX_taskinfo_loc" << std::endl;
	}
	else
	{
		_p_structtaskinfo[_taskinfo_loc].classname = classname;
		_p_structtaskinfo[_taskinfo_loc].windowtext = windowtext;
		_p_structtaskinfo[_taskinfo_loc].processname = processname;
		_p_structtaskinfo[_taskinfo_loc].type = type;
		_taskinfo_loc++;
	}
}

//����ö�������Ϣ
void TaskInfo::get_top_window()
{
	//��ô���
	HWND tophwnd;
	tophwnd = GetForegroundWindow();
	CString strTopClassName = _T("");
	GetClassName(tophwnd, strTopClassName.GetBuffer(256), 256);
	CString strTopWindowText = _T("");
	GetWindowText(tophwnd, strTopWindowText.GetBuffer(256), 256);

	//��ý���
	DWORD dwProcessID;
	DWORD dwXianChenID;
	dwXianChenID = GetWindowThreadProcessId(tophwnd, &dwProcessID);
	CString processName;
	get_process_name(processName, dwProcessID);

	//���Ӵ�����Ϣ
	append_structtaskinfo(strTopClassName, strTopWindowText, processName, 0);
}

//���ȫ��������Ϣ
void TaskInfo::get_windows()
{
	//1.�Ȼ�����洰��
	CWnd* pDesktopWnd = CWnd::GetDesktopWindow();
	//2.���һ���Ӵ���
	CWnd* pWnd = pDesktopWnd->GetWindow(GW_CHILD);

	HWND hwnd;
	//3.ѭ��ȡ�������µ������Ӵ���
	while (pWnd != NULL)
	{
		hwnd = pWnd->GetSafeHwnd();

		//Shell_TrayWnd ����������
		//Progman ����
		if (!GetWindow(hwnd, GW_OWNER) && IsWindowVisible(hwnd))
		{
			CString strClassName = _T("");
			GetClassName(hwnd, strClassName.GetBuffer(256), 256);
			CString strWindowText = _T("");
			GetWindowText(hwnd, strWindowText.GetBuffer(256), 256);

			strClassName.ReleaseBuffer();
			strWindowText.ReleaseBuffer();

			//��ý���
			DWORD dwProcessID;
			DWORD dwXianChenID;
			dwXianChenID = GetWindowThreadProcessId(hwnd, &dwProcessID);

			CString processName;

			get_process_name(processName, dwProcessID);

			//���Ӵ�����Ϣ
			append_structtaskinfo(strClassName, strWindowText, processName, 1);
		}
		//������һ���Ӵ���
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
}

//�������(����)��Ϣ
//type:0ȫ��,1��Ч��Ϣ
void TaskInfo::print_tasklist(const int& type)
{
	for (int i = 0; i < _taskinfo_loc; i++)
	{
		if (type == 1) //���������Ч��Ϣ
		{
			//����Ϣ��Ч,��������ǰѭ��
			if ((_p_structtaskinfo[i].processname.Compare("SynTPEnh.exe") == 0) ||   //С��V1000������...
		        (
				    (_p_structtaskinfo[i].processname.Compare("explorer.exe") == 0) && //explorer.exeһ�Ѷ���
					(
					    (_p_structtaskinfo[i].classname.Compare("Shell_TrayWnd") == 0) ||
					    (_p_structtaskinfo[i].classname.Compare("Shell_SecondaryTrayWnd") == 0) ||
					    (_p_structtaskinfo[i].classname.Compare("ApplicationFrameWindow") == 0) ||
						(_p_structtaskinfo[i].classname.Compare("EdgeUiInputTopWndClass") == 0) ||
						(_p_structtaskinfo[i].classname.Compare("DummyDWMListenerWindow") == 0) ||
						(_p_structtaskinfo[i].classname.Compare("Progman") == 0)
				     )
				) ||
				(_p_structtaskinfo[i].processname.Compare("SystemSettings.exe") == 0) ||
				(_p_structtaskinfo[i].processname.Compare("ApplicationFrameHost.exe") == 0) ||
				(_p_structtaskinfo[i].processname.Compare("newssvc.exe") == 0) ||
				(
					(_p_structtaskinfo[i].processname.Compare("MicrosoftEdgeCP.exe") == 0) &&
					(_p_structtaskinfo[i].classname.Compare("Windows.UI.Core.CoreWindow") == 0)
				) ||
				(
				    (_p_structtaskinfo[i].processname.Compare("MicrosoftEdge.exe") == 0) &&
					(_p_structtaskinfo[i].classname.Compare("Windows.UI.Core.CoreWindow") == 0)
				)
			)
			continue;
		}
		print_chinese(1, "ClassName:", _p_structtaskinfo[i].classname);
		print_chinese(1, "WindowText:", _p_structtaskinfo[i].windowtext);
		print_chinese(1, "ProcessName:", _p_structtaskinfo[i].processname);
		if (_p_structtaskinfo[i].type == 0) print_chinese(1, "topWindow", "");
		else print_chinese(1, "common", "");
	}
}

//�ⲿɾ��ʵ���ӿ�
void TaskInfo::self_destroy()
{
	if (_ptaskinfo != NULL)
	{
		delete _ptaskinfo;
	}
	_ptaskinfo = NULL;
}

//������ļ�
//printtype 0:cmd, 1:�ļ�
void TaskInfo::print_chinese(const int& printtype, const CString& inputpre, const CString& inputstr)
{
	if( printtype == 0) std::cout << inputpre.GetString() << inputstr.GetString() << std::endl;
	else
	{
		//_file.open("D:\\PC\\CodeSources\\mix-python-cpp\\data.txt", std::ios_base::out | std::ios_base::app);
		_file.open("data.txt", std::ios_base::out | std::ios_base::app);
		_file << inputpre.GetString() << inputstr.GetString() << "\n";
		_file.close();
	}
}

//��ý�������
void TaskInfo::get_process_name(CString& nProcessName, const DWORD& nPid)
{
	PROCESSENTRY32 nPT;
	nPT.dwSize = sizeof(nPT);
	HANDLE nSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	BOOL nRet = Process32First(nSnapShot, &nPT);
	while (nRet)
	{
		if (nPid == nPT.th32ProcessID)
		{
			nProcessName = nPT.szExeFile;
			return;
		}
		nRet = Process32Next(nSnapShot, &nPT);
	}
}

void TaskInfo::refresh_tasklist()
{
	get_top_window();
	get_windows();
	print_tasklist(1);
}


void TaskInfo::debug_print()
{
	;
}

TaskInfo* TaskInfo::_ptaskinfo = NULL;
int TaskInfo::_MAX_TASKINFO_LENGTH = 50;
/*********************************End TaskInfo*************************************/
