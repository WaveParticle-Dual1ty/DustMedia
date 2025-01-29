#version 450 core

layout(location = 0) in vec4 VS_Color;
layout(location = 1) in vec2 VS_Texcoord;

layout(location = 0) out vec4 g_OutColor;

void main()
{
    g_OutColor = vec4(1, 0, 0, 1);
}
