#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHight)
{
	m_pixle_size.x = pixelWidth;
	m_pixle_size.y = pixelHight;
	m_aspectRatio = static_cast<float>(pixelHight)/pixelWidth;
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_State = State::CALCULATING;
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHight);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}
void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x_size,y_size };
	m_State = CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	int x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size.x = x_size;
	m_plane_size.y = y_size;
	m_State = CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixle)
{
	m_plane_center = mapPixleToCoords(mousePixle);
	m_State = State::CALCULATING;

}
void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	ss << "Mandelbrot Set" << endl
		<< "Center: (" << m_plane_center.x << ',' << m_plane_center.y << ')' << endl
		<< "Cursor: (" << m_mouseLocation.x << ',' << m_mouseLocation.y << ')' << endl
		<< "Left-click to zoom in" << endl
		<< "Right-click to zoom out";
	text.setString(ss.str());
}
void ComplexPlane::updateRender()
{
	if (m_State == CALCULATING)
	{
		//j=x , i=y
		for (int i = 0; i < m_pixle_size.y; i++)
		{
			for (int j = 0; j < m_pixle_size.x; j++)
			{
				m_vArray[j + i * m_pixle_size.x].position = { (float)j,(float)i };
				Vector2i pixle = { j,i };
				Vector2f coord = mapPixleToCoords(pixle);
				int iteration = countIteration(coord); 
				Uint8 r, g, b;
				iterationsToRGB(iteration,r,g,b);
				m_vArray[j + i * m_pixle_size.x].color = { r,g,b };
			}
		}
		m_State = DISPLAYING;
	}
}
void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
	Vector2f coords = mapPixleToCoords(mousPixel);
	m_mouseLocation.x = coords.x;
	m_mouseLocation.y = coords.y;
}

//private helper functoins

int ComplexPlane::countIteration(Vector2f coord)
{
	// x = r, y = i
	complex<double> c( coord.x,coord.y );
	complex<double> z = c;
	int i = 0;
	while (abs(z) < 2.0 && i < 64)
	{
		z = z * z + c;
		i++;
	}
	return i;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count < 8)
	{
		//Electric Purple
		r = 170;
		g = 0;
		b = 255;
	}
	else if (count < 16)
	{
		//Vivid Violet
		r = 73;
		g = 0;
		b = 255;
	}
	else if (count < 24)
	{
		//Electric Indigo
		r = 0;
		g = 24;
		b = 255;
	}
	else if (count < (MAX_ITER / 8) * 4)
	{
		//Bright Azure
		r = 0;
		g = 121;
		b = 255;
	}
	else if (count < (MAX_ITER / 8) * 5)
	{
		//Vivid Sky Blue
		r = 0;
		g = 219;
		b = 255;
	}
	else if (count < (MAX_ITER / 8) * 6)
	{
		//Bright Aqua
		r = 0;
		g = 255;
		b = 194;
	}
	else if (count < (MAX_ITER / 8) * 7)
	{
		//Spring Green
		r = 0;
		g = 255;
		b = 97;
	}
	else if (count < MAX_ITER)
	{
		//Neon Green
		r = 0;
		g = 255;
		b = 0;
	}
	else
	{
		// black
		r = 0;
		g = 0;
		b = 0;
	}
}
Vector2f ComplexPlane::mapPixleToCoords(Vector2i mousePixle)
{
	Vector2f coords;
	coords.x = (static_cast<float>(mousePixle.x) / (m_pixle_size.x - 1)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x * 0.5f);
	coords.y = (1.0f - static_cast<float>(mousePixle.y) / (m_pixle_size.y - 1)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y * 0.5f);
	return coords;
}