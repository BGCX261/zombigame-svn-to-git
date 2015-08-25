//----------------------------------------------------------------------------------
// CShadowMapRenderToTextureSceneEffect class
// Author: 
//
// Description:
// Esta clase nos servir� para crear un efecto de escena que realizar� un prerenderizado
// de la escena seg�n unas t�cnicas espec�ficas.
//----------------------------------------------------------------------------------

#pragma once
#ifndef INC_SHADOWMAP_RENDER_TO_TEXTURE_MANAGER_H_
#define INC_SHADOWMAP_RENDER_TO_TEXTURE_MANAGER_H_

#include "Base.h"
#include <d3dx9.h> 
#include "XML/XMLTreeNode.h"
#include "RenderToTextureSceneEffect.h"


class CRenderManager;
class CProcess;
class CLight;

class CShadowMapRenderToTextureSceneEffect : public CRenderToTextureSceneEffect
{
	private:
		CLight *m_LightShadowCast;

	public:
		CShadowMapRenderToTextureSceneEffect(CXMLTreeNode &atts);
		~CShadowMapRenderToTextureSceneEffect();
		void PreRender(CRenderManager *RM, CProcess *Proc);
};

#endif