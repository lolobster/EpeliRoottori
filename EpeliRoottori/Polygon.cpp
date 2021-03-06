#include "Polygon.h"
#include <array>

Polygon::Polygon(int sides, float radius, float scale, GLfloat rotation, GLfloat posX, GLfloat posY, GLfloat cx, GLfloat cy, GLfloat cz, const char* filePath) //glm::vec2 position, glm::vec3 color)
{
	//texture lataus
	tex.LoadTextures(filePath);

	//varataan tilaa taulukoille
	data = new GLfloat[7 * sides + 7];
	indices = new GLuint[3 * sides];

	GLfloat _rotation = rotation * M_PI/180;
	angle = _rotation;
	//alustetaan arvoja
	this->scale = scale;
	this->sides = sides;
	this->radius = radius;
	numberOfIndices = 0;
	numberOfElements = 0;
	textCoordX = 0;
	textCoordY = 0;
	x = 0;
	y = 0;
	size = sides;
	//theta = 2.0f * M_PI / int(sides);
	counter = 0;

	//t�ytet��n data vertex atribuuteilla, indices oikeilla koordinaateilla
	for (int i = 0; i < sides + 1; i++)
	{
		theta = (i * 2.0f * M_PI / sides) +  (M_PI)/4 + _rotation;
		

		//Textuurit
		if (i != 0)
		{
			textCoordX = cos(theta + ((3 * M_PI) / 2) + _rotation) / 2 + 0.5f;
			textCoordY = sin(theta + ((3 * M_PI) / 2) + _rotation)  / 2 + 0.5f;
		}
		else
		{
			textCoordX = 0.5;
			textCoordY = 0.5;
		}
		//End of Textuurit

		//Indices
		if (i != 0 && i < sides - 1)
		{
			indices[i * 3] = indices[0];
			indices[i * 3 + 1] = indices[i * 3 - 1];
			indices[i * 3 + 2] = i + 2;
			numberOfIndices += 3;
		}
		else if (i == 0)
		{
			indices[0] = 0;
			indices[1] = 1;
			indices[2] = 2;
			numberOfIndices += 3;
		}
		else
		{
			indices[i * 3] = indices[0];
			indices[i * 3 + 1] = indices[i * 3 - 1];
			indices[i * 3 + 2] = 1;
			numberOfIndices += 3;
		}
		//End of indices
		//Position
		x = posX + (radius * sin(theta)) * scale;
		y = posY + (radius * cos(theta)) * scale;

		if (i != 0)
		{
			data[i * 7] = x;
			data[i * 7 + 1] = y;
		}
		else
		{
			data[i * 7] = posX;
			data[i * 7 + 1] = posY;
		}

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
}

Polygon::Polygon(int sides, float radius, float scale, GLfloat rotation, GLfloat posX, GLfloat posY, GLfloat cx, GLfloat cy, GLfloat cz) //glm::vec2 position, glm::vec3 color)
{	
	 data = new GLfloat[7 * sides + 7];
	 indices = new GLuint[3 * sides];


	 numberOfIndices = 0;
	 numberOfElements = 0;
	 textCoordX = 0;
	 textCoordY = 0;
	 x = 0;
	 y = 0;
	 size = sides;
	 //theta = 2.0f * M_PI / int(sides);
	 counter = 0;

	 for (int i = 0; i < sides + 1; i++)
	 { 
		 theta = (i * 2.0f * M_PI / sides);
		 textCoordX = cos(theta) / 2 + 0.5f;
		 textCoordY = sin(theta) / 2 + 0.5f;

		 if (i != 0 && i < sides -1)
		 {
			 indices[i * 3] = indices[0];
			 indices[i * 3 + 1] = indices[i * 3 -1];
			 indices[i * 3 + 2] = i + 2;	
			 numberOfIndices += 3;
		 }		
		 else if (i == 0)
		 {
			 indices[0] = 0;
			 indices[1] = 1;
			 indices[2] = 2;
			 numberOfIndices += 3;
		 }
		 else
		 {
			 indices[i * 3] = indices[0];
			 indices[i * 3 + 1] = indices[i * 3 - 1];
			 indices[i * 3 + 2] = 1;
			 numberOfIndices += 3;
		 }

		 
		 x = posX + (radius * sin(theta)) * scale;
		 y = posY + (radius * cos(theta)) * scale;

		 if (i != 0)
		 {
			 data[i * 7] = x;
			 data[i * 7 + 1] = y;
		 }
		 else
		 {
			 data[i * 7] = posX;
			 data[i * 7 + 1] = posY;
		 }

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
//	delete[] data;
//	delete[] indices;
}

void Polygon::Update()
{

}

void Polygon::PrintData()
{
	int element = 0;
	int counter = 1;
	std::cout << "------start------" << std::endl;
	for (int i = 0; i < 7 + size * 7 * (sizeof((data)) / sizeof((data[0]))); i++)
	{
		if (element > 6)
		{
			element = 0;
		}

		if (element == 0)
		{
			std::cout << "Position X : " << data[i] << std::endl;
		}
		else if (element == 1)
		{
			std::cout << "Position Y : " << data[i] << std::endl;
		}
		else if (element == 2)
		{
			std::cout << "Color X : " << data[i] << std::endl;
		}
		else if (element == 3)
		{
			std::cout << "Color Y : " << data[i] << std::endl;
		}
		else if (element == 4)
		{
			std::cout << "Color Z : " << data[i] << std::endl;
		}
		else if (element == 5)
		{
			std::cout << "TexCoord X: "<< data[i] << std::endl;
		}
		else if (element == 6)
		{
			std::cout << "TextCoord Y: "<<data[i] << std::endl;
		}
		element++;
		
	}

	std::cout << "--------indices--------" << std::endl;

	for (int i = 0; i < 3 * size * (sizeof((data)) / sizeof((data[0]))); i++)
	{
		std::cout << indices[i] << ", ";

		if (counter == 3)
		{
			std::cout << std::endl;
			counter = 0;
		}

		counter++;
	}
	std::cout << "-------end------" << std::endl;

}

GLfloat Polygon::GetX()
{
	return x;
}
GLfloat Polygon::GetY()
{
	return y;
}

GLfloat Polygon::GetTextCoordX()
{
	return textCoordX;
}
GLfloat Polygon::GetTextCoordY()
{
	return textCoordY;
}

GLfloat Polygon::GetColorX()
{
	return colorX;
}
GLfloat Polygon::GetColorY()
{
	return colorY;
}
GLfloat Polygon::GetColorZ()
{
	return colorZ;
}

int Polygon::GetSize()
{
	return size;
}

GLuint* Polygon::GetIndices()
{
	return indices;
}

GLfloat* Polygon::GetData()
{
	return data;
}

GLuint Polygon::GetNumberOfElements()
{
	return numberOfElements;
}

GLuint Polygon::GetNumberOfIndices()
{
	return numberOfIndices;
}

GLuint Polygon::GetTexture()
{
	return tex.GetID();
}

void Polygon::DemoEffect(GLfloat degree)
{
	GLfloat _rotation = 0;
	_rotation = (degree * M_PI / 180);  //radiaaneiksi
	angle += _rotation;
	GLfloat _x = 0;
	GLfloat _y = 0;
	//t�ytet��n data vertex atribuuteilla, indices oikeilla koordinaateilla
	for (int i = 0; i < sides + 1; i++)
	{
		//Tekstuurit
		theta = (angle * i * 2.0f * M_PI / sides) + (M_PI) / 4 + _rotation;	

		if (i != 0)
		{
			textCoordX = cos(theta + ((3 * M_PI) / 2) + _rotation) / 2 + 0.5f;
			textCoordY = sin(theta + ((3 * M_PI) / 2) + _rotation) / 2 + 0.5f;
		}
		else
		{
			textCoordX = 0.5;
			textCoordY = 0.5;
		}
		//Tekstuurit End

		//Position
		_x = x + (radius * sin(theta)) * scale;
		_y = y + (radius * cos(theta)) * scale;
		_x += _rotation;
		_y += _rotation;


		if (i != 0)
		{
			data[i * 7] = _x;
			data[i * 7 + 1] = _y;
		}
		else
		{
			data[i * 7] = this->x;
			data[i * 7 + 1] = this->y;
		}
		//Position End
	}
}

void Polygon::Rotate(GLfloat degree)
{
	

	GLfloat _rotation = 0;
	_rotation = (degree * M_PI / 180);  //radiaaneiksi
	angle += _rotation;
	//GLfloat _x = 0;
	//GLfloat _y = 0;
	////t�ytet��n data vertex atribuuteilla, indices oikeilla koordinaateilla
	//for (int i = 0; i < sides + 1; i++)
	//{
	//	//Tekstuurit
	//	theta = (angle * i * 2.0f * M_PI / sides) + (M_PI) / 4 + _rotation;

	//	if (i != 0)
	//	{
	//		textCoordX = cos(theta + ((3 * M_PI) / 2) + _rotation) / 2 + 0.5f;
	//		textCoordY = sin(theta + ((3 * M_PI) / 2) + _rotation) / 2 + 0.5f;
	//	}
	//	else
	//	{
	//		textCoordX = 0.5;
	//		textCoordY = 0.5;
	//	}
		//Tekstuurit End

		//Position
		//_x = x + (radius * sin(theta)) * scale;
		//_y = y + (radius * cos(theta)) * scale;
		//_x += _rotation;
		//_y += _rotation;

		
	//glTranslatef(-radius / 2, -radius / 2, 0);
		//glRotatef(_rotation, x, y, 0.0f);
		//glTranslatef(+radius / 2, +radius / 2, 0);

		//if (i != 0)
		//{
		//	data[i * 7] = _x;
		//	data[i * 7 + 1] = _y;
		//}
		//else
		//{
		//	data[i * 7] = this->x;
		//	data[i * 7 + 1] = this->y;
		//}
		//Position End
	//}
}

void Polygon::Translate(glm::vec2 value)
{
	for (int i = 0; i < sides + 1; i++)
	{
		data[i * 7] += value.x;
		data[i * 7 + 1] += value.y;
	}
}