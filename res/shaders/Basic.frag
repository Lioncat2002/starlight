#version 400 core

in vec2 pass_textureCoords;
in vec3 surfaceNormals;
in vec3 toLightVector;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform vec3 lightColor;

void main(){
	vec3 unitNormal =normalize(surfaceNormals);
	vec3 unitLightNormal=normalize(toLightVector);

	float nDotl=dot(unitNormal,unitLightNormal);

	float brightness=max(nDotl,0.5);
	vec3 diffuse=brightness*lightColor;
	out_Color=vec4(diffuse,1.0)*texture(textureSampler,pass_textureCoords);
}