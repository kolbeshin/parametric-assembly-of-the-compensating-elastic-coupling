#pragma once
#include "afxdialogex.h"


// CNewDialog2 dialog


class CNewDialog2 : public CDialog
{
	

public:
	CNewDialog2(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNewDialog2();
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CNewDialog2 };
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
	CComboBox execution2;
	afx_msg
		BOOL OnInitDialog();
	void OnCbnSelchangeCombo2();
	double lDeep;
	double B1;
	afx_msg void OnBnClickedOk();
	double d_star;
	double H;
};
