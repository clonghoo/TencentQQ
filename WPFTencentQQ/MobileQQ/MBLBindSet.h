#pragma once
#include "afxwin.h"
#include"resource.h"
#include"../CCodecWarpper/ConfigData.h"
#include<NetLib.h>
#include"UserMsg.h"


// CMBLBindSet �Ի���

class CMBLBindSet : public CDialogEx
{
	DECLARE_DYNAMIC(CMBLBindSet)

public:
	CMBLBindSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMBLBindSet();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	// �ֻ�����
	CEdit mEditPhoneNo;
	// ��֤��
	CEdit mEditCheckNo;
	CConfigData *pConfig;
	std::string strsessionSid;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};
