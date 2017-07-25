//----------------------------------------------------------------
#include "GGUIImagesetBase.h"
//----------------------------------------------------------------
GGUIImagesetBase::GGUIImagesetBase()
:m_eImagesetType(GGUIImagesetType_Normal)
{

}
//----------------------------------------------------------------
GGUIImagesetBase::~GGUIImagesetBase()
{
	
}
//----------------------------------------------------------------
GGUIImagesetType GGUIImagesetBase::GetImagesetType() const
{
	return m_eImagesetType;
}
//----------------------------------------------------------------
