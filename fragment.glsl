#version 420 core

in vec2 v_tex_coords;

out vec4 color;

uniform sampler2D tex;
uniform mat4 frag_proj;

void main(){
	vec2 final_tex_coords = (frag_proj * vec4(v_tex_coords, 1.0, 1.0)).xy;
	color = texture(tex, final_tex_coords);
	//color = vec4(1.0, 1.0, 1.0, 1.0);
}
