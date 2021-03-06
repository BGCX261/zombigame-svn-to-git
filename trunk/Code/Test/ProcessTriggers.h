/*----------------------------------------------------------------------------------*\
 * CProcessTriggers class                                                               *
 * Author: Miquel Rojas                                                             *
 * Last Modification: Miquel Rojas                                                  *
 * Description:                                                                     *
 * Clase ProcessTriggers.                                                              *
\*----------------------------------------------------------------------------------*/
#pragma once
#ifndef INC_TRIGGERS_PROCESS_H_
#define INC_TRIGGERS_PROCESS_H_

#include "Process.h"
#include "InputManager.h"
#include "TexturedVertex.h"
#include "Math/MathUtils.h"
#include "StaticMeshes/StaticMeshManager.h"


//-----------FORWARD DECLARATION-----------
class CObject3D;
class CRenderManager;
class CActionToInput;
class CRenderableAnimatedInstanceModel;
class CRenderableObject;
//-----------------------------------------

class CProcessTriggers: public CProcess
{
public:
  //Construct
	CProcessTriggers();
  //Destruct
	virtual ~CProcessTriggers();

  //functions
  ///<summary>
/// CProcessTriggers:: Init : Lectura de los XML. Creaci�n y asignaci�n de las c�maras a los objetos.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
	void							Init						      					();


///<summary>
/// CProcessTriggers:: Update : Actualizaci�n de todos los procesos.
///</summary>
///<param name="elapsedTime">Tiempo transcurrido.</param>
///<returns name=""></returns>
	void							Update					      					(float elapsedTime);

///<summary>
/// CProcessTriggers:: PreRender : Prerenderizaci�n de efectos.
///</summary>
///<param name="rm">RenderManager.</param>
///<returns name=""></returns>
  void              PreRender                       (CRenderManager * rm);


///<summary>
/// CProcessTriggers:: Render : Renderiza todo.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
  void							Render					      					(CRenderManager * rm);


  ///<summary>
/// CProcessTriggers:: RenderScene : Renderiza la escena.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
  void							RenderScene											(CRenderManager * rm);

///<summary>
/// CProcessTriggers:: RenderDebugInfo() : muestra la informaci�n del pitch, yaw, position y n�mero de caras de los objetos est�ticos y din�micos.
///</summary>
///<param name=""></param>
///<returns name=""></returns>

  void							RenderDebugInfo									();

private:

	//functions

///<summary>
/// CProcessTriggers:: CheckActionsFromInputs : Seg�n una entrada de teclado ejecuta su acci�n asociada.
///</summary>
///<param name="elapsedTime">Tiempo transcurrido.</param>
///<returns name=""></returns>
  void  						CheckActionsFromInputs					(float elapsedTime);

  ///<summary>
/// CProcessTriggers:: LoadXMLs : Carga todos los XML.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
void  						LoadXMLs												();

///<summary>
/// CProcessTriggers:: InitCameras : Crea las c�maras y las asocia a un objeto.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
void  						InitCameras											();
  
///<summary>
/// CProcessTriggers:: GetPositionObj : Nos devuelve un Vect3f con la posici�n del objeto.
///</summary>
///<param name="p_vObj">Objeto del que vamos a obtener la posici�n.</param>
///<returns name="posicion">Vector de 3 floats con la posici�n del objeto.</returns>
  Vect3f						GetPositionObj									(CObject3D* p_vObj);

  
///<summary>
/// CProcessTriggers:: UpdateLua : Scripts de LUA.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
  void 							UpdateLua												();

  
///<summary>
/// CProcessTriggers:: MovPlayer : Calcula los movimientos y la velocidad del player.
///</summary>
///<param name="elapsedTime">Tiempo transcurrido.</param>
///<returns name=""></returns>
  void							MovPlayer                       (float elapsedTime);
  void              MovCamera                       ();
	void							MovPlayerIA                     (float elapsedTime);

///<summary>
/// CProcessTriggers:: MovMouse : Movimiento del rat�n asociado a la c�mara.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
  void							MovMouse												(); 

///<summary>
/// CProcessTriggers:: Render3D : Renderiza la parte de 2D.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
  void							Render2D												(CRenderManager* rm);

  
///<summary>
/// CProcessTriggers:: Render3D : Renderiza la parte de 3D.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
  void							Render3D												(CRenderManager* rm);
  void							RenderMovIA 										(CRenderManager* rm);
//  float             AjusteDireccion                 ();

///<summary>
/// CProcessTriggers:: MemoryTest : Pruebas para grabar en RAM o VRAM.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
  void							MemoryTest											();

	//variables
	//float																							m_fPosX, m_fPosY, m_TimerCounter, m_iDirection, m_fFPS;
	//float 																						m_fRotacion;
	//float																							m_MaxVision, m_MinVision;
	//bool																							m_bDrawCube;
  float                                             m_DeltaFromXML;
	//CObject3D*																				m_pObject3D;
	//CObject3D*  																			m_pObject3D_Pivotal;
  CActionToInput* m_pAction;
	CRenderableAnimatedInstanceModel * 								m_pPlayer1;
//	CRenderableAnimatedInstanceModel * 								m_pPlayer2;
  float m_fSpeed1;
 // float m_fSpeedZombie;
 // float m_fAngleParcialZombie;
 // float m_fAngleTotalZombie;
 // Vect3f m_V3DirPlayer2Optimo;
 // Vect3f m_V3DirectorPlayer2;
 // Vect3f m_V3RightPlayer2;
 // Vect3f m_V3UpPlayer2;
 // 
 // bool m_bChaser; //false=cazador player 1, true=cazador player 2
	float																							m_MovementSpeed, m_RunTime, m_RestTime;
//  CSceneEffectManager* m_SceneEffectManager;
};

#endif

