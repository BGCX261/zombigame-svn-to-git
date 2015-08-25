//----------------------------------------------------------------------------------
// CMapManager class
// Author: Jordi Arnal
//
// Description:
// Template class for creating Map Managers
//----------------------------------------------------------------------------------
#pragma once
#ifndef INC_MAP_MANAGER_H_
#define INC_MAP_MANAGER_H_

#include "Base.h"
#include "Logger/Logger.h"
#include <string>
#include <map>

template<class T>
class CMapManager
{
	protected:
		typedef std::map<std::string, T*>			TMapResource;
		TMapResource													m_Resources;  //mapa de recursos

	public:
	  
		virtual T* GetResource(const std::string &Name)
		{
		  //busca en el mapa el nombre del recurso
			std::map<std::string, T*>::iterator iter = m_Resources.find(Name);

      //devuelve el elemento o nulo si no existe
			if(iter == m_Resources.end())
			{
				return NULL;
			}
			else
			{
				return iter->second;
			}
		}

	//Agrega un elemento al mapa.
	virtual void AddResource(const std::string &Name, T *Resource)
	{
	  //si recorre el mapa y no lo encuentra, lo añade
		if (m_Resources.find(Name) == m_Resources.end()) 
		{
			m_Resources[Name]=Resource;
		}
	}
	
	//elimina los elementos del mapa
	void Destroy()
	{
		std::map<std::string, T*>::iterator iter = m_Resources.begin();
    std::map<std::string, T*>::iterator itEnd = m_Resources.end();
    for(; iter != itEnd; ++iter)
    { 
      CHECKED_DELETE(iter->second);
    }
    m_Resources.clear();
	}
};

#endif