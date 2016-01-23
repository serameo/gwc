/*
 * Filename: gwcapp.cpp
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 17-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#include "gwcapp.h"
#include "gwcerr.h"

using namespace gwc::win32;
using namespace std;


///////////////////////////////////////////////////////////////////////////////
// GWCApplication
GWCApplication::GWCApplication(HINSTANCE hInst, LPSTR lpszCmdLine, int nCmdShow)
  : m_pMainWnd(NULL)
  , m_hInst(hInst)
  , m_pszCmdLine(lpszCmdLine)
  , m_nCmdShow(nCmdShow)
{
  m_pDialogs = new std::vector<GWCWindow*>();
}

GWCApplication::~GWCApplication()
{
  delete m_pDialogs;
}

BOOL GWCApplication::InitInstance()
{
  return TRUE;
}

void GWCApplication::ExitInstance(int nCode)
{
}

int GWCApplication::Run()
{
  int nError = GWC_APP_ERR_NONE;
  if (!InitInstance())
  {
    nError = GWC_APP_ERR_INIT;
    ExitInstance(nError);
    return nError;
  }

  if ( m_pMainWnd )
  {
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
      if ( !AreDialogMessages(&msg) &&
           !m_pMainWnd->TranslateAccelerator(&msg) )
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
  }
  ExitInstance(nError);
  return nError;
}

int GWCApplication::RegisterModelessDialog(GWCWindow *pModelessDlg)
{
  std::vector<GWCWindow*>::iterator it = find(m_pDialogs->begin(), m_pDialogs->end(), pModelessDlg);
  if (it != m_pDialogs->end())
  {
    // already registered
    return 1;
  }
  m_pDialogs->push_back(pModelessDlg);
  return 0; // succeeded
}


BOOL GWCApplication::AreDialogMessages(LPMSG lpMsg)
{
  std::vector<GWCWindow*>::iterator it = m_pDialogs->begin();
  for (; it != m_pDialogs->end(); ++it)
  {
    if (::IsDialogMessage((*it)->m_hWnd, lpMsg))
    {
      return TRUE;
    }
  }
  return FALSE;
}
