/*
 * Filename: gwc.cpp
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 12-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#include "gwc.h"
#include "gwcrc.h"
#include "gwcdlg.h"

using namespace gwc::win32;

HINSTANCE g_hInstDll = NULL;
BOOL WINAPI DllMain(HINSTANCE hInstDll, DWORD dwReason, LPVOID lpReserved)
{
  g_hInstDll = hInstDll;
  switch (dwReason)
  {
  case DLL_PROCESS_ATTACH:
  case DLL_PROCESS_DETACH:
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
    break;
  }
  return  TRUE;
}


#ifdef __cplusplus
extern "C" {
#endif

BOOL GWCAPI GWC_Init()
{
  return TRUE;
}

void GWCAPI GWC_Release()
{
}

UINT GWCAPI GWC_GetVersion()
{
  return GWC_VERSION;
}

class GWCAboutDlg : public GWCDialog
{
public:
  GWCAboutDlg()
    : GWCDialog(NULL, IDD_GWC_ABOUT)
  {
  }
};
void GWCAPI GWC_About()
{
  GWCAboutDlg dlg;
  dlg.Show(g_hInstDll);
}


#ifdef __cplusplus
}
#endif
