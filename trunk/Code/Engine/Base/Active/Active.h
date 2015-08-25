//----------------------------------------------------------------------------------
// CNamed Class
// Author: Miquel Rojas
//
// Description:
// Para ver si un objeto esta activo
// 
//----------------------------------------------------------------------------------
#pragma once

#ifndef INC_ACTIVE_H_
#define INC_ACTIVE_H_

class CActive
{
	public:
		CActive () : m_bIsOk(false), m_bIsActive(false){}
		virtual ~CActive() { Done(); }

		virtual	bool				Init								();
		virtual void				Done               	();
		bool								IsOk               	() const { return m_bIsOk; }

		bool								GetActive             ();
		void                SetActive             (bool state);
    
		void        				Release   					();

  private:
		bool                m_bIsOk;          
		bool                m_bIsActive;
};

#endif