//----------------------------------------------------------------------------------
// Class CBaseRendering
// Author: Miguel Rojas
//
// Description:
// 
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef BASERENDERING_H_
#define BASERENDERING_H_

#include <string>
#include "BaseGame.h"

//Class
class CRenderManager;

class CBaseRendering:public CBaseGame
{
public:
  // Init and End protocols
  CBaseRendering () : m_bIsOk(false) { }
  virtual ~CBaseRendering () { Done(); }

	virtual	void				Init								();
	virtual bool        PostInit            (const std::string &file);
  virtual void				Done               	();
  bool								IsOk               	() const { return m_bIsOk; }

  // -----------------------
  // Read functions
  // -----------------------

  // -----------------------
  // Write functions
  // -----------------------
	virtual void							Render					      					(CRenderManager * rm);
	virtual void							RenderScene											(CRenderManager * rm);
  virtual void							RenderDebugInfo									();
  virtual void              PreRender                       (CRenderManager* rm);
  void                      SetDebugRender                  (bool _m)                           { m_bDebugRender = _m; }
  bool                      GetDebugRender                  ()                                  { return m_bDebugRender; }
  
protected:

  void        				Release   					();
  // member variables
  bool                m_bIsOk;          // Initialization boolean control

	virtual void							Render2D												(CRenderManager* rm);
	virtual void							Render3D												(CRenderManager* rm);
  
  
private:
  bool                      m_bDebugRender;


	// Types 
	//uncomment to derived classes
  typedef CBaseGame Inherited;
};

 
#endif