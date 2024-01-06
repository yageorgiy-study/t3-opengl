#version 400

flat in vec3 colour; //flat = без градиента
// uniform vec3 prog_color;
out vec4 frag_colour;

void main() {
    frag_colour = vec4 (colour, 1.0f);
//   frag_colour = vec4 (prog_color, 1.0f);
}
