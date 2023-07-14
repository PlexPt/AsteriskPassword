
// AsteriskPasswordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AsteriskPassword.h"
#include "AsteriskPasswordDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CAsteriskPasswordDlg::CAsteriskPasswordDlg(CWnd* pParent)
	: CDialogEx(CAsteriskPasswordDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bDragging = FALSE;
}

void CAsteriskPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAsteriskPasswordDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BOOL CAsteriskPasswordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

HWND CAsteriskPasswordDlg::SmallestWindowFromPoint(POINT point)
{
	HWND hWndSmallest = NULL;
	HWND hWndParent = ::WindowFromPoint(point);

	if (hWndParent != NULL) {
		RECT rcParent;
		::GetWindowRect(hWndParent, &rcParent);

		// ����������ڸ������ڣ����Ƚ���������Ϊ��С����
		if (::PtInRect(&rcParent, point)) {
			hWndSmallest = hWndParent;
		}
		else {
			// ���򣬱��������ڵ�����ͬ�����ڣ����Ұ������������С����
			HWND hWndChild = ::GetWindow(hWndParent, GW_HWNDNEXT);
			while (hWndChild != NULL) {
				if (::IsWindowVisible(hWndChild)) {
					RECT rcChild;
					::GetWindowRect(hWndChild, &rcChild);

					if (::PtInRect(&rcChild, point) && ::GetParent(hWndChild) == hWndParent) {
						// �����ǰ�Ӵ��ڰ����������ҿɼ�����Ƚ����С��ѡ����С�Ĵ���
						if ((rcChild.right - rcChild.left) * (rcChild.bottom - rcChild.top) <
							(rcParent.right - rcParent.left) * (rcParent.bottom - rcParent.top)) {
							hWndSmallest = hWndChild;
							rcParent = rcChild;
						}
					}
				}
				hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
			}
		}
	}

	return hWndSmallest;
}

VOID CAsteriskPasswordDlg::GetControllerText()
{
	POINT p;
	HWND hWnd;
	LRESULT ch;
	INT nLength;
	LONG lWindowLong;
	TCHAR szClassName[MAX_PATH];
	const UINT nTimeout = 1000;

	GetCursorPos(&p);
	hWnd = SmallestWindowFromPoint(p);
	if (hWnd != NULL) {
		nLength = ::SendMessage(hWnd, WM_GETTEXTLENGTH, 0, 0);
		if (nLength > 0) {
			m_strBuffer.GetBufferSetLength(nLength);

			::GetClassName(hWnd, szClassName, MAX_PATH);
			if (::lstrcmpi(szClassName, L"Edit") == 0) {
				lWindowLong = ::GetWindowLong(hWnd, -16);
				::SetWindowWord(hWnd, -16, 0);
				::SetWindowLong(hWnd, -16, lWindowLong & 0xFFFFFFDF);
				::SendMessageTimeout(hWnd, WM_GETTEXT, nLength + 1, (LPARAM)m_strBuffer.GetBuffer(nLength + 1), SMTO_NOTIMEOUTIFNOTHUNG, nTimeout, NULL);
				::SetWindowLong(hWnd, -16, lWindowLong);

			} else {
				ch = ::SendMessage(hWnd, EM_GETPASSWORDCHAR, 0, 0);
				::PostMessage(hWnd, EM_SETPASSWORDCHAR, 0, 0);
				::SendMessageTimeout(hWnd, WM_GETTEXT, nLength + 1, (LPARAM)m_strBuffer.GetBuffer(nLength + 1), SMTO_NOTIMEOUTIFNOTHUNG, nTimeout, NULL);
				::PostMessage(hWnd, EM_SETPASSWORDCHAR, ch, 0);
			}
			
			m_strBuffer.ReleaseBuffer();

			if (!m_strBuffer.IsEmpty()) {
				CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT);
				pEdit->SetWindowText(m_strBuffer);
				m_strBuffer.Empty();
			}
		}
		else {
			m_strBuffer.Empty();
		}
	}
}

void CAsteriskPasswordDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* pChildWnd = ChildWindowFromPoint(point, CWP_ALL);
	if (pChildWnd != NULL && pChildWnd->GetDlgCtrlID() == IDC_STATIC0)
	{
		SetCapture();
		m_bDragging = TRUE;
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CAsteriskPasswordDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragging)
	{
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));
		GetControllerText();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CAsteriskPasswordDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDragging)
	{
		::ReleaseCapture();
		m_bDragging = FALSE;
		::SetCursor(::LoadCursor(NULL, IDC_ARROW));
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
