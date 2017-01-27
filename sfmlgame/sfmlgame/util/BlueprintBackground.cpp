#include "BlueprintBackground.h"
#include "GameWindow.h"
#include "Log.h"

BlueprintBackground::BlueprintBackground()
{
	texture = TextureManager::get("blueprint");
	xline.setFillColor(sf::Color(255, 255, 255, 100));
	yline.setFillColor(sf::Color(255, 255, 255, 100));
}


BlueprintBackground::~BlueprintBackground()
{
}

void BlueprintBackground::draw()
{
	sf::RenderWindow& w = GameWindow::getInternalHandle();
	sf::Vector2i ts(100, 100);

	sf::Vector2f p1 = w.mapPixelToCoords(sf::Vector2i(0, 0));
	sf::Vector2f p2 = w.mapPixelToCoords(sf::Vector2i(w.getSize()));

	sf::Vector2i ip1(floor(p1.x/ts.x), floor(p1.y/ts.y));
	sf::Vector2i ip2(ceil(p2.x / ts.x), ceil(p2.y / ts.y));


	if (ip1 != ipos1 || ip2 != ipos2)
	{
		ipos1 = ip1;
		ipos2 = ip2;

		pos1 = p1;
		pos2 = p2;
		update();
	}

	sf::RenderStates states;
	states.texture = texture;

	GameWindow::getInternalHandle().draw(grid, states);

	GameWindow::getInternalHandle().draw(xline);
	GameWindow::getInternalHandle().draw(yline);
}

void BlueprintBackground::update()
{
	grid.clear();

	sf::RenderWindow& w = GameWindow::getInternalHandle();

	sf::Vector2i ts(100, 100);

	sf::Vector2f startPos( floor(pos1.x/ts.x)*ts.x, floor(pos1.y / ts.y)*ts.y);
	sf::Vector2f endPos(ceil(pos2.x / ts.x)*ts.x, ceil(pos2.y / ts.y)*ts.y);

	int countx = (endPos.x - startPos.x)/ ts.x;
	int county = (endPos.y - startPos.y) / ts.y;

	grid.setPrimitiveType(sf::Quads);
	grid.resize(countx*county*4);

	for (int x = 0; x < countx; x++)
	{
		for (int y = 0; y < county; y++)
		{
			sf::Vertex* quad = &grid[(x + y * countx) * 4];

			quad[0].position = sf::Vector2f(startPos.x + x * ts.x, startPos.y + y * ts.y);
			quad[1].position = sf::Vector2f(startPos.x + (x+1) * ts.x, startPos.y + y * ts.y);
			quad[2].position = sf::Vector2f(startPos.x + (x+1) * ts.x, startPos.y + (y+1) * ts.y);
			quad[3].position = sf::Vector2f(startPos.x + x * ts.x, startPos.y + (y+1) * ts.y);

			quad[0].texCoords = sf::Vector2f(0.f,0.f);
			quad[1].texCoords = sf::Vector2f(ts.x,0.f);
			quad[2].texCoords = sf::Vector2f(ts.x, ts.y);
			quad[3].texCoords = sf::Vector2f(0.f, ts.y);
		}
	}

	float linesize = 2.f;

	xline.setPosition(sf::Vector2f((startPos.x+endPos.x)/2.f , 0.f ));
	xline.setSize(sf::Vector2f((endPos.x - startPos.x), linesize));
	xline.setOrigin(xline.getSize() / 2.f);

	yline.setPosition(sf::Vector2f(0.f, (startPos.y + endPos.y) / 2.f));
	yline.setSize(sf::Vector2f(linesize, (endPos.y - startPos.y)));
	yline.setOrigin(yline.getSize() / 2.f);
}
