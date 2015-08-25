//----------------------------------------------------------------------------------
// Class LogicGame
// Author: Miquel Rojas
//
// Description:
// Mantiene la maquina de estados del juego (inicio, desarrollo, fin partida, etc...)
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef LOGICGAME_H_
#define LOGICGAME_H_

// Includes
#include "Base.h"

// estados del juego
#define GS_NO_STATE             0
#define GS_CAMERA_CINEMATIC     1
#define GS_LEVEL_UPDATE         2
#define GS_PREPARE_CHANGE_LEVEL 3
#define GS_CHANGE_LEVEL         4
#define GS_GAME_OVER_TRANSITION 5
#define GS_GAME_OVER            6
#define GS_LEVEL_SELECTED       7

#define G_GAME_OVER             0

class CCoreFIH;

//Class
class CLogicGame
{
public:
  // Init and End protocols
  CLogicGame() : m_bIsOk(false), m_bRenderDebugInfo(false),m_pCoregame(0), m_ucGameState(0), m_DeltaFromXML(0.0f){}
  virtual ~CLogicGame() { Done(); }

	virtual	bool				Init								();
  virtual void				Done               	();
  bool								IsOk               	() const { return m_bIsOk; }


  void                LoadLuaScripts      ();
  void                Register2LUA        ();

  // -----------------------
  // Read functions
  // -----------------------
  CCoreFIH*				    GetCoreGame         () {return m_pCoregame;}
  bool                GetRenderInfo       () {return m_bRenderDebugInfo;}
  
  // -----------------------
  // State functions
  // -----------------------
	void    						CheckActionsFromInputs					(float elapsedTime);
  
  void                GameOver            ();
  void                ReStart             ();

private:
  void        				Release   					();

  // member variables
  bool                m_bIsOk;          // Initialization boolean control
  CCoreFIH*				    m_pCoregame;
  uint8               m_ucGameState;
	
	float               m_DeltaFromXML;
  bool                m_bRenderDebugInfo;
	// Types 
	//uncomment to derived classes
  //typedef CProcess Inherited;
};


#endif