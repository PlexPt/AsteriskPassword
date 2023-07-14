
// AsteriskPasswordDlg.h : ͷ�ļ�
//

#pragma once


// CAsteriskPasswordDlg �Ի���
class CAsteriskPasswordDlg : public CDialogEx
{
// ����
public:
	CAsteriskPasswordDlg(CWnd* pParent = NULL);
	enum { IDD = IDD_ASTERISKPASSWORD_DIALOG };

protected:
	HICON m_hIcon;
	BOOL m_bDragging;
	CString m_strBuffer;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void GetControllerText();
	HWND SmallestWindowFromPoint(POINT pt);
	// HWND SmallestWindowFromPoint(HWND hWndParent, POINT point);

	DECLARE_MESSAGE_MAP()
};
