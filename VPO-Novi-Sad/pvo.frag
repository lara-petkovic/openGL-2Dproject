#version 330 core

in vec2 chTex;
out vec4 outCol;

uniform sampler2D uTex;

void main()
{
    float distance = length(chTex - vec2(0.5, 0.25));

    float radius = 0.05;

    if (distance <= radius)
    {
        outCol = vec4(0.0, 1.0, 0.0, 1.0); // Green color
    }
    else
    {
        outCol = texture(uTex, chTex);
    }
}
