#version 450 core

layout(location = 0) in vec2 VS_Texcoord;

layout(binding = 0) uniform sampler g_Sampler;
layout(binding = 1) uniform texture2D g_Texture;

layout(location = 0) out vec4 g_OutColor;

void main()
{
    g_OutColor = texture(sampler2D(g_Texture, g_Sampler), VS_Texcoord);
}
