#include "Polygon.h"
#include <array>

Polygon::Polygon(int sides, float radius, float scale, GLfloat rotation, GLfloat posX, GLfloat posY, GLfloat cx, GLfloat cy, GLfloat cz) //glm::vec2 position, glm::vec3 color)
{	
	 data = new GLfloat[7 * sides];
	 indices = new GLuint[sides];

	 numberOfElements = 0;
	 textCoordX = 0;
	 textCoordY = 0;
	 x = 0;
	 y = 0;
	 size = sides;
	 theta = 2.0f * M_PI / int(sides);
	 counter = 0;

	 for (int i = 0; i < sides; i++)
	 { 
		 indices[i] = i;
		 angle = i * sides;
		 x = posX + (radius * sin(angle)) * scale;
		 y = posY + (radius * cos(angle)) * scale;

		 if (counter == 0)
		 {
			 textCoordX = 0;
			 textCoordY = 0;
		 }
		 else if (counter == 1)
		 {
			 textCoordX = 0;
			 textCoordY = 1;
		 }
		 else if (counter == 2)
		 {
			 textCoordX = 1;
			 textCoordY = 1;
		 }
		 else if (counter == 3)
		 {
			 textCoordX = 1;
			 textCoordY = 0;
		 }
		 else
		 {
			 counter = 0;
		 }

		 data[i * 7]	 = x;
		 data[i * 7 + 1] = y;
		 //data[i * 8 + 2] = 0;//position Z
		 data[i * 7 + 2] = cx;
		 data[i * 7 + 3] = cy;
		 data[i * 7 + 4] = cz;
		 data[i * 7 + 5] = textCoordX;
		 data[i * 7 + 6] = textCoordY;		 

		 counter++;
		 if (counter > 3)
		 {
			 counter = 0;
		 }		 

		 numberOfElements += 7;

	 }
	 //printData();

}

Polygon::~Polygon()
{
	//delete[] data;
	//delete[] indices;
}

void Polygon::update()
{

}

void Polygon::drawSquare(glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color, std::string textureName, Shader *shader)
{
	/*this->shader.Use();
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f* size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));


	model = glm::scale(model, glm::vec3(size, 1.0f));
*/
	shader->Use();

	//glBindTexture(GL_TEXTURE_2D, m_worldmap.TexName());

	//// Right
	//glBegin(GL_QUADS);
	//glNormal3d(1, 0, 0);
	//glTexCoord2f(0, 1);
	//glVertex3dv(c);
	//glTexCoord2f(0, 0);
	//glVertex3dv(b);
	//glTexCoord2f(1, 0);
	//glVertex3dv(f);
	//glTexCoord2f(1, 1);
	//glVertex3dv(g);
	//glEnd();

	glDisable(GL_TEXTURE_2D);


}

/*
void Polygon::drawPolygon(int sides, float radius, float scale, GLfloat rotation, glm::vec2 position, glm::vec3 color, Shader *shader)
{
	//tuohon GL_DRAW  juttuun	
	GLfloat theta = 2.0f * M_PI / int(sides);
	float tangentialFactor = tanf(theta);
	float radialFactor = cosf(theta);
	float x = radius * scale;
	float y = rotation;


	glBegin(GL_POLYGON);
	for (int i = 0; i < sides; i++)
	{
		glVertex2f(x + position.x, y + position.y);

		float ix = -y;
		float iy = x;

		x += ix * tangentialFactor;
		y += iy * tangentialFactor;

		x *= radialFactor;
		y *= radialFactor;

		GLfloat _x = x + position.x;
		GLfloat _y = y + position.y;


		//glTexCoord2f(x + position.x, y + position.y);

		//vertices.push_back(_x);
		//vertices.push_back(_y);

		//vertices.push_back(color.x);
		//vertices.push_back(color.y);
		//vertices.push_back(color.z);


		//glVertexAttrib3f(1, color.x, color.y, color.z);		
		//glColor3f(color.x, color.y, color.z);
	}
	glEnd();



	//loppu


	////std::vector<GLfloat> vertices;
	////std::vector<int> indices;

	//GLfloat *vertices = new GLfloat[sides * 3];
	//GLfloat *textureVerices = new GLfloat[sides * 2];
	//int *indices = new int[sides + 1];

	//angle = rotation;
	//xCenter = 0.0;
	//yCenter = 0.0;
	//GLfloat x = 0.0 + position.x;
	//GLfloat y = 0.0 + position.y;

	//GLfloat theta = 2.0f * M_PI / int(sides);

	//for (int i = 0; i < sides; i++)
	//{
	//	x = xCenter + radius * cos(angle);
	//	y = yCenter + radius * sin(angle);
	//	angle += theta;

	//	indices[i] = i;

	//	vertices[i * 3] = x;			//x
	//	vertices[(i * 3) + 1] = y;		//y
	//	vertices[(i * 3) + 2] = 0.0f;	//z
	//	//vertices.insert(0, x);
	//	//vertices.push_back(y);



	//}


	//

	//std::vector<GLfloat> pos;
	//std::vector<GLfloat>color;
	//std::vector<GLfloat>tex;

	//std::vector<GLfloat> handler;

	////GLfloat vertices[sides];
	////GLuint indices[];

	////glClear(GL_COLOR_BUFFER_BIT);
	////glColor3i(color.x, color.y, color.z);

	////glGenBuffers(1, &vbo);
	////glBindBuffer(GL_ARRAY_BUFFER, vao);
	////glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATUC_DRAW);

	////glDisable(GL_TEXTURE_2D);

	////glBegin(GL_POLYGON);
	//for (int i = 0; i < sides; i++)
	//{
	//	glVertex2f(x + position.x, y + position.y);

	//	float ix = -y;
	//	float iy = x;

	//	x += ix * tangentialFactor;
	//	y += iy * tangentialFactor;

	//	x *= radialFactor;
	//	y *= radialFactor;

	//	GLfloat _x = x + position.x;
	//	GLfloat _y = y + position.y;
	//	
	//	vertices.push_back(_x);
	//	vertices.push_back(_y);

	//	vertices.push_back(color.x);
	//	vertices.push_back(color.y);
	//	vertices.push_back(color.z);

	//	
	//	//glVertexAttrib3f(1, color.x, color.y, color.z);		
	//	//glColor3f(color.x, color.y, color.z);
	//}
	////glEnd();

	//glGenVertexArrays(1, &vao);
	//glGenBuffers(1, &vbo);
	//glGenBuffers(1, &ebo);

	//glBindVertexArray(vao);

	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, sides, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0 );

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);


	//shader->Use();
	//glBindVertexArray(vao);
	//glDrawElements(GL_TRIANGLES, sides, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);



}
*/

