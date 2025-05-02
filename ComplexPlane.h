#pragma once
#include <complex>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <sstream>

using namespace sf;
using namespace std;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum State {
	CALCULATING,
	DISPLAYING
};

class ComplexPlane : public Drawable
{
public: 
	ComplexPlane(int pixelWidth, int pixelHight);
	void draw(RenderTarget& target, RenderStates states) const override;
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2i mousePixle);
	void loadText(Text& text);
	void updateRender();
	void setMouseLocation(Vector2i mousPixel);

private:
	VertexArray m_vArray;
	State m_State;
	Vector2f m_mouseLocation;
	Vector2i m_pixle_size;
	Vector2f m_plane_center;
	Vector2f m_plane_size;
	int m_zoomCount;
	float m_aspectRatio;

	int countIteration(Vector2f coord);
	void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
	Vector2f mapPixleToCoords(Vector2i mousePixle);
};