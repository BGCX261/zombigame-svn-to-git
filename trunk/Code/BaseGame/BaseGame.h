/*----------------------------------------------------------------------------------*\
 * CBaseGame class                                                                  *
 * Author: Miquel Rojas                                                             *
 * Description:                                                                     *
 * Proceso Base Game                                                                *
 *    Clase que gestionará el juego a partir de las clase de updating, rendering,   *
 *    logic(estados del juego).                                                     *
 *    Esta derivada de proceso por lo que puede ser llamada desde el main principal *
 *                                                                                  *
 *    Se puede utilizar como plantilla de otros juegos                              *
 *    Contendra el CORE del motor para comunicarse con las clases que derivan de    *
 *    esta clase.                                                                   *
\*----------------------------------------------------------------------------------*/

#pragma once
#ifndef INC_BASEGAME_H_
#define INC_BASEGAME_H_

#include "Process.h"

//-----------FORWARD DECLARATION-----------
class CRenderManager;
//class CRenderableObject;
class CCoreFIH;
//class CCameraKeyController;

class CBaseRendering;
class CBaseUpdating;
class CGameLogic;

//-----------------------------------------
class CBaseGame: public CProcess
{
public:
  //Construct
	CBaseGame():m_pBaseRendering(0),m_pBaseUpdating(0),m_pBaseLogic(0),m_pCoregame(0){};
  //Destruct
	virtual ~CBaseGame(){ Done(); }

  //functions
	virtual void 			Init						      					();
	virtual bool      PostInit                        (const std::string &file);
	virtual void      Done();
  virtual bool			IsOk               	            () const { return m_bIsOk; }
	virtual void			Update					      					(float elapsedTime);
	virtual void			Render					      					(CRenderManager * rm);
  virtual void			RenderScene											(CRenderManager * rm);
  virtual void      RenderDebugInfo();
  
  //updatables
  CBaseUpdating*    GetBaseUpdating                 ()    {return m_pBaseUpdating;}

  //renderables
  CBaseRendering*   GetBaseRendering                ()    {return m_pBaseRendering;}

  //logicables
  CGameLogic*       GetLogicGame                    ()    {return m_pBaseLogic;}

protected:
	//functions
	void  						LoadCommonXMLs								  ();
  bool              LoadGameConfig                  ();

	//extras de IA
	CCoreFIH*         GetCoreGame                     ()    {return m_pCoregame;}
	//void              UpdateCamera                   ();
  //CCameraKeyController*                             m_pCameraKeyController;
  //bool                                              m_bDebugRender;
	//bool                                              m_bEndAnimation;

private:
  void        				Release   					();

  // member variables
  bool                m_bIsOk;          // Initialization boolean control

  CCoreFIH*																					m_pCoregame;
  CBaseRendering*                                   m_pBaseRendering;
  CBaseUpdating*                                    m_pBaseUpdating;
  CGameLogic*                                       m_pBaseLogic;
  
  typedef CProcess Inherited;
};

#endif