void Polygon::drawPolygon(Shader *shader)
{

	GLuint MatrixID = glGetUniformLocation(shader->GetShaderProgram(), "MVP");

























	//GLuint tex = 0;
	//glGenTextures(1, &tex);
	//glBindTexture(GL_TEXTURE_2D, tex);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	//TextureManager texManager;

	//texManager.loadTextures("../data/Dickbutt.png", tex);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	


	//for (int iz = 0; iz < sides; iz++)
	//{
	//	indices[iz] = iz;
	//}

	//glGenVertexArrays(1, &vao);
	//glBindVertexArray(vao);

	//glGenBuffers(1, &vbo);
	//
	//glBindVertexArray(vao);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////position
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);

	////color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);
	//
	////Textures
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//shader->Use();
	//glBindVertexArray(vao);
	//glDrawElements(GL_TRIANGLES, sides, GL_UNSIGNED_INT, 0);
	//glBindVertexArray(0);


	//glBegin(GL_POLYGON);
	//for (int i = 0; i < sides; i++)
	//{
	//	glVertexAttrib3f(1, color.x, color.y, color.z);

	//	glVertex2f(x + position.x, y + position.y);

	//	float ix = -y;
	//	float iy = x;

	//	x += ix * tangentialFactor;
	//	y += iy * tangentialFactor;

	//	x *= radialFactor;
	//	y *= radialFactor;

	//	GLfloat _x = x + position.x;
	//	GLfloat _y = y + position.y;

	//	
	//	
	//	//vertices.push_back(_x);
	//	//vertices.push_back(_y);

	//	//vertices.push_back(color.x);
	//	//vertices.push_back(color.y);
	//	//vertices.push_back(color.z);


	//		
	//	//glColor3f(color.x, color.y, color.z);
	//}
	//glEnd();


	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, 1);
	//glUniform1i(glGetUniformLocation(s.GetShaderProgram(), "myTextureSampler3"), 0);

}


void Polygon::printData()
{
	std::cout << "------start------" << std::endl;
	for (int i = 0; i < 8 * (sizeof((data)) / sizeof((data[0]))); i++)
	{
		std::cout << data[i] << std::endl;
	}

	std::cout << "--------indices--------" << std::endl;

	for (int i = 0; i < size * (sizeof((data)) / sizeof((data[0]))); i++)
	{
		std::cout << indices[i] << std::endl;
	}
	std::cout << "-------end------" << std::endl;

}

GLfloat Polygon::getX()
{
	return x;
}
GLfloat Polygon::getY()
{
	return y;
}

GLfloat Polygon::getTextCoordX()
{
	return textCoordX;
}
GLfloat Polygon::getTextCoordY()
{
	return textCoordY;
}

GLfloat Polygon::getColorX()
{
	return colorX;
}
GLfloat Polygon::getColorY()
{
	return colorY;
}
GLfloat Polygon::getColorZ()
{
	return colorZ;
}

int Polygon::getSize()
{
	return size;
}

GLuint* Polygon::getIndices()
{
	return indices;
}

GLfloat* Polygon::getData()
{
	return data;
}

GLuint Polygon::getNumberOfElements()
{
	return numberOfElements;
}