//----------------------------------------------------------------
#include "NwLogicFlowHelp.h"
#include "GGUIImagesetIO.h"
#include "NwUIMain.h"
#include "NwUIEffect.h"
#include "NwSceneSPK.h"
//----------------------------------------------------------------
bool NwLogicFlowHelp_Create()
{
    GGUIImagesetIO::Read("uitexture/mm1.txt", GGUIImagesetType_Normal);
	GGUIImagesetIO::Read("uitexture/nwfont.ggm", GGUIImagesetType_Font);
	GGUIImagesetIO::Read("uitexture/mm7.txt", GGUIImagesetType_Normal);
	GGUIImagesetIO::Read("uitexture/mm8.txt", GGUIImagesetType_Normal);

	if (NwUIMain::CreateUIMain() == false)
	{
		return false;
	}

	if (NwUIEffect::CreateUIEffect() == false)
	{
		return false;
	}

	if (NwSceneSPK::CreateSceneSPK() == false)
	{
		return false;
	}

    NwSceneSPK::Get()->StartSPK();

	return true;
}
//----------------------------------------------------------------
void NwLogicFlowHelp_Release()
{
	NwUIEffect::ReleaseUIEffect();
	NwUIMain::ReleaseUIMain();
	NwSceneSPK::ReleaseSceneSPK();
}
//----------------------------------------------------------------
void NwLogicFlowHelp_Update(float fDeltaTime)
{
	if (NwUIMain::Get())
	{
		NwUIMain::Get()->UpdateUIMain(fDeltaTime);
	}
	if (NwSceneSPK::Get())
	{
        NwSceneSPK::Get()->UpdateSceneSPK(fDeltaTime);
	}
}
//----------------------------------------------------------------
