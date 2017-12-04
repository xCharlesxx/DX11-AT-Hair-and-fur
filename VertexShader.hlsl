struct Input {
	float2 position : POSITION;
	float3 color : COLOR;
};

struct Output {
	float4 position : SV_POSITION;
	float4 world_pos : POSITION; 
	float3 color : COLOR;
};


cbuffer Object :register(b0)
{
	matrix m_model;
}


cbuffer Frame :register(b1)
{
	matrix m_view;
}

Output main(Input input) {
	Output output;

	output.position = mul(input.position, m_model);

	output.position = mul(output.position, m_view);

	output.world_pos = mul(input.position, m_model);

	return output;
}
