#include "BaseGame.h"
#include "RenderingGame/BaseRendering.h"
#include "UpdatingGame/BaseUpdating.h"
#include "CoreFIH.h"

#include "RenderManager.h"
#include "Shaders/EffectManager.h"
#include "Shaders/SceneEffectManager.h"
#include "SoundManager.h"

//#include "FontManager/FontManager.h"
//#include "Timer/Timer.h"
//#include "RenderableObjects/RenderableObjectsManager.h"
//#include "RenderableObjects/RenderableAnimatedInstanceModel.h"
//#include "Lights/LightManager.h"
//#include "Lights/OmniLight.h"
//#include "Lights/LightEffects/LightEffect2.h"
//#include "StaticMeshes/StaticMeshManager.h"
//#include "AnimationModel/AnimatedInstanceModel.h"
//#include "AnimationModel/AnimatedModelManager.h"
//#include "Texture/TextureManager.h"
//#include "ScriptManager.h"
//#include "Cameras/ThPSCamera.h"
//#include "Cameras/CameraManager.h"
//#include "Cameras/CameraKeyController.h"
//#include "Particles/ParticleManager.h"
//#include "RenderablePhysX/RenderablePhysXManager.h"
//#include "CharacterController/PhysicController.h"
//#include "Trigger/TriggerManager.h"
//#include "BillBoard/BillboardManager.h"

#include "Utils/BaseUtils.h"
#include <luabind/luabind.hpp>

#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

//CBaseGame::CBaseGame()
//{
//
////  m_DeltaFromXML = 0.0;
//	m_pCoregame = 0;
//	m_bDebugRender = false;
////  m_ucChangeLevel = 0;
////  m_pCameraKeyController = 0;
//  //m_bSonando = false;
//  //m_ucGameState = GS_NO_STATE;
//  //m_bEndAnimation = false;
//  //m_fAcumElapsedTime = 0.0f;
//
//}

///<summary>
/// CBaseGame:: Init : Lectura de los XML. Creación y asignación de las cámaras a los objetos.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
void CBaseGame::Init()
{
  //Adecuacion de ejes con para cal3d
//  CalLoader::setLoadingMode(LOADER_ROTATE_X_AXIS);
  
  //(CAMBIARLO POR EL CORE DEL JUEGO CORRESPONDIENTE)
  //CoreFIH 
	m_pCoregame = new CCoreFIH();
  m_pCoregame->Init();

  PostInit("");

  //xmls del juego y config establecida
  LoadCommonXMLs();
  LoadGameConfig();

/*
  //TODO.. GESTIONAR CORRECTAMENTE, QUE ESTO DE LIBERAR TEXTURA CUANDO SE VIENE DE LA PANTALLA DE TITULO
  // se liberan las texturas cargadas por la ventana de GUI anterior (cuando viene de la pantalla del titulo)
  CORE->GetTextureManager()->Destroy();

  //ESTO PUEDE ESTAR AQUI
  CalLoader::setLoadingMode(LOADER_ROTATE_X_AXIS);

  //CORRECTO QUE SE INICIE COREFIH PERO NO SPIRIT NI HISTORIAS EL NIVEL GESTIONARLO CON LA CLASE CORRESPONDIENTE
 // //IA4
	m_pCoregame = new CCoreFIH();
  m_pCoregame->Init();

 // //espiritu init
 // m_pCoregame->InitSpirit();

 // m_ucCurrentLevel = 1;

  //CORRECTO QUE SE CARGUE LA CONFIG DEL JUEGO Y LOS XML
  LoadCommonXMLs();
  //LoadLevelXMLs(m_ucCurrentLevel);
  LoadGameConfig();

  //TODO ESTO EN LA CLASE CORRESPONDIENTE
  //m_pCoregame->GetZombieManager()->RegistroAnimacionesCallback();

  //m_pCore->GetGUIManager()->Done();
  //m_pCore->GetGUIManager()->Init("Data/GUI/inGameGUI.xml");
  //m_pCore->GetGUIManager()->SetVisiblePointerMouse(false);
  //m_pCore->GetGUIManager()->ActiveWindowsWithEffect("Main.xml", TE_SHADOW_OFF, 1.5f);

	CORE->GetTriggerManager()->RegistraTriggers();

  CRenderManager * rm = CORE->GetRenderManager();

  //Partículas
  CORE->GetParticleManager()->Init(rm);

	//BillboardAnimado
	CORE->GetBillboardManager()->Init(rm);

  //:Player
  //m_pCoregame->InitPlayer("Data/Player.xml");
  //m_pPlayer = m_pCoregame->GetPlayer();
  //m_pCoregame->GetZombieManager()->SetActiveZombies(false);
  //Triggers
	//m_pCore->GetTriggerManager()->Init();


 //Sonido
  CORE->GetSoundManager()->SetListener(CORE->GetCameraManager()->GetCamera()->GetObject3D());
  CORE->GetSoundManager()->CrossFade("game_music", 3000);

  // iniciar animacion de la camara.
  ((CThPSCamera*)CORE->GetCameraManager()->GetCamera())->SetZoom(1.f);
  m_pCameraKeyController = new CCameraKeyController("Data/CameraPath.xml", CORE->GetCameraManager()->GetCamera());

  CORE->GetTimer()->ResetTimer();
*/
}


