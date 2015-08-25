#include "LevelManager.h"

#include "Core.h"

#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )

//----------------------------------------------------------------------------
// Init data
//----------------------------------------------------------------------------
bool CLevelManager::Init()
{
  m_bIsOk = true;

  if (!m_bIsOk){
    Release();
  }

  return m_bIsOk;
}

//----------------------------------------------------------------------------
// Finalize data
//----------------------------------------------------------------------------
void CLevelManager::Done()
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
void CLevelManager::Release()
{
//free memory
}

///<summary>
/// CLevelManager:: LoadLevelXMLs : Carga los XML necesarios segun el nivel.
///</summary>
///<param name="_level"></param>
///<returns name=""></returns>
void CLevelManager::LoadLevelXMLs(uint8 _level)
{
  //switch (_level)
  //{
  //  case 1:
  //  {
  //    m_pCore->GetStaticMeshManager()->Load("Data/Level1/StaticMeshManager.xml");
  //    m_pCore->GetLigthManager()->Load("Data/Level1/lights.xml");
  //    m_pCore->GetAnimatedModelManager()->Load("Data/Level1/AnimatedModels.xml");
  //    m_pCore->GetRenderableObjectsManager()->Load("Data/Level1/RenderableObjects.xml");
  //    m_pCore->GetPhysicsManager()->LoadInvisibleBlockingBoxes("Data/Level1/InvisibleBoxes.xml");
  //    m_pCore->GetBillboardManager()->LoadXML("Data/Level1/ParticlesAnimation.xml");
  //    m_pCore->GetParticleManager()->LoadXML("Data/Level1/Particles.xml");
  //    m_pCore->GetTriggerManager()->Load("Data/Level1/Triggers.xml");

  //    m_pCoregame->GetZombieManager()->Load("Data/Level1/ZombieLoader.xml");
  //    m_pCoregame->GetSpirit()->LoadXML("Data/Level1/spirit.xml"); 
  //  }
  //  break;

  //  case 2:
  //  {
  //    m_pCore->GetStaticMeshManager()->Load("Data/Level2/StaticMeshManager.xml");
  //    m_pCore->GetLigthManager()->Load("Data/Level2/lights.xml");
  //    m_pCore->GetAnimatedModelManager()->Load("Data/Level2/AnimatedModels.xml");
  //    m_pCore->GetRenderableObjectsManager()->Load("Data/Level2/RenderableObjects.xml");
  //  //  l_pCore->GetPhysicsManager()->LoadInvisibleBlockingBoxes("Data/Level1/InvisibleBoxes.xml");
 	//    //if(m_pCore->GetBillboardManager())
  // 	  //  m_pCore->GetBillboardManager()->LoadXML("Data/Level1/ParticlesAnimation.xml");
  //    m_pCoregame->GetZombieManager()->Load("Data/Level2/ZombieLoader.xml");
  //  }
  //  break;
  //}
}


///<summary>
/// CLevelManager::ReleaseLevel : Libera memoria de los managers para poder cargr un nuevo nivel.
///</summary>
void CLevelManager::ReleaseLevel()
{
  //m_pCoregame->ReleaseSpirit();
  //m_pCoregame->GetZombieManager()->Done();
  //  
  //    // CHECKED_DELETE(m_pRenderManager);
  //    // CHECKED_DELETE(m_pFontManager);
  //    // CHECKED_DELETE(m_pLanguageManager);
  //    // CHECKED_DELETE(m_pInputManager);
  //m_pCore->GetStaticMeshManager()->Destroy();
  //m_pCore->GetRenderableObjectsManager()->CleanUp();
  //m_pCore->GetLigthManager()->Done(); // CHECKED_DELETE(m_pLightManager);
  //m_pCore->GetAnimatedModelManager()->Destroy();
  //    // CHECKED_DELETE(m_pEffectManager);
  //    // CHECKED_DELETE(m_pTimer);
  //// CHECKED_DELETE(m_pScriptManager);
  //    //CHECKED_DELETE(m_pCameraManager);
  //m_pCore->GetGUIManager()->Done();
  //m_pCore->GetPhysicsManager()->Done();
  //m_pCore->GetTextureManager()->Destroy();
  //// CHECKED_DELETE(m_pSceneEffectManager);
  //m_pCore->GetParticleManager()->Done();
  ////    m_pCore->GetSoundManager()->Done();
  //m_pCore->GetRenderablePhysXManager()->Destroy();
  //m_pCore->GetTriggerManager()->Done();
  //m_pCore->GetItemManager()->Done();
  //m_pCore->GetBillboardManager()->Done();
}

