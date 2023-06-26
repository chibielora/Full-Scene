#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

out vec3 vertexColor;
out vec2 texCoord;
out vec3 FragPos;
out vec3 FragNormal;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
		
void main()	{
	FragPos = vec3(model * vec4(position, 1.0));
	FragNormal = mat3(transpose(inverse(model))) * normal;
	gl_Position = projection * view * vec4(FragPos, 1.0);

	vertexColor = color;
	texCoord = uv;
}