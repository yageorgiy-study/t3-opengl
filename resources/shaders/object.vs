#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texture;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 normal;
out vec3 f_pos;
out vec2 texture_coords;

void main () {

 	normal = mat3(transpose(inverse(model))) * vertex_normal;
 	f_pos = vec3(model * vec4(vertex_position, 1.0));
	texture_coords = vertex_texture;

	gl_Position = projection * view * model * vec4 (vertex_position, 1.0);
}

