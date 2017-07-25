//----------------------------------------------------------------
#ifndef _GGUIImagesetBase_h_
#define _GGUIImagesetBase_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
class GGUIImagesetBase
{
public:
	GGUIImagesetBase();
	virtual ~GGUIImagesetBase();
	GGUIImagesetType GetImagesetType() const;
	
protected:
	GGUIImagesetType m_eImagesetType;
};
//----------------------------------------------------------------
#endif //_GGUIImagesetBase_h_
//----------------------------------------------------------------
