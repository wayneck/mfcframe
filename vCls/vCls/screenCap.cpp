// screenCap.cpp : implementation file
//

#include "stdafx.h"
#include "vCls.h"
#include "screenCap.h"
#include "afxdialogex.h"

CPoint screenCap_ptEnd;                     
CPoint screenCap_ptBegin; 
int  ifFinish;

// screenCap dialog

IMPLEMENT_DYNAMIC(screenCap, CDialog)

screenCap::screenCap(CWnd* pParent /*=NULL*/)
	: CDialog(screenCap::IDD, pParent)
{

}

screenCap::~screenCap()
{
}

void screenCap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(screenCap, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_QUERYDRAGICON()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// screenCap message handlers

BOOL screenCap::OnInitDialog()                                                                          
{     
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);            
	m_hMyCursor = ::LoadCursor(NULL, IDC_CROSS);               
	m_bIsBegin = FALSE;                                        
	m_bIsEnd = FALSE; 
	i=0;
	// Add "About..." menu item to system menu.                                                                                                                                                                                                                                                                                          
	// TODO: Add extra initialization here                                                                        
	//加入WS_EX_LAYERED扩展属性,以下用于对话框透明显示                                                            
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,                                                               
	GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) ^ 0x80080);
	HINSTANCE hInst = LoadLibraryW(L"User32.DLL");                                                                  
                                                                                                                
	if(hInst)                                                                                                     
	{                                                                                                             
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);                                                    
		MYFUNC fun = NULL;                                                                                          
                                                                                                                
		//取得SetLayeredWindowAttributes函数指针                                                                    
		fun = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");                                          
		if (fun)                                                                                                    
		{                                                                                                           
			fun(this->GetSafeHwnd(), 0, 20, 2);                                                                       
		}                                                                                                           
		FreeLibrary(hInst);                                                                                         
	}                                                                                                             
                                                                                                                
	//窗口最大化                                                                                                  
	ShowWindow(SW_SHOWMAXIMIZED);                                                                                 
	return TRUE;  // return TRUE  unless you set the focus to a control                                           
}                                                                                                               
                                                                                                                
void screenCap::OnSysCommand(UINT nID, LPARAM lParam)                                                   
{                                                                                                               
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)                                                                           
	{                                                                                                             
		screenCap dlgAbout;                                                                                         
		dlgAbout.DoModal();                                                                                         
	}                                                                                                             
	else                                                                                                          
	{                                                                                                             
		// 注释掉，使窗口不能被移动                                                                                 
	//	CDialog::OnSysCommand(nID, lParam);                                                                       
	}                                                                                                             
}                                                                                                               
                                                                                                                



void screenCap::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bIsBegin == FALSE)                                 
	{                                                        
		m_bIsBegin = TRUE;                                     
		m_ptBegin = point;  
		screenCap_ptBegin = point;
	}                                                        
                                                           
	CDialog::OnLButtonDown(nFlags, point);                   

}


void screenCap::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

// TODO: Add your message handler code here and/or call default       
m_ptEnd = point; 
screenCap_ptEnd = point;
m_bIsEnd = TRUE;                                                      
m_bIsBegin = FALSE;  
i=2;
CDialog::OnLButtonUp(nFlags, point);                                  

}


void screenCap::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if (m_bIsBegin == TRUE && m_bIsEnd == FALSE)                              
	{                                                                         
		CClientDC dc(this);                                                     
		CPen pen(PS_SOLID, 4, RGB(0, 0, 0));                                    
		                                                                        
		dc.SelectObject(&pen);                                                  
		dc.Rectangle(m_ptBegin.x, m_ptBegin.y, point.x, point.y);               
	}                                                                         
                                                                            
	CDialog::OnMouseMove(nFlags, point);                                      

}


void screenCap::OnRButtonDown(UINT nFlags, CPoint point)
{	                                                                                                                                             
	CDialog::OnRButtonDown(nFlags, point);                                                   

}


BOOL screenCap::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: Add your message handler code here and/or call default

	if(i==2){
	screenCap::ShowWindow(SW_HIDE);
	m_bIsBegin = FALSE;
	m_bIsEnd = FALSE;
	ifFinish = 2;
	i=0;
	}
	ifFinish = 0;
	if ((HTCLIENT == nHitTest)                                                        
		&& (m_hMyCursor != NULL))                                                       
    {                                                                               
        ::SetCursor(m_hMyCursor);                                                   
        return TRUE;                                                                
    }                                                                               
                                                                                    
	return CDialog::OnSetCursor(pWnd, nHitTest, message);                             

}


HCURSOR screenCap::OnQueryDragIcon()
{
	// TODO: Add your message handler code here and/or call default

	return (HCURSOR) m_hIcon;   
}


void screenCap::OnPaint()
{
	if (IsIconic())                                                       
	{                                                                     
		CPaintDC dc(this); // device context for painting                   
                                                                        
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);        
                                                                        
		// Center icon in client rectangle                                  
		int cxIcon = GetSystemMetrics(SM_CXICON);                           
		int cyIcon = GetSystemMetrics(SM_CYICON);                           
		CRect rect;                                                         
		GetClientRect(&rect);                                               
		int x = (rect.Width() - cxIcon + 1) / 2;                            
		int y = (rect.Height() - cyIcon + 1) / 2;                           
                                                                        
		// Draw the icon                                                    
		dc.DrawIcon(x, y, m_hIcon);                                         
	}                                                                     
	else                                                                  
	{                                                                     
		CDialog::OnPaint();                                                 
	}                                                                     

}