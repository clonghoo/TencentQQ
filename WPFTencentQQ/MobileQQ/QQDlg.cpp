
// QQDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQ.h"
#include "QQDlg.h"
#include "afxdialogex.h"
#include"Dlg_Login.h"
#include"UserMsg.h"
#include "../UtilLib/err_code.h"
#include"UserMsg.h"
#include"MyLog.h"
#include"../CCodecWarpper/PackReq.h"
#include"../CCodecWarpper/ResponeBindMobile.h"
#include"../CCodecWarpper/ResponeUploadAddressBookV2.h"
#include"../CCodecWarpper/RespondQueryQQBindingStat.h"
#include"../CCodecWarpper/ResponeVerifySmscode.h"
#include"../CCodecWarpper/ResponeQueryQQMobileContactsV3.h"
#include"../CCodecWarpper/ResponeUploadAddressBook.h"
#include"../CCodecWarpper/ResponeUpdateAddressBook.h"
#include"../CCodecWarpper/SummaryCardRespSearch.h"
#include"../CCodecWarpper/RespGetEncounterV2.h"
#include"SeqSerial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// COffineQQDlg �Ի���


COffineQQDlg::COffineQQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COffineQQDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COffineQQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, mStatic1);
	DDX_Control(pDX, IDC_LIST1, mList1);
	DDX_Control(pDX, IDC_STATIC2, mStatic2);
	DDX_Control(pDX, IDC_STATIC3, mStatic3);
	DDX_Control(pDX, IDC_LIST2, mList2);
	DDX_Control(pDX, IDC_LIST3, mList3);
	DDX_Control(pDX, IDC_STATIC4, mStatic4);
	DDX_Control(pDX, IDC_STATIC5, mStatic5);
	DDX_Control(pDX, IDC_TREE1, mTreeCtrl);
}

BEGIN_MESSAGE_MAP(COffineQQDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &COffineQQDlg::OnLogin)
	ON_MESSAGE(WM_RECEIVED_MSG, &COffineQQDlg::OnReceivedMsg)
	ON_MESSAGE(WM_TRANSMIT_MSG, &COffineQQDlg::OnTransmitMsg)
	ON_COMMAND(ID_32772, &COffineQQDlg::OnOffineLine)
	ON_COMMAND(ID_32779, &COffineQQDlg::On32779)
	ON_COMMAND(ID_32784, &COffineQQDlg::On32784)
	ON_MESSAGE(WM_LOGINSUCCESSED, &COffineQQDlg::OnLoginsuccessed)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_TRAY_NOTIFICATION, &COffineQQDlg::OnTrayNotification)
	ON_COMMAND(ID_32793, &COffineQQDlg::On32793)
	ON_COMMAND(ID_32794, &COffineQQDlg::On32794)
	ON_COMMAND(ID_32799, &COffineQQDlg::OnNetSet)
	ON_COMMAND(ID_32800, &COffineQQDlg::OnMachineSet)
	ON_COMMAND(ID_32801, &COffineQQDlg::On32801)
	ON_COMMAND(ID_32802, &COffineQQDlg::On32802)
	ON_COMMAND(ID_32803, &COffineQQDlg::On32803)
	ON_COMMAND(ID_32804, &COffineQQDlg::On32804)
END_MESSAGE_MAP()


// COffineQQDlg ��Ϣ�������

BOOL COffineQQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	pMobileQuery=NULL;
	pMBLBindSet=NULL;
	pNickNameQuery=NULL;
	pSearchDlg=NULL;
	//���ñ��������ַ���
	_wsetlocale(LC_ALL,L"chs");

	//��ʼ��ini�����
	mSimpleIniA.SetUnicode(false);
	mSimpleIniA.SetMultiKey(true);
	mSimpleIniA.SetMultiLine(true);
	//��װ�쳣��
	if(!this->SetDumpFunc())
	{
		//���öԻ�����־
		return FALSE;
	}
	StatusLogText("COffineQQDlg �쳣��������ϡ�����");
	if(!this->SetDlgUI())
	{
		//���öԻ�����־
		return FALSE;
	}
	StatusLogText("COffineQQDlg �Ի���������ϡ�����");

	GlobeVar::pMainWnd = &this->m_hWnd;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COffineQQDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COffineQQDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COffineQQDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//��������Dump�߳�
