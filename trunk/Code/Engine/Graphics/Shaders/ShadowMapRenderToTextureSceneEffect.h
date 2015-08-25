//----------------------------------------------------------------------------------
// CShadowMapRenderToTextureSceneEffect class
// Author: 
//
// Description:
// Esta clase nos servirá para crear un efecto de escena que realizará un prerenderizado
// de la escena según unas técnicas específicas.
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