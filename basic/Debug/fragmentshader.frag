// Minimal fragment shader

#version 420

in vec3 frag_normals;
in vec3 frag_position;
in vec3 frag_light_dir;
in vec2 ftexcoord;
in vec4 frag_colour;
out vec4 outputColor;

uniform sampler2D tex1;
uniform uint applyLighting;
// Global constants (for this vertex shader)
vec3 specular_albedo = vec3(1.0, 0.8, 0.6);
int shininess = 8;
vec3 normalized_light;
void main()
{
	float distanceToLight = length(frag_light_dir);	// For attenuation
	normalized_light = normalize(frag_light_dir);					// Normalise our light vector


	// Calculate the specular component using Phong specular reflection
	vec3 V = normalize(-frag_position.xyz);
	vec3 R = reflect(-normalized_light, frag_normals);
	vec3 specular = pow(max(dot(R, V), 0.0), shininess) * specular_albedo;
	
	// Calculate the attenuation factor;
	float attenuation_k = 0.75;
	float attenuation = 2.4 / (1.0 + attenuation_k * pow(distanceToLight, 2));
	vec4 texture_diffuse = vec4(1.0, 1.0, 1.0, 1.0);//I want white light for the textures since I want their colours to come out clearly
	vec3 diffuse = max(dot(frag_normals, normalized_light), 0.0) * texture_diffuse.xyz;
	vec4 texcolour = texture(tex1, ftexcoord);
	vec4 ambient = vec4(1, 1, 1, 1);
	if(applyLighting == 1)//Lighting is applied to everything except the skybox and the sun
	{
		vec4 texture_diffuse = vec4(diffuse,1) * texcolour;

		outputColor = attenuation * (texture_diffuse + vec4(specular, 1));
		//I'm only using specular and diffuse since I don't want an ambient colour.  
		//I think the scene looks far beter without an ambient colour with more focus on the texture colour
	}
	else
	{
		//At the moment this is only used for the skybox and sun.  I want them to show fully regardless of light positions
		outputColor = texcolour;
	}
}