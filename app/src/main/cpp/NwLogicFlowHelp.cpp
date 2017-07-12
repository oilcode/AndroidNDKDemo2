//----------------------------------------------------------------
#include "NwLogicFlowHelp.h"
#include "GGUIImagesetIO.h"
#include "NwUIMain.h"
//----------------------------------------------------------------
bool NwLogicFlowHelp_Create()
{
    GGUIImagesetIO::Read("uitexture/mm1.txt");
	GGUIImagesetIO::Read("uitexture/mm2.txt");
    GGUIImagesetIO::Read("uitexture/mm3.txt");

	if (NwUIMain::CreateUIMain() == false)
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------
void NwLogicFlowHelp_Release()
{
	NwUIMain::ReleaseUIMain();
}
//----------------------------------------------------------------
void NwLogicFlowHelp_Update(float fDeltaTime)
{
	if (NwUIMain::Get())
	{
		NwUIMain::Get()->UpdateUIMain(fDeltaTime);
	}
}
//----------------------------------------------------------------
