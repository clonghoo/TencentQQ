// MBLBindSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MBLBindSet.h"
#include "afxdialogex.h"
#include"../CCodecWarpper/PackReq.h"
#include"../CCodecWarpper/ResponeVerifySmscode.h"
#include"../CCodecWarpper/ResponeBindMobile.h"
#include"UserMsg.h"


// CMBLBindSet �Ի���

IMPLEMENT_DYNAMIC(CMBLBindSet, CDialogEx)

CMBLBindSet::CMBLBindSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMBLBindSet::IDD, pParent)
{

}

CMBLBindSet::~CMBLBindSet()
{
}

void CMBLBindSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mEditPhoneNo);
	DDX_Control(pDX, IDC_EDIT2, mEditCheckNo);
}


BEGIN_MESSAGE_MAP(CMBLBindSet, CDialogEx)
	ON_MESSAGE(WM_RECEIVED_MSG, &CMBLBindSet::OnReceivedMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CMBLBindSet::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON8, &CMBLBindSet::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON2, &CMBLBindSet::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMBLBindSet ��Ϣ�������

afx_msg LRESULT CMBLBindSet::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 0:
		{
			CResponeBindMobile *pResponeBindMobile=static_cast<CResponeBindMobile*>((void*)lParam);

			if(pResponeBindMobile->alreadyBindedUin.value().size()==0)
			{
				if(pResponeBindMobile->sessionSid.value().size()==0)
				{
					//��½QQ�����Ѱ��ֻ����룬���Ƚ���󶨻����л���½δ��QQ����
					CString strFormat;
					strFormat.Format("δ��ѯ�����");
					AfxMessageBox(strFormat);
				}else
				{
					//��½QQ����δ�󶨣���Ŀ���ֻ�����δ���κ�QQ����
					std::string strMobileNo;
					strMobileNo.append((char*)pResponeBindMobile->sessionSid.value().contents(),pResponeBindMobile->sessionSid.value().size());
					strsessionSid=strMobileNo;
					CString strFormat;
					strFormat.Format("Ŀ���ֻ�����%sδ���κ�QQ",strMobileNo.c_str());
					AfxMessageBox(strFormat);
				}
			}else
			{
				//��½QQ����δ�󶨣���Ŀ���ֻ������Ѱ�QQ����
				CString strFormat;
				strFormat.Format("�Ѱ��˺�:%s",pResponeBindMobile->alreadyBindedUin.value().c_str());
				AfxMessageBox(strFormat);
			}
			delete pResponeBindMobile;
			pResponeBindMobile=NULL;
		}break;
	case 1:
		{
			CResponeVerifySmscode *pResponeVerifySmscode=
				static_cast<CResponeVerifySmscode*>((void*)lParam);
			if(pResponeVerifySmscode->sessionSid.value().size()==0)
			{
				CString strFormat;
				strFormat.Format("��ʧ��");
				AfxMessageBox(strFormat);
			}else
			{
				CString strFormat;
				strFormat.Format("�󶨳ɹ�");
				AfxMessageBox(strFormat);
			}
			delete pResponeVerifySmscode;
			pResponeVerifySmscode=NULL;
		}break;
	case 2:
		{
			AfxMessageBox("����󶨳ɹ�");
		}break;
	default:
		{
			return 0;
		}break;
	}
	return 0;
}

//������
void CMBLBindSet::OnBnClickedButton1()
{
	CString str;
	this->mEditCheckNo.GetWindowTextA(str);
	if(str.GetLength()==0)
	{
		AfxMessageBox("��֤��Ϊ��");
		return;
	}
	if(strsessionSid.size()==0)
	{
		AfxMessageBox("���Ȳ�ѯĿ���ֻ������Ƿ��");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(account_RequestVerifyBindingSmscode);
	pConfig->mRequestVerifyBindingSmscode.smsCode.value(str.GetBuffer());
	ByteBuffer bt;
	bt.append(strsessionSid.c_str(),strsessionSid.size());
	pConfig->mRequestVerifyBindingSmscode.sessionSid.value(bt);
	mPack.pConfig=pConfig;
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}

//�����
void CMBLBindSet::OnBnClickedButton8()
{
	if(pConfig->mRequestCancelBindMobile.mobileNo.value().size()==0||
		pConfig->mRequestCancelBindMobile.nationCode.value().size()==0)
	{
		AfxMessageBox("���Ȳ�ѯ��½�����״̬");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(account_RequestCancelBindMobile);
	mPack.pConfig=pConfig;
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}

//��֤
void CMBLBindSet::OnBnClickedButton2()
{
	CString str1;
	mEditPhoneNo.GetWindowTextA(str1);
	if(str1.GetLength()==0)
	{
		AfxMessageBox("�������Ϊ��");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(account_RequestBindMobile);
	mPack.pConfig=pConfig;
	mPack.pConfig->mRequestBindMobile.mobileNo.value("+86");
	mPack.pConfig->mRequestBindMobile.nationCode.value(str1.GetBuffer(0));
	mPack.PackData();
	SendPacket(pConfig->m_iCurrentClientID,(unsigned char*)mPack.pack.contents(),mPack.pack.size());
	CString strFormat;
	strFormat.Format("��ѯ����:%s%s","+86",str1);
	//OutputEdit(strFormat);
}


BOOL CMBLBindSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//��ʼ��ѯ
	//CPackReq mPack;
	//mPack.SetPacketType(account_RequestQueryQQBindingStat);
	//pConfig->isNeedCode=false;
	//mPack.pConfig=pConfig;
	//mPack.PackData();
	//SendPacket(pConfig->m_iCurrentClientID,&(mPack.pack));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
