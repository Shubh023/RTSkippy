#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform float scale;

void main()
{
   float s = sin(5 * scale);
   gl_Position = vec4(aPos.x + aPos.x * s, aPos.y + aPos.y * s, aPos.z + aPos.z * s, 1.0);
   color = aColor;
}