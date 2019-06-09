
// directorysearchDlg.h : header file
//

#pragma once
#include "B+tree.h"
// CdirectorysearchDlg dialog
class CdirectorysearchDlg : public CDialogEx
{
// Construction
public:
	CdirectorysearchDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTORYSEARCH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString browseValue;
	btree b;
	afx_msg void OnClickedIndex();
	CString searchText;
	afx_msg void OnClickedSearch();
	afx_msg void OnBnClickedOk();
//	CButton exitBtn;
};
