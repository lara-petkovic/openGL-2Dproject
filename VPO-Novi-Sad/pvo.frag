#version 330 core

in vec2 chTex;
out vec4 outCol;

uniform sampler2D uTex;
uniform vec4 circleColor;

void main()
{
    float distance = length(chTex - vec2(0.5, 0.25));

    float circleRadius = 0.03;

    if (distance < circleRadius)
    {
        outCol = circleColor;
    }
    else
    {
        outCol = texture(uTex, chTex);
    }
}
