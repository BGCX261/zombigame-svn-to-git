//----------------------------------------------------------------------------------
// Class InitEndProtocol
// Author: Miquel Rojas
//
// Description:
// Protocolo de inicio y final para control de objetos
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef INIT_END_PROTOCOL_H_
#define INIT_END_PROTOCOL_H_

// Includes

//Class
class CInitEndProtocol
{
public:
  // Init and End protocols
  CInitEndProtocol() : m_bIsOk(false){}
  virtual ~CInitEndProtocol() { Done(); }

	virtual	bool				Init								();
  virtual void				Done               	();
  virtual bool				IsOk               	();

  // -----------------------
  // Read functions
  // -----------------------

  // -----------------------
  // Write functions
  // -----------------------

private:
  virtual void        Release   					();

  // member variables
  bool                m_bIsOk;          // Initialization boolean control

	// Types 
	//uncomment to derived classes
  //typedef CProcess Inherited;
};


#endif