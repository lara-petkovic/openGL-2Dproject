#version 330 core

in vec2 chTex;
out vec4 outCol;

uniform sampler2D uTex;
uniform vec4 circleColor;

//helicopters
uniform vec2 pointPositions[5];
uniform float pointRadii[5];
uniform float pointSpeeds[5];
uniform float pointColorTimers[5];

void main()
{
    float distanceCenter = length(chTex - vec2(0.5, 0.25)); // base
    float circleRadiusCenter = 0.03;

    float distance1 = length(chTex - vec2(0.95, 0.1));
    float circleRadius1 = 0.013;

    float distance2 = length(chTex - vec2(0.92, 0.1));
    float circleRadius2 = 0.013;

    float distance3 = length(chTex - vec2(0.89, 0.1));
    float circleRadius3 = 0.013;

    float distance4 = length(chTex - vec2(0.86, 0.1));
    float circleRadius4 = 0.013;

    float distance5 = length(chTex - vec2(0.83, 0.1));
    float circleRadius5 = 0.013;

    float distance6 = length(chTex - vec2(0.80, 0.1));
    float circleRadius6 = 0.013;

    float distance7 = length(chTex - vec2(0.77, 0.1));
    float circleRadius7 = 0.013;

    float distanceCityCenter = length(chTex - vec2(0.71, 0.53));
    float circleRadiusCityCenter = 0.007;

    // Adjust horizontal distance between circles
    float horizontalDistance = 0.04;


    for (int i = 0; i < 5; ++i) {
        // Raèunanje distance izmeðu taèke i piksela
        float distancePoint = length(chTex - pointPositions[i]);
        float pulsatingColor = 0.5 + 0.5 * sin(pointColorTimers[i] * distancePoint);


        // Ako je piksel unutar radijusa pulsirajuæe taèke
        if (distancePoint < pointRadii[i])
        {
            // Pulsacija boje od crvene do bele i nazad
            vec3 pulsatingColorRGB = vec3(1.0, pulsatingColor, pulsatingColor);
            outCol = vec4(pulsatingColorRGB, 1.0);
            return; // Koristimo 'return' umesto 'break' kako bismo odmah prekinuli funkciju
        }
    }


    if (distanceCenter < circleRadiusCenter ||
        distance1 < circleRadius1 ||
        distance2 < circleRadius2 ||
        distance3 < circleRadius3 ||
        distance4 < circleRadius4 ||
        distance5 < circleRadius5 ||
        distance6 < circleRadius6 ||
        distance7 < circleRadius7)
    {
        outCol = circleColor;
    }
    else if (distanceCityCenter < circleRadiusCityCenter)
    {
        // Set color for the city center dot (black color)
        outCol = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        outCol = texture(uTex, chTex);
    }
}
