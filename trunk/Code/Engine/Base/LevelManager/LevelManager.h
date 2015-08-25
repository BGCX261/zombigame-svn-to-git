//----------------------------------------------------------------------------------
// Class LevelManager
// Author: Miquel Rojas
//
// Description:
// Level control
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef LEVELMANAGER_H_
#define LEVELMANAGER_H_

// Includes
#include "Base.h"

//Class
class CLevelManager
{
public:
  // Init and End protocols
  CLevelManager () : m_bIsOk(false){}
  virtual ~CLevelManager () { Done(); }

	virtual	bool				Init								();
  virtual void				Done               	();
  bool								IsOk               	() const { return m_bIsOk; }

  // -----------------------
  // Read functions
  // -----------------------
  void              ChangeLevel                     (uint8 _level);
	void  						LoadLevelXMLs										(uint8 _level);
  void              LoadLevel                       (uint8 _level);
  void              ReleaseLevel                    ();

  // -----------------------
  // Write functions
  // -----------------------

private:
  void        				Release   					();

  // member variables
  bool                m_bIsOk;          // Initialization boolean control
  uint8               m_ucCurrentLevel;
  uint8               m_ucChangeLevel;

	// Types 
	//uncomment to derived classes
  //typedef CProcess Inherited;
};


#endif