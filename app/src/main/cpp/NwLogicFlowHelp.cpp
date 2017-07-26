//----------------------------------------------------------------
#include "NwLogicFlowHelp.h"
#include "GGUIImagesetIO.h"
#include "NwUIMain.h"
#include "NwUISPK.h"
//----------------------------------------------------------------
bool NwLogicFlowHelp_Create()
{
    GGUIImagesetIO::Read("uitexture/mm1.txt", GGUIImagesetType_Normal);
	GGUIImagesetIO::Read("uitexture/mm2.txt", GGUIImagesetType_Normal);
    GGUIImagesetIO::Read("uitexture/mm3.txt", GGUIImagesetType_Normal);
	GGUIImagesetIO::Read("uitexture/mm4.txt", GGUIImagesetType_Normal);
	GGUIImagesetIO::Read("uitexture/mm5.txt", GGUIImagesetType_Normal);
	GGUIImagesetIO::Read("uitexture/mm6.txt", GGUIImagesetType_Font);

	if (NwUIMain::CreateUIMain() == false)
	{
		return false;
	}

	if (NwUISPK::CreateUISPK() == false)
	{
		return false;
	}

	return true;
}
//----------------------------------------------------------------
void NwLogicFlowHelp_Release()
{
	NwUIMain::ReleaseUIMain();
	NwUISPK::ReleaseUISPK();
}
//----------------------------------------------------------------
void NwLogicFlowHelp_Update(float fDeltaTime)
{
	if (NwUIMain::Get())
	{
		NwUIMain::Get()->UpdateUIMain(fDeltaTime);
	}
	if (NwUISPK::Get())
	{
		NwUISPK::Get()->UpdateUISPK(fDeltaTime);
	}
}
//----------------------------------------------------------------
