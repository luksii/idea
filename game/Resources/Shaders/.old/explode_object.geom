#version 420 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float time;
out vec2 TexCoords;

in VS_OUT
{
    vec2 texCoords;
    vec3 normal;
} gs_in[];


vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

vec4 Explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
    return position + vec4(direction, 0.0);
}

void main()
{
    vec3 normal = GetNormal();

    for (int i = 0; i < gl_in.length(); i++)
    {
        gl_Position = Explode(gl_in[i].gl_Position, normal);
        TexCoords = gs_in[i].texCoords;
        EmitVertex();
    }

    EndPrimitive();
}