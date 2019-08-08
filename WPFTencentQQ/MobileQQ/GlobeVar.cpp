#include"GlobeVar.h"
#include"Lock.h"
#include"UserMsg.h"

namespace GlobeVar
{
	HWND *pDlgLogin=0;
	HWND *pMainWnd=0;

	CRespondQueryQQBindingStat mRespondQueryQQBindingStat;
	void Error_Check(unsigned int mode)
	{
		switch(mode)
		{
		case RESULT_SUCCESS:
			{
			}break;
		case ERR_LOGIN_FAILED:
			{
				AfxMessageBox("��½ʧ��,�����µ�½");
			}break;
		case ERR_LOGIN_PASSWORD:
			{
				AfxMessageBox("�������,����������");
			}break;
		default:
			{
				char buf[0x20]={0};
				sprintf(buf,"%0x04",mode);
				MessageBox(NULL,buf,"error",MB_OK);
				exit(-1);
			}break;
		}
	}

	CRITICAL_SECTION cs_NetCallBack;
	void __stdcall MainCallBackHandle(unsigned int _socket, unsigned int msgType, unsigned char* msg, unsigned int bytes)
	{
		CLock mLock(&cs_NetCallBack);
		mLock.Lock();
		switch (msgType)
		{
		case 0x0000:
		{
			//�µ�����
			::PostMessage(*pDlgLogin, WM_RECEIVED_MSG, (WPARAM)(0), (LPARAM)(msg));
		} break;
		case 0x0001:
		{
			//��������
			ByteBuffer buffer;
			buffer.append(msg, bytes);
			::SendMessage(*pDlgLogin, WM_RECEIVED_MSG, (WPARAM)(1), (LPARAM)(&buffer));
		} break;
		case 0x0002:
		{
			//���ӶϿ�
			::PostMessage(*pDlgLogin, WM_RECEIVED_MSG, (WPARAM)(2), (LPARAM)(msg));
		}break;
		default:
		{
		} break;
		}
		mLock.UnLock();
	}
};