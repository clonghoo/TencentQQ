#include"GlobeVar.h"


namespace GlobeVar
{
	void Error_Check(unsigned int mode)
	{
		switch (mode)
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
			char buf[0x20] = { 0 };
			sprintf(buf, "%0x04", mode);
			MessageBox(NULL, buf, "error", MB_OK);
			exit(-1);
		}break;
		}
	}
	void __stdcall MainCallBackHandle(unsigned int, unsigned int, unsigned char*, unsigned int)
	{

	}
};