///<summary>
/// CLevelManager::LoadLevel : Carga en memoria y establece los parametros necesarios segun cada nivel.
///</summary>
void CLevelManager::LoadLevel(uint8 _level)
{
//  if (_level != m_ucCurrentLevel)
//  {
//    ReleaseLevel();
//
//    m_pCore->GetPhysicsManager()->Init();
//    m_pCoregame->GetZombieManager()->Init();
//
//    //espiritu init
//    if (_level == 1)
//    {
//      m_pCoregame->InitSpirit();
//    }
//    
//    LoadLevelXMLs(_level);
//
//    //    m_pCoregame->GetZombieManager()->RegistroAnimacionesCallback();
//  
//
//    //Partículas
//    //m_pCore->GetParticleManager()->Init(rm);
//
//	  //BillboardAnimado
//	  //m_pCore->GetBillboardManager()->Init(rm);
//
//    switch (_level)
//    {
//      case 1:
//      {
//        m_pCoregame->GetZombieManager()->RegistroAnimacionesCallback();
//        //Partículas
//        //m_pCore->GetParticleManager()->Init("");
//        m_pCore->GetParticleManager()->Init(m_pCore->GetRenderManager());
//        // Animated Billboard
//        //m_pCore->GetBillboardManager()->Init("");
//        m_pCore->GetBillboardManager()->Init(m_pCore->GetRenderManager());
//        
//        m_pCoregame->GetZombieManager()->SetActiveZombies(false);
//        
//        m_pCoregame->GetSpirit()->SetParticleEmitter("pHitodama1", "pHitodama2");
//        
//        // iniciar animacion de la camara.
//        ((CThPSCamera*)m_pCore->GetCameraManager()->GetCamera())->SetZoom(1.f);
//        m_pCameraKeyController->ResetTime();// = new CCameraKeyController("Data/CameraPath.xml", m_pCore->GetCameraManager()->GetCamera());
//        
//        m_ucGameState = GS_CAMERA_CINEMATIC;
//
//        break;
//      }
//
//      case 2:
//      {
//        CObject3D * l_pCameraObject = m_pCore->GetCameraManager()->GetCamera()->GetObject3D();
//        l_pCameraObject->SetYaw(0.0f);
//        l_pCameraObject->SetPitch(-0.21f);
//        l_pCameraObject->SetRoll(0.0f);
//
//        m_ucGameState = GS_LEVEL_UPDATE;
//
//        break;
//      }
//    }
//
//    m_pCore->GetGUIManager()->Init("Data/GUI/inGameGUI.xml");
//
//    //IA4
//	  m_pCore->GetTriggerManager()->RegistraTriggers();
//
//    //:Player
//    m_pPlayer->InitCamera();
//    m_pPlayer->AssignLights();
//    m_pPlayer->AssingAnimation();
//    m_pPlayer->InicializaController();
//    m_pCoregame->GetHealthIndicator()->AssignGUIElements(); // reestablece las texturas del indicador de salud
//
//    m_ucCurrentLevel = _level;
//  }
//  else
//  {
//    switch (m_ucCurrentLevel)
//    {
//      case 1:
//      {
//        m_ucGameState = GS_CAMERA_CINEMATIC;
//        break;
//      }
//
//      case 2:
//      {
//        m_ucGameState = GS_LEVEL_UPDATE;
//        m_pCore->GetScriptManager()->RunCode("revive_boss()");
//        break;
//      }
//    }
//  }
//
//  m_pCore->GetSoundManager()->CrossFade("game_music", 1000);
//  m_pCore->GetGUIManager()->ActiveWindowsWithEffect("Main.xml", TE_SHADOW_OFF, 2.0f);
//  m_pCore->GetGUIManager()->SetVisiblePointerMouse(false);
//  m_pPlayer->ReStart();
//  /*m_pCoregame->InitPlayer("Data/Player.xml");
//    m_pPlayer = m_pCoregame->GetPlayer();
//    m_pCoregame->GetZombieManager()->SetActiveZombies(false);*/
//   
//
//    //Triggers
////	  m_pCore->GetTriggerManager()->Init();
//
//	  //Items
//	  //m_pCore->GetItemManager()->AddItem(Vect3f(17.5f,1.37f,13.6f));
//
//    //espiritu asigna emisor particulas
//	  //m_pCoregame->GetSpirit()->SetParticleEmitter("pHitodama1", "pHitodama2");
//
//   //Sonido
//    //m_pCore->GetSoundManager()->SetListener(m_pCore->GetCameraManager()->GetCamera()->GetObject3D());
//    
////  LoadLuaScripts();
//  
//  m_ucChangeLevel = 0;
//  m_pCore->GetTimer()->ResetTimer();
}

///<summary>
/// CBaseGame::LoadLevel : Establece lso parametros previos a la carga de un nivel (getión de estados, sonido y GUI).
///</summary>
void CLevelManager::ChangeLevel(uint8 _level)
{
  //if (_level != m_ucCurrentLevel)
  //{
  //  if (m_ucGameState == GS_GAME_OVER)
  //  {
  //    std::string l_sLoadWindowName;
  //    baseUtils::FormatSrting(l_sLoadWindowName, "Loading%d.xml", _level);
  //    m_pCore->GetGUIManager()->ActiveWindows(l_sLoadWindowName);
  //    m_pCore->GetGUIManager()->SetVisiblePointerMouse(false);
  //    m_ucGameState = GS_LEVEL_SELECTED;
  //    m_ucChangeLevel = _level;
  //  }
  //  else
  //  {
  //    m_fTimer = 0.0f;
  //    m_pPlayer->SetSate(-1);
  //    m_pPlayer->Update(0.f);
  //    m_ucChangeLevel = _level;
  //    m_ucGameState = GS_PREPARE_CHANGE_LEVEL;
  //  }
  //}
  //else
  //{
  //  LoadLevel(_level);
  //}
}



//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------