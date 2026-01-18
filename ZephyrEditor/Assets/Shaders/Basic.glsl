#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjection;
    vec3 u_CameraPosition;
} camera;

// Per-object uniform (set 0, binding 1)
layout(std140, binding = 1) uniform Object
{
    mat4 u_Model;
} object;

out vec3 v_WorldPos;
out vec3 v_Normal;
out vec2 v_TexCoord;

void main()
{
    vec4 worldPos = object.u_Model * vec4(a_Position, 1.0);
    v_WorldPos = worldPos.xyz;
    v_Normal = mat3(object.u_Model) * a_Normal;
    v_TexCoord = a_TexCoord;
    
    gl_Position = camera.u_ViewProjection * worldPos;
}

#type fragment
#version 450 core

in vec3 v_WorldPos;
in vec3 v_Normal;
in vec2 v_TexCoord;

out vec4 FragColor;

layout(std140, binding = 0) uniform Camera
{
    mat4 u_ViewProjection;
    vec3 u_CameraPosition;
} camera;

void main()
{
    // Simple lighting (no material properties yet)
    vec3 normal = normalize(v_Normal);
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0)); // Directional light
    
    // Ambient
    vec3 ambient = vec3(0.3);
    
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.8);
    
    // Simple color based on normal (debug visualization)
    vec3 color = normal * 0.5 + 0.5; // Remap [-1,1] to [0,1]
    
    // Combine
    vec3 result = (ambient + diffuse) * color;
    
    FragColor = vec4(result, 1.0);
}