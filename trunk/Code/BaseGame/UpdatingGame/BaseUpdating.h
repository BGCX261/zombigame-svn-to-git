//----------------------------------------------------------------------------------
// Class CBaseUpdating
// Author: Miguel
//
// Description:
// 
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef BASEUPDATING_H_
#define BASEUPDATING_H_

// Includes
#include "BaseGame.h"
#include <string>
//Class
class CBaseUpdating:public CBaseGame
{
public:
  // Init and End protocols
  CBaseUpdating() : m_bIsOk(false){}
  virtual ~CBaseUpdating() { Done(); }

	virtual	void				Init								();
	virtual bool        PostInit            (const std::string &file);
  virtual void				Done               	();
  bool								IsOk               	() const { return m_bIsOk; }
  virtual void        Update              (float);
  // -----------------------
  // Read functions
  // -----------------------

  // -----------------------
  // Write functions
  // -----------------------

private:
  void        				Release   					();

  // member variables
  bool                m_bIsOk;          // Initialization boolean control

	// Types 
	//uncomment to derived classes
  typedef CBaseGame Inherited;
};


#endif