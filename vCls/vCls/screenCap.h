#pragma once


// screenCap dialog

class screenCap : public CDialog
{
	DECLARE_DYNAMIC(screenCap)

public:
	screenCap(CWnd* pParent = NULL);   // standard constructor
	virtual ~screenCap();

// Dialog Data
	enum { IDD = IDD_SCREENCAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	int i;
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HCURSOR OnQueryDragIcon();
private:
	BOOL m_bIsEnd;                      
	BOOL m_bIsBegin;                    
	HCURSOR m_hMyCursor;                
	CPoint m_ptEnd;                     
	CPoint m_ptBegin;                   
	HCURSOR m_hCursor;         
};
