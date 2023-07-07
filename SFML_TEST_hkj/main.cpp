#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <set>
#include <iostream>
using namespace sf;
using namespace std;
struct line_s {
	double x1;
	double y1;
	double x2;
	double y2;
};
int main()
{
	RenderWindow window(VideoMode(1000, 1000), "SFML works!", Style::Fullscreen);
	vector<vector<line_s>> koh(1);
	koh[0].push_back({200, 300, 1000, 300});
	koh[0].push_back({ 200, 300, 600, 893 });
	koh[0].push_back({ 600, 893, 1000, 300 });
	int sost = 0;
	bool fl = 1;
	while (window.isOpen())
	{
		Event event;
		if (fl) {
			window.clear();
			if (sost >= koh.size()) {
				vector<line_s> l_koh;
				for (long long i = 0; i < koh[sost - 1].size(); i++) {
					double x1 = koh[sost - 1][i].x1;
					double x2 = koh[sost - 1][i].x2;
					double y1 = koh[sost - 1][i].y1;
					double y2 = koh[sost - 1][i].y2;
					double x3 = x1 + (x2 - x1) / 3.;
					double y3 = y1 + (y2 - y1) / 3.;
					double y4 = y1 + 2 * (y2 - y1) / 3.;
					double x4 = x1 + 2 * (x2 - x1) / 3.;
					double l = sqrt(pow((x1 - x2), 2.) + pow((y1 - y2), 2.));
					double h = l / (2. * sqrt(3));
					double sina = (y2 - y1) / l;
					double cosa = (x2 - x1) / l;
					double x5, y5;
					if (i < koh[sost - 1].size() / 3.) {
						x5 = (x2 + x1) / 2. + h * sina;
						y5 = (y2 + y1) / 2. - h * cosa;
					}
					else {
						x5 = (x2 + x1) / 2. - h * sina;
						y5 = (y2 + y1) / 2. + h * cosa;
					}
					l_koh.push_back({ x1, y1, x3, y3 });
					l_koh.push_back({ x3, y3, x5, y5 });
					l_koh.push_back({ x5, y5, x4, y4 });
					l_koh.push_back({ x4, y4, x2, y2 });
				}
				koh.push_back(l_koh);
			}
			for (int i = 0; i < koh[sost].size(); i++) {
				sf::Vertex line[] =
				{
					sf::Vertex(sf::Vector2f(koh[sost][i].x1, koh[sost][i].y1)),
					sf::Vertex(sf::Vector2f(koh[sost][i].x2, koh[sost][i].y2))
				};
				line->color = Color::Green;
				window.draw(line, 2, Lines);
			}
			sf::ConvexShape convex;
			convex.setPointCount(3);
			convex.setPoint(0, sf::Vector2f(900, 900));
			convex.setPoint(1, sf::Vector2f(950, 925));
			convex.setPoint(2, sf::Vector2f(900, 950));
			window.draw(convex);
			convex.setPoint(0, sf::Vector2f(850, 900));
			convex.setPoint(1, sf::Vector2f(800, 925));
			convex.setPoint(2, sf::Vector2f(850, 950));
			window.draw(convex);
			convex.setPointCount(4);
			convex.setPoint(0, sf::Vector2f(1000, 900));
			convex.setPoint(1, sf::Vector2f(1100, 900));
			convex.setPoint(2, sf::Vector2f(1100, 1000));
			convex.setPoint(3, sf::Vector2f(1000, 1000));
			window.draw(convex);
			fl = 0;
			window.display();
		}
		bool cont = 1;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					long long x = event.mouseButton.x;
					long long y = event.mouseButton.y;
					if (x < 950 && x > 900 && y > 900 && y < 950) {
						if (sost < 9) {
							sost++;
							fl = 1;
						}
					}
					if (x < 850 && x > 800 && y > 900 && y < 950) {
						if (sost > 0) {
							sost--;
							fl = 1;
						}
					}
					if (x < 1100 && x > 1000 && y > 900 && y < 1000) {
						cont = 0;
					}
				}
			}
		}
		if (!cont) {
			break;
		}
	}
	return 0;
}