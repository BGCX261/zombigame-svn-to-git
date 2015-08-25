//----------------------------------------------------------------------------------
// CRenderTextureSceneEffect class
// Author: Javier Gedeón
// Modificada por : Katherine Capdevilla y Miquel Rojas
// Última modificación: Andrea 18/01/11
// Description:
// Esta clase nos permitirá crear efectos de escena que se utilizarán para volcar el
// frame buffer sobre una textura para poder ser utilizada a posteriori.
//----------------------------------------------------------------------------------

#pragma once
#ifndef INC_RENDERTEXTURESCENEEFFECT_H_
#define INC_RENDERTEXTURESCENEEFFECT_H_

#include "Base.h"
#include <string>
#include "Math/Matrix44.h"
#include "SceneEffect.h"
#include <d3dx9.h> 

class CTexture;
class CRenderManager;
class CXMLTreeNode;

class CRenderTextureSceneEffect : public CSceneEffect
{
	protected:
		CTexture *m_Texture;
		LPDIRECT3DSURFACE9 m_Surface;

	public:
		CRenderTextureSceneEffect(CXMLTreeNode &atts);
		~CRenderTextureSceneEffect();
		void CaptureFrameBuffers(CRenderManager *RM);
};

#endif