BOOL COffineQQDlg::SetDumpFunc(void)
{
	SetUnhandledExceptionFilter(GPTUnhandledExceptionFilter);

	g_DumpThread=CreateThread(NULL,0,ThreadProc,NULL,CREATE_SUSPENDED,NULL);
	if(g_DumpThread==NULL)
	{
		return FALSE;
	}
	return TRUE;
}

//�����������Ի����UI
BOOL COffineQQDlg::SetDlgUI(void)
{
	SI_Error rc = mSimpleIniA.LoadFile("configure.ini");
    if (rc < 0) return false;

	//��ʼ��MainFrame UI����
	int x=0,y=0,height=0,width=0;
	height=mSimpleIniA.GetLongValue("MainFrame","height");
	width=mSimpleIniA.GetLongValue("MainFrame","width");
	RECT rect={0};
	this->GetWindowRect(&rect);
	this->MoveWindow(rect.left,rect.top,width,height,TRUE);

	//�����б�
	x=mSimpleIniA.GetLongValue("mStatic4","x");
	y=mSimpleIniA.GetLongValue("mStatic4","y");
	height=mSimpleIniA.GetLongValue("mStatic4","height");
	width=mSimpleIniA.GetLongValue("mStatic4","width");
	mStatic4.MoveWindow(x,y,width,height);

	x=mSimpleIniA.GetLongValue("mTreeCtrl","x");
	y=mSimpleIniA.GetLongValue("mTreeCtrl","y");
	height=mSimpleIniA.GetLongValue("mTreeCtrl","height");
	width=mSimpleIniA.GetLongValue("mTreeCtrl","width");
	mTreeCtrl.MoveWindow(x,y,width,height);

	mTreeCtrl.SetItemHeight(26);
	mTreeCtrl.SetImageList();
	mTreeCtrl.SetStyle(TVS_HASBUTTONS,0);	
	
	//��Ϣ�б�
	x=mSimpleIniA.GetLongValue("mStatic1","x");
	y=mSimpleIniA.GetLongValue("mStatic1","y");
	height=mSimpleIniA.GetLongValue("mStatic1","height");
	width=mSimpleIniA.GetLongValue("mStatic1","width");
	mStatic1.MoveWindow(x,y,width,height);

	x=mSimpleIniA.GetLongValue("mList1","x");
	y=mSimpleIniA.GetLongValue("mList1","y");
	height=mSimpleIniA.GetLongValue("mList1","height");
	width=mSimpleIniA.GetLongValue("mList1","width");
	mList1.MoveWindow(x,y,width,height);

	//������Ϣ
	x=mSimpleIniA.GetLongValue("mStatic2","x");
	y=mSimpleIniA.GetLongValue("mStatic2","y");
	height=mSimpleIniA.GetLongValue("mStatic2","height");
	width=mSimpleIniA.GetLongValue("mStatic2","width");
	mStatic2.MoveWindow(x,y,width,height);

	x=mSimpleIniA.GetLongValue("mList2","x");
	y=mSimpleIniA.GetLongValue("mList2","y");
	height=mSimpleIniA.GetLongValue("mList2","height");
	width=mSimpleIniA.GetLongValue("mList2","width");
	mList2.MoveWindow(x,y,width,height);
	this->mList2.Clear();
	char  _column2[][20]={"���","���ͷ�","����ʱ��","��Ϣ����"};
	this->mList2.SetHeaders(_column2,sizeof(_column2)/sizeof(*_column2));

	//Ⱥ����Ϣ
	x=mSimpleIniA.GetLongValue("mStatic3","x");
	y=mSimpleIniA.GetLongValue("mStatic3","y");
	height=mSimpleIniA.GetLongValue("mStatic3","height");
	width=mSimpleIniA.GetLongValue("mStatic3","width");
	mStatic3.MoveWindow(x,y,width,height);

	x=mSimpleIniA.GetLongValue("mList3","x");
	y=mSimpleIniA.GetLongValue("mList3","y");
	height=mSimpleIniA.GetLongValue("mList3","height");
	width=mSimpleIniA.GetLongValue("mList3","width");
	mList3.MoveWindow(x,y,width,height);
	this->mList3.Clear();
	char  _column3[][20]={"���","Ⱥ��","���ͷ�","����ʱ��","��Ϣ����"};
	this->mList3.SetHeaders(_column3,sizeof(_column3)/sizeof(*_column3));

	//������Ϣ
	x=mSimpleIniA.GetLongValue("mStatic5","x");
	y=mSimpleIniA.GetLongValue("mStatic5","y");
	height=mSimpleIniA.GetLongValue("mStatic5","height");
	width=mSimpleIniA.GetLongValue("mStatic5","width");
	mStatic5.MoveWindow(x,y,width,height);

	//����״̬��
	this->m_Status.Create(WS_CHILD|WS_VISIBLE|CCS_BOTTOM,CRect(0,0,0,0), this, IDC_STATUSBARCTRL);
	this->m_Status.SetUI();

	//����Ĭ��״̬
	this->m_Send=0;
	this->m_Recv=0;
	this->m_Abandon=0;
	this->m_Status.Updata(m_Send,m_Recv,m_Abandon);
	this->m_Status.SetProcessBar(0);
	
	//this->SetUinStatus(BeOffine); //����״̬
	return TRUE;
}

