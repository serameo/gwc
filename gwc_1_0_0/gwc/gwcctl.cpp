/*
 * Filename: gwcctl.cpp
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 19-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#include "gwcctl.h"
#include "gwcerr.h"

using namespace gwc::win32;

///////////////////////////////////////////////////////////////////////////////
// GWCControl
GWCControl::GWCControl()
  : m_pPrevWndProc(NULL)
{
}

LRESULT CALLBACK GWCControl::StaticControlProc(HWND hCtrl, UINT message, WPARAM wParam, LPARAM lParam)
{
  GWCWindow *pCtrl = (GWCWindow*)::GetWindowLongPtr(hCtrl, GWL_USERDATA);
  WNDPROC lpPrevWndProc = (WNDPROC)::GetWindowLongPtr(hCtrl, GWL_WNDPROC);
  switch (message)
  {
  case WM_CREATE:
    {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pCtrl = (GWCWindow*)lpcs->lpCreateParams;
      pCtrl->m_hWnd = hCtrl;
      ::SetWindowLongPtr(hCtrl, GWL_USERDATA, (LONG)pCtrl);
    }
    break;
  }
  if (pCtrl)
  {
    return pCtrl->WindowProc(message, wParam, lParam);
  }
  return ::DefWindowProc(hCtrl, message, wParam, lParam);
}
BOOL GWCControl::CreateEx(DWORD dwExStyle,
  LPCTSTR lpWindowName,
  DWORD dwStyle,
  int x, int y, int w, int h,
  GWCWindow* pParentWnd,
  UINT nID,
  HINSTANCE hInst)
{
  GWC_ASSERT(pParentWnd != NULL && pParentWnd->m_hWnd != NULL);
  GWC_ASSERT(m_hWnd == NULL);
  GWC_ASSERT(m_pPrevWndProc == NULL);

  HWND hCtrl = ::CreateWindowEx(dwExStyle,
    GetClassName(),
    lpWindowName,
    dwStyle,
    x, y, w, h,
    pParentWnd->m_hWnd,
    (HMENU)nID,
    hInst,
    this);
  if (NULL == hCtrl)
  {
    return FALSE;
  }
  return TRUE;
}

BOOL GWCControl::Create(
  LPCTSTR lpWindowName,
  DWORD dwStyle,
  int x, int y, int w, int h,
  GWCWindow* pParentWnd,
  UINT nID,
  HINSTANCE hInst)
{
  return CreateEx(0, 
    lpWindowName,
    dwStyle,
    x, y, w, h,
    pParentWnd,
    nID,
    hInst);
}

LRESULT GWCControl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  if (m_pPrevWndProc)
  {
    return ::CallWindowProc(m_pPrevWndProc, m_hWnd, message, wParam, lParam);
  }
  return GWCWindow::DefWindowProcW(message, wParam, lParam);
}

BOOL GWCControl::Subclass(GWCWindow *pWnd)
{
  GWC_ASSERT(pWnd != NULL && pWnd->m_hWnd != NULL);
  GWC_ASSERT(m_hWnd == NULL);
  GWC_ASSERT(m_pPrevWndProc == NULL);

  m_hWnd = pWnd->m_hWnd;
  m_pPrevWndProc = (WNDPROC)::SetWindowLongPtr(m_hWnd, GWL_WNDPROC, (LONG)StaticControlProc);
  ::SetWindowLongPtr(m_hWnd, GWL_USERDATA, (LONG)this);

  return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
// GWCButton

inline LPCTSTR GWCButton::GetClassName()
{
  return TEXT("BUTTON");
}