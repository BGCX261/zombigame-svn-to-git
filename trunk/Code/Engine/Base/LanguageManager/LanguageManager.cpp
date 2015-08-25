#include "Base.h"
#include "Logger/Logger.h"
#include "LanguageManager.h"
#include "xml/XMLTreeNode.h"
#include "Exceptions/Exception.h"
#include "Core.h"
#include "Utils/BaseUtils.h"

#include <sys/stat.h> //Para verificacion de existencia de archivos xml

#if defined( _DEBUG )
#include "Memory/MemLeaks.h"
#endif // defined( _DEBUG )


bool CLanguageManager::Init()
{
  std::string msg_error = "LanguageManager::Init";
  LOGGER->AddNewLog(ELL_INFORMATION, msg_error.c_str());

  if(m_sCurrentLanguage.compare(""))
  {
    Reload();
  }
  else
  {
    m_LanguageXMLPath = "Data/Language/languages.xml";
    m_sCurrentLanguage = "spanish";
    if( LoadLanguages() )
    {
      LoadXMLs();
    }
    else
    {
      return false;
    }
  }
  return true;
}


bool CLanguageManager::LoadLanguages()
{
  bool IsOK = true;
  CXMLTreeNode parser;
  if (parser.LoadFile(m_LanguageXMLPath)) 
  {
    CXMLTreeNode l_Languages = parser["languages"];
    if (!l_Languages.Exists())
    {
      IsOK = false;
      std::string msg_error = "LanguageManager::LoadXML->Error al intentar leer el archivo de lenguajes";
      LOGGER->AddNewLog(ELL_ERROR, msg_error.c_str());
      throw CException(__FILE__, __LINE__, msg_error);
    }
    else
    {
      for(int i = 0; i < l_Languages.GetNumChildren();i++)
      {
        if(!l_Languages(i).IsComment())
        {
          IsOK = ReadNewLanguage(l_Languages(i), i);
        }
      }
      
      SetCurrentLanguage(m_sCurrentLanguage);
    }
    
  }
  return IsOK;
}

bool CLanguageManager::ReadNewLanguage(const CXMLTreeNode &_language, const int &i)
{
  //obtiene propiedades del xml
  const char* l_id              = _language.GetPszProperty("id");;
  const char* l_path            = _language.GetPszProperty("path");
  const bool l_defaultLanguage  = _language.GetBoolProperty("default");
  
  
    //guarda los paths
  SetXmlFile(l_path);
  
  //idioma actual
  if(l_defaultLanguage)
  {
      //comprueba que el idioma por defecto existe
      SetCurrentLanguage(l_id);
    //baseUtils::FormatSrting(m_sCurrentLanguage,"%s" ,l_id);
  }
  return true;
}

void CLanguageManager::Unload()
{
  //Tener en cuenta que se puede hacer un reload!
  std::map<std::string, TLanguage>::iterator it_1			= m_Languages.begin();
  std::map<std::string, TLanguage>::iterator itEnd_1	= m_Languages.end();
  while (it_1 != itEnd_1)
  {
    it_1->second.clear();
    ++it_1;
  }
  m_Languages.clear();


}

bool CLanguageManager::Reload()
{
  LoadXMLs();
  return true;
}

void CLanguageManager::LoadXMLs ()
{
  Unload();
  std::vector<std::string>::const_iterator it			= m_vXML_Files.begin();
  std::vector<std::string>::const_iterator itEnd	= m_vXML_Files.end();
  while (it != itEnd)
  {
    std::string xmlPath = *it;
    LoadXML(xmlPath);
    ++it;
  }
}



