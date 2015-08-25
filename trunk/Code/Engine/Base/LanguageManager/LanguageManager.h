//----------------------------------------------------------------------------------
// CLanguageManager class
// Author: Enric Vergara
//
// Description:
// Esta clase será la que se encargue de dar un string en el lenguage que este seteado actualmente
//----------------------------------------------------------------------------------
#pragma once
#ifndef INC_LANGUAGE_MANAGER_H_
#define INC_LANGUAGE_MANAGER_H_

#include "Math/Color.h"
#include <vector>
#include <map>

struct SLiteral
{
	std::string	m_sFontId;
	CColor			m_cColor;
	std::string	m_value;
};

class CXMLTreeNode;

class CLanguageManager
{
public:
  CLanguageManager::CLanguageManager():m_sCurrentLanguage(""),m_LanguageXMLPath(""){}
	virtual ~CLanguageManager(void) {/*Nothing*/;}

  bool            Init                ();
	bool						GetLiteral					(const std::string& id, SLiteral& sliteral) const;
	void						SetCurrentLanguage	(const std::string& id);
  bool            Reload              ();
  void            Unload              ();
	
private:
  bool            LoadLanguages       ();
	void						LoadXMLs						();																//se puede hacer un reload
	void						LoadXML							(const std::string& pathFile);
	bool            ReadNewLanguage     (const CXMLTreeNode &_language, const int &i);
	void						SetXmlFile					(const std::string& pathFile);

	
	typedef std::map<std::string,SLiteral>      TLanguage;

	std::vector<std::string>					          m_vXML_Files;           // paths donde se guardan los xml con los idiomas 
	std::map<std::string, TLanguage>	          m_Languages;            // mapa de mapas con las palabras en cada idioma 
	std::string												          m_sCurrentLanguage;     // idioma actual
  const char *                                m_LanguageXMLPath;      // path del archivo xml donde se guarda un idioma
};

#endif //INC_LANGUAGE_MANAGER_H_