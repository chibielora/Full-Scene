#include <mesh.h>
#include <iostream>
#include <glm/gtc/constants.hpp>

// Control Shaders and Vertices
Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements) : Mesh(GL_TRIANGLES, vertices, elements) {}
Mesh::Mesh(GLenum mode, std::vector<Vertex>& vertices, std::vector<uint32_t>& elements) : _mode{ mode } {
	// Bind newly generated triangles
	glGenVertexArrays(1, &_vertexArrayObject);
	glGenBuffers(1, &_vertexBufferObject);
	glGenBuffers(1, &_elementBufferObject);

	// Sets up Vertex buffer that requires access in GLU
	glBindVertexArray(_vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>
		(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

	// Sets up Elements buffer that requires access in GLU
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>
		(elements.size() * sizeof(uint32_t)), elements.data(), GL_STATIC_DRAW);

	// Bind Vertex attributes [Position, Size, Type, Normalize Values (Stride in bytes and Offset)]
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Position));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Color));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Normal));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, Uv));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	_elementCount = elements.size();
}

Mesh Mesh::CreateBox(float width, float height, float depth, glm::vec4 color)
{
	std::vector<Vertex> vertices {};
	std::vector<uint32_t> indices {};

	float x0 = -width / 2;
	float x1 = width / 2;
	float y0 = 0;
	float y1 = height;
	float z0 = -depth / 2;
	float z1 = depth / 2;
	glm::vec3 normal;

	// top
	normal = { 0.f, 1.f, 0.f };
	vertices.push_back({
		.Position = { x0, y1, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 0.f }
	});
	vertices.push_back({
		.Position = { x1, y1, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 0.f }
	});
	vertices.push_back({
		.Position = { x0, y1, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 1.f }
	});
	vertices.push_back({
		.Position = { x1, y1, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 1.f }
	});

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	// back
	normal = { 0.f, 0.f, -1.f };
	vertices.push_back({
		.Position = { x0, y0, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 0.f }
	});
	vertices.push_back({
		.Position = { x1, y0, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 0.f }
	});
	vertices.push_back({
		.Position = { x0, y1, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 1.f }
	});
	vertices.push_back({
		.Position = { x1, y1, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 1.f }
	});

	indices.push_back(4);
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(7);

	// right
	normal = { 1.f, 0.f, 0.f };
	vertices.push_back({
		.Position = { x1, y0, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 0.f }
		});
	vertices.push_back({
		.Position = { x1, y0, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 0.f }
		});
	vertices.push_back({
		.Position = { x1, y1, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 1.f }
		});
	vertices.push_back({
		.Position = { x1, y1, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 1.f }
		});

	indices.push_back(8);
	indices.push_back(11);
	indices.push_back(9);
	indices.push_back(8);
	indices.push_back(10);
	indices.push_back(11);

	// front
	normal = { 0.f, 0.f, 1.f };
	vertices.push_back({
		.Position = { x1, y1, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 0.f }
		});
	vertices.push_back({
		.Position = { x0, y1, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 0.f }
		});
	vertices.push_back({
		.Position = { x1, y0, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 1.f }
		});
	vertices.push_back({
		.Position = { x0, y0, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 1.f }
		});

	indices.push_back(12);
	indices.push_back(13);
	indices.push_back(15);
	indices.push_back(12);
	indices.push_back(15);
	indices.push_back(14);

	// left
	normal = { -1.f, 0.f, 0.f };
	vertices.push_back({
		.Position = { x0, y0, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 0.f }
	});
	vertices.push_back({
		.Position = { x0, y0, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 0.f }
	});
	vertices.push_back({
		.Position = { x0, y1, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 1.f }
		});
	vertices.push_back({
		.Position = { x0, y1, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 1.f }
	});

	indices.push_back(16);
	indices.push_back(17);
	indices.push_back(18);
	indices.push_back(16);
	indices.push_back(18);
	indices.push_back(19);

	// bottom
	normal = { 0.f, -1.f, 0.f };
	vertices.push_back({
		.Position = { x1, y0, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 1.f }
		});
	vertices.push_back({
		.Position = { x0, y0, z1 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 1.f }
		});
	vertices.push_back({
		.Position = { x1, y0, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 1.f, 0.f }
		});
	vertices.push_back({
		.Position = { x0, y0, z0 },
		.Color = color,
		.Normal = normal,
		.Uv = { 0.f, 0.f }
		});

	indices.push_back(20);
	indices.push_back(21);
	indices.push_back(23);
	indices.push_back(20);
	indices.push_back(23);
	indices.push_back(22);

	return Mesh(vertices, indices);
}

