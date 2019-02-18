#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;

uniform int check;
uniform float time;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec4 color;
	vec4 anotherColor;
	vec2 newCoord;

	newCoord = texcoord;

	color = texture2D(texture_1, newCoord);

	if (check == 1) {
		anotherColor = texture2D(texture_2, newCoord);
		color = mix(color, anotherColor, 0.5f);
	}

	if (color.w >= 0.5f) {
		out_color = color;
	} else {	
		discard;
	}
}