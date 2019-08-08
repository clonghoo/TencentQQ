
// QQDlg.h : ͷ�ļ�
//

#pragma once
#include <locale.h>
#include"GlobeVar.h"
#include"..\Packet\ConfigData.h"
#include"MFCStatus.h"
#include "afxwin.h"
#include"MyListCtrl.h"
#include"OwnerDrawTreeCtrl.h"
#include"..\Packet\FolderList.h"
#include"..\Packet\ClassModel.h"
#include"..\Packet\CommonUnPack.h"


// COffineQQDlg �Ի���
class COffineQQDlg : public CDialogEx
{
// ����
public:
	COffineQQDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CSimpleIniA mSimpleIniA;
	CConfigData Config;
	unsigned int m_Send;
	unsigned int m_Recv;
	unsigned int m_Abandon;
	HANDLE gHeartThread[2];
	FolderList mFolderList;	//�����б�
private:
	BOOL SetDumpFunc(void);
	BOOL SetDlgUI(void);
	static DWORD _stdcall HeartThreadProc( LPVOID lpParam );

	void InitSendPacket();
	void DlgSend(unsigned int ClientID,ByteBuffer &b){SendPacket(ClientID,(unsigned char*)b.contents(),b.size());AddSend();};
	//״̬�ĸı�
	void AddSend(){m_Send++;m_Status.Updata(m_Send,m_Recv,m_Abandon);};
	void AddRecv(){m_Recv++;m_Status.Updata(m_Send,m_Recv,m_Abandon);};
	void AddAbandon(){m_Abandon++;m_Status.Updata(m_Send,m_Recv,m_Abandon);};
	void SetUinStatus(UinStatus status);
	inline void UpdateUinStatus();
	//�յ����ݰ��ļ�¼
	void RecvPacketRecords(CCommonUnPack*);
	//�������ݰ�������
	BOOL SetHeartPacket();
	//��ʼ�������б�
	void InitFriendsList(FolderList&);
	//����һ��������Ϣ
	void InsertRecvMsg(TextMsg);
public:
	afx_msg void OnLogin();
	afx_msg void OnOffineLine();
	afx_msg void On32779();
	afx_msg void On32780();
	afx_msg void On32781();
	afx_msg void On32782();
	afx_msg void On32784();
	afx_msg void On32783();
	afx_msg void OnClose();
	afx_msg void On32793();
public:
	// ��ʾ��Ϣ�б�
	CStatic mStatic1;
	// ��Ϣ�б�
	CListBox mList1;
	CStatic mStatic2;
	CStatic mStatic3;
	MyListCtrl mList2;     //������Ϣ�б�
	MyListCtrl mList3;    //Ⱥ����Ϣ�б�
	// ��ʾ���ѷ���
	CStatic mStatic4;
	CStatic mStatic5;
	// ����˺����б�
	COwnerDrawTreeCtrl mTreeCtrl;
	//״̬��
	MFCStatus m_Status;
protected:
	afx_msg LRESULT OnReceivedMsg(WPARAM wParam, LPARAM lParam); //������������������ݰ���Ϣ
	afx_msg LRESULT OnTransmitMsg(WPARAM wParam, LPARAM lParam); //��������������Ϣ
	afx_msg LRESULT OnLoginsuccessed(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
public:
	BOOL TrayMessage(HWND,DWORD,HICON,PSTR);
};
