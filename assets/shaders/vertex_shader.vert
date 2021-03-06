
#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coord;
layout(location = 3) in vec4 in_vert_color;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out vec3 world_pos;
out vec3 normal;
out vec2 tex_coord;
out vec4 vert_color;

void main()
{
	mat4 model_view_matrix = view_matrix * model_matrix;

	vec4 model_pos = model_view_matrix * vec4(in_position, 1.0);
	gl_Position = proj_matrix * model_pos;

	vec4 n = model_view_matrix * vec4(in_normal, 0.0);

	world_pos = vec3(model_matrix * vec4(in_position, 1.0));
	normal = mat3(transpose(inverse(model_matrix))) * in_normal;
	tex_coord= in_tex_coord;	
	vert_color = in_vert_color;
}