/**
* LoadXML 
* pathFile - (string) camino al archivo del idioma
*/
void CLanguageManager::LoadXML (const std::string& pathFile)
{
  //carga archivo
  CXMLTreeNode parser;
  if (!parser.LoadFile(pathFile.c_str()))
  {
    std::string msg_error = "LanguageManager::LoadXML->Error al intentar leer el archivo de lenguaje: " + pathFile;
    LOGGER->AddNewLog(ELL_ERROR, msg_error.c_str());
    throw CException(__FILE__, __LINE__, msg_error);
  }

  /*<Language id="english">
  <literal id="xfiles"  font="X-Files"  color="0.5 0.5 0.5 0.5" value="Hi World"/>
  <literal id="xfiles"  font="X-Files"  color="0.1 0.1 0.1 0.8" value="Exit"/>  
  </Language>*/

  LOGGER->AddNewLog(ELL_INFORMATION, "LanguageManager::LoadXML-> Parseando fichero de lenguaje: %s", pathFile.c_str());

  //obtiene nodo idioma
  CXMLTreeNode  m = parser["Language"];
  std::string id_language	= m.GetPszProperty("id");
  TLanguage language;
  if (m.Exists())
  {
    int count = m.GetNumChildren();
    for (int i = 0; i < count; ++i)
    {
      if (!m(i).IsComment())
      {
        //for each literal:
        SLiteral l_literal;
        
        //obtiene propiedades del nodo          
        std::string id			= m(i).GetPszProperty("id");
        l_literal.m_sFontId	= m(i).GetPszProperty("font");
        Vect4f vecColor			= m(i).GetVect4fProperty("color", Vect4f(0.f,0.f,0.f,0.f));	
        l_literal.m_value		= m(i).GetPszISOProperty("value", "nothing");	
        l_literal.m_cColor	= CColor(vecColor.x, vecColor.y, vecColor.z, vecColor.w);
        language.insert(std::pair<std::string,SLiteral>(id, l_literal));
        LOGGER->AddNewLog(ELL_INFORMATION, "LanguageManager::LoadXML-> Añadido literal(%s,%s,[%f,%f,%f,%f],%s)", 
        id.c_str(), l_literal.m_sFontId.c_str(),vecColor.x,vecColor.y,vecColor.z,vecColor.w, l_literal.m_value.c_str());	
      }
    }
  }
  if (m_Languages.find(id_language) != m_Languages.end())
  {
    //Ya está registrado el identificador id_language
    LOGGER->AddNewLog(ELL_WARNING, "LanguageManager::LoadXML-> Ya se ha registrado un language con identificador %s", id_language.c_str());
  }
  else
  {
    m_Languages.insert(std::pair<std::string, TLanguage>(id_language, language));
  }
}


/**
* SetXmlFile
* pathFile - (string) camino al archivo del idioma
*/
void CLanguageManager::SetXmlFile (const std::string& pathFile)
{
  std::vector<std::string>::iterator it			= m_vXML_Files.begin();
  std::vector<std::string>::iterator itEnd	= m_vXML_Files.end();
  bool exist = false;
  //busca en el vector de archivos de idiomas
  while(it != itEnd)
  {
    //comprueba que el idioma exista en el vector y sale si es asi
    std::string xmlFile = *it;
    if (xmlFile == pathFile)
    {
      exist = true;
      break;
    }
    ++it;
  }

  //lo introduce en el vector si no existia previamente
  if (!exist)
  {
    m_vXML_Files.push_back(pathFile);
    LOGGER->AddNewLog(ELL_INFORMATION, "LanguageManager::SetXmlFile-> Se ha añadido el xml: %s", pathFile.c_str());
  }
}

/**
* GetLiteral 
* id - (string) palabra clave para buscar la traduccion al idioma actual
* sLiteral - (SLiteral) palabra traducida al idioma actual
*/
bool CLanguageManager::GetLiteral (const std::string& id, SLiteral& sliteral) const
{
  //comprueba si existe el idioma actual
  std::map<std::string, TLanguage>::const_iterator it = m_Languages.find(m_sCurrentLanguage);
  if (it != m_Languages.end())
  {
    //en el idioma, busca la palabra id
    TLanguage currentLanguage = it->second;
    TLanguage::const_iterator it_aux = currentLanguage.find(id);
    //si lo encuentra la carga en sliteral
    if (it_aux != currentLanguage.end())
    {
      sliteral = it_aux->second;
      return true;
    }
  }
  
  return false;
}


/**
* SetCurrentLanguage 
* id - (string) si existe el idioma lo pone como activo
*/
void CLanguageManager::SetCurrentLanguage (const std::string& id)
{
  std::map<std::string, TLanguage>::iterator it = m_Languages.find(id);
  if (it != m_Languages.end())
  {
    LOGGER->AddNewLog(ELL_INFORMATION, "LanguageManager::SetCurrentLanguage-> Se ha seteado como current el language %s", id.c_str());
  }
  else
  {
    LOGGER->AddNewLog(ELL_WARNING, "LanguageManager::SetCurrentLanguage-> El language %s no esta registrado", id.c_str());
  }
}
