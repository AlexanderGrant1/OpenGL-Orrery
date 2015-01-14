// Specify minimum OpenGL version
#version 400

// Define the vertex attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec3 frag_normals;//done
out vec3 frag_position;//done
out vec3 frag_light_dir;//done
out vec2 ftexcoord;//done
// These are the uniforms that are defined in the application
uniform mat4 model, view, projection;
uniform mat3 normalmatrix;
uniform vec4 lightpos;


void main()
{
	vec4 position_h = vec4(position, 1.0);	// Convert the (x,y,z) position to homogeneous coords (x,y,z,w)
	vec3 light_pos3 = lightpos.xyz;			

	// Define our vectors to calculate diffuse and specular lighting
	mat4 mv_matrix = view * model;		// Calculate the model-view transformation
	frag_position = vec3(mv_matrix * position_h);	// Modify the vertex position (x, y, z, w) by the model-view transformation

	mat4 N4 = inverse(transpose(mv_matrix));
	mat3 N3 = mat3(N4);
	frag_normals = normalize(N3 * normal);
	frag_light_dir = light_pos3 - frag_position.xyz;		// Calculate the vector from the light position to the vertex in eye space

	gl_Position = (projection * view * model) * position_h;
	ftexcoord = texcoord;
}



