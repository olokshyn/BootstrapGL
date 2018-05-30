#version 330 core

in vec3 fragment_world_position;
in vec3 fragment_normal;
in vec2 diffuse_map_coords;

out vec4 frag_color;

struct LightProperties
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirectionalLight
{
    vec3 direction;
    LightProperties properties;
};

struct PointLight
{
    vec3 position;
    LightProperties properties;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    PointLight light;
    vec3 direction;
    float cut_off;
    float outer_cut_off;
    bool enabled;
};

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct FragmentLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectionalLight directional_light;
uniform PointLight point_light;
uniform SpotLight spot_light;
uniform Material material;

uniform vec3 viewer_position;

void calc_light(inout FragmentLight fragment_light,
                in LightProperties light_properties,
                float light_intensity,
                in vec3 light_direction,
                in vec3 view_direction,
                float shininess)
{
    fragment_light.ambient += light_properties.ambient
                              * light_intensity;

    vec3 norm = normalize(fragment_normal);
    fragment_light.diffuse += light_properties.diffuse
                              * light_intensity
                              * max(dot(norm, light_direction), 0.0);

    vec3 reflect_direction = normalize(reflect(-light_direction, norm));
    fragment_light.specular += light_properties.specular
                               * light_intensity
                               * pow(max(dot(view_direction,
                                             reflect_direction),
                                         0.0),
                                     shininess);
}

float point_light_intensity(in PointLight light)
{
    float distance = length(light.position - fragment_world_position);
    return 1.0 / (light.constant + light.linear * distance +
                  light.quadratic * (distance * distance));
}

float spot_light_intensity(in SpotLight light)
{
    float theta = dot(normalize(light.light.position - fragment_world_position),
                      normalize(-light.direction));
    float epsilon = light.cut_off - light.outer_cut_off;
    return clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);
}

float _replace_value(float old_value, float new_value)
{
    return old_value > 0.0 ? new_value : new_value;
}

void main()
{
    FragmentLight fragment_light;
    fragment_light.ambient = vec3(0.0);
    fragment_light.diffuse = vec3(0.0);
    fragment_light.specular = vec3(0.0);

    vec3 view_direction = normalize(viewer_position - fragment_world_position);

    calc_light(fragment_light,
               point_light.properties,
               point_light_intensity(point_light),
               normalize(point_light.position - fragment_world_position),
               view_direction,
               material.shininess);


    calc_light(fragment_light,
               directional_light.properties,
               1.0,
               -directional_light.direction,
               view_direction,
               material.shininess);

    if (spot_light.enabled)
    {
        calc_light(fragment_light,
                   spot_light.light.properties,
                   min(spot_light_intensity(spot_light),
                       point_light_intensity(spot_light.light)),
                   -spot_light.direction,
                   view_direction,
                   material.shininess);
    }

    fragment_light.ambient *= texture(material.diffuse, diffuse_map_coords).rgb;
    fragment_light.diffuse *= texture(material.diffuse, diffuse_map_coords).rgb;
    fragment_light.specular *= texture(material.specular, diffuse_map_coords).rgb;

    frag_color = vec4(fragment_light.ambient
                      + fragment_light.diffuse
                      + fragment_light.specular,
                      1.0);

}
