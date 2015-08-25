#include "BaseRendering.h"
#include "RenderManager.h"
#include "BaseGame.h"


#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )


//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
void CBaseRendering::Init()
{
  if (!m_bIsOk)
  {
    Done();								//We call Done()  to release before the parent class
  }
}

bool CBaseRendering::PostInit(const std::string &_file)
{
  return true;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void CBaseRendering::Done()
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
void CBaseRendering::Release()
{
//free memory
}

void	CBaseRendering::Render(CRenderManager * rm)
{
  RenderScene( rm );
}

void	CBaseRendering::RenderScene(CRenderManager * rm)
{

  Render3D( rm );
  Render2D( rm ); 
  RenderDebugInfo(); 
}

void	CBaseRendering::RenderDebugInfo()
{
  Inherited::RenderDebugInfo();
}

void  CBaseRendering::PreRender(CRenderManager* rm)
{


}

void	CBaseRendering::Render2D(CRenderManager* rm)
{

}

void	CBaseRendering::Render3D(CRenderManager* rm)
{

}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------