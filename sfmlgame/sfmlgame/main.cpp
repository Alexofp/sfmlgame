#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include <vector> 
#include <algorithm>
#include <string>

int main()
{
	srand(time(NULL));

	int SIZE_WINDOW = 800;
	int POS = SIZE_WINDOW - 30;

	sf::RenderWindow window(sf::VideoMode(SIZE_WINDOW, SIZE_WINDOW), "WOW DOGE!");
	sf::Font font;
	font.loadFromFile("sansation.ttf");


	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(25);
	sf::Text score = text;
	score.setFillColor(sf::Color::Yellow);
	score.setCharacterSize(15);

	sf::Text health = score;
	health.setPosition(SIZE_WINDOW, 0);
	health.setString("HP: 0");



	text.setPosition(sf::Vector2f(SIZE_WINDOW / 2, SIZE_WINDOW / 2));



	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	sf::CircleShape shape(100.f);


	sf::RectangleShape box;
	box.setSize(sf::Vector2f(30,8));
	box.setFillColor(sf::Color::Red);
	box.setPosition(sf::Vector2f(100, POS));
	box.setOrigin(box.getSize()/2.f);

	std::vector<sf::CircleShape> shapes;
	bool lose = false;
	setlocale(LC_ALL, "rus");

	int frame = 0;
	int ct = 0;
	int hp = 3;

	while (window.isOpen())
	{
		ct++;
		frame--;
		if(frame < 0)
		{
			frame = rand() % 5 + 2;
			int count = rand() % 4;
			for (int i = 0; i < count; i++) {
				sf::CircleShape crap(2.f);
				float posX = rand() % SIZE_WINDOW;
				crap.setPosition(sf::Vector2f(posX, 0));
				shapes.push_back(crap);
			}
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && box.getPosition().x - box.getSize().x / 2 > 0)
			box.move(sf::Vector2f(-3, 0));
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && box.getPosition().x + box.getSize().x / 2 < SIZE_WINDOW)
			box.move(sf::Vector2f(3, 0));

		window.clear();

		for (auto &circle : shapes)
		{
			for(int i = 0; i < 4; i++)
			{
				circle.move(0, 1);
				if (circle.getPosition().y == POS)
				{
					int x = circle.getPosition().x;
					int boxX = box.getPosition().x;
					int rightX = boxX + box.getSize().x / 2;
					int leftX = boxX - box.getSize().x / 2;
					if (x > leftX && x < rightX)
					{
						hp--;
						if (hp == 0) {
							lose = true;
							break;
						}
					}
				}
			}


			window.draw(circle);
		}
		shapes.erase(
		std::remove_if(shapes.begin(), shapes.end(), [SIZE_WINDOW](sf::CircleShape &a) {return a.getPosition().y > SIZE_WINDOW; }), shapes.end());

		health.setString("HP: " + std::to_string(hp));
		health.setOrigin(health.getGlobalBounds().width, 0);

		score.setString("Score: " + std::to_string(ct));

		window.draw(score);
		window.draw(health);
		window.draw(box);

		if (lose) {


			text.setString("YOU LOSE!!!!!\nYOUR SCORE " + std::to_string(ct));
			text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);

			window.draw(text);

		}


		window.display();

		if (lose)
		{
			shapes.clear();
			sf::sleep(sf::seconds(5));
			lose = false;
			ct = 0;
		}
		//std::cout << shapes.size() << std::endl;
	}

	return 0;
}