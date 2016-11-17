
// vClsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "vCls.h"
#include "vClsDlg.h"
#include "afxdialogex.h"

#include<iostream>  
#include<windows.h> 
#include<stdio.h>
#include<Strsafe.h>
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


// CvClsDlg �Ի���




CvClsDlg::CvClsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CvClsDlg::IDD, pParent)
	, m_editReceive(_T(""))
	, m_editSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvClsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, m_comb1);
	DDX_Control(pDX, IDC_COMBO4, m_comb2);
	DDX_Control(pDX, IDC_MSCOMM1, m_mscom);
	DDX_Text(pDX, IDC_EDIT1, m_editReceive);
	DDX_Text(pDX, IDC_EDIT6, m_editSend);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Control(pDX,IDC_STATICResolving,m_Resolving);
	DDX_Control(pDX, IDC_COMBO2, combo_AreaMode);
	DDX_Control(pDX, IDC_COMBO1, combo_ScendMode);
}

BEGIN_MESSAGE_MAP(CvClsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CvClsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CvClsDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CvClsDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CvClsDlg::OnEnChangeEdit3)	
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CvClsDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CvClsDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CvClsDlg::OnBnClickedButtonSend)

END_MESSAGE_MAP()


// CvClsDlg ��Ϣ�������

BOOL CvClsDlg::OnInitDialog()
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
CString str;  int i;   
for(i=0;i<15;i++)
  {     
  str.Format(_T("com %d"),i+1); 
  m_comb1.InsertString(i,str);   
  }   
m_comb1.SetCurSel(8);//Ԥ��COM��  
//������ѡ����Ͽ�   
CString str1[]={_T("300"),_T("600"),_T("1200"),_T("2400"),_T("4800"),_T("9600"),
               _T("19200"),_T("38400"),_T("43000"),_T("56000"),_T("57600"),_T("115200")};
for(int i=0;i<12;i++)
   {   
   int judge_tf = m_comb2.AddString(str1[i]);
   if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
        MessageBox(_T("build baud error!"));   
   }    
m_comb2.SetCurSel(0);//Ԥ�ò�����Ϊ"115200" 
	
	//set scene mode 
	CString str2[]={_T(""),_T("MILD"),_T("MODERATE"),_T("FOG"),_T("MAX"),_T("DARK"),_T("MEDICAL")};
	for(int i=0;i<7;i++)
   {   
   int judge_tf = combo_ScendMode.AddString(str2[i]);
   if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
        MessageBox(_T("build baud error!"));   
   }    	
	combo_ScendMode.SetCurSel(0);

	//��ȡ����ʾ�ֱ���
	myScreenWidth = GetSystemMetrics ( SM_CXSCREEN ); 
	myScreenHeight= GetSystemMetrics ( SM_CYSCREEN );
	char resolvingtmp[10];
	CString w;
	w.Format(_T("%d  %d"),myScreenWidth,myScreenHeight);
	m_Resolving.SetWindowTextW((w));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CvClsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CvClsDlg::OnPaint()
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
HCURSOR CvClsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CvClsDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	proceedDataSend();
	CEdit* startX;
	startX = (CEdit*) GetDlgItem(IDC_EDIT2);
	CEdit* startY;
    startY = (CEdit*) GetDlgItem(IDC_EDIT3);
	CEdit* endX;
    endX = (CEdit*) GetDlgItem(IDC_EDIT4);
	CEdit* endY;
    endY = (CEdit*) GetDlgItem(IDC_EDIT5);
	startY->SetWindowTextW(_T(""));
	startX->SetWindowTextW(_T(""));
	endY->SetWindowTextW(_T(""));
	endX->SetWindowTextW(_T(""));
}


void CvClsDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	POINT point;      
    unsigned long rgb;  
    CDC *scr;
	int clilckNo=0;
	CEdit* startX;
    startX = (CEdit*) GetDlgItem(IDC_EDIT2);
	CEdit* startY;
    startY = (CEdit*) GetDlgItem(IDC_EDIT3);
	CEdit* endX;
    endX = (CEdit*) GetDlgItem(IDC_EDIT4);
	CEdit* endY;
    endY = (CEdit*) GetDlgItem(IDC_EDIT5);
	TCHAR chTemp[10];
    printf("please input a number:");
	//MessageBox(width,height);   

	Sleep(2); 
	while(1)  
    {  
		
        if(GetAsyncKeyState(VK_LBUTTON)& 0x01)  //�������  
        {  
            //scr=GetDC();                     //��ȡ��Ļ�豸����  
            GetCursorPos(&point);             //��ȡ��ǰ���λ��  
            //printf("x %d y %d",point.x,point.y); 
			if(clilckNo == 1){
				position[0] = point.x*100/myScreenWidth;				
				position[1] = point.y*100/myScreenHeight;
				swprintf(chTemp,L"%d",point.x);			
				startX->SetWindowTextW(chTemp);
				startX->SetFocus();
				swprintf(chTemp,L"%d",point.y);	
				startY->SetWindowTextW(chTemp);
				startY->SetFocus();
				UpdateData(true);
				Sleep(5); 
			}
			if(clilckNo == 2){
				position[2] = point.x*100/myScreenWidth;				
				position[3] = point.y*100/myScreenHeight;
				swprintf(chTemp,L"%d",point.x);
				endX->SetWindowTextW(chTemp);
				swprintf(chTemp,L"%d",point.y);
				endY->SetWindowTextW(chTemp);
			}			
			clilckNo++;
            //rgb=GetPixel(scr,point.x,point.y);//��ȡ��굱ǰλ�õ���ɫ  
			//ReleaseDC(scr);                 //�ͷ���Ļ�豸����
         }
         if(clilckNo==3)
			break;
         
    }
}


void CvClsDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CvClsDlg::OnEnChangeEdit3()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CvClsDlg::OnBnClickedButtonOpen()
{
	// TODO: Add your control notification handler code here
	CString	str,str1,n;
//�����ַ���
GetDlgItemText(IDC_BUTTON_OPEN,str);
CWnd *h1;
h1=GetDlgItem(IDC_BUTTON_OPEN);
//ָ��ؼ���caption
if(!m_mscom.get_PortOpen())
	{
	m_comb2.GetLBText(m_comb2.GetCurSel(),str1);//ȡ����ѡ���ַ������������str1����
	str1=str1+','+'n'+','+'8'+','+'1';//��仰�ܹؼ�
	m_mscom.put_CommPort((m_comb1.GetCurSel()+1));//ѡ�񴮿�
	m_mscom.put_InputMode(1);//�������뷽ʽΪ�����Ʒ�ʽ
	MessageBox(str1); 
	m_mscom.put_Settings(str1);//������Ϊ���������騢�Ͽ���У�飬8����λ��1��ֹͣλ
	m_mscom.put_InputLen(1024);//���õ�ǰ���������ݳ���Ϊ1024
	m_mscom.put_RThreshold(1);//������һ���ַ������¼�
	m_mscom.put_RTSEnable(1);
	//����RT����
	m_mscom.put_PortOpen(true);
	//�򿪴���
	if(m_mscom.get_PortOpen())
		{
			str=_T("�رմ���");
			UpdateData(true);
			h1->SetWindowText(str);//�ı䰴ť����Ϊ�����رմ��ڡ�}
		}
	else
		{
		MessageBox(_T("cant close"));
		m_mscom.put_PortOpen(false);
		if(str!=(_T("�򿪴���")))
			{
				str=_T("�򿪴���");
				UpdateData(true);
				h1->SetWindowText(str);
				//�ı䰴ť����Ϊ�򿪴���
			}
		}
	}
}


void CvClsDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	m_editReceive=_T("");//�����ձ༭���Ϳո��
	UpdateData(false);
	//��������
}
#define CmdLength 12
void CvClsDlg::proceedDataSend()
{
	CByteArray HexDataBuf;
	int i = 0;
	int j=0 ;
	CHAR  doResolCmd[CmdLength][12]={"SEWL","SEWT","SEWR","SEWB","SPRO MAX","SPRO MILD"};
	//swprintf(chTemp,L"%d",point.y);
	char  sendCmd[][12]={0};
	BYTE SendBuf[128]={0};
	BYTE GetData[256]={0};
	
	int GetLen = 0;

	if(position[0] > position[2]){
		j =position[0];
		position[0] = position[2];
		position[2] = j;
	}
	if(position[1] > position[3]){
		j =position[1];
		position[1] = position[3];
		position[3] = j;
	}

	for(i=0;i<4;i++){
		sprintf(doResolCmd[i],"%s %d",doResolCmd[i],position[i]);
		GetLen = sizeof(doResolCmd[i]);
		for(j=0; j<GetLen; j++)
		{
			GetData[j] = (BYTE)doResolCmd[i][j];
			SendBuf[j]= (unsigned char)GetData[j];
		}
		SendBuf[GetLen]=13;
		//���ַ���ת��Ϊ�ֽ�����
		HexDataBuf.SetSize(GetLen+1);            
		//���������СΪ֡����  
		for(j=0; j<(GetLen+1); j++)
		{
			HexDataBuf.SetAt(j,SendBuf[j]);
		}
		m_mscom.put_Output(COleVariant(HexDataBuf)); 
	
	}
	
	
}

void CvClsDlg::OnBnClickedButtonSend()
{
	CByteArray HexDataBuf;
	int i = 0;
	BYTE SendBuf[128]={0};
	BYTE GetData[256]={0};
	int SendLen = 0;
	int GetLen = 0;
	char szBuf[3] = {0};
	//CString strTemp =_T("");
	// TODO: Add your control notification handler code here
	UpdateData(true);
	//���¿ؼ�����
	//m_mscom.put_Output(COleVariant(m_editSend));//�ѷ��ͱ༭������ݷ��ͳ�ȥ
	GetLen = m_editSend.GetLength();
	for(i=0; i<GetLen; i++)
	{
	GetData[i] = (BYTE)m_editSend.GetBuffer()[i];
	SendBuf[i]= (unsigned char)GetData[i];
	}
	SendBuf[GetLen]=13;
//���ַ���ת��Ϊ�ֽ�����

	HexDataBuf.SetSize(GetLen+1);            
//���������СΪ֡����  
	for(i=0; i<(GetLen+1); i++)
	{
	HexDataBuf.SetAt(i,SendBuf[i]);
	}
	m_mscom.put_Output(COleVariant(HexDataBuf)); 
//����ʮ����������
	//CADtestDlg::m_SendNum += SendLen;

}
BEGIN_EVENTSINK_MAP(CvClsDlg, CDialogEx)
	ON_EVENT(CvClsDlg, IDC_MSCOMM1, 1, CvClsDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CvClsDlg::OnCommMscomm1()
{
	// TODO: Add your message handler code here
	if(m_mscom.get_CommEvent()==2)
	{   
	char str[1024]={0};   
	long k;    
	VARIANT InputData=m_mscom.get_Input(); //��������   
	COleSafeArray fs;    
	fs=InputData; //VARIANT�ͱ䨤��ת��ΪCOleSafeArray�ͱ���   
	for(k=0;k<fs.GetOneDimSize();k++)    
	fs.GetElement(&k,str+k); //ת��ΪBYTE������        
	m_editReceive+=str;      // ���յ��༭������
	//SetTimer(1,10,NULL);  //��ʱ10ms    
	UpdateData(false);   
	}

m_Edit.SetSel(-1, -1);   
this->SetDlgItemTextW(IDC_EDIT1,m_editReceive);
//��m_EditReceive������ʾ��IDΪIDC_EDIT1�ı༭������λ��  
m_Edit.LineScroll(m_Edit.GetLineCount()-1,0);
//����ֱ���������������һ
}




