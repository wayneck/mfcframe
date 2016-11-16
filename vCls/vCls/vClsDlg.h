
// vClsDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"

// CvClsDlg 对话框
class CvClsDlg : public CDialogEx
{
// 构造
public:
	CvClsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VCLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
private:
	CComboBox m_comb1;
	CComboBox m_comb2;
public:
	CMscomm1 m_mscom;
private:
	CString m_editReceive;
	CString m_editSend;
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSend();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	CEdit m_Edit;
};
