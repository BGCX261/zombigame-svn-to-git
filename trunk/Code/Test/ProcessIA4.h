/*----------------------------------------------------------------------------------*\
 * CProcessIA4 class                                                               *
 * Author: Miquel Rojas                                                             *
 * Last Modification: Miquel Rojas                                                  *
 * Description:                                                                     *
 * Clase ProcessIA4.                                                              *
\*----------------------------------------------------------------------------------*/
#pragma once
#ifndef INC_IA4_PROCESS_H_
#define INC_IA4_PROCESS_H_

#include "Process.h"
#include "InputManager.h"
//#include "TexturedVertex.h"
#include "Math/MathUtils.h"
#include "StaticMeshes/StaticMeshManager.h"


//-----------FORWARD DECLARATION-----------
class CObject3D;
class CRenderManager;
class CActionToInput;
class CRenderableAnimatedInstanceModel;
class CRenderableObject;
class CCoreFIH;
class CPlayer;
//-----------------------------------------

class CProcessIA4: public CProcess
{
public:
  //Construct
	CProcessIA4();
  //Destruct
	virtual ~CProcessIA4();

	bool																							m_bMove;

  //functions
  ///<summary>
/// CProcessIA4:: Init : Lectura de los XML. Creaci�n y asignaci�n de las c�maras a los objetos.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
	void							Init						      					();


///<summary>
/// CProcessIA4:: Update : Actualizaci�n de todos los procesos.
///</summary>
///<param name="elapsedTime">Tiempo transcurrido.</param>
///<returns name=""></returns>
	void							Update					      					(float elapsedTime);

///<summary>
/// CProcessIA4:: PreRender : Prerenderizaci�n de efectos.
///</summary>
///<param name="rm">RenderManager.</param>
///<returns name=""></returns>
  void              PreRender                       (CRenderManager * rm);


///<summary>
/// CProcessIA4:: Render : Renderiza todo.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
  void							Render					      					(CRenderManager * rm);


  ///<summary>
/// CProcessIA4:: RenderScene : Renderiza la escena.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
  void							RenderScene											(CRenderManager * rm);

///<summary>
/// CProcessIA4:: RenderDebugInfo() : muestra la informaci�n del pitch, yaw, position y n�mero de caras de los objetos est�ticos y din�micos.
///</summary>
///<param name=""></param>
///<returns name=""></returns>

  void							RenderDebugInfo									();
  CCoreFIH*         GetCoreGame                     ()    {return m_pCoregame;}
private:

	//functions

///<summary>
/// CProcessIA4:: CheckActionsFromInputs : Seg�n una entrada de teclado ejecuta su acci�n asociada.
///</summary>
///<param name="elapsedTime">Tiempo transcurrido.</param>
///<returns name=""></returns>
  void  						CheckActionsFromInputs					(float elapsedTime);

  ///<summary>
/// CProcessIA4:: LoadXMLs : Carga todos los XML.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
void  						LoadXMLs												();

///<summary>
/// CProcessIA4:: InitCameras : Crea las c�maras y las asocia a un objeto.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
void  						InitCameras											();
  
///<summary>
/// CProcessIA4:: GetPositionObj : Nos devuelve un Vect3f con la posici�n del objeto.
///</summary>
///<param name="p_vObj">Objeto del que vamos a obtener la posici�n.</param>
///<returns name="posicion">Vector de 3 floats con la posici�n del objeto.</returns>
  Vect3f						GetPositionObj									(CObject3D* p_vObj);

  
///<summary>
/// CProcessIA4:: UpdateLua : Scripts de LUA.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
  void 							UpdateLua												();

  
///<summary>
/// CProcessIA4:: MovPlayer : Calcula los movimientos y la velocidad del player.
///</summary>
///<param name="elapsedTime">Tiempo transcurrido.</param>
///<returns name=""></returns>
  void							MovPlayer                       (float elapsedTime);
  void              MovCamera                       ();
	void							MovPlayerIA                     (float elapsedTime);

///<summary>
/// CProcessIA4:: MovMouse : Movimiento del rat�n asociado a la c�mara.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
  void							MovMouse												(); 

///<summary>
/// CProcessIA4:: Render3D : Renderiza la parte de 2D.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
  void							Render2D												(CRenderManager* rm);

  
///<summary>
/// CProcessIA4:: Render3D : Renderiza la parte de 3D.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
  void							Render3D												(CRenderManager* rm);
  void							RenderMovIA 										(CRenderManager* rm);
//  float             AjusteDireccion                 ();

///<summary>
/// CProcessIA4:: MemoryTest : Pruebas para grabar en RAM o VRAM.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
  void							MemoryTest											();

	//variables
	//float																							m_fPosX, m_fPosY, m_TimerCounter, m_iDirection, m_fFPS;
	//float 																						m_fRotacion;
	//float																							m_MaxVision, m_MinVision;
  float                                             m_DeltaFromXML;
	//CObject3D*																				m_pObject3D;
	//CObject3D*  																			m_pObject3D_Pivotal;
  CActionToInput* m_pAction;
//	CPlayer*                           								m_pPlayer;
  CRenderableAnimatedInstanceModel * 								m_pPlayer1;
	
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
  CCoreFIH* m_pCoregame;
};

#endif