Mesh Mesh::CreateCircle(float radius, uint32_t sectors, glm::vec4 color) {
	std::vector<Vertex> vertices {};
	std::vector<uint32_t> indices {};

	// center vertex
	vertices.push_back({
		.Position = { 0.f, 0.f, 0.f },
		.Color = color,
		.Normal = { 0.f, 1.f, 0.f },
		.Uv = { 0.5f, 0.5f }
	});

	float angleStep = glm::two_pi<float>() / sectors;
	float angle = 0;

	for (uint32_t i = 1; i <= sectors + 1; i++) {
		float cos = glm::cos(angle);
		float sin = glm::sin(angle);

		angle += angleStep;

		vertices.push_back({
			.Position = { cos * radius, 0.f, sin * radius },
			.Color = color,
			.Normal = { 0.f, 1.f, 0.f },
			.Uv = { cos * 0.5 + 0.5, sin * 0.5 + 0.5 }
		});

		if (i != 1) {
			indices.push_back(i - 1);
			indices.push_back(0);
			indices.push_back(i);
		}
	}

	return Mesh(vertices, indices);
}

Mesh Mesh::CreateCylinder(float height, float topRadius, float bottomRadius, uint32_t sectors, glm::vec4 color)
{
	std::vector<Vertex> vertices = {};
	std::vector<uint32_t> indices;

	float angleDelta = glm::two_pi<float>() / sectors;

	float angle = 0;

	for (uint32_t i = 0; i <= sectors; i++) {
		float cos = glm::cos(angle);
		float sin = glm::sin(angle);

		angle += angleDelta;

		vertices.push_back({
			.Position = { cos * bottomRadius, 0, sin * bottomRadius },
			.Color = color,
			.Normal = { cos, 0.f, sin },
			.Uv = { angle / glm::two_pi<float>(), 0.f}
		});
		vertices.push_back({
			.Position = { cos * topRadius, height, sin * topRadius },
			.Color = color,
			.Normal = { cos, 0.f, sin },
			.Uv = { angle / glm::two_pi<float>(), 1.f}
		});
		if (i == 0) {
			// can't form triangles with one set of vertices
			continue;
		}

		uint32_t b0 = 2 * i - 2,
			t0 = 2 * i - 1,
			b1 = 2 * i,
			t1 = 2 * i + 1;

		// side 1
		indices.push_back(b0);
		indices.push_back(t1);
		indices.push_back(b1);

		// side 2
		indices.push_back(b0);
		indices.push_back(t0);
		indices.push_back(t1);
	}

	return Mesh(vertices, indices);
}

/*
* Sphere code taken from http://www.songho.ca/opengl/gl_sphere.html 
*/
Mesh Mesh::CreateSphere(float radius, uint32_t stacks, uint32_t sectors, glm::vec4 color)
{
	std::vector<Vertex> vertices {};
	std::vector<uint32_t> indices {};

	float x, y, z, xy;
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;

	float sectorStep = glm::two_pi<float>() / sectors;
	float stackStep = glm::pi<float>() / stacks;
	float sectorAngle, stackAngle;

	for (uint32_t i = 0; i <= stacks; ++i)
	{
		stackAngle = glm::half_pi<float>() - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * glm::cos(stackAngle);             // r * cos(u)
		z = radius * glm::sin(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// first and last vertices have same position and normal, but different tex coords
		for (uint32_t j = 0; j <= sectors; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * glm::cos(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * glm::sin(sectorAngle);             // r * cos(u) * sin(v)

			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / static_cast<float>(sectors);
			t = (float)i / static_cast<float>(stacks);

			vertices.push_back({
				.Position = { x, y, z },
				.Color = color,
				.Normal = { nx, ny, nz },
				.Uv = { s, t }
			});
		}
	}

	uint32_t k1, k2;
	for (uint32_t i = 0; i < stacks; ++i)
	{
		k1 = i * (sectors + 1);     // beginning of current stack
		k2 = k1 + sectors + 1;      // beginning of next stack

		for (uint32_t j = 0; j < sectors; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (stacks - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	return Mesh(vertices, indices);
}

void Mesh::Draw() {
	// Bind Buffers
	glBindVertexArray(_vertexArrayObject);

	// Gl draw calls [First Index, How Many Elements Should be Drawn, What Kind of Element]
	glDrawElements(_mode, (GLsizei)_elementCount, GL_UNSIGNED_INT, nullptr);
}