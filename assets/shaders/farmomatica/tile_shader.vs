#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;

out vec2 fragTexCoord;

uniform mat4 mvp;
uniform vec2 screenOffset;
uniform float depth;

void main()
{
    fragTexCoord = vertexTexCoord;

    vec3 pos = vertexPosition;
    pos.xy += screenOffset;
    pos.z = depth;

    gl_Position = mvp * vec4(pos, 1.0);
}