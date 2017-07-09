//----------------------------------------------------------------
#ifndef _GGUIPanelManager_h_
#define _GGUIPanelManager_h_
//----------------------------------------------------------------
#include "GGUIWindowPanel.h"
//----------------------------------------------------------------
class GGUIPanelManager
{
public:
	static bool CreateUIPanelManager();
	static void ReleaseUIPanelManager();
	static GGUIPanelManager* Get();

	void UpdateUIPanelManager(float fDeltaTime);
	void RenderUIPanelManager();
	void InputUIPanelManager(GGUIInputMsg* kInputMsg);
	//游戏分辨率发生了变化，调整所有Panel的坐标和宽高。
	void ResolutionChanged(float newWidth, float newHeight);

	void AddUIPanel(GGUIWindowPanel* pPanel, int eSpaceType);
	void RemoveUIPanel(GGUIWindowPanel* pPanel, int eSpaceType);
	GGUIWindowPanel* GetUIPanel(int eSpaceType, int nIndex);
	//把Panel设置到最上层。
	//处于最上层的Panel，会绘制在最上层，优先处理input。
	void MakeTopUIPanel(GGUIWindowPanel* pPanel);

	void UISpace_SetVisible(int eSpaceType, bool bVisible);
	bool UISpace_GetVisible(int eSpaceType);
	int UISpace_GetPanelCount(int eSpaceType);

private:
	GGUIPanelManager();
	~GGUIPanelManager();
	bool InitUIPanelManager();
	void ClearUIPanelManager();

private:
	static GGUIPanelManager* ms_pInstance;
	//本类只维护GGUIWindowPanel对象的指针，由外界负责创建和删除GGUIWindowPanel对象。
	//Panel序号越大，越靠近屏幕，越绘制在上层，越优先处理input。
	SoArray m_kUISpaceArray[GGUIPanelSpace_Max];
	bool m_bUISpaceVisible[GGUIPanelSpace_Max];
};
//----------------------------------------------------------------
inline GGUIPanelManager* GGUIPanelManager::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_GGUIPanelManager_h_
//----------------------------------------------------------------
