struct VS_Input
{
  float4 pos : SV_Position;
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
  float4 wPos = mul(input.pos, model);
  float4 vPos = mul(wPos, view);
  float4 pPos = mul(vPos, proj);
  return pPos;
}