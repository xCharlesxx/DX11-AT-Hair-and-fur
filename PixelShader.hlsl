struct Output {
	float4 position : SV_POSITION;
	float4 world_pos : POSITION;
	float3 color : COLOR;
};

float4 main(Output input) : SV_TARGET{
	return float4(input.color.r, input.color.g, input.color.b, 1);
}
