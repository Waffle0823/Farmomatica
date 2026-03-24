#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

void main()
{
    vec4 color = texture(texture0, fragTexCoord) * colDiffuse;

    if (color.a < 0.1)
        discard;

    finalColor = color;
}