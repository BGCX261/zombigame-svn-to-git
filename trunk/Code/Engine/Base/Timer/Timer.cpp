#include <Windows.h>
#include <assert.h>
#include "Timer.h"

//Inicializamos todas las variables
CTimer::CTimer (uint32 avgSamples)
: m_uSamples(avgSamples)
, m_fElpasedTime(0.f)
, m_dLastTime(0)
, m_fFPS(0.f)
, m_fFPSTime(0.f)
, m_uFPSCount(0)
, m_fLastFps(0.f)
, m_uIndex(0)
, m_dTotalTime(0)
{
	m_Deltas = new float[m_uSamples];
	for(uint32 j=0;j<m_uSamples;j++)
	{
		m_Deltas[j] = 0;
	}
}

CTimer::~CTimer( void )
{
  CHECKED_DELETE_ARRAY(m_Deltas);
	//delete[] m_Deltas;
}


// Actualiza los valores FPS, ElapsedTime y los timers (los normales y los inputs)
void CTimer::Update( void )
{

	//-----Actualizacion de los valores FPS y ElpasedTime-----
	//Calculo de la diferencia de tiempo (m_fElpasedTime)
	
	//obtiene tiempo actual
	double	l_dCurTime = timeGetTime();

  
  //entra por primera vez
	if( m_dLastTime == 0 )
		m_dLastTime = l_dCurTime;

  
  //para el indice actual se le da la diferencia en milesimas 
	m_Deltas[m_uIndex] = (float)((l_dCurTime - m_dLastTime) * 0.001);
	m_dLastTime    = l_dCurTime;


  //hace la mediana de las deltas de tiempo para evitar picos de tiempo
	float d = 0;
	for(unsigned int j=0; j<m_uSamples; j++)
	{
		d += m_Deltas[j];
	}
	d /= (float)m_uSamples;
	m_fElpasedTime = d;
	m_uIndex = (++m_uIndex) % m_uSamples;


	//Calculo de los frames por segundo (m_fFPS)
	m_uFPSCount++;
	m_fFPSTime += m_fElpasedTime;
	m_fFPS = m_uFPSCount/m_fFPSTime;

	if( l_dCurTime - m_fLastFps > 1000 )	//Solo mostramos los fps cada segundo
	{
		m_fFPS = m_uFPSCount/m_fFPSTime;
		m_uFPSCount = 0;
		m_fFPSTime = 0;
		m_fLastFps = (float)l_dCurTime;
	}

  //calcula el tiempo total desde que se ejecuta la aplicacion
  m_dTotalTime += m_fElpasedTime;
	//---------------------------------------------//
}

///<summary>
/// Reestablece el timer a los valores por defecto (0)
///</summary>
void CTimer::ResetTimer()
{
  m_fElpasedTime = 0.f;
  m_dLastTime = 0;
  m_fFPS = 0.f;
  m_fFPSTime = 0.f;
  m_uFPSCount = 0;
  m_fLastFps = 0.f;
  m_uIndex = 0;
  m_dTotalTime = 0;
  //float l_fLast = m_uIndex == 0 ? m_Deltas[m_uIndex-1] : m_Deltas[m_uSamples-1];
  for(uint32 j=0;j<m_uSamples;j++)
	{
		m_Deltas[j] = 0;
	}
}
