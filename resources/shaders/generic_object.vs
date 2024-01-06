#version 400

in vec3 vertex_position;
in vec3 vertex_colour;
flat out vec3 colour; //flat = без градиента

// uniform vec3 prog_color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
//   colour = prog_color;
    colour = vertex_colour;
    gl_Position = projection * view * model * vec4(vertex_position, 1.0f);
}
