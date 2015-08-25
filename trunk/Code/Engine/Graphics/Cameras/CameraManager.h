/*----------------------------------------------------------------------------------*\
 * CGameProcess class                                                               *
 * Author: Marco Torres                                                             *
 * Last Modification: Andrea Cristobo                                               *
 * Description:                                                                     *
 * Clase CameraManager.                                                             *
 * Gestiona todas las cámaras de la escena																				  *
\*----------------------------------------------------------------------------------*/
#pragma once
#ifndef CAMERA_MANAGER_H_
#define CAMERA_MANAGER_H_

//-----------FORWARD DECLARATION-----------
class CCamera;
class CThPSCamera;
class CFPSCamera;
class CObject3D;
class CFrustum;
class CCameraKeyController;
//-----------------------------------------

#include "Base.h"
#include "MapManager/MapManager.h"
#include <vector>
#include "Math/Vector3.h"
#include <string>

class CCameraManager : CMapManager<CCamera>
{
public:
  //Construct
	CCameraManager();
  //Destruct
	virtual ~CCameraManager();

  //functions
	bool      Init						      ();
	bool      Load									(const std::string &FileName);
	bool      Reload								();
	void      CleanUp								();
	void      AddCamera					    (const std::string &Name, CCamera * camera); //agregar un Object3D en lugar de camara
  void      AddCameraKeyController (const std::string &FileName, CCamera* _pCamera, bool _bCycle, bool _bReverse);
	void      ResetToDefaultCamera  ();
  void      DrawCameras           ();
  // -----------------------
  // Read functions
  // -----------------------
  CCamera *	GetCamera					    (){return m_DefaultCamera;}
	CCamera *	GetCameraByName       (const std::string CameraName);
  float     GetYawFactorCamera    ()                                  {return m_fYawFactorDefaultCamera;}
  float     GetPitchFactorCamera  ()                                  {return m_fPitchFactorDefaultCamera;}
  float     GetPitchUpperLimit    ()                                  {return m_fPitchUpperLimitDefaultCamera;}
  float     GetPitchLowerLimit    ()                                  {return m_fPitchLowerLimitDefaultCamera;}

  // -----------------------
  // Write functions
  // -----------------------
	void      SetCamera             (CCamera* camera);
  void      SetYawFactorCamera    (float y)                           {m_fYawFactorDefaultCamera = y;}
  void      SetPitchFactorCamera  (float p)                           {m_fPitchFactorDefaultCamera = p;}
  void      SetPitchUpperLimit    (float ul)                          {m_fPitchUpperLimitDefaultCamera = ul;}
  void      SetPitchLowerLimit    (float ll)                          {m_fPitchLowerLimitDefaultCamera = ll;}
  
  /*FRUSTUM*/
  void      UpdateFrustumCamera   ();
  CFrustum* GetFrustum            () const                            { return m_Frustum; }
	
	//TODO función para cambiar de cámaras (asigne una cámara del mapa a la ppal)
  
private:
  //Almacenamiento de camaras
	typedef std::map<std::string, CCamera*>				TDefaultCameraMap;
	TDefaultCameraMap															m_CamerasMap;
	
	//archivo de lectura
  std::string                                   m_FileName;
  
  //Camara por defecto
	CCamera*																			m_DefaultCamera;
  CFrustum*                                     m_Frustum;

  //factores de movimiento de la camara por defecto 
  float                                         m_fYawFactorDefaultCamera;
  float                                         m_fPitchFactorDefaultCamera;
  float                                         m_fPitchUpperLimitDefaultCamera;
  float                                         m_fPitchLowerLimitDefaultCamera;
};

#endif