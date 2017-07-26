//----------------------------------------------------------------
#ifndef _GGUIImagesetBase_h_
#define _GGUIImagesetBase_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
class GGUIImagesetBase
{
public:
	GGUIImagesetType GetImagesetType() const;

protected:
	friend class GGUIImagesetManager;
	GGUIImagesetBase();
	virtual ~GGUIImagesetBase();

protected:
	GGUIImagesetType m_eImagesetType;
};
//----------------------------------------------------------------
#endif //_GGUIImagesetBase_h_
//----------------------------------------------------------------
