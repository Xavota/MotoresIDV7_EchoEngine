struct VS_Input
{
  float3 pos : Position;
};

float4 main(VS_Input input) : SV_Position
{
  return float4(input.pos.xyz, 1.0f);
}