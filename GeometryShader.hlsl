struct GSOutput
{
	float4 pos : SV_POSITION;
	float4 normal : NORMAL;
};
//
//void newVertexLayer(inout TriangleStream<GSOutput> output, int layer, float4 pos, float4 normal)
//{
//	GSOutput element; 
//	element.pos = mul(pos, m_model);
//	element.normal = mul(normal, m_model); 
//	element.layer = layer; 
//	output.Append(element);
//}
//
//
[maxvertexcount(3)]
void main(triangle float4 input[3] : SV_POSITION, inout TriangleStream<GSOutput> output)
{
//	for (uint i = 0; i < 3; i++)
//	{
//		newVertexLayer(output, input[0].position + (input[0].normal * i), input[0].normal, i);
//		newVertexLayer(output, input[1].position + (input[1].normal * i), input[1].normal, i);
//		newVertexLayer(output, input[2].position + (input[2].normal * i), input[2].normal, i);
//		output.RestartStrip(); 
//	}
}
