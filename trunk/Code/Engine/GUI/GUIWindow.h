//----------------------------------------------------------------------------------
// CGUIWindow class
// Author: Enric Vergara
//
// Description:
// Esta clase gestiona el pintado y update de una ventana de la GUI. Esta ventana es simplemente una agrupacion
// de GuiElements que se lee al inicio de la aplicacion de un fichero .xml
//----------------------------------------------------------------------------------
#pragma once
#ifndef INC_GUI_WINDOW_H
#define INC_GUI_WINDOW_H

#include "GuiElement.h"
#include <string>
#include <vector>
#include <map>
#include "Math/MathUtils.h"


//---Forward Declarations---
class CTexture;
class CButton;
class CCheckButton;
class CXMLTreeNode;
class CTextureManager;
class CSlider;
class CDialogBox;
class CEditableTextBox;
class CRadioBox;
class CImage;
class CAnimatedImage;
class CProgressBar;
class CStaticText;
//--------------------------

class CGUIWindow
{

	public:
		CGUIWindow(): m_sLuaCode_OnKeyDown (""), m_uInputKeyDown(0), m_sLuaCode_OnUpdateWindows(""), m_sWindowsName(""),
								m_sLuaCode_OnLoadWindows(""), m_sLuaCode_OnSaveWindows("") {}
		virtual ~CGUIWindow();

		void	Render						(CRenderManager *renderManager, CFontManager* fm);
		void	Update						(CInputManager* intputManager, float elapsedTime);
		bool	AddGuiElement				(CGuiElement * inGuiElement);
		bool	ReleaseGuiElement			(const std::string & name);
		void	SetName						(const std::string& name) {m_sWindowsName = name;}

		//--- PARSERFILE FUNCTION ---
		bool	LoadXML						(const std::string &xmlGuiFile, const Vect2i& screenResolution);
		void	RegisterElements		(std::map<std::string,CGuiElement*>& elements);
		void	LoadWindows					();
		void	SaveWindows					();

	private:
		void	IsKeyDown					(CInputManager* intputManager);	

		void	LoadButton					(CButton** button, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
		void	LoadCheckButton			(CCheckButton** checkButton, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
		void	LoadSlider					(CSlider** slider, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
		void	LoadDialogBox				(CDialogBox** dialogBox, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
		void	LoadEditableTextBox	(CEditableTextBox** editableTextBox, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
		void	LoadRadioBox				(CRadioBox** radioBox, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
		void	_LoadImage					(CImage** image, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
    void  LoadAnimatedImage   (CAnimatedImage** image_aux, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
		void	LoadProgressBar			(CProgressBar** progressBar, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);
		void	LoadStaticText			(CStaticText** staticText, CXMLTreeNode& pNewNode, const Vect2i& screenResolution, CTextureManager* tm);

	private:
		std::vector<CGuiElement*>			m_GuiElementsVector;
		std::string							m_sLuaCode_OnSaveWindows;
		std::string							m_sLuaCode_OnLoadWindows;
		std::string							m_sLuaCode_OnKeyDown;
		std::string							m_sLuaCode_OnUpdateWindows;
		uint32								m_uInputKeyDown;
		std::string							m_sWindowsName;
};

#endif //INC_GUI_WINDOW_H