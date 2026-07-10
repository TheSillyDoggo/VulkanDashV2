$input a_position, a_color0, a_texcoord0, i_data0, i_data1, i_data2, i_data3, i_data4
$output v_color0, v_texcoord0

#include <bgfx_shader.sh>

float degToRads(float v)
{
    return v * 0.01745329252f;
}

void main()
{
    vec2 inst_pos      = i_data0.xy;
    vec2 inst_scale    = i_data0.zw;
    vec2 inst_rotation = i_data1.xy;
    vec2 inst_skew     = i_data1.zw;
    vec4 inst_uvs      = i_data2;
    vec4 inst_color    = i_data4;
    vec2 inst_size     = i_data3.xy;
    vec2 inst_anchor   = i_data3.zw;

    vec2 localPos = (a_position.xy - inst_anchor) * inst_size;

    float skewXFactor = tan(inst_skew.x);
    float skewYFactor = tan(inst_skew.y);
    
    vec2 scaledSkewedPos;
    scaledSkewedPos.x = (localPos.x + localPos.y * skewXFactor) * inst_scale.x;
    scaledSkewedPos.y = (localPos.y + localPos.x * skewYFactor) * inst_scale.y;

    float cosX = cos(inst_rotation.x);
    float sinX = sin(inst_rotation.x);
    float cosY = cos(inst_rotation.y);
    float sinY = sin(inst_rotation.y);

    vec2 rotatedPos;
    rotatedPos.x = scaledSkewedPos.x * cosX - scaledSkewedPos.y * sinY;
    rotatedPos.y = scaledSkewedPos.x * sinX + scaledSkewedPos.y * cosY;

    vec2 finalPos = rotatedPos + inst_pos;
    gl_Position = mul(u_modelViewProj, vec4(finalPos, 0.0, 1.0));

    v_texcoord0 = mix(inst_uvs.xy, inst_uvs.zw, a_texcoord0.xy);
    v_color0 = inst_color;
}