//��½��ť
void COffineQQDlg::OnLogin()
{
	if(Config.mStatus!=BeOffine)
	{
		AfxMessageBox("����ע���ѵ�¼�˺�");
		return;
	}
	Dlg_Login login_dlg;
	login_dlg.SetIocpParam(m_ConfigDlg.m_iPortNr,
		m_ConfigDlg.m_iMaxNumberOfConnections,
		m_ConfigDlg.m_iNrOfIOWorkers,
		m_ConfigDlg.m_iNrOfLogicalWorkers,
		m_ConfigDlg.m_iMaxNrOfFreeBuff,
		m_ConfigDlg.m_iMaxNrOfFreeContext,
		m_ConfigDlg.m_iSendInOrder,
		m_ConfigDlg.m_bReadInOrder,
		m_ConfigDlg.m_iNrPendlingReads);
	login_dlg.pConfig=&Config;
	login_dlg.DoModal();
}

afx_msg LRESULT COffineQQDlg::OnReceivedMsg(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case 1:
		{
			//��������
			break;
		}break;
	case 2:
		{
			//�ͻ��˶Ͽ�
			unsigned int* piID = reinterpret_cast<unsigned int*>(lParam);
			mList1.AddString("�ͻ��˶Ͽ��ɹ�");
			delete piID;
			return 0;
		}break;
	default:
		{
			GlobeVar::Error_Check(ERR_COMMON);
			return 0;
		}break;
	}

	//��������ָ��+1
	AddRecv();

	ByteBuffer *pRecv=(ByteBuffer*)(lParam);
	CCommonUnPack *packet= new CCommonUnPack();
	packet->Wrapping(*pRecv);
	packet->pConfig=&Config;
	delete pRecv;
	pRecv=NULL;
	unsigned int ret=packet->UnPackData();

	//��������
	if(packet->Analysis()!=RESULT_SUCCESS)
	{
		mList1.AddString("���ݰ�����...");
		return 0;
	}

	//��¼�յ����ݰ�
	RecvPacketRecords(packet);

	//�鿴���ݰ��Ƿ���Ҫ����
	if(ret==ERR_PACKET_ABANDON)
	{
		//��������ָ��+1
		AddAbandon();
		return 0;
	}
	GlobeVar::Error_Check(ret);

	switch(packet->GetPackType())
	{
	case GrayUinPro_Check:
		{
			packet->DispatchCmd();
			//CPackReq *p=new CPackReq();
			//Config.strServiceCmd=STR_friendlist_GetTroopListReqV2;
			//p->SetPacketType(friendlist_GetTroopListReqV2);
			//Config.isNeedCode=false;
			//Config.isSidUsed=true;
			//p->pConfig=&Config;
			//p->PackData();
			//SendPacket(Config.m_iCurrentClientID,&(p->pack));
			//delete p;
		}break;
	case friendlist_GetTroopListReqV2:
		{
			packet->DispatchCmd();
			//CPackReq *p=new CPackReq();
			//pConfig->strServiceCmd=STR_friendlist_GetTroopListReqV2;
			//p->SetPacketType(friendlist_GetTroopListReqV2);
			//pConfig->isNeedCode=false;
			//p->pConfig=pConfig;
			//p->PackData();
			//SendPacket(pConfig->m_iCurrentClientID,&(p->pack));
			//delete p;
		}break;
	case OidbSvc_0x7a2_0:
		{
			packet->DispatchCmd();
			//����StatSvc_register
			CPackReq *p=new CPackReq();
			p->SetPacketType(StatSvc_register);
			Config.mRegisterCmd=CmdOnLine;
			p->pConfig=&Config;
			p->PackData();
			SendPacket(Config.m_iCurrentClientID,(unsigned char*)p->pack.contents(), p->pack.size());
			delete p;
		}break;
	case StatSvc_register:
		{
			packet->DispatchCmd();
			if(Config.mRegisterCmd==BeOnLine)
			{
				//���߳ɹ�
				if(!this->SetHeartPacket())
				{
					GlobeVar::Error_Check(ERR_COMMON);
				}
			}else if(Config.mRegisterCmd==BeOffine)
			{
				////���������߳̽����¼�����
				SetEvent(gHeartThread[1]);
				////����IOCP
				EndTheSystem();
				Config.restart();
				this->m_Send=0;
				this->m_Recv=0;
				this->m_Abandon=0;
				this->m_Status.Updata(m_Send,m_Recv,m_Abandon);
				this->m_Status.SetProcessBar(0);
				SetUinStatus(BeOffine);
				//��������б�
				this->mList1.ResetContent();   //�����Ϣ�б�
				this->mTreeCtrl.DeleteAllItems();  //��������б�
				//mFolderList.Clear();
				mList2.Clear();//���������Ϣ�б�
			}
		}break;
	case account_RequestBindMobile:
		{
			CResponeBindMobile *pResponeBindMobile=new CResponeBindMobile();
			packet->DispatchCmd(pResponeBindMobile);
			mSeqSerial.SeqRun(packet->GetSeq(),this,pResponeBindMobile);

			if(pMBLBindSet!=NULL&&pMBLBindSet->m_hWnd!=NULL)
			{
				//������Ϣ
				::PostMessageA(pMBLBindSet->m_hWnd,WM_RECEIVED_MSG,0,(LPARAM)pResponeBindMobile);
			}
		}break;
	case account_RequestCancelBindMobile:
		{
			packet->DispatchCmd();
			if(pMBLBindSet!=NULL&&pMBLBindSet->m_hWnd!=NULL)
			{
				//������Ϣ
				::PostMessageA(pMBLBindSet->m_hWnd,WM_RECEIVED_MSG,2,NULL);
			}
		}break;
	case account_RequestUploadAddressBookV2:
		{
			CResponeUploadAddressBookV2 *pResponeUploadAddressBookV2=new CResponeUploadAddressBookV2();
			packet->DispatchCmd(pResponeUploadAddressBookV2);
			if(pNickNameQuery!=NULL&&pNickNameQuery->m_hWnd!=NULL)
			{
				//������Ϣ
				::PostMessageA(pNickNameQuery->m_hWnd,WM_RECEIVED_MSG,0,(LPARAM)pResponeUploadAddressBookV2);
			}
		}break;
	case account_RequestQueryQQBindingStat:
		{
			CRespondQueryQQBindingStat *pRespondQueryQQBindingStat=new CRespondQueryQQBindingStat();
			packet->DispatchCmd(pRespondQueryQQBindingStat);
			mSeqSerial.SeqRun(packet->GetSeq(),this,pRespondQueryQQBindingStat);
		}break;
	case account_RequestVerifyBindingSmscode:
		{
			CResponeVerifySmscode *pResponeVerifySmscode=new CResponeVerifySmscode();
			packet->DispatchCmd(pResponeVerifySmscode);
			if(pMBLBindSet!=NULL&&pMBLBindSet->m_hWnd!=NULL)
			{
				//������Ϣ
				::PostMessageA(pMBLBindSet->m_hWnd,WM_RECEIVED_MSG,1,(LPARAM)pResponeVerifySmscode);
			}
		}break;
	case account_RequestQueryQQMobileContactsV3:
		{
			CResponeQueryQQMobileContactsV3 *pResponeQueryQQMobileContactsV3=new CResponeQueryQQMobileContactsV3();
			packet->DispatchCmd(pResponeQueryQQMobileContactsV3);
			if(pMobileQuery!=NULL&&pMobileQuery->m_hWnd!=NULL)
			{
				//������Ϣ
				::PostMessageA(pMobileQuery->m_hWnd,WM_RECEIVED_MSG,1,(LPARAM)pResponeQueryQQMobileContactsV3);
			}
		}break;
	case account_RequestUploadAddressBook:
		{
			CResponeUploadAddressBook *pResponeUploadAddressBook=new CResponeUploadAddressBook();
			packet->DispatchCmd(pResponeUploadAddressBook);
		}break;
	case account_RequestUpdateAddressBook:
		{
			CResponeUpdateAddressBook *pResponeUpdateAddressBook=new CResponeUpdateAddressBook();
			packet->DispatchCmd(pResponeUpdateAddressBook);
		}break;
	case SummaryCard_ReqSearch:
		{
			CSummaryCardRespSearch *pSummaryCardRespSearch=new CSummaryCardRespSearch();
			packet->DispatchCmd(pSummaryCardRespSearch);
			if(pSearchDlg!=NULL&&pSearchDlg->m_hWnd!=NULL)
			{
				//������Ϣ
				::PostMessageA(pSearchDlg->m_hWnd,WM_RECEIVED_MSG,0,(LPARAM)pSummaryCardRespSearch);
			}
		}break;
	case EncounterSvc_ReqGetEncounter:
		{
			CRespGetEncounterV2 *pRespGetEncounterV2=new CRespGetEncounterV2();
			packet->DispatchCmd(pRespGetEncounterV2);
			mSeqSerial.SeqRun(packet->GetSeq(),this,NULL);
		}break;
	case TYPE_HULUE:
		{
		}break;
	}
	return 0;
}