bool CBaseGame::PostInit(const std::string &file)
{
  bool l_bIsOk = true;
  
  m_pBaseUpdating = new CBaseUpdating();
  if(!m_pBaseUpdating)
  {
    LOGGER->AddNewLog(ELL_ERROR, "Base Updating no ha reservado memoria");
    l_bIsOk = false;  
  }

  m_pBaseRendering = new CBaseRendering();
  if(!m_pBaseRendering)
  {
    LOGGER->AddNewLog(ELL_ERROR, "Base Rendering no ha reservado memoria");
    l_bIsOk = false;  
  }
  
  m_bIsOk = l_bIsOk;
  return m_bIsOk;
}

void CBaseGame::Done()
{
  if (IsOk())
  {
    Release();
    m_bIsOk = false;
  }
}

void CBaseGame::Release()
{
  CHECKED_DELETE(m_pBaseRendering);
  CHECKED_DELETE(m_pBaseUpdating);
  CHECKED_DELETE(m_pCoregame);
}


///<summary>
/// CBaseGame:: RenderScene : Renderiza la escena.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
void CBaseGame::RenderScene(CRenderManager* rm) 
{
  if( GetBaseRendering() )
  {
    GetBaseRendering()->RenderScene( rm );
  }
}


void CBaseGame::RenderDebugInfo()
{  
  Inherited::RenderDebugInfo();
}
///<summary>
/// CBaseGame:: Update : Actualización de todos los procesos.
///</summary>
///<param name="elapsedTime">Tiempo transcurrido.</param>
///<returns name=""></returns>
void CBaseGame::Update(float elapsedTime)
{
  if( GetBaseUpdating() )
  {
    GetBaseUpdating()->Update( elapsedTime );
  }
  //switch (m_ucGameState)
  //{
  //  case GS_CAMERA_CINEMATIC:
  //  {
  //    m_pCameraKeyController->Update(elapsedTime);

  //    if (m_pCameraKeyController->Finished())
  //    {
  //      CThPSCamera* l_pCamera = (CThPSCamera*)m_pCore->GetCameraManager()->GetCamera();
  //      l_pCamera->SetZoom(7.0f);
  //      l_pCamera->SetZn(0.1f);
  //      l_pCamera->SetZf(300.0f);
  //      l_pCamera->GetObject3D()->SetPitch(-0.39f);
  //      
  //      m_ucGameState = GS_LEVEL_UPDATE;
  //    }
  //    break;
  //  }
  //  
  //  case GS_LEVEL_UPDATE:
  //  {
  //    CActionToInput * l_Action = m_pCore->GetInputManager()->GetActionToInput();
  //    CheckActionsFromInputs(elapsedTime);

  //    if ((m_DeltaFromXML = l_Action->DoAction("ReloadRenderableObjects")) != 0.0f )
  //    {
  //      m_pCore->GetRenderableObjectsManager()->Reload();
  //    }

  //    m_pPlayer->Update(elapsedTime);

  //    // updates especificos de cada nivel
  //    switch (m_ucCurrentLevel)
  //    {
  //      case 1:
  //      {
  //        int l_iTextActual = m_pCore->GetBillboardManager()->GetBAnimationByInstance("pTormenta")->GetTextureAct();
  //        if ((l_iTextActual == 70 || l_iTextActual == 177) && !m_bSonando)
  //        {
  //          m_pCore->GetSoundManager()->PlaySound("thunder");
  //          m_bSonando = true;
  //        }
  //        if (l_iTextActual == 71 || l_iTextActual == 178)
  //        {
  //          m_bSonando = false;
  //        }

  //        //Items
  //        m_pCore->GetItemManager()->Update(elapsedTime);

  //        if(m_pCore->GetItemManager()!=NULL)
  //        {
  //          m_pCore->GetItemManager()->CheckColisions();
  //        }
  //        
  //        //Animación puerta palanca
  //        if (!m_bEndAnimation)
  //        {
	 //         CBillboardManager * m_pBillboardM = m_pCore->GetBillboardManager();
	 //         int l_iTextAct = 	m_pBillboardM->GetBAnimationByInstance("pPuerta")->GetTextureAct();
	 //         bool l_bActive = m_pBillboardM->GetActive();
	 //         if (!l_bActive && l_iTextAct > 28)
	 //         {
		//          std::string l_stBox = "PuertaPalanca";
		//          Vect3f l_v3Pos = Vect3f(0.0f, -10.0f, 0.0f);
		//          CORE->GetPhysicsManager()->SetInvisbleBoxPosition(l_stBox,l_v3Pos);
		//          m_bEndAnimation = true;
	 //         }
  //    	  }

  //        //spirit
  //        if ((m_pCoregame->GetSpirit() != NULL) && (m_ucCurrentLevel == 1))//lo quito despues de las pruebas del boss, sino me peta
  //          m_pCoregame->GetSpirit()->Update(elapsedTime);
  //      }
  //      break;

  //      case 2:
  //      {
  //        COmniLight* l_LightLightning = (COmniLight*)m_pCore->GetLigthManager()->GetResource("relampago");
  //        CLightEffect2* l_LightningEffect = (CLightEffect2*)l_LightLightning->GetEffect();
  //        int l_wLightningCurrentKeyframe = l_LightningEffect->GetCurrentKeyframe();
  //        if (l_wLightningCurrentKeyframe == 2 && !m_bSonando)
  //        {
  //          m_pCore->GetSoundManager()->PlaySoundVolume("thunder", 0.2f);
  //          m_bSonando = true;
  //        }
  //        if (l_wLightningCurrentKeyframe == 3)
  //        {
  //          m_bSonando = false;
  //        }
  //      }
  //      break;
  //    }

  //    UpdateCamera();

  //    //m_pCore->GetCameraManager()->GetCamera()->InitShake();
  //    m_pCore->GetCameraManager()->GetCamera()->CameraShake(elapsedTime);

  //    //IA4
  //    m_pCoregame->GetZombieManager()->Update(elapsedTime);

  //    // Sound
  //    Vect3f l_PlayerPos = m_pPlayer->GetPhysicController()->GetPosition();
  //    m_pCore->GetSoundManager()->UpdateSound(l_PlayerPos);
 
  //    break;
  //  }
  //  
  //  case GS_PREPARE_CHANGE_LEVEL:
  //  {
  //    CheckActionsFromInputs(elapsedTime);
  //    
  //    if (m_fTimer < 3.0f)
  //    {
  //      m_fTimer += elapsedTime;
  //    }
  //    else
  //    {
  //      if (m_ucChangeLevel != G_GAME_OVER)
  //      {
  //        std::string l_sLoadWindowName;
  //        baseUtils::FormatSrting(l_sLoadWindowName, "Loading%d.xml", m_ucChangeLevel);
  //    
  //        m_pCore->GetGUIManager()->ActiveWindowsWithEffect(l_sLoadWindowName, TE_FADE_TO_BLACK, 2.0f);
  //        m_pCore->GetSoundManager()->PlaySound("level2");

  //        m_ucGameState = GS_CHANGE_LEVEL;
  //      }
  //      else
  //      {
  //        
  //        m_pCore->GetGUIManager()->ActiveWindowsWithEffect("End.xml", TE_SHADOW, 5.0f);
  //        m_ucGameState = GS_GAME_OVER_TRANSITION;
  //      }
  //    }

  //    break;
  //  }
  //  
  //  case GS_CHANGE_LEVEL:
  //  {
  //    CheckActionsFromInputs(elapsedTime);
  //    
  //    std::string l_sLoadWindowName;
  //    baseUtils::FormatSrting(l_sLoadWindowName, "Loading%d.xml", m_ucChangeLevel);
  //    
  //    if (m_pCore->GetGUIManager()->GetCurrentWindow() == l_sLoadWindowName)
  //    {
  //      LoadLevel(m_ucChangeLevel);
  //    }

  //    break;
  //  }
  //  
  //  case GS_GAME_OVER_TRANSITION:
  //  {
  //    if (m_pCore->GetGUIManager()->GetCurrentWindow() != "End.xml")
  //    {
  //      CheckActionsFromInputs(elapsedTime);
  //    }
  //    else
  //    {
  //      m_ucGameState = GS_GAME_OVER;
  //    }

  //    break;
  //  }
  //  
  //  case GS_GAME_OVER:
  //  {
  //    break;
  //  }
  //  
  //  case GS_LEVEL_SELECTED:
  //  {
  //    std::string l_sLoadWindowName;
  //    baseUtils::FormatSrting(l_sLoadWindowName, "Loading%d.xml", m_ucChangeLevel);
  //    
  //    if (m_pCore->GetGUIManager()->GetCurrentWindow() == l_sLoadWindowName)
  //    {
  //      LoadLevel(m_ucChangeLevel);
  //    }

  //    break;
  //  }
/*    CORE->GetRenderableObjectsManager()->Update(elapsedTime);
    
    //Partículas
    CORE->GetParticleManager()->Update(elapsedTime);

	  //Billboard animado
	  CORE->GetBillboardManager()->Update(elapsedTime);
  	
*/ 	
	  //test
	  //if(m_pCoregame->GetSingletonPtr()->GetPlayer()->GetPhysicController()->GetPosition().y < -3.0f)
   // {
  	//    (float)m_pCoregame->GetSingletonPtr()->GetPlayer()->GetPhysicController()->GetPosition().y = 3.0f;
   // }
//  }
}

