//--------------------------------------------------------------------------------------------------
#ifndef _NwUIEffect_h_
#define _NwUIEffect_h_
//--------------------------------------------------------------------------------------------------
#include "NwBaseInclude.h"
//--------------------------------------------------------------------------------------------------
#define UIEffect_MaxDamageNumber 8
#define UIEffect_EventID_DamageNumberFirst 100
//--------------------------------------------------------------------------------------------------
struct stDamageNumberParam
{
	int nNumber;
	float fStartPosX;
	float fStartPosY;
	float fTime;
};
//--------------------------------------------------------------------------------------------------
class NwUIEffect : public GGUIWindowPanel
{
public:
    static bool CreateUIEffect();
    static void ReleaseUIEffect();
    static NwUIEffect* Get();

    void PlayDamageNumber(const stDamageNumberParam& kParam);

private:
    NwUIEffect();
    ~NwUIEffect();
    bool InitUIEffect();
    void ClearUIEffect();
    void CreateWindow_DamageNumber();
    GGUIWindowText* GetUnusedDamageNumber(int* pIndex);
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    //re-write parent functions
    void UpdateWindow(float fDeltaTime);
    bool InputWindow(GGUIInputMsg* pInputMsg);
    void ProcessUIEvent(int nEventType, void* pParam);
    void ProcessActionEvent(int nEventId);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

private:
	static NwUIEffect* ms_pInstance;
	GGUIWindowText* m_pDamageNumberList[UIEffect_MaxDamageNumber];
};
//--------------------------------------------------------------------------------------------------
inline NwUIEffect* NwUIEffect::Get()
{
	return ms_pInstance;
}
//--------------------------------------------------------------------------------------------------
#endif //_NwUIEffect_h_
//--------------------------------------------------------------------------------------------------
