һ��LogLib VS2017�����ļ��� ��c++����̨Ӧ���Լ�MFC֧��
LogLib.exe ��LogLib��ȡ���� ����data.txt
main.py ��ȡ��ɾ��data.txt HTTP POST��Զ�̷�����

����VS2017�������ã� ��������-����-��ĿĬ��ֵ-MFC��ʹ�ã��ڹ���DLL��ʹ��MFC
��������-C/C++-Ԥ����ͷ����ʹ��Ԥ����ͷ
��������-����-��ĿĬ��ֵ-�ַ�����δ����     ��ע��c++�ַ�̫���ң������ҹ���

�������_WIN32_WINNT not defined. Defaulting to _WIN32_WINNT_MAXVER (see WinSDKVer.h) ��Ҫ��
��Ϊ���Ƴ���/���̶�windowsƽ̨�汾��Ҫ�� ��û��


c++�� LogLib.cppΪ�������
TaskInfo.cpp/h�ṩMFC��ȡӦ�ó����TaskInfo��
Log.cpp/h�ṩLog��־��

����c++���ɵ�data.txt��ʽ��
ÿ��ʱ�����==============\n��ͷ
ÿ��������7�У����飺������鿴data.txt����\web_project\localtest\LogLib\LogLib��
ClassName:ConsoleWindowClass
WindowText:D:\PC_git_library\web_project\localtest\LogLib\x64\Debug\LogLib.exe
ProcessName:VsDebugConsole.exe
type:common                                               //topWindow or common
StartTime:Sun Mar 31 05:40:11 2019          // is a timestr
RunningTime:Thu Jan  1 00:00:00 1970      //PresentTime-StartTime,�Ҵ������ʱ�����timestr��this is bug, need fix 
PresentTime:Sun Mar 31 05:40:11 2019     // is a timestr