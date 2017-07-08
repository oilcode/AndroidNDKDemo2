//-----------------------------------------------------------------------------
//È¥³ý±àÒëwarning
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif //_CRT_SECURE_NO_WARNINGS
//-----------------------------------------------------------------------------
#include "GGUIErrorHandler.h"
#include "GGUIBaseInclude.h"
//-----------------------------------------------------------------------------
#define GGUIErrorHandler_PrintBuffSize 2048
char GGUIErrorHandler_PrintBuff[GGUIErrorHandler_PrintBuffSize];
//-----------------------------------------------------------------------------
void GGUIErrorHandler::Print(const char* szFormat, ...)
{
	va_list klist;
	va_start(klist, szFormat);
	vsnprintf(GGUIErrorHandler_PrintBuff, GGUIErrorHandler_PrintBuffSize, szFormat, klist);
	va_end(klist);
	//
	SoIDEOutputLogInfo("%s", GGUIErrorHandler_PrintBuff);
	SoMessageBox("GGUI Error", GGUIErrorHandler_PrintBuff);
}
//-----------------------------------------------------------------------------