///<summary>
/// CBaseGame:: Render : Renderiza todo.
///</summary>
///<param name="rm">Puntero a render manager.</param>
///<returns name=""></returns>
void CBaseGame::Render(CRenderManager* rm) 
{

  RenderScene(rm);
	////IA

	////eje principal
 // Mat44f matWorld;
 // matWorld.SetIdentity();
 // rm->SetTransform(matWorld);
 // rm->DrawAxis(5);
/*

  CSceneEffectManager *l_pSceneEffectManager = CORE->GetSceneEffectManager();
  // Andres: esta linea la comento para no usar efectos de escena
  //l_pSceneEffectManager->ActivateRenderSceneEffects();

  CEffectManager *l_EffectManager=CORE->GetEffectManager();
  l_EffectManager->SetAnimatedModelTechnique(NULL);
  l_EffectManager->SetStaticMeshTechnique(NULL);

  //Renderizamos la escena
  RenderScene(rm);

  l_pSceneEffectManager->CaptureFrameBuffers(rm);
  l_pSceneEffectManager->PostRender(rm);
  l_pSceneEffectManager->CaptureFrameBuffersAfterPostRender(rm);

	//Triggers
  CORE->GetTriggerManager()->Render();

  //RenderScene(rm);

  //Física
  if(m_bDebugRender)
  {
    CPhysicsManager* l_PhysManager = CORE->GetPhysicsManager();
    l_PhysManager->DebugRender(rm);
  }
*/
}


