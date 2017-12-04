struct Input {
	float3 position : POSITION;
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
	matrix m_projection; 
}

Output main(Input input) {
	Output output;

	output.position = mul(input.position, m_model);

	output.position = mul(output.position, m_view);

	output.position = mul(output.position, m_projection);

	output.world_pos = mul(input.position, m_model);

	return output;
}
