//#include "Lighting.h"
//
//
//
//Lighting::Lighting()
//{
//}
//
//XMFLOAT3 Lighting::ShiftTangent(XMFLOAT3 T, XMFLOAT3 N, float shift)
//{
//	XMFLOAT3 shiftedT = T + shift * N; 
//	return normalize (shiftedT);
//}
//
//float Lighting::StrandSpecular(XMFLOAT3 T, XMFLOAT3 V, XMFLOAT3 L, float exponent)
//{
//	XMFLOAT3 H = normalize(L + V);
//	float dotTH = dot(T, H); 
//	float sinTH = sqrt(1.0f - dotTH*dotTH);
//	float dirAtten = smoothstep(-1f, 0f, dot(T, H));
//	return dirAtten * pow(sinTH, exponent); 
//}
//
//
//
//XMFLOAT4 HairLighting(XMFLOAT3 tangent, XMFLOAT3 normal, XMFLOAT3 lightVec, XMFLOAT3 viewVec, XMFLOAT2 uv, float ambOcc)
//{
//	//Shift tangents
//	float shiftTex = tex2D(tSpecShift, uv) - 0.5;
//	XMFLOAT3 t1 = ShiftTangent(tangent, normal, primaryShift + shiftTex); 
//	XMFLOAT3 t2 = ShiftTangent(tangent, normal, secondaryShift + shiftTex);
//
//	//Diffuse lighting: the lerp shifts the shadow boundary for a softer look 
//	XMFLOAT3 diffuse = saturate(lerp(0.25f, 1f, dot(normal, lightVec))); 
//	diffuse *= diffuseColor;
//
//	//Specular lighting
//	XMFLOAT3 specular = specularColor1 * StrandSpecular(t1, viewVec, lightVec, specExp1); 
//
//	//Add 2nd specular term, modulated with noise texture
//	float specMask = tex2d(tSpecMask, uv); // approximate sparkles using texture
//	specular += specularColor2 * specMask * StrandSpecular(t2, viewVec, lightVec, specExp2); 
//
//	//Final color assembly
//	XMFLOAT3 p1; 
//	float p2; 
//	p1 = (diffuse + specular) * tex2D(tBase, uv) * lightColor; 
//	p1 *= ambOcc; 
//	p2 = tex2D(tAlpha, uv); 
//	return XMFLOAT4(p1.x, p1.y, p1.z, p2); 
//}