//---------------------------------------------------------------------------------//
//-------------------FUNCIONES PROPIAS DE GAMEPROCESS_TEST-------------------------//
//---------------------------------------------------------------------------------//

///<summary>
/// CBaseGame:: LoadCommonXMLs : Carga los ficheros XML comunes a todo el juego.
///</summary>
void CBaseGame::LoadCommonXMLs()
{
  CORE->GetEffectManager()->Load("Data/Effects.xml");
  CORE->GetSceneEffectManager()->LoadXML("Data/scene_effects.xml");
  if (CORE->GetSoundManager()->IsOk())
  {
    CORE->GetSoundManager()->Init("Data/Sounds.xml");
  }
}


///<summary>
/// CBaseGame:: LoadGameConfig : Carga de un XML los parametros de configuracion del juego.
///</summary>
///<param>Puntero a render manager.</param>
///<returns>Bool isOK</returns>
bool CBaseGame::LoadGameConfig()
{

  CXMLTreeNode l_FileXML;
  std::string l_sFileName = "Data/gameConfig.xml";

  // Carga del fichero de configuracion
  if (l_FileXML.LoadFile(l_sFileName.c_str()))
  {
    CXMLTreeNode l_Params = l_FileXML["camera"];
    if (l_Params.Exists())
    {
/*      CORE->GetCameraManager()->SetYawFactorCamera( l_Params.GetFloatProperty("yawFactor", 0.18f) );
      CORE->GetCameraManager()->SetPitchFactorCamera ( l_Params.GetFloatProperty("pitchFactor", 0.18f) );
      CORE->GetCameraManager()->SetPitchUpperLimit( l_Params.GetFloatProperty("pitchUpperLimit", 0.5f) );
      CORE->GetCameraManager()->SetPitchLowerLimit( l_Params.GetFloatProperty("pitchLowerLimit", -1.5f) );
*/ 
   
    }
    return true;
  }
  else
  {
	  	LOGGER->AddNewLog(ELL_ERROR, "CPlayer::Init->Error al intentar abrir el archivo: %s" ,l_sFileName.c_str() );
  	  return false;
  }
}


