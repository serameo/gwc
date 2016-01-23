/*
 * Filename: gwcctl.h
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 19-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#ifndef _GWC_CONTROLS_H_
#define _GWC_CONTROLS_H_

#include "gwcwnd.h"

namespace gwc
{
namespace win32
{
  // control
class GWCAPI GWCControl : public GWCWindow
{
  GWCControl(const GWCControl&);
  GWCControl& operator=(const GWCControl&);
public:
  GWCControl();
  BOOL Create(LPCTSTR lpWindowName, 
    DWORD dwStyle, 
    int x, 
    int y, 
    int w, 
    int h,
    GWCWindow *pParentWnd, 
    UINT hMenu,
    HINSTANCE hInst = NULL);
  BOOL CreateEx(DWORD dwExStyle,
    LPCTSTR lpWindowName, 
    DWORD dwStyle, 
    int x, 
    int y, 
    int w, 
    int h,
    GWCWindow *pParentWnd, 
    UINT hMenu,
    HINSTANCE hInst = NULL);
  BOOL Subclass(GWCWindow *pWnd);
protected:
  WNDPROC m_pPrevWndProc;

protected:
  virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
  static LRESULT CALLBACK StaticControlProc(HWND hCtrl, UINT message, WPARAM wParam, LPARAM lParam);
};

  // button
class GWCAPI GWCButton : public GWCControl
{
  GWCButton(const GWCButton&);
  GWCButton& operator=(const GWCButton&);
public:
  virtual LPCTSTR GetClassName();

  // button messages mapping
  void Click()
  { SendMessage(BM_CLICK); }
  UINT GetCheck()
  { return (UINT)SendMessage(BM_GETCHECK); }
  HICON GetIcon()
  { return (HICON)SendMessage(BM_GETIMAGE, IMAGE_ICON); }
  HBITMAP GetBitmap()
  { return (HBITMAP)SendMessage(BM_GETIMAGE, IMAGE_BITMAP); }
  UINT GetState()
  { return (UINT)SendMessage(BM_GETSTATE); }
  void SetCheck(UINT fCheck)
  { SendMessage(BM_SETCHECK, (WPARAM)fCheck); }
  void SetDontClick(BOOL fDontClick = TRUE)
  { SendMessage(BM_SETDONTCLICK, (WPARAM)fDontClick); }
  HICON SetIcon(HICON hIcon)
  { return (HICON)SendMessage(BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon); }
  HBITMAP SetBitmap(HBITMAP hbmp)
  { return (HBITMAP)SendMessage(BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbmp); }
  void SetState(BOOL fState = TRUE)
  { SendMessage(BM_SETSTATE, (WPARAM)fState); }
  void SetStyle(DWORD dwStyle, BOOL fRedraw)
  { SendMessage(BM_SETSTYLE, (WPARAM)dwStyle, MAKELPARAM(fRedraw, 0)); }

  BOOL GetIdealSize(SIZE *pSize)
  { return (BOOL)SendMessage(BCM_GETIDEALSIZE, 0, (LPARAM)pSize); }
  BOOL GetImageList(BUTTON_IMAGELIST *pImg)
  { return (BOOL)SendMessage(BCM_GETIMAGELIST, 0, (LPARAM)pImg); }
  BOOL GetNote(LPTSTR pszNote, DWORD *pdwSize)
  { return (BOOL)SendMessage(BCM_GETNOTE, (WPARAM)pdwSize, (LPARAM)pszNote); }
  UINT GetNoteLength()
  { return (UINT)SendMessage(BCM_GETNOTELENGTH); }
  BOOL GetSplitInfo(BUTTON_SPLITINFO *pSplitInfo)
  { return (BOOL)SendMessage(BCM_GETSPLITINFO, 0, (LPARAM)pSplitInfo); }
  BOOL GetTextMargin(RECT *pRect)
  { return (BOOL)SendMessage(BCM_GETTEXTMARGIN, 0, (LPARAM)pRect); }
  BOOL SetDropDownState(BOOL fState = TRUE)
  { return (BOOL)SendMessage(BCM_SETDROPDOWNSTATE, (WPARAM)fState); }
  BOOL SetImageList(BUTTON_IMAGELIST *pImg)
  { return (BOOL)SendMessage(BCM_SETIMAGELIST, 0, (LPARAM)pImg); }
  BOOL SetNote(LPCTSTR pszNote)
  { return (BOOL)SendMessage(BCM_SETNOTE, 0, (LPARAM)pszNote); }
  BOOL SetShield(BOOL fShield)
  { return (BOOL)SendMessage(BCM_SETNOTE, 0, (LPARAM)fShield); }
  BOOL SetSplitInfo(BUTTON_SPLITINFO *pSplitInfo)
  { return (BOOL)SendMessage(BCM_SETSPLITINFO, 0, (LPARAM)pSplitInfo); }
  BOOL SetTextMargin(RECT *pRect)
  { return (BOOL)SendMessage(BCM_SETTEXTMARGIN, 0, (LPARAM)pRect); }

};

} // namespace Windows
} // namespace GW

#endif // _GWC_CONTROLS_H_
