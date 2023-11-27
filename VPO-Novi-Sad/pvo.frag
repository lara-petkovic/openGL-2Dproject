#version 330 core

in vec2 chTex;
out vec4 outCol;

uniform sampler2D uTex; // Zaduzen za teksturu

uniform vec4 circleColor;

// Helikopteri
uniform vec2 pointPositions[5];
uniform float pointRadii[5];
uniform float pointSpeeds[5];
uniform float pointColorTimers[5];

uniform int isSpacePressed;
uniform vec2 blueCirclePosition;

void main()
{
    float distances[8];
    float circleRadii[8];

    distances[0] = length(chTex - vec2(0.5, 0.25));
    circleRadii[0] = 0.03;

    // Broj dronova
    for (int i = 1; i <= 7; ++i)
    {
        distances[i] = length(chTex - vec2(0.95 - 0.03 * float(i - 1), 0.1));
        circleRadii[i] = 0.013;
    }

    distances[7] = length(chTex - vec2(0.71, 0.53));
    circleRadii[7] = 0.007;

    float horizontalDistance = 0.04;
    float distanceBlueCircle;

    if (isSpacePressed == 1)
    {
        distanceBlueCircle = length(chTex - blueCirclePosition);

        if (distanceBlueCircle < 0.013)
        {
            outCol = vec4(0.0, 0.0, 1.0, 1.0);
            return;
        }
    }

    // Pulsiranje helikoptera
    for (int i = 0; i < 5; ++i)
    {
        float distancePoint = length(chTex - pointPositions[i]);
        float dynamicPulsationSpeed = pointSpeeds[i] * (1.0 - distancePoint);
        float pulsatingColor = 0.5 + 0.5 * sin(pointColorTimers[i] + distancePoint * dynamicPulsationSpeed);

        if (distancePoint < pointRadii[i])
        {
            vec3 pulsatingColorRGB = vec3(1.0, 1.0 - pulsatingColor, 1.0 - pulsatingColor);
            outCol = vec4(pulsatingColorRGB, 1.0);
            return;
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        if (distances[i] < circleRadii[i])
        {
            outCol = (i == 7) ? vec4(0.0, 0.0, 0.0, 1.0) : circleColor;
            return;
        }
    }

    outCol = texture(uTex, chTex);
}
