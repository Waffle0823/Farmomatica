#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

out vec2 fragTexCoord;
out vec4 fragColor;

uniform mat4 mvp;
uniform vec3 tilePos;
uniform vec2 tileDim;
uniform vec2 screenCenter;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;
    
    float isoX = (tilePos.x - tilePos.y) * (tileDim.x / 2.0);
    float isoY = (tilePos.x + tilePos.y) * (tileDim.y / 4.0) - tilePos.z * (tileDim.y / 2.0);
    
    float screenX = isoX + screenCenter.x;
    float screenY = isoY + screenCenter.y;
    
    vec3 transformedPos = vertexPosition;
    transformedPos.x += screenX;
    transformedPos.y += screenY;
    
    vec4 position = mvp * vec4(transformedPos, 1.0);
    
    float depth = 1.0 - (tilePos.x + tilePos.y + tilePos.z) / 1000.0;
    position.z = depth;
    
    gl_Position = position;
}