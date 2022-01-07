#version 140

in vec3 position;

uniform mat4 u_mat;
uniform vec3 orientation;
// uniform float theta;

vec4 quat_mult(vec4 a, vec4 b)
{
    return vec4(
        ((a.w*b.x) + (a.x*b.w) + (a.y*b.z) - (a.z*b.y)), // x
        ((a.w*b.y) - (a.x*b.z) + (a.y*b.w) + (a.z*b.x)), // y
        ((a.w*b.z) + (a.x*b.y) - (a.y*b.x) + (a.z*b.w)), // z
        ((a.w*b.w) - (a.x*b.x) - (a.y*b.y) - (a.z*b.z))  // w
    );
}

vec4 quat_conj(vec4 q)
{
    return vec4(-q.x, -q.y, -q.z, q.w);
}

vec4 quat_inv(vec4 q)
{
    float mag_sqr = q.x*q.x + q.y*q.y + q.z*q.z * q.w*q.w;
    return quat_conj(q)/mag_sqr;
}

vec4 quat_rot(float angle, vec3 axis){
    float half_angle = angle/2;
    float sin_half_angle = sin(half_angle);
    return vec4(
        axis.x * sin_half_angle,
        axis.y * sin_half_angle,
        axis.z * sin_half_angle,
        cos(half_angle)
    );
}

void main(){

    vec4 pos = vec4(position, 1.f);

    vec4 rotx = quat_rot(orientation.z, vec3(0.f, 0.f, 1.f));
    vec4 roty = quat_rot(orientation.y, vec3(0.f, 1.f, 0.f));
    vec4 rotz = quat_rot(orientation.x, vec3(1.f, 0.f, 0.f));

    vec4 rot = quat_mult(rotz,quat_mult(roty,rotx));

    gl_Position = u_mat * quat_mult(rot,quat_mult(pos, quat_conj(rot)));

}