afx_msg LRESULT COffineQQDlg::OnTransmitMsg(WPARAM wParam, LPARAM lParam)
{
	ActionCommand *pAction=(ActionCommand*)wParam;
	switch(pAction->sCmd)
	{
	case ACTION_SEND_MSG:
		{
			CString str;
			str.Format("������Ϣ->%d",pAction->sSubCmd);
			mList1.AddString(str);

			//CCommReq* p=new CCommReq();
			//p->SetPacketType(CODE_00CD01);
			//p->pConfig=&Config;
			//p->PackData();
			//DlgSend(p->pConfig->m_iCurrentClientID,p->pack);
			//delete p;p=NULL;
		}break;
	case ACTION_QUERY_USERDATA:
		{
			CString str;
			str.Format("��ѯ����->%d",pAction->sSubCmd);
			mList1.AddString(str);
		}break;
	default:
		{
			//AppendLog("COffineQQDlg::OnTransmitMsg error");
		}break;
	}

	return 0;
}

/*
void COffineQQDlg::InitFriendsList(FolderList& mFriends)
{
	//�ȳ�ʼ�����ѷ���
	for (int i =0; i < mFriends.mList1.size(); i ++) 
	{
		CString strSet;
		strSet.Format("%s",mFriends.mList1[i].strClusterName.c_str());
		HTREEITEM Root=mTreeCtrl.InsertItem(strSet.GetBuffer(0),-1,-1);
		//���غ���
		for(int j=0;j<mFriends.mList1[i].Friends.size();j++)
		{
			CString strFriend;
			strFriend.Format("%d",mFriends.mList1[i].Friends[j].dwUin);
			mTreeCtrl.InsertItem(strFriend,Root,TVI_LAST);
		}

	//		//���ڵ�
	//HTREEITEM Root=mTreeCtrl.InsertItem(TEXT("gym��Ϸ����"),0,0,TVI_ROOT,TVI_LAST);

	////mTreeCtrl.SetItemImage(Root,0,1);

	////��������Ϸ
	//HTREEITEM GameItem1=mTreeCtrl.InsertItem(TEXT("������"),7,6,Root,TVI_LAST);
	//
	//	HTREEITEM Room_Item1_1=mTreeCtrl.InsertItem(TEXT("��ͨվ��"),8,6,GameItem1,TVI_LAST);
	//		HTREEITEM Room_Item1_1_1=mTreeCtrl.InsertItem(TEXT("������"),9,6,Room_Item1_1,TVI_LAST);
	//		HTREEITEM Room_Item1_1_2=mTreeCtrl.InsertItem(TEXT("�߼���"),9,6,Room_Item1_1,TVI_LAST);
	//		HTREEITEM Room_Item1_1_3=mTreeCtrl.InsertItem(TEXT("VIP��"),9,6,Room_Item1_1,TVI_LAST);
	//
	//
	//	HTREEITEM Room_Item1_2=mTreeCtrl.InsertItem(TEXT("����վ��"),8,6,GameItem1,TVI_LAST);
	//		HTREEITEM Room_Item1_2_1=mTreeCtrl.InsertItem(TEXT("û�к��ʵķ���"),9,6,Room_Item1_2,TVI_LAST);

	//	HTREEITEM Room_Item1_3=mTreeCtrl.InsertItem(TEXT("����վ��"),8,6,GameItem1,TVI_LAST);
	//		HTREEITEM Room_Item1_3_1=mTreeCtrl.InsertItem(TEXT("û�к��ʵķ���"),9,6,Room_Item1_3,TVI_LAST);


	////����������Ϸ
	//HTREEITEM GameItem2=mTreeCtrl.InsertItem(TEXT("��������"),7,6,Root,TVI_LAST);

	//	HTREEITEM Room_Item2_1=mTreeCtrl.InsertItem(TEXT("û�к��ʵ�վ��"),8,6,GameItem2,TVI_LAST);

	////�����ƾ���Ϸ
	//HTREEITEM GameItem3=mTreeCtrl.InsertItem(TEXT("�����ƾ�"),7,6,Root,TVI_LAST);

	//	HTREEITEM Room_Item3_1=mTreeCtrl.InsertItem(TEXT("û�к��ʵ�վ��"),8,6,GameItem3,TVI_LAST);

	////չ�����нڵ�
	////ExpandAllItem(&m_TreeCtrl,m_TreeCtrl.GetRootItem());

	}
}
*/


void COffineQQDlg::RecvPacketRecords(CCommonUnPack* p)
{
	CString type;
	type.Format("%s",p->pConfig->strServiceCmd.c_str());
	DataLogBytes(type,(unsigned char*)p->pack.contents(),p->pack.size()-p->pack.rpos());
	StatusLogText(p->pConfig->strServiceCmd.c_str());
}

/*
void COffineQQDlg::InsertRecvMsg(TextMsg msg)
{
	int num=mList2.GetItemCount();
	CString size;
	size.Format("%d",num+1);
	mList2.InsertItem(num,size);
	CString Uin;
	Uin.Format("%d",msg.Uin);
	mList2.SetItemText(num,1,Uin);
	CString time;
	time.Format("%d",msg.Time);
	mList2.SetItemText(num,2,time);
	CString strContent;
	strContent.Format("%s",msg.MsgContent.c_str());
	mList2.SetItemText(num,3,strContent);
}
*/

void COffineQQDlg::InitSendPacket()
{
	//���õ�ǰ��Ϣ֪ͨ����
	ChangeNotifyWnd(m_hWnd,WM_RECEIVED_MSG);
	//����OidbSvc.0x7a2_0
	CPackReq *p=new CPackReq();
	p->SetPacketType(OidbSvc_0x7a2_0);
	p->SetSeq(mSeqSerial.GetNexSeq());
	p->pConfig=&Config;
	p->PackData();
	SendPacket(Config.m_iCurrentClientID, (unsigned char*)p->pack.contents(), p->pack.size());
	delete p;
	//����GrayUinPro_Check
	//p=new CPackReq();
	//Config.strServiceCmd=STR_GrayUinPro_Check;
	//p->SetPacketType(GrayUinPro_Check);
	//Config.isNeedCode=false;
	//Config.isSidUsed=false;
	//p->pConfig=&Config;
	//p->PackData();
	//SendPacket(Config.m_iCurrentClientID,&(p->pack));
	//delete p;
	
	//��ʼ��ѯ��״̬
	CPackReq mPack;
	mPack.SetPacketType(account_RequestQueryQQBindingStat);
	mPack.SetSeq(mSeqSerial.GetNexSeq(CSeqSerial::initial_RequestQueryQQBindingStat));
	mPack.pConfig=&Config;
	mPack.PackData();
	SendPacket(Config.m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}

BOOL COffineQQDlg::SetHeartPacket()
{
	LARGE_INTEGER li;
	li.QuadPart = 0;
	gHeartThread[0]=CreateWaitableTimer(NULL, FALSE, NULL);
	SetWaitableTimer(gHeartThread[0], &li, 300*1000, NULL, NULL, FALSE);		//5����

	gHeartThread[1]=CreateEvent(NULL, TRUE, FALSE, NULL); //��ʼ��ΪFALSE���˹������¼������ڽ����߳�

	//�����ֹ���̵߳�����
	HANDLE Thread=CreateThread(NULL,0,HeartThreadProc,this,0,NULL);
	if(Thread==NULL)
	{
		return FALSE;
	}
	return TRUE;
}

DWORD _stdcall COffineQQDlg::HeartThreadProc( LPVOID lpParam )
{
	COffineQQDlg *pThis=static_cast<COffineQQDlg*>(lpParam);
	CPackReq p;
	p.SetPacketType(StatSvc_register);
	pThis->Config.mRegisterCmd=CmdHeartBeat;
	p.pConfig=&pThis->Config;
	p.PackData();

	//��װheartBeat��
	bool isLiving=true;
	while(isLiving)
	{
		DWORD dw=WaitForMultipleObjects(2,pThis->gHeartThread,FALSE,INFINITE);
		switch(dw)
		{
			case WAIT_FAILED:
				break;
			case WAIT_TIMEOUT:
				break;
			case WAIT_OBJECT_0 + 0:
				{
					pThis->DlgSend(p.pConfig->m_iCurrentClientID,p.pack);
					pThis->mList1.AddString("�����������ݰ�");
				}break;
			case WAIT_OBJECT_0 + 1:
				{
					isLiving=false;
				}
				break;
		}
	}
	CloseHandle(pThis->gHeartThread[0]);
	CloseHandle(pThis->gHeartThread[1]);
	return 1;
}

//����״̬
void COffineQQDlg::SetUinStatus(UinStatus status)
{
	CMenu *pMenu=GetMenu();
	pMenu->GetSubMenu(0)->CheckMenuItem(3,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(4,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(5,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(6,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(7,MF_BYPOSITION|MF_UNCHECKED);
	pMenu->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_UNCHECKED);
	switch(status)
	{
	case BeOnLine:
		{
			pMenu->GetSubMenu(0)->CheckMenuItem(3,MF_BYPOSITION|MF_CHECKED);
		}break;
	case BeInvisible:
		{
			pMenu->GetSubMenu(0)->CheckMenuItem(8,MF_BYPOSITION|MF_CHECKED);
		}break;
	default:
		{
		}break;
	}
	Config.mStatus=status;	
	UpdateUinStatus();
}

void COffineQQDlg::UpdateUinStatus()
{
	CString strStatus;
	switch(Config.mStatus)
	{
	case BeOffine:
		{
			strStatus=BeOffineTip;
		}break;
	case BeOnLine:
		{
			strStatus=BeOnLineTip;
		}break;
	case BeInvisible:
		{
			strStatus=BeInvisibleTip;
		}break;
	case BeOther:
		{
			strStatus=BeOtherTip;
		}break;
	default:
		{
			return;
		}break;
	}
	this->m_Status.UpdataUinStatus(Config.qq_id,CString(&Config.UserName[1]),strStatus);
}

/*��������*/
void COffineQQDlg::On32779()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("���ȵ�¼�˺�");
		return;
	}
	SetUinStatus(BeOnLine);
	/*CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);*/
}

/*����*/
void COffineQQDlg::On32784()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("���ȵ�¼�˺�");
		return;
	}
	// TODO: �ڴ���������������
	SetUinStatus(BeInvisible);
	
	/*CCommReq p;
	p.SetPacketType(Type000D);
	p.pConfig=&Config;
	p.PackData();
	DlgSend(p.pConfig->m_iCurrentClientID,p.pack);*/
}

