#include <Cube.hpp>
#include <Vertex_Array_Object.hpp>
#include <Vertex_Buffer_Object.hpp>
#include <Vertex_Attribute_Information.hpp>

namespace prz
{
	const GLfloat Cube::coordinates_[] =
	{
	   -1.f, +1.f, +1.f,        // 0
	   +1.f, +1.f, +1.f,        // 1
	   +1.f, -1.f, +1.f,        // 2
	   -1.f, -1.f, +1.f,        // 3
	   -1.f, +1.f, -1.f,        // 4
	   -1.f, +1.f, +1.f,        // 5
	   -1.f, -1.f, +1.f,        // 6
	   -1.f, -1.f, -1.f,        // 7
	   +1.f, +1.f, -1.f,        // 8
	   -1.f, +1.f, -1.f,        // 9
	   -1.f, -1.f, -1.f,        // 10
	   +1.f, -1.f, -1.f,        // 11
	   +1.f, +1.f, +1.f,        // 12
	   +1.f, +1.f, -1.f,        // 13
	   +1.f, -1.f, -1.f,        // 14
	   +1.f, -1.f, +1.f,        // 15
	   -1.f, -1.f, +1.f,        // 16
	   +1.f, -1.f, +1.f,        // 17
	   +1.f, -1.f, -1.f,        // 18
	   -1.f, -1.f, -1.f,        // 19
	   -1.f, +1.f, -1.f,        // 20
	   +1.f, +1.f, -1.f,        // 21
	   +1.f, +1.f, +1.f,        // 22
	   -1.f, +1.f, +1.f,        // 23
	};

	const GLfloat Cube::normals_[] =
	{
		0.f,  0.f, +1.f,        // 0
		0.f,  0.f, +1.f,        // 1
		0.f,  0.f, +1.f,        // 2
		0.f,  0.f, +1.f,        // 3
	   -1.f,  0.f,  0.f,        // 4
	   -1.f,  0.f,  0.f,        // 5
	   -1.f,  0.f,  0.f,        // 6
	   -1.f,  0.f,  0.f,        // 7
		0.f,  0.f, -1.f,        // 8
		0.f,  0.f, -1.f,        // 9
		0.f,  0.f, -1.f,        // 10
		0.f,  0.f, -1.f,        // 11
	   +1.f,  0.f,  0.f,        // 12
	   +1.f,  0.f,  0.f,        // 13
	   +1.f,  0.f,  0.f,        // 14
	   +1.f,  0.f,  0.f,        // 15
		0.f, -1.f,  0.f,        // 16
		0.f, -1.f,  0.f,        // 17
		0.f, -1.f,  0.f,        // 18
		0.f, -1.f,  0.f,        // 19
		0.f, +1.f,  0.f,        // 20
		0.f, +1.f,  0.f,        // 21
		0.f, +1.f,  0.f,        // 22
		0.f, +1.f,  0.f,        // 23
	};

	const GLfloat Cube::textureUVs_[] =
	{
		0.f, 0.f,               // 0
		1.f, 0.f,               // 1
		1.f, 1.f,               // 2
		0.f, 1.f,               // 3
		0.f, 0.f,               // 4
		1.f, 0.f,               // 5
		1.f, 1.f,               // 6
		0.f, 1.f,               // 7
		0.f, 0.f,               // 8
		1.f, 0.f,               // 9
		1.f, 1.f,               // 10
		0.f, 1.f,               // 11
		0.f, 0.f,               // 12
		1.f, 0.f,               // 13
		1.f, 1.f,               // 14
		0.f, 1.f,               // 15
		0.f, 0.f,               // 16
		1.f, 0.f,               // 17
		1.f, 1.f,               // 18
		0.f, 1.f,               // 19
		0.f, 0.f,               // 20
		1.f, 0.f,               // 21
		1.f, 1.f,               // 22
		0.f, 1.f,               // 23
	};

	const GLubyte Cube::indices_[] =
	{
		1,  0,  3,              // front
		1,  3,  2,
		5,  4,  7,              // left
		5,  7,  6,
		9,  8,  11,             // back
		9,  11, 10,
		13, 12, 15,             // right
		13, 15, 14,
		17, 16, 19,             // top
		17, 19, 18,
		20, 23, 22,             // bottom
		20, 22, 21,
	};

	Cube::Cube(const PString& name) :
		Mesh(Primitive_Mode::TRIANGLES, sizeof(indices_), Indices_Type::UNSIGNED_BYTE, name)
	{
		unsigned int nCoordinates = sizeof(coordinates_);

		PList< PVAI > vertexAttributes =
		{
			PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(coordinates_,  sizeof(coordinates_), 3)), VBO_ORDER::COORDINATES),
			PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(normals_,  sizeof(normals_), 3)), VBO_ORDER::NORMALS),
			PVAI(PSPtr< PVBO >(std::make_shared< PVBO >(textureUVs_, sizeof(textureUVs_), 2)), VBO_ORDER::TEXTURE_COORD)
		};

		vao_ = std::make_shared< PVAO >
		(
			vertexAttributes,
			PSPtr< PVBO >(std::make_shared< PVBO >(indices_, nVertices_, 1, Vertex_Buffer_Object::Target::ELEMENT_ARRAY_BUFFER))
		);
	}
}