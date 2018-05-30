#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 in_diffuse_map_coords;

out vec3 fragment_world_position;
out vec3 fragment_normal;
out vec2 diffuse_map_coords;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
    fragment_world_position = vec3(model_matrix * vec4(pos, 1.0));
    fragment_normal = mat3(transpose(inverse(model_matrix))) * normal;
    diffuse_map_coords = in_diffuse_map_coords;
    gl_Position = projection_matrix
                  * view_matrix
                  * vec4(fragment_world_position, 1.0f);
}
