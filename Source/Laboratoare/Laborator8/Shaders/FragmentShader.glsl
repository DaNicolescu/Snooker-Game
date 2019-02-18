#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform float cut_off;
uniform int light_type;
uniform vec3 object_color;

layout(location = 0) out vec4 out_color;

void main()
{
	vec3 N = normalize(world_normal);
	vec3 L = normalize( light_position - world_position );
	vec3 V = normalize( eye_position - world_position );
	vec3 H = normalize( L + V );

	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(N, L), 0);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(normalize(N), H), 0), material_shininess);
	}

	
	// TODO: compute light
	float dist; 
	float light;

	float spot_light = dot(-L, light_direction);
	float spot_light_limit = cos(cut_off);

	if (light_type != 0) {
		
		if (spot_light > cos(cut_off)) {
		// fragmentul este iluminat de spot, deci se calculeaza valoarea luminii conform  modelului Phong
		// se calculeaza atenuarea luminii
			float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);
			light = ambient_light + light_att_factor * (specular_light + diffuse_light);
		} else {
			light = ambient_light;
		}
	} else {
		dist = distance(light_position, world_position); 
		light = ambient_light +  1 / (dist * dist) * (specular_light + diffuse_light);
	}


	// TODO: write pixel out color
	out_color = vec4(object_color * light, 1);
}