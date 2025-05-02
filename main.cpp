#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
#include <iostream>




using namespace sf;

using namespace std;




int main()

{

	int pixelWidth = VideoMode::getDesktopMode().width;

	int pixelHeight = VideoMode::getDesktopMode().height;

	VideoMode vm(pixelWidth, pixelHeight);

	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

	ComplexPlane mandelbrot_set(pixelWidth, pixelHeight);

	Font font;
	Text text;
	font.loadFromFile("ComicSansMs.ttf");
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::Red);

	while (window.isOpen())

	{

		///Input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					Vector2i location = { event.mouseButton.x ,event.mouseButton.y };
					mandelbrot_set.setCenter(location);
					mandelbrot_set.zoomIn();
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					std::cout << "the Right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					Vector2i location = { event.mouseButton.x ,event.mouseButton.y };
					mandelbrot_set.setCenter(location);
					mandelbrot_set.zoomOut();
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				Vector2i mouseLocation(event.mouseMove.x, event.mouseMove.y);
				mandelbrot_set.setMouseLocation(mouseLocation);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))

		{

			window.close();

		}

		



		///Update

		mandelbrot_set.updateRender();
		mandelbrot_set.loadText(text);


		///Draw

		window.clear();

		window.draw(mandelbrot_set);
		window.draw(text);

		window.display();

	}




}