/*ע��*/
void COffineQQDlg::OnOffineLine()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("���ȵ�¼�˺�");
		return;
	}
	CPackReq mPack;
	mPack.SetPacketType(StatSvc_register);
	mPack.SetSeq(mSeqSerial.GetNexSeq());
	Config.mRegisterCmd=CmdOffLine;
	mPack.pConfig=&Config;
	mPack.PackData();
	SendPacket(Config.m_iCurrentClientID,(unsigned char*)mPack.pack.contents(), mPack.pack.size());
}

/*��½�ɹ�*/
afx_msg LRESULT COffineQQDlg::OnLoginsuccessed(WPARAM wParam, LPARAM lParam)
{
	//���ε�½�ɹ�
	AfxMessageBox("��½�ɹ�");
	//��ʾ�û��˺���Ϣ�Լ�״̬
	SetUinStatus(BeOnLine);
	InitSendPacket();
	return 0;
}

//�رճ���
void COffineQQDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(Config.mStatus!=BeOffine)
	{
		//����
		if(IDYES==MessageBox("ȷ���رճ��򣿵��ת����������","�ر�",MB_YESNO))
		{
			OnOffineLine();
			CDialogEx::OnClose();
		}else
		{
			TrayMessage(m_hWnd,NIM_ADD,NULL,"���̳���");
			TrayMessage(m_hWnd,NIM_MODIFY,m_hIcon,"���̳���");
			ShowWindow(SW_HIDE);
		}
	}else
	{
		CDialogEx::OnClose();
	}
}

//��������
BOOL COffineQQDlg::TrayMessage(HWND hWnd,DWORD dwMessage,HICON hIcon,PSTR pszTip)
{
	BOOL bReturn;
	NOTIFYICONDATA NofityData;
	NofityData.cbSize=sizeof(NOTIFYICONDATA);
	NofityData.hWnd=hWnd;
	NofityData.uID=IDR_MAINFRAME;
	NofityData.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	NofityData.uCallbackMessage=WM_TRAY_NOTIFICATION;
	NofityData.hIcon=hIcon;
	lstrcpyn(NofityData.szTip,pszTip,sizeof(NofityData.szTip));
	bReturn=Shell_NotifyIcon(dwMessage,&NofityData);
	return bReturn;
}

//������Ϣ����
afx_msg LRESULT COffineQQDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
	case WM_RBUTTONUP:
		{
			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);//�õ����λ�� 
			CMenu temp,*ptr=NULL;
            temp.LoadMenu(IDR_MENU3);
            ptr = temp.GetSubMenu(0);
			if(ptr==NULL) return 0;
			SetForegroundWindow();
			UINT uFlags = TPM_RIGHTBUTTON;
            if (GetSystemMetrics(SM_MENUDROPALIGNMENT) != 0)
            {
                uFlags |= TPM_RIGHTALIGN;
            }
            else
            {
                uFlags |= TPM_LEFTALIGN;
            }
			ptr->TrackPopupMenuEx( uFlags, lpoint->x, lpoint->y, this, NULL);
			temp.DestroyMenu();
			delete lpoint;
		}break;
	case WM_LBUTTONDBLCLK:
		{
			ShowWindow(SW_SHOW);
			TrayMessage(m_hWnd,NIM_DELETE,NULL,"");
		}break;
	}

	return 0;
}

//���̹رճ���
void COffineQQDlg::On32793()
{
	// TODO: �ڴ���������������
	if(Config.mStatus!=BeOffine)
	{
		//����
		if(IDYES==MessageBox("ȷ��ע���˺Ų��رճ���","�ر�",MB_YESNO))
		{
			OnOffineLine();
			Sleep(3000);
			//ͣ�����뷢����Ϣ����
			DestroyWindow();
		}
	}
}

//������
void COffineQQDlg::On32794()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("���ȵ�¼�˺�");
		return;
	}
	pMBLBindSet=new CMBLBindSet;
	pMBLBindSet->pConfig=&Config;
	pMBLBindSet->DoModal();
	delete pMBLBindSet;
	pMBLBindSet=NULL;
}

//��������
void COffineQQDlg::OnNetSet()
{
	// TODO: �ڴ���������������
	m_ConfigDlg.DoModal();
}

//Ӳ������
void COffineQQDlg::OnMachineSet()
{
	// TODO: �ڴ���������������
	m_MachineDlg.pConfig=&Config;
	m_MachineDlg.DoModal();
}

//�󶨲�ѯ
void COffineQQDlg::On32801()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("���ȵ�¼�˺�");
		return;
	}
	pMobileQuery=new CMobileNo();
	pMobileQuery->pConfig=&Config;
	pMobileQuery->DoModal();
	delete pMobileQuery;
	pMobileQuery=NULL;
}

//�ǳƲ�ѯ
void COffineQQDlg::On32802()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("���ȵ�¼�˺�");
		return;
	}
	pNickNameQuery=new CNickNameQuery();
	pNickNameQuery->pConfig=&Config;
	pNickNameQuery->DoModal();
	delete pNickNameQuery;
	pNickNameQuery=NULL;
}

//��������
void COffineQQDlg::On32803()
{
	if(Config.mStatus==BeOffine)
	{
		AfxMessageBox("���ȵ�¼�˺�");
		return;
	}
	pSearchDlg=new CSearchDlg();
	pSearchDlg->pConfig=&Config;
	pSearchDlg->DoModal();
	delete pSearchDlg;
	pSearchDlg=NULL;
}

//�����˹���
void COffineQQDlg::On32804()
{
	// TODO: �ڴ���������������
	//if(Config.mStatus==BeOffine)
	//{
	//	AfxMessageBox("���ȵ�¼�˺�");
	//	return;
	//}
	pCNearByDlg=new CCNearByDlg();
	pCNearByDlg->pConfig=&Config;
	pCNearByDlg->DoModal();
	delete pCNearByDlg;
	pCNearByDlg=NULL;
}
