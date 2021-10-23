struct VS_Input
{
  float3 pos : Position;
};

cbuffer Model : register(b0)
{
  float4x4 model;
};

cbuffer View : register(b1)
{
  float4x4 view;
};

cbuffer Proyection : register(b2)
{
  float4x4 proj;
};

float4 main(VS_Input input) : SV_Position
{
  float4 wPos = mul(float4(input.pos.xyz, 1.0f), model);
  float4 vPos = mul(float4(wPos.xyz, 1.0f), view);
  float4 pPos = mul(float4(vPos.xyz, 1.0f), proj);
  return float4(pPos.xyz, 1.0f);
}