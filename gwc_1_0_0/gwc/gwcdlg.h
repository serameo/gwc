/*
 * Filename: gwcdlg.h
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 16-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 * resource: https://msdn.microsoft.com/en-us/library/windows/desktop/aa381002(v=vs.85).aspx
 * ref: https://msdn.microsoft.com/en-us/library/windows/desktop/aa381003(v=vs.85).aspx
 */
#ifndef _GWC_DIALOGS_H_
#define _GWC_DIALOGS_H_

#include "gwcwnd.h"

namespace gwc
{
namespace win32
{
  // window base class
class GWCAPI GWCDialog : public GWCWindow
{
  LPCTSTR m_pszTemplate;
  GWCWindow *m_pParentWnd;

  GWCDialog();
  GWCDialog(const GWCDialog&);
  GWCDialog& operator=(const GWCDialog&);
public:
  GWCDialog(GWCWindow *pParentWnd, LPCTSTR lpszTemplate);
  GWCDialog(GWCWindow *pParentWnd, UINT nIDTemplate);

  virtual UINT Show(HINSTANCE hInst = NULL, BOOL bIsModalDialog = TRUE);

protected:
  static BOOL CALLBACK StaticDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

public:
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

  GWCWindow* GetDlgItem(int nID);
  UINT       GetDlgCtrlID(GWCWindow *pWnd);
  UINT       GetDlgItemInt(int nID, BOOL *pTranslated, BOOL bSigned);
  UINT       GetDlgItemText(int nID, LPTSTR lpString, int cchMax);

public:
  virtual void OnOK();
  virtual void OnCancel();
  virtual void OnDestroy();
  virtual BOOL OnInitDialog();
};

}//namespace Windows
}//namespace GWC

#endif //_GWC_DIALOGS_H_
