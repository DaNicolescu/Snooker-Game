#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 object_color;
uniform float inc_distance;
uniform int do_animation;

// Output value to fragment shader
out vec3 color;

void main()
{
	vec3 new_position = v_position;
	color = object_color;

	if (do_animation == 1) {
		new_position.x += (1 - cos(inc_distance)) / 13.33f;
	}

	gl_Position = Projection * View * Model * vec4(new_position, 1.0);
}
