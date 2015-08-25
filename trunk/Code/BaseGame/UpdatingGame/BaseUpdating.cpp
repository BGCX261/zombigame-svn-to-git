#include "BaseUpdating.h"


#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )


//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
void CBaseUpdating::Init()
{
  if (!m_bIsOk)
  {
    Done();								//We call Done()  to release before the parent class
  }
}


bool CBaseUpdating::PostInit(const std::string &file)
{
  return true;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void CBaseUpdating::Done()
{
//	Inherited::Done();			//Parent class Done
  if (IsOk())
  {
    Release();
  }
}

//----------------------------------------------------------------------------
// Free memory
//----------------------------------------------------------------------------
void CBaseUpdating::Release()
{
//free memory
}


void CBaseUpdating::Update(float _dt)
{

}
 
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------