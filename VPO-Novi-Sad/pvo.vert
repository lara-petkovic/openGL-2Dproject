#version 330 core

layout(location = 0) in vec2 inPos; // Pozicija vrha u prostoru
layout(location = 1) in vec2 inTex; // Teksturne koordinate vrha
out vec2 chTex; // Izlazna promenljiva koja prenosi teksturne koordinate od vertex shadera do fragment shadera.

uniform vec2 blueCirclePosition;

void main()
{
    if (chTex == vec2(0.95, 0.1) ||
        chTex == vec2(0.92, 0.1) ||
        chTex == vec2(0.89, 0.1) ||
        chTex == vec2(0.86, 0.1) ||
        chTex == vec2(0.83, 0.1) ||
        chTex == vec2(0.80, 0.1) ||
        chTex == vec2(0.77, 0.1) ||
        chTex == vec2(0.71, 0.53))
    {
        // Primenjujemo blueCirclePosition na poziciju vertexa
        // gl_Position -> (x,y,z,w) w = 1.0
        // Izlaz sejdera:
        gl_Position = vec4(inPos.x + blueCirclePosition.x, inPos.y + blueCirclePosition.y, 0.0, 1.0);
    }
    else
    {
        gl_Position = vec4(inPos, 0.0, 1.0);
    }
    chTex = vec2((inPos.x + 1.0) * 0.5, (inPos.y + 1.0) * 0.5);
}
