/*
 * Filename: gwcapp.h
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 17-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#ifndef _GWC_APPLICATION_H_
#define _GWC_APPLICATION_H_

#include "gwcwnd.h"
#include "gwcstl.h"

namespace gwc
{
namespace win32
{
// application base class
class GWCAPI GWCApplication
{
  GWCApplication();
  GWCApplication(const GWCApplication&);

private:
  std::vector<GWCWindow*>   *m_pDialogs;

public:
  GWCWindow *m_pMainWnd;
  HINSTANCE  m_hInst;
  LPSTR      m_pszCmdLine;
  int        m_nCmdShow;

public:
  GWCApplication(HINSTANCE hInst, LPSTR lpszCmdLine, int nCmdShow);
  virtual ~GWCApplication();
  virtual int Run();
  int RegisterModelessDialog(GWCWindow *pModelessDlg);

protected:
  virtual BOOL InitInstance();
  virtual void ExitInstance(int nCode);

  BOOL AreDialogMessages(LPMSG lpMsg);
};

}// namespace Windows
}// namespace GWC

#endif // 
