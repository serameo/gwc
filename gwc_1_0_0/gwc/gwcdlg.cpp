/*
 * Filename: gwcdlg.cpp
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 16-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#include "gwcx.h"
#include "gwcdlg.h"

using namespace gwc::win32;

///////////////////////////////////////////////////////////////////////////////
// GWCDialog
GWCDialog::GWCDialog(GWCWindow *pParentWnd, LPCTSTR lpszTemplate)
  : m_pParentWnd(pParentWnd)
  , m_pszTemplate(lpszTemplate)
{
}

GWCDialog::GWCDialog(GWCWindow *pParentWnd, UINT nIDTemplate)
  : m_pParentWnd(pParentWnd)
  , m_pszTemplate(MAKEINTRESOURCE(nIDTemplate))
{
}

BOOL CALLBACK GWCDialog::StaticDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  GWCWindow *pWnd = (GWCWindow*)::GetWindowLongPtr(hDlg, GWL_USERDATA);
  switch (message)
  {
  case WM_INITDIALOG:
    {
      pWnd = (GWCWindow*)lParam;
      pWnd->m_hWnd = hDlg;
      ::SetWindowLongPtr(hDlg, GWL_USERDATA, (LONG)pWnd);
    }
    break;
  }
  if (pWnd)
  {
    return (LRESULT)(UINT)pWnd->WindowProc(message, wParam, lParam);
  }
  return FALSE;
}

LRESULT GWCDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_INITDIALOG:
    return OnInitDialog();

  case WM_DESTROY:
    OnDestroy();
    break;

  case WM_COMMAND:
    {
      GWCWindow *pCtrl = (GWCWindow*)::GetWindowLongPtr((HWND)lParam, GWL_USERDATA);
      UINT nID = LOWORD(wParam);
      UINT nCode = HIWORD(wParam);
      switch (nID)
      {
      case IDOK: OnOK(); break;
      case IDCANCEL: OnCancel(); break;
      default: OnCommand(nID, pCtrl, nCode); break;
      }
    }
    break;
  }
  return DefWindowProc(message, wParam, lParam);
}

LRESULT GWCDialog::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  return (LRESULT)(UINT)FALSE;
}

void GWCDialog::OnCancel()
{
  ::EndDialog(m_hWnd, IDCANCEL);
}

void GWCDialog::OnOK()
{
  ::EndDialog(m_hWnd, IDOK);
}

BOOL GWCDialog::OnInitDialog()
{
  HWND hWndChild = ::GetWindow(m_hWnd, GW_CHILD);
  for (; hWndChild != NULL; hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT))
  {
    GWCWindow *pCtrl = new GWCWindow();
    pCtrl->m_hWnd = hWndChild;
    ::SetWindowLongPtr(hWndChild, GWL_USERDATA, (LONG)pCtrl);
  }
  return TRUE;
}

void GWCDialog::OnDestroy()
{
  HWND hWndChild = ::GetWindow(m_hWnd, GW_CHILD);
  for (; hWndChild != NULL; hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT))
  {
    GWCWindow *pCtrl = (GWCWindow*)::GetWindowLongPtr(hWndChild, GWL_USERDATA);
    if (pCtrl)
      delete pCtrl;
  }
}

UINT GWCDialog::Show(HINSTANCE hInst, BOOL bIsModalDialog)
{
  UINT nID = (UINT)(-1);
  if (bIsModalDialog)
  {
    nID = ::DialogBoxParam(hInst,
      m_pszTemplate,
      (m_pParentWnd ? m_pParentWnd->m_hWnd : NULL),
      (DLGPROC)StaticDialogProc,
      (LPARAM)this);
  }
  else
  {
    HWND hDlg = ::CreateDialogParam(hInst,
      m_pszTemplate,
      (m_pParentWnd ? m_pParentWnd->m_hWnd : NULL),
      (DLGPROC)StaticDialogProc,
      (LPARAM)this);
    nID = (UINT)hDlg;
  }
  return nID;
}

GWCWindow* GWCDialog::GetDlgItem(int nID)
{
  HWND hCtrl = ::GetDlgItem(m_hWnd, nID);
  return (GWCWindow*)::GetWindowLongPtr(hCtrl, GWL_USERDATA);
}

UINT GWCDialog::GetDlgCtrlID(GWCWindow *pWnd)
{
  return (pWnd ? ::GetDlgCtrlID(pWnd->m_hWnd) : ::GetDlgCtrlID(NULL));
}

UINT GWCDialog::GetDlgItemInt(int nID, BOOL *pTranslated, BOOL bSigned)
{
  return ::GetDlgItemInt(m_hWnd, nID, pTranslated, bSigned);
}

UINT GWCDialog::GetDlgItemText(int nID, LPTSTR lpString, int cchMax)
{
  return ::GetDlgItemText(m_hWnd, nID, lpString, cchMax);
}
