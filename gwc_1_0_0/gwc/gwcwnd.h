/*
 * Filename: gwcwnd.h
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 12-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#ifndef _GWC_WINDOWS_H_
#define _GWC_WINDOWS_H_

#include "gwc.h"

namespace gwc
{
namespace win32
{
  // window base class
class GWCAPI GWCWindow
{
  GWCWindow(const GWCWindow&);
  GWCWindow& operator=(const GWCWindow&);
public:
  HWND m_hWnd;

public:
  virtual LPCTSTR GetClassName();

public:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  virtual BOOL TranslateAccelerator(LPMSG lpmsg);

protected:
  virtual BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);
  virtual void OnDestroy();
  virtual BOOL OnInitDialog();
  virtual void OnCommand(int nID, GWCWindow *pCtrl, UINT nCode);
  virtual void OnPaint(HDC hdc);

public:
  GWCWindow();
  BOOL ShowWindow(int nCmdShow);
  BOOL UpdateWindow();
  BOOL AnimateWindow(DWORD dwTime, DWORD dwFlags);
  BOOL SetWindowText(LPCTSTR lpszWindowText);
  LRESULT SendMessage(UINT message, WPARAM wParam = 0L, LPARAM lParam = 0L);
  BOOL PostMessage(UINT message, WPARAM wParam = 0L, LPARAM lParam = 0L);
}; // GWCWindow

  // frame window
class GWCAPI GWCFrameWindow : public GWCWindow
{
  GWCFrameWindow(const GWCFrameWindow&);
  GWCFrameWindow& operator=(const GWCFrameWindow&);
protected:
  static LRESULT CALLBACK StaticWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
  GWCFrameWindow();
  BOOL RegisterWindow(LPWNDCLASS lpWndCls);
  BOOL RegisterWindow(HINSTANCE hInst,
  HBRUSH hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
    HCURSOR hCursor = ::LoadCursor(NULL, IDC_ARROW),
    HICON hIcon = ::LoadIcon(NULL, IDI_APPLICATION),
    LPCTSTR lpszMenuName = NULL,
    UINT uStyle = (CS_HREDRAW | CS_VREDRAW));

public:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  BOOL Create(LPCTSTR lpWindowName, 
    DWORD dwStyle, 
    int x = CW_USEDEFAULT, 
    int y = CW_USEDEFAULT, 
    int w = CW_USEDEFAULT, 
    int h = CW_USEDEFAULT, 
    GWCWindow *pParentWnd = NULL, 
    HMENU hMenu = NULL,
    HINSTANCE hInst = NULL);
  BOOL CreateEx(DWORD dwExStyle,
    LPCTSTR lpWindowName,
    DWORD dwStyle,
    int x = CW_USEDEFAULT, 
    int y = CW_USEDEFAULT, 
    int w = CW_USEDEFAULT, 
    int h = CW_USEDEFAULT, 
    GWCWindow *pParentWnd = NULL, 
    HMENU hMenu = NULL,
    HINSTANCE hInst = NULL);
}; // GWCFrameWindow

  // mdi windows
class GWCAPI GWCMDIWindow : public GWCFrameWindow
{
  GWCMDIWindow(const GWCMDIWindow&);
  GWCMDIWindow& operator=(const GWCMDIWindow&);

  HMENU m_hMenu;
  int   m_nWindowMenuPos;
public:
  GWCMDIWindow();
  HMENU GetMDIMenu();
  void  SetMDIMenu(HMENU hMenu);
  HMENU GetWindowMenu();
  void  SetWindowMenuPos(int nPos);

  BOOL RegisterWindow(LPWNDCLASS lpWndCls);
  BOOL RegisterWindow(HINSTANCE hInst,
  HBRUSH hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
    HCURSOR hCursor = ::LoadCursor(NULL, IDC_ARROW),
    HICON hIcon = ::LoadIcon(NULL, IDI_APPLICATION),
    LPCTSTR lpszMenuName = NULL,
    UINT uStyle = (CS_HREDRAW | CS_VREDRAW));
}; // GWCMDIWindow

class GWCMDIChildWindow;
class GWCAPI GWCMDIFrameWindow : public GWCMDIWindow
{
  GWCMDIFrameWindow(const GWCMDIFrameWindow&);
  GWCMDIFrameWindow& operator=(GWCMDIFrameWindow&);
public:
  GWCMDIFrameWindow();
  virtual ~GWCMDIFrameWindow();
  virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  virtual BOOL TranslateAccelerator(LPMSG lpmsg);
  // mdi messages
  void MDICascade();
  void MDITile();
  void MDIIconArrange();

protected:
  virtual BOOL OnCreate(LPCREATESTRUCT lpcs);
  virtual BOOL OnCreateClient(LPCLIENTCREATESTRUCT lpccs);
  virtual void OnCommand(int nID, GWCWindow *pCtrl, UINT nCode);
  virtual void OnMDICascade();
  virtual void OnMDITile();
  virtual void OnMDIIconArrange();

public:
  HWND m_hWndClient;
}; // GWCMDIFrameWindow

class GWCAPI GWCMDIChildWindow : public GWCMDIWindow
{
  GWCMDIChildWindow(const GWCMDIChildWindow&);
  GWCMDIChildWindow& operator=(GWCMDIChildWindow&);

  BOOL Create(LPCTSTR lpWindowName, 
    DWORD dwStyle, 
    int x, 
    int y, 
    int w, 
    int h, 
    GWCWindow *pParentWnd, 
    HMENU hMenu,
    HINSTANCE hInst);
  BOOL CreateEx(DWORD dwExStyle,
    LPCTSTR lpWindowName,
    DWORD dwStyle,
    int x, 
    int y, 
    int w, 
    int h, 
    GWCWindow *pParentWnd, 
    HMENU hMenu,
    HINSTANCE hInst);

  GWCMDIFrameWindow *m_pFrameWnd;
public:
  GWCMDIChildWindow();
  GWCMDIChildWindow(GWCMDIFrameWindow *pFrameWnd);
  BOOL RegisterWindow(LPWNDCLASS lpWndCls);
  BOOL RegisterWindow(HINSTANCE hInst,
  HBRUSH hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
    HCURSOR hCursor = ::LoadCursor(NULL, IDC_ARROW),
    HICON hIcon = ::LoadIcon(NULL, IDI_APPLICATION),
    LPCTSTR lpszMenuName = NULL,
    UINT uStyle = (CS_HREDRAW | CS_VREDRAW));
  BOOL Create(LPCTSTR lpWindowName, HMENU hMenu, int nWindowMenuPos, 
    HINSTANCE hInst = NULL);

protected:
  virtual int GetClassSize();
  static LRESULT CALLBACK StaticMDIChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
  virtual void OnMDIActivate(GWCWindow *pActivatedWnd);

public:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  GWCMDIFrameWindow *GetFrame();
}; //GWCMDIChildWindow

} // namespace Windows
} // namespace GW

#endif // _GWC_WINDOWS_H_
