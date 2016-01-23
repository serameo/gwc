/*
 * Filename: gwcwnd.cpp
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 12-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#include "gwcx.h"
#include "gwcwnd.h"
#include "gwcrc.h"
#include "gwcerr.h"

using namespace gwc::win32;

///////////////////////////////////////////////////////////////////////////////
// GWCWindow
GWCWindow::GWCWindow()
  : m_hWnd(NULL)
{
}

LPCTSTR GWCWindow::GetClassName()
{
  return NULL;
}

LRESULT GWCWindow::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  return DefWindowProc(message, wParam, lParam);
}

LRESULT GWCWindow::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  return ::DefWindowProc(m_hWnd, message, wParam, lParam);
}

BOOL GWCWindow::ShowWindow(int nCmdShow)
{
  return ::ShowWindow(m_hWnd, nCmdShow);
}

BOOL GWCWindow::UpdateWindow()
{
  return ::UpdateWindow(m_hWnd);
}

BOOL GWCWindow::AnimateWindow(DWORD dwTime, DWORD dwFlags)
{
  return ::AnimateWindow(m_hWnd, dwTime, dwFlags);
}

BOOL GWCWindow::SetWindowText(LPCTSTR lpszWindowText)
{
  return ::SetWindowText(m_hWnd, lpszWindowText);
}

LRESULT GWCWindow::SendMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
  return ::SendMessage(m_hWnd, message, wParam, lParam);
}
BOOL GWCWindow::PostMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
  return ::PostMessage(m_hWnd, message, wParam, lParam);
}

BOOL GWCWindow::TranslateAccelerator(LPMSG lpmsg)
{
  return FALSE;
}


BOOL GWCWindow::OnCreate(LPCREATESTRUCT lpcs)
{
  return TRUE;
}

void GWCWindow::OnDestroy()
{
}

BOOL GWCWindow::OnInitDialog()
{
  return TRUE;
}


void GWCWindow::OnCommand(int nID, GWCWindow *pCtrl, UINT nCode)
{
}

void GWCWindow::OnPaint(HDC hdc)
{
}

///////////////////////////////////////////////////////////////////////////////
// GWCFrameWindow
GWCFrameWindow::GWCFrameWindow()
{
}

LRESULT CALLBACK GWCFrameWindow::StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  GWCWindow *pWnd = (GWCWindow*)::GetWindowLongPtr(hWnd, GWL_USERDATA);
  switch (message)
  {
  case WM_CREATE:
    {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pWnd = (GWCWindow*)lpcs->lpCreateParams;
      pWnd->m_hWnd = hWnd;
      ::SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)pWnd);
    }
    break;
  }
  if (pWnd)
  {
    return pWnd->WindowProc(message, wParam, lParam);
  }
  return ::DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL GWCFrameWindow::Create(LPCTSTR lpWindowName, 
  DWORD dwStyle, 
  int x, 
  int y, 
  int w, 
  int h, 
  GWCWindow *pParentWnd, 
  HMENU hMenu,
  HINSTANCE hInst)
{
  return CreateEx(0, lpWindowName, dwStyle,
    x, y, w, h,
    pParentWnd,
    hMenu);
}

BOOL GWCFrameWindow::CreateEx(DWORD dwExStyle,
  LPCTSTR lpWindowName,
  DWORD dwStyle,
  int x, 
  int y, 
  int w, 
  int h, 
  GWCWindow *pParentWnd, 
  HMENU hMenu,
  HINSTANCE hInst)
{
  HWND hWnd = ::CreateWindowEx(dwExStyle,
    GetClassName(),
    lpWindowName,
    dwStyle,
    x, y, w, h,
    (pParentWnd ? pParentWnd->m_hWnd : NULL),
    hMenu,
    hInst,
    this);
  if (hWnd)
  {
    ::SetWindowText(hWnd, lpWindowName);
  }
  return (hWnd != NULL);
}

BOOL GWCFrameWindow::RegisterWindow(LPWNDCLASS lpWndCls)
{
  lpWndCls->lpfnWndProc = (WNDPROC)StaticWindowProc;
  lpWndCls->lpszClassName = GetClassName();
  return ::RegisterClass(lpWndCls);
}

BOOL GWCFrameWindow::RegisterWindow(HINSTANCE hInst,
  HBRUSH hbrBackground,
  HCURSOR hCursor,
  HICON hIcon,
  LPCTSTR lpszMenuName,
  UINT uStyle)
{
  WNDCLASS wc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = hbrBackground;
  wc.hCursor = hCursor;
  wc.hIcon = hIcon;
  wc.hInstance = hInst;
  wc.lpszMenuName = lpszMenuName;
  wc.style = uStyle;
  wc.lpfnWndProc = (WNDPROC)StaticWindowProc;
  wc.lpszClassName = GetClassName();
  return ::RegisterClass(&wc);
}

LRESULT GWCFrameWindow::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_CREATE: 
    return OnCreate((LPCREATESTRUCT)lParam);

  case WM_DESTROY:
    OnDestroy();
    break;

  case WM_COMMAND:
    {
      GWCWindow *pCtrl = (GWCWindow*)::GetWindowLongPtr((HWND)lParam, GWL_USERDATA);
      UINT nID = LOWORD(wParam);
      UINT nCode = HIWORD(wParam);
      OnCommand(nID, pCtrl, nCode);
    }
    break;

  case WM_PAINT:
    {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(m_hWnd, &ps);
      OnPaint(hdc);
      EndPaint(m_hWnd, &ps);
    }
    break;
  }
  return DefWindowProc(message, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////
// GWCMDIWindow
GWCMDIWindow::GWCMDIWindow()
  : m_hMenu(NULL)
  , m_nWindowMenuPos(0)
{
}

HMENU GWCMDIWindow::GetWindowMenu()
{
  return ::GetSubMenu(m_hMenu, m_nWindowMenuPos);
}

void GWCMDIWindow::SetWindowMenuPos(int nPos)
{
  m_nWindowMenuPos = nPos;
}

HMENU GWCMDIWindow::GetMDIMenu()
{
  return m_hMenu;
}

void GWCMDIWindow::SetMDIMenu(HMENU hMenu)
{
  m_hMenu = hMenu;
}

BOOL GWCMDIWindow::RegisterWindow(LPWNDCLASS lpWndCls)
{
  lpWndCls->lpfnWndProc = (WNDPROC)StaticWindowProc;
  lpWndCls->lpszClassName = GetClassName();
  lpWndCls->lpszMenuName = NULL;
  return ::RegisterClass(lpWndCls);
}

BOOL GWCMDIWindow::RegisterWindow(HINSTANCE hInst,
  HBRUSH hbrBackground,
  HCURSOR hCursor,
  HICON hIcon,
  LPCTSTR lpszMenuName,
  UINT uStyle)
{
  WNDCLASS wc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = hbrBackground;
  wc.hCursor = hCursor;
  wc.hIcon = hIcon;
  wc.hInstance = hInst;
  wc.lpszMenuName = NULL;
  wc.style = uStyle;
  wc.lpfnWndProc = (WNDPROC)StaticWindowProc;
  wc.lpszClassName = GetClassName();
  return ::RegisterClass(&wc);
}


///////////////////////////////////////////////////////////////////////////////
// GWCMDIFrameWindow
GWCMDIFrameWindow::GWCMDIFrameWindow()
  : m_hWndClient(NULL)
{
}

GWCMDIFrameWindow::~GWCMDIFrameWindow()
{
}

BOOL GWCMDIFrameWindow::TranslateAccelerator(LPMSG lpmsg)
{
  return (GWCFrameWindow::TranslateAccelerator(lpmsg) || ::TranslateMDISysAccel(m_hWndClient, lpmsg) );
}

LRESULT GWCMDIFrameWindow::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  return ::DefFrameProc(m_hWnd, m_hWndClient, message, wParam, lParam);
}

BOOL GWCMDIFrameWindow::OnCreate(LPCREATESTRUCT lpcs)
{
  if ( !GWCFrameWindow::OnCreate(lpcs) )
  {
    return FALSE;
  }
  CLIENTCREATESTRUCT ccs;
  if ( !OnCreateClient(&ccs) )
  {
    return FALSE;
  }
  m_hWndClient = ::CreateWindowEx(0,
    TEXT("MDICLIENT"), NULL,
    WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN|WS_VSCROLL|WS_HSCROLL,
    0, 0, 0, 0,
    m_hWnd,
    (HMENU)ID_MDICLIENT,
    lpcs->hInstance,
    (LPSTR)&ccs);
  return TRUE;
}

BOOL GWCMDIFrameWindow::OnCreateClient(LPCLIENTCREATESTRUCT lpccs)
{
  lpccs->hWindowMenu = GetWindowMenu();
  lpccs->idFirstChild = IDM_WINDOW_FIRSTCHILD;
  return TRUE;
}

void GWCMDIFrameWindow::MDICascade()
{
  ::SendMessage(m_hWndClient, WM_MDICASCADE, 0, 0L);
}

void GWCMDIFrameWindow::MDITile()
{
  ::SendMessage(m_hWndClient, WM_MDITILE, 0, 0L);
}

void GWCMDIFrameWindow::MDIIconArrange()
{
  ::SendMessage(m_hWndClient, WM_MDIICONARRANGE, 0, 0L);
}

void GWCMDIFrameWindow::OnCommand(int nID, GWCWindow *pCtrl, UINT nCode)
{
  switch (nID)
  {
  case IDM_WINDOW_CASCADE:
    OnMDICascade();
    break;

  case IDM_WINDOW_TILE:
    OnMDITile();
    break;

  case IDM_WINDOW_ARRANGEICONS:
    OnMDIIconArrange();
    break;

  default:
    GWCMDIWindow::OnCommand(nID, pCtrl, nCode);
    break;
  }
}

void GWCMDIFrameWindow::OnMDICascade()
{
  MDICascade();
}

void GWCMDIFrameWindow::OnMDITile()
{
  MDITile();
}

void GWCMDIFrameWindow::OnMDIIconArrange()
{
  MDIIconArrange();
}

///////////////////////////////////////////////////////////////////////////////
// GWCMDIChildWindow
GWCMDIChildWindow::GWCMDIChildWindow()
  : m_pFrameWnd(NULL)
{
}

GWCMDIChildWindow::GWCMDIChildWindow(GWCMDIFrameWindow *pFrameWnd)
  : m_pFrameWnd(pFrameWnd)
{
}

LRESULT CALLBACK GWCMDIChildWindow::StaticMDIChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  GWCWindow *pWnd = (GWCWindow*)::GetWindowLongPtr(hWnd, GWL_USERDATA);
  switch (message)
  {
  case WM_CREATE:
    {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      LPMDICREATESTRUCT lpmcs = (LPMDICREATESTRUCT)lpcs->lpCreateParams;
      pWnd = (GWCWindow*)lpmcs->lParam;
      pWnd->m_hWnd = hWnd;
      ::SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)pWnd);
    }
    break;
  }
  if (pWnd)
  {
    return pWnd->WindowProc(message, wParam, lParam);
  }
  return ::DefMDIChildProc(hWnd, message, wParam, lParam);
}

LRESULT GWCMDIChildWindow::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  return ::DefMDIChildProc(m_hWnd, message, wParam, lParam);
}

inline int GWCMDIChildWindow::GetClassSize()
{
  return sizeof(GWCMDIChildWindow);
}

BOOL GWCMDIChildWindow::RegisterWindow(LPWNDCLASS lpWndCls)
{
  lpWndCls->lpfnWndProc = (WNDPROC)StaticMDIChildProc;
  lpWndCls->lpszClassName = GetClassName();
  lpWndCls->cbWndExtra = GetClassSize();
  lpWndCls->lpszMenuName = NULL;
  return ::RegisterClass(lpWndCls);
}

BOOL GWCMDIChildWindow::RegisterWindow(HINSTANCE hInst,
  HBRUSH hbrBackground,
  HCURSOR hCursor,
  HICON hIcon,
  LPCTSTR lpszMenuName,
  UINT uStyle)
{
  WNDCLASS wc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = GetClassSize();
  wc.hbrBackground = hbrBackground;
  wc.hCursor = hCursor;
  wc.hIcon = hIcon;
  wc.hInstance = hInst;
  wc.lpszMenuName = NULL;
  wc.style = uStyle;
  wc.lpfnWndProc = (WNDPROC)StaticMDIChildProc;
  wc.lpszClassName = GetClassName();
  return ::RegisterClass(&wc);
}

BOOL GWCMDIChildWindow::Create(LPCTSTR lpWindowName, 
  HMENU hMenu, 
  int nWindowMenuPos,
  HINSTANCE hInst)
{
  GWC_ASSERT( m_pFrameWnd != NULL );
  GWC_ASSERT( hMenu != NULL );
  if ( NULL == m_pFrameWnd || NULL == hMenu)
  {
    return FALSE;
  }
  SetMDIMenu(hMenu); // to initialize window menu
  SetWindowMenuPos(nWindowMenuPos);

  MDICREATESTRUCT mcs;
  mcs.szClass = GetClassName();
  mcs.hOwner = hInst;
  mcs.szTitle = lpWindowName;
  mcs.x = CW_USEDEFAULT;
  mcs.y = CW_USEDEFAULT;
  mcs.cx = CW_USEDEFAULT;
  mcs.cy = CW_USEDEFAULT;
  mcs.style = MDIS_ALLCHILDSTYLES;
  mcs.lParam = (LPARAM)this;
  HWND hWnd = (HWND)::SendMessage(m_pFrameWnd->m_hWndClient, 
    WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mcs);

  return (hWnd != NULL);
}

GWCMDIFrameWindow *GWCMDIChildWindow::GetFrame()
{
  return m_pFrameWnd;
}

LRESULT GWCMDIChildWindow::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_MDIACTIVATE:
    {
      GWCWindow *pActivatedWnd = (GWCWindow*)::GetWindowLongPtr((HWND)lParam, GWL_USERDATA);
      if ( pActivatedWnd == this )
      {
        ::SendMessage(m_pFrameWnd->m_hWndClient,
          WM_MDISETMENU, 
          (WPARAM)GetMDIMenu(), 
          (LPARAM)GetWindowMenu());
      }
      OnMDIActivate(pActivatedWnd);
      if ( pActivatedWnd != this )
      {
        ::SendMessage(m_pFrameWnd->m_hWndClient,
          WM_MDISETMENU, 
          (WPARAM)m_pFrameWnd->GetMDIMenu(), 
          (LPARAM)m_pFrameWnd->GetWindowMenu());
      }
      ::DrawMenuBar(m_pFrameWnd->m_hWnd);
    }
    return 0;
  }
  return GWCMDIWindow::WindowProc(message, wParam, lParam);
}

void GWCMDIChildWindow::OnMDIActivate(GWCWindow *pActivatedWnd)
{
}
