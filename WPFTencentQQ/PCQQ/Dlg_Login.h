#pragma once
#include "afxwin.h"
#include"IOCPSettingsDlg.h"
#include"GlobeVar.h"
#include"..\Packet\ConfigData.h"
#include"..\Packet\CommonUnPack.h"


// Dlg_Login �Ի���

class Dlg_Login : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_Login)

public:
	Dlg_Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_Login();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
public:
	CSimpleIni m_Ini;
	// �û��˻�
	CString m_Account;
	// �û�����
	CString m_Password;
	// ������ʾ��½������Ϣ
	CListBox m_List;
	IOCPSettingsDlg m_ConfigDlg;
	CConfigData *pConfig;
private:
	//�յ����ݰ��ļ�¼
	void RecvPacketRecords(CCommonUnPack*);
protected:
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam);
};
