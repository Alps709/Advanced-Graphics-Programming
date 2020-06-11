#version 450 core

#define WORK_GROUP_SIZE 128

layout(local_size_x = WORK_GROUP_SIZE, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding = 0) buffer positionBuffer { vec4 position[]; };
layout(std430, binding = 1)	buffer velocityBuffer { vec4 velocity[]; };
layout(std430, binding = 2)	buffer initVelocityBuffer { vec4 initVelocity[]; };

uniform vec3 u_gravity;
uniform vec3 u_particleSystemPos;
uniform float u_deltaTime;

void main()
{
	uint i = gl_GlobalInvocationID.x;

	velocity[i].xyz += u_gravity;

	position[i].xyz += velocity[i].xyz * u_deltaTime;
	position[i].w -= u_deltaTime;

	if (position[i].w <= 0.0f)
	{
		position[i].xyzw = vec4(u_particleSystemPos, initVelocity[i].w);
		velocity[i] = initVelocity[i];
	}
}