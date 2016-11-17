
// vClsDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CvClsDlg 对话框




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


// CvClsDlg 消息处理程序

BOOL CvClsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
CString str;  int i;   
for(i=0;i<15;i++)
  {     
  str.Format(_T("com %d"),i+1); 
  m_comb1.InsertString(i,str);   
  }   
m_comb1.SetCurSel(8);//预置COM口  
//波特率选择组合框   
CString str1[]={_T("300"),_T("600"),_T("1200"),_T("2400"),_T("4800"),_T("9600"),
               _T("19200"),_T("38400"),_T("43000"),_T("56000"),_T("57600"),_T("115200")};
for(int i=0;i<12;i++)
   {   
   int judge_tf = m_comb2.AddString(str1[i]);
   if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
        MessageBox(_T("build baud error!"));   
   }    
m_comb2.SetCurSel(0);//预置波特率为"115200" 
	
	//set scene mode 
	CString str2[]={_T(""),_T("MILD"),_T("MODERATE"),_T("FOG"),_T("MAX"),_T("DARK"),_T("MEDICAL")};
	for(int i=0;i<7;i++)
   {   
   int judge_tf = combo_ScendMode.AddString(str2[i]);
   if((judge_tf==CB_ERR)||(judge_tf==CB_ERRSPACE))
        MessageBox(_T("build baud error!"));   
   }    	
	combo_ScendMode.SetCurSel(0);

	//读取，显示分辨率
	myScreenWidth = GetSystemMetrics ( SM_CXSCREEN ); 
	myScreenHeight= GetSystemMetrics ( SM_CYSCREEN );
	char resolvingtmp[10];
	CString w;
	w.Format(_T("%d  %d"),myScreenWidth,myScreenHeight);
	m_Resolving.SetWindowTextW((w));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CvClsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
		
        if(GetAsyncKeyState(VK_LBUTTON)& 0x01)  //监视左键  
        {  
            //scr=GetDC();                     //获取屏幕设备场景  
            GetCursorPos(&point);             //获取当前鼠标位置  
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
            //rgb=GetPixel(scr,point.x,point.y);//获取鼠标当前位置的颜色  
			//ReleaseDC(scr);                 //释放屏幕设备场景
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
//定义字符串
GetDlgItemText(IDC_BUTTON_OPEN,str);
CWnd *h1;
h1=GetDlgItem(IDC_BUTTON_OPEN);
//指向控件的caption
if(!m_mscom.get_PortOpen())
	{
	m_comb2.GetLBText(m_comb2.GetCurSel(),str1);//取得所选的字符串，并存放在str1里面
	str1=str1+','+'n'+','+'8'+','+'1';//这句话很关键
	m_mscom.put_CommPort((m_comb1.GetCurSel()+1));//选择串口
	m_mscom.put_InputMode(1);//设置输入方式为二进制方式
	MessageBox(str1); 
	m_mscom.put_Settings(str1);//波特率为（波特率组á合框）无校验，8数据位，1个停止位
	m_mscom.put_InputLen(1024);//设置当前接收区数据长度为1024
	m_mscom.put_RThreshold(1);//缓冲区一个字符引发事件
	m_mscom.put_RTSEnable(1);
	//设置RT允许
	m_mscom.put_PortOpen(true);
	//打开串口
	if(m_mscom.get_PortOpen())
		{
			str=_T("关闭串口");
			UpdateData(true);
			h1->SetWindowText(str);//改变按钮名称为‘’关闭串口”}
		}
	else
		{
		MessageBox(_T("cant close"));
		m_mscom.put_PortOpen(false);
		if(str!=(_T("打开串口")))
			{
				str=_T("打开串口");
				UpdateData(true);
				h1->SetWindowText(str);
				//改变按钮名称为打开串口
			}
		}
	}
}


void CvClsDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	m_editReceive=_T("");//给接收编辑框发送空格符
	UpdateData(false);
	//更新数据
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
		//将字符串转化为字节数据
		HexDataBuf.SetSize(GetLen+1);            
		//设置数组大小为帧长度  
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
	//更新控件数据
	//m_mscom.put_Output(COleVariant(m_editSend));//把发送编辑框的数据发送出去
	GetLen = m_editSend.GetLength();
	for(i=0; i<GetLen; i++)
	{
	GetData[i] = (BYTE)m_editSend.GetBuffer()[i];
	SendBuf[i]= (unsigned char)GetData[i];
	}
	SendBuf[GetLen]=13;
//将字符串转化为字节数据

	HexDataBuf.SetSize(GetLen+1);            
//设置数组大小为帧长度  
	for(i=0; i<(GetLen+1); i++)
	{
	HexDataBuf.SetAt(i,SendBuf[i]);
	}
	m_mscom.put_Output(COleVariant(HexDataBuf)); 
//发送十六进制数据
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
	VARIANT InputData=m_mscom.get_Input(); //读缓冲区   
	COleSafeArray fs;    
	fs=InputData; //VARIANT型变à量转换为COleSafeArray型变量   
	for(k=0;k<fs.GetOneDimSize();k++)    
	fs.GetElement(&k,str+k); //转换为BYTE型数组        
	m_editReceive+=str;      // 接收到编辑框里面
	//SetTimer(1,10,NULL);  //延时10ms    
	UpdateData(false);   
	}

m_Edit.SetSel(-1, -1);   
this->SetDlgItemTextW(IDC_EDIT1,m_editReceive);
//将m_EditReceive内容显示到ID为IDC_EDIT1的编辑框的最后位置  
m_Edit.LineScroll(m_Edit.GetLineCount()-1,0);
//将垂直滚动条滚动到最后一
}




