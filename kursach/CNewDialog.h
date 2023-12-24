#pragma once
#include "afxdialogex.h"


// CNewDialog dialog

class CNewDialog : public CDialog
{
	DECLARE_DYNAMIC(CNewDialog)

public:
	CNewDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CNewDialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double D;
	double D1;
	double D2;
	double d;
	double L;
	double L1;
	double l;
	double l1;
	double l2;
	double B;
	double b1;
	double R;
	CComboBox execution;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	double lDeep;
	double B1;
};
