#version 330
in vec2 fragTexCoord;
in vec4 fragColor;


uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;



uniform vec4 nearColor;
uniform vec4 farColor;
uniform float depthPower=2.0;
uniform float maxDepth=10.0;
void main()
{
vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;
float originalDepth=gl_FragCoord.z/gl_FragCoord.w;
 float depth= clamp(pow(originalDepth/maxDepth,depthPower),0,1);
 
finalColor=fragColor*(nearColor+(farColor-nearColor)*depth);
//finalColor=vec4(depth,depth,depth,1.0);
}