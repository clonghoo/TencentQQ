// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// Packet.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

#ifdef _DEBUG
#pragma comment(lib,"../LibD/JceProtocol.lib")
#pragma comment(lib,"../LibD/CipherLib.lib")
#pragma comment(lib,"../LibD/UtilLib.lib")
#pragma comment(lib,"jsoncpp.lib")
#pragma comment(lib,"/debug/libprotobufd.lib")
#pragma comment(lib,"/debug/libprotobuf-lited.lib")
#pragma comment(lib,"/debug/libprotocd.lib")
#else
#pragma comment(lib,"../Lib/JceProtocol.lib")
#pragma comment(lib,"../Lib/CipherLib.lib")
#pragma comment(lib,"../Lib/UtilLib.lib")
#pragma comment(lib,"jsoncpp.lib")
#pragma comment(lib,"/release/libprotobuf.lib")
#pragma comment(lib,"/release/libprotobuf-lite.lib")
#pragma comment(lib,"/release/libprotoc.lib")
#endif