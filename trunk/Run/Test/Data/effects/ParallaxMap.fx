#ifndef INC_PARALLAXMAP_H_
#define INC_PARALLAXMAP_H_

#include "lights.fx"


//Efecto ParallaxMap
//--------------------------------------------------
TNORMALMAP_TEXTURED_VERTEX_PS mainVS(TNORMALMAP_TEXTURED_VERTEX_VS IN)
{
	TNORMALMAP_TEXTURED_VERTEX_PS l_OUT=(TNORMALMAP_TEXTURED_VERTEX_PS)0;
	l_OUT.HPosition = mul(IN.Position, g_WorldViewProjectionMatrix);
	l_OUT.UV = IN.UV;
	
	l_OUT.WorldTangent = mul(IN.Tangent, g_WorldMatrix);
	l_OUT.WorldTangent = -l_OUT.WorldTangent;
	l_OUT.WorldBinormal = mul(cross(IN.Tangent, IN.Normal), g_WorldMatrix);
	l_OUT.WorldNormal = mul(IN.Normal, g_WorldMatrix);
	l_OUT.WorldPosition = mul(IN.Position, g_WorldMatrix);
	
	return l_OUT;
}

 float3 CalcParallaxMap(float3 Vn, float3 WorldNormal, float3 WorldTangent, float3 WorldBinormal, float2 UV, out float2 OutUV)
 {
	 // view directions
	 //float3 Vn = normalize(WorldPosition);
	 float2 l_UV = UV;
	 // parallax code
	 float3x3 tbnXf = float3x3(WorldTangent,WorldBinormal,WorldNormal);
	 float4 l_NormalMapColor = tex2D(NormalTextureSampler,l_UV);
	// float height = l_NormalMapColor.w * 0.06 - 0.03;
	 float height = l_NormalMapColor.w * g_Bump - g_Bump*0.5;
	 OutUV=l_UV + height * mul(tbnXf,Vn).xy;
	 // normal map
	 float3 tNorm = l_NormalMapColor.xyz - float3(0.5,0.5,0.5);
	 // transform tNorm to world space
	 tNorm = normalize(tNorm.x*WorldTangent - tNorm.y*WorldBinormal + tNorm.z*WorldNormal);
	 return tNorm;
 }
 float4 mainPS(TNORMALMAP_TEXTURED_VERTEX_PS IN):COLOR 
 {
	float3 Nn = normalize(IN.WorldNormal);
	float3 Tn = normalize(IN.WorldTangent);
	float3 Bn = normalize(IN.WorldBinormal);
	float2 l_UV;
	float3 Vn = normalize(g_CameraPosition - IN.WorldPosition);
	Nn = CalcParallaxMap(Vn, Nn, Tn, Bn, IN.UV, l_UV);

	float3x3 worldToTangentSpace;
    worldToTangentSpace[0] = IN.WorldTangent;
    worldToTangentSpace[1] = IN.WorldBinormal;
    worldToTangentSpace[2] = IN.WorldNormal;
	
	
	float4 l_DiffuseColor = tex2D(DiffuseTextureSampler, l_UV);
	float3 l_Ambient = g_LightAmbient.xyz * g_LightAmbient.w;
    
	float3 l_TotalDiffuseValue=0;
	float3 l_TotalSpecularValue=0;
	//CalcLightingForBumMap(l_Ambient, l_DiffuseColor, Nn, IN.WorldPosition, worldToTangentSpace,l_TotalDiffuseValue, l_TotalSpecularValue);
	
	//return l_DiffuseColor2 * (l_Ambient + float4(l_TotalDiffuseValue + l_TotalSpecularValue, 1));
	//float3 l_Ambient = g_LightAmbient*g_LightAmbientColor*l_DiffuseColor.xyz;
	// return float4(l_Ambient+l_TotalDiffuseValue+l_TotalSpecularValue,l_DiffuseColor.a);
	return l_DiffuseColor;
}
technique ParallaxTechnique {
	pass p0 {
		CullMode = None;
		VertexShader = compile vs_3_0 mainVS();
		PixelShader = compile ps_3_0 mainPS();
	}
}
//--------------------------------------------------

#endif