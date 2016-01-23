/*
 * Filename: gwc.h
 * Author: Seree Rakwong
 * e-mail: meo.rakwong@gmail.com
 * Date: 12-JAN-16
 * Description: All macros are cloned from "WindowsX.h"
 */
#ifndef _GENERIC_WINDOWS_CLASSES_H_
#define _GENERIC_WINDOWS_CLASSES_H_

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#ifndef GWC_EXPORTS
#define GWCAPI __declspec(dllimport)
#else
#define GWCAPI __declspec(dllexport)
#endif

#define GWC_MINOR_VERSION (0X01)
#define GWC_MAJOR_VERSION (0X00)
#define GWC_VERSION       ((GWC_MAJOR_VERSION<<16) | (GWC_MINOR_VERSION))

#ifdef __cplusplus
extern "C" {
#endif

BOOL GWCAPI GWC_Init();
void GWCAPI GWC_Release();
UINT GWCAPI GWC_GetVersion();
void GWCAPI GWC_About();

#ifdef __cplusplus
}
#endif

#endif // _GENERIC_WINDOWS_CLASSES_H_
