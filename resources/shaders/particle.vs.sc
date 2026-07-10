$input a_position, a_color0, a_texcoord0, i_data0, i_data1
$output v_color0, v_texcoord0

#include <bgfx_shader.sh>

void main()
{
    vec2  instancePos = i_data0.xy;
    float rotation    = -(i_data0.z * 0.01745329252f);
    float size        = i_data0.w;

    vec2 localPos = a_position.xy * size;

    float s = sin(rotation);
    float c = cos(rotation);
    mat2 rotMat = mat2(c, -s, 
                       s,  c);
    localPos = mul(rotMat, localPos);

    vec3 worldPosition = vec3(localPos + instancePos, a_position.z);

    gl_Position = mul(u_modelViewProj, vec4(worldPosition, 1.0));

    v_color0    = i_data1; 
    v_texcoord0 = a_texcoord0;
}