//TODO.. MOVER ESTA FUNCION A CAMARA O PLAYER
//void CBaseGame::UpdateCamera()
//{
  ////PRUEBA CON RAYOS
  //CThPSCamera * l_ActiveCamera = (CThPSCamera*) CORE->GetCameraManager()->GetCamera();
  //Vect3f l_ActualPosition = l_ActiveCamera->GetEye();
  //CPhysicsManager * l_PhysXManager = CORE->GetPhysicsManager();
  //std::vector<CPhysicUserData*> l_ImpactObjects;
  //Vect3f pos = l_ActiveCamera->GetLookAt();
  //Vect3f& dir = l_ActiveCamera->GetDirection();
  //dir = dir * -1.f;
  //dir.Normalize();
  //SCollisionInfo info;
  //CPhysicUserData* m_ClosestActorCamera = l_PhysXManager->RaycastClosestActor(pos,dir,PX_MSK_ALL_SCENARIO,m_ClosestActorCamera,info);
  //if(m_ClosestActorCamera != NULL)
  //{
  //  float l_CollisionDistance = info.m_fDistance;
  //  if(l_CollisionDistance < CAMERA_ZOOM)
  //  {
  //    l_CollisionDistance = l_CollisionDistance - 0.1f;
  //    l_ActiveCamera->SetZoom(l_CollisionDistance);
  //    //TODO: Alpha del personaje de acuerdo a la distancia de la camara.
  //  }
  //}
  //else
  //{
  //  l_ActiveCamera->SetZoom(4.0f);
  //}
  //Vect3f l_CameraPosition = m_pPlayer->GetPhysicController()->GetPosition();
  //l_CameraPosition.y += 0.6f;
  //l_ActiveCamera->GetObject3D()->SetPosition(l_CameraPosition);
//}