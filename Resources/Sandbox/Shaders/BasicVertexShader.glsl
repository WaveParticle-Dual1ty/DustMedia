#version 450 core

layout(location = 0) in vec4 InPosition;
layout(location = 1) in vec4 InColor;
layout(location = 2) in vec2 InTexcoord;

layout(location = 0) out vec4 VS_Color;
layout(location = 1) out vec2 VS_Texcoord;

void main()
{
    gl_Position = InPosition;

    VS_Color = InColor;
    VS_Texcoord = InTexcoord;
}