//----------------------------------------------------------------------------------
// CTimer class
// Author: Enric Vergara
//
// Description:
// Contiene toda la informacion relacionada con el tiempo, es decir:
//	- FPS: los frames por segundo a que va la aplicacion
//	- ElapsedTime: el tiempor que ha pasado dsd la ultima llamad a Update
//----------------------------------------------------------------------------------
#pragma once 
#ifndef INC_TIMERMANAGER_H_
#define INC_TIMERMANAGER_H_

#include "Base.h"

class CTimer
{

public:

	CTimer(uint32 avgSamples);
	~CTimer();

	void			Update					();
	float			GetElapsedTime	() const { return m_fElpasedTime; }
	float			GetFPS					() const { return m_fFPS; }
  double    GetTotalTime    () const {  return m_dTotalTime;  }
  void      ResetTimer      ();

private:

	float			m_fElpasedTime; // ElapsedTime
	float			m_fFPS;					// FPS
	float			m_fLastFps;     // last FPS count
	float			m_fFPSTime;     
	double		m_dLastTime;    // last time crono
	uint32		m_uFPSCount;
	float*		m_Deltas;				// array of instant delta times
	uint32		m_uSamples;			// deltas arrays length
	uint32		m_uIndex;				// current array position
  double    m_dTotalTime;   // total time of execution
};

#endif //INC_TIMERMANAGER_H_