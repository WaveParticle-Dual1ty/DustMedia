#version 450 core

layout(location = 0) in vec4 VS_Color;
layout(location = 1) in vec2 VS_Texcoord;

layout(push_constant) uniform PushConsts
{
    vec4 Color;
} g_PushConsts;

layout(binding = 0) uniform sampler2D g_TextureSampler;

layout(location = 0) out vec4 g_OutColor;

void main()
{
    g_OutColor = texture(g_TextureSampler, VS_Texcoord) * g_PushConsts.Color;
}
