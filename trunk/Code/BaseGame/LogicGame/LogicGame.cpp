#include "LogicGame.h"
#include "CoreFIH.h"

#include "ScriptManager.h"
#include "GUIManager.h"

#include "Cameras/ThPSCamera.h"
#include "Cameras/CameraManager.h"
#include "Cameras/CameraKeyController.h"
#include "InputManager.h"
#include "ActionToInput.h"

//#include "ZombieManager/ZombieManager.h"
#include "Player/Player.h"
//#include "ItemManager.h"
//#include "Spirit/Spirit.h"


#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool CLogicGame::Init()
{
  m_bIsOk = true;
  
  // LUA
  LoadLuaScripts();
  Register2LUA();


  m_ucGameState = GS_CAMERA_CINEMATIC;
  
  if (!m_bIsOk)
  {
    Release();
  }

  return m_bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void CLogicGame::Done()
{
  if (IsOk())
  {
    Release();
    m_bIsOk = false;
  }
}

//----------------------------------------------------------------------------
// Free memory
//----------------------------------------------------------------------------
void CLogicGame::Release()
{
//free memory
}


///<summary>
/// CLogicGame::GameOver : Prepara parametros para cambiar de estado y poder mostrar al ventana de GameOVer de seleccion de nivel.
///</summary>
void CLogicGame::GameOver()
{
  m_pCoregame->GetSingletonPtr()->GetPlayer()->SetSate(-1);
  m_pCoregame->GetSingletonPtr()->GetPlayer()->Update(0.f);
  //TODO.. se debe avisar al manager de niveles
//  m_ucChangeLevel = G_GAME_OVER;
  m_ucGameState = GS_PREPARE_CHANGE_LEVEL;
}

///<summary>
/// CLogicGame::ReStart : Reestablece el player a su estado inicial. En el nivel2 también al boss.
///</summary>
void CLogicGame::ReStart()
{
  //switch (m_ucCurrentLevel)
  //{
  //  case 1:
  //  {
  //    break;
  //  }

  //  case 2:
  //  {
  //    CORE->GetScriptManager()->RunCode("revive_boss()");
  //    break;
  //  }
  //}
//  m_pCoregame->GetSingletonPtr()->GetPlayer()->ReStart();
}

///<summary>
/// CBaseGame:: CheckActionsFromInputs : Según una entrada de teclado ejecuta su acción asociada.
///</summary>
///<param name="elapsedTime">Tiempo transcurrido.</param>
///<returns name=""></returns>
void CLogicGame::CheckActionsFromInputs(float elapsedTime)
{
  CActionToInput * l_Action = CORE->GetInputManager()->GetActionToInput();

  #if defined( _DEBUG )

  if((m_DeltaFromXML = l_Action->DoAction("ProcessInfo")) != 0.0f )
  {
    m_bRenderDebugInfo = !m_bRenderDebugInfo; //Esto solo se dibuja en tiempo de renderingScene
  }
  
  if((m_DeltaFromXML = l_Action->DoAction("ReloadLua")) != 0.0f )
  {
    LoadLuaScripts();
  }
  #endif // defined( _DEBUG )

// ACCIONES DE DEBUG HABILITADAS TEMPORALMENTE TAMBIEN EN RELEASE
  //if((m_DeltaFromXML = l_Action->DoAction("ReloadPlayer")) != 0.0f )
  //{
  //  m_pPlayer->Reload();
  //}

  if((m_DeltaFromXML = l_Action->DoAction("getKey")) != 0.0f )
  {
    CORE->GetScriptManager()->RunCode("llave_in()");
  }

  if((m_DeltaFromXML = l_Action->DoAction("GameOver")) != 0.0f )
  {
    //ChangeLevel(2);
    //LoadLevel(2);
    CORE->GetGUIManager()->ActiveWindows("End.xml");
    m_ucGameState = GS_GAME_OVER;
  }

// END - ACCIONES DE DEBUG - 
  CCamera * l_ActualCamera = CORE->GetCameraManager()->GetCamera();
  
  if(!l_ActualCamera->GetShake())
  {
    //YawViewerCam
    if((m_DeltaFromXML = l_Action->DoAction("YawViewerCam")) != 0.0f )
    {
      float l_fYawFactor = CORE->GetCameraManager()->GetYawFactorCamera();
		  float l_fCameraYaw = l_ActualCamera->GetObject3D()->GetYaw() - m_DeltaFromXML * elapsedTime * l_fYawFactor; //*0.005f;

      // restringiendo el angulo de Yaw de la camara para que siempre esté entre -PI y PI
      //TODO.. no lo veo claro esto
      while (l_fCameraYaw > FLOAT_PI_VALUE)
        l_fCameraYaw -= FLOAT_2PI_VALUE;
      while (l_fCameraYaw < -FLOAT_PI_VALUE)
        l_fCameraYaw += FLOAT_2PI_VALUE;

      l_ActualCamera->GetObject3D()->SetYaw(l_fCameraYaw);
    }
    //PitchViewerCam
    if((m_DeltaFromXML = l_Action->DoAction("PitchViewerCam")) != 0.0f )
    {
      float l_fPitchFactor = CORE->GetCameraManager()->GetPitchFactorCamera();
      float l_fPitch = l_ActualCamera->GetObject3D()->GetPitch();

      l_fPitch -= m_DeltaFromXML  * elapsedTime * l_fPitchFactor; //* 0.005f;

      // estableciendo un limite para el angulo
      float l_fPitchLowerLimit = CORE->GetCameraManager()->GetPitchLowerLimit();
      float l_fPitchUpperLimit = CORE->GetCameraManager()->GetPitchUpperLimit();
      
      if (l_fPitch > l_fPitchLowerLimit && l_fPitch < l_fPitchUpperLimit)
        l_ActualCamera->GetObject3D()->SetPitch(l_fPitch);
      else
      {
        if (l_fPitch < l_fPitchLowerLimit)
          l_ActualCamera->GetObject3D()->SetPitch(l_fPitchLowerLimit);
        else if (l_fPitch > l_fPitchUpperLimit)
          l_ActualCamera->GetObject3D()->SetPitch(l_fPitchUpperLimit);
      }
    }
    //SlowZoomViewerCam
    if((m_DeltaFromXML = l_Action->DoAction("SlowZoomViewerCam")) != 0.0f )
    {
      CThPSCamera * cam = (CThPSCamera*)CORE->GetCameraManager()->GetCamera();
      cam->AddZoom(m_DeltaFromXML * -0.005f);
    }
    else 
    { //ZoomViewerCam
      if((m_DeltaFromXML = l_Action->DoAction("ZoomViewerCam")) != 0.0f )
      {
        CThPSCamera * cam = (CThPSCamera*)CORE->GetCameraManager()->GetCamera();
        cam->AddZoom(m_DeltaFromXML * -0.01f);
      }
    }
  }
}


///<summary>
/// CBaseGame::LoadLuaScripts : Carga y ejecuta todos los scripts LUA del juego
///</summary>
void CLogicGame::LoadLuaScripts()
{
    CORE->GetScriptManager()->RunFile("Data/LUAScripts/variables.lua");
	  CORE->GetScriptManager()->RunFile("Data/LUAScripts/init.lua");
	  CORE->GetScriptManager()->RunFile("Data/LUAScripts/zombis.lua");
	  CORE->GetScriptManager()->RunFile("Data/LUAScripts/triggers.lua");
	  CORE->GetScriptManager()->RunFile("Data/LUAScripts/zombi_boss.lua");
}


//TODO.. hay que registrar en el momeonto correcto
void CLogicGame::Register2LUA()
{
 // lua_State * l_LS = CORE->GetScriptManager()->GetLuaState();
	//using namespace luabind;
 // 
 // // Videogame ---------------------------------------------
 // module(l_LS)
 //   [
 //     // registramos la clase CBaseGame
 //     class_<CLogicGame>("CLogicGame")
 //     // registramos su constructor
 //     .def(constructor<>())
 //     .def("change_level", &CLogicGame::ChangeLevel)
 //     .def("load_level", &CLogicGame::LoadLevel)
 //     .def("game_over", &CLogicGame::GameOver)
 //     .def("re_start", &CLogicGame::ReStart)
 //   ];

 // globals(l_LS)["g_logicgame"] = this;
}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------