
// vClsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"

// CvClsDlg �Ի���
class CvClsDlg : public CDialogEx
{
// ����
public:
	CvClsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VCLS_DIALOG };

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
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
private:
	CComboBox m_comb1;
	CComboBox m_comb2;
	CComboBox combo_AreaMode;
	CComboBox combo_ScendMode;
public:
	CMscomm1 m_mscom;
private:
	CString m_editReceive;
	CString m_editSend;
public:
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void proceedDataSend();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	CEdit m_Edit;
	int position[4];
	int myScreenWidth;
	int myScreenHeight;
	CStatic m_Resolving;

};
