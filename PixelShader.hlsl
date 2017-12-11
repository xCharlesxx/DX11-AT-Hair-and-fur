struct Output {
	float4 position : SV_POSITION;
	float4 world_pos : POSITION;
	float2 TexCoord: TEXCOORD;
	float3 normal : NORMAL;
	float3 color : COLOR;
};
struct Light
{
	float3 dir;
	float3 pos;
	float  range;
	float3 att;
	float4 ambient;
	float4 diffuse;
};
Texture2D ObjTexture;
SamplerState ObjSamplerState;
Light light; 
float4 main(Output input) : SV_TARGET{
	return float4(input.color.r, input.color.g, input.color.b, 1);
}
//float4 main(Output input) : SV_TARGET
//{
//	input.normal = normalize(input.normal);
//
//	float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.TexCoord);
//
//	float3 finalColor = float3(1.0f, 0.0f, 0.0f);
//
//	//Create the vector between light position and pixels position
//	float3 lightToPixelVec = light.pos - input.world_pos;
//
//	//Find the distance between the light pos and pixel pos
//	float d = length(lightToPixelVec);
//
//	//Create the ambient light
//	float3 finalAmbient = diffuse * light.ambient;
//
//	//If pixel is too far, return pixel color with ambient light
//	if (d > light.range)
//	return float4(finalAmbient, diffuse.a);
//
//	//Turn lightToPixelVec into a unit length vector describing
//	//the pixels direction from the lights position
//	lightToPixelVec /= d;
//
//	//Calculate how much light the pixel gets by the angle
//	//in which the light strikes the pixels surface
//	float howMuchLight = dot(lightToPixelVec, input.normal);
//
//	//If light is striking the front side of the pixel
//	if (howMuchLight > 0.0f)
//	{
//		//Add light to the finalColor of the pixel
//		finalColor += howMuchLight * diffuse * light.diffuse;
//
//		//Calculate Light's Falloff factor
//		finalColor /= light.att[0] + (light.att[1] * d) + (light.att[2] * (d*d));
//	}
//
//	//make sure the values are between 1 and 0, and add the ambient
//	finalColor = saturate(finalColor + finalAmbient);
//
//	//Return Final Color
//	return float4(finalColor, diffuse.a);
//}
