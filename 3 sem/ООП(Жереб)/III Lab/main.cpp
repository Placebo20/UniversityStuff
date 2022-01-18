#include "menu.h"

using namespace sf;

struct point { int x, y; };

void Stealth()
{
	HWND Stealth;
	AllocConsole();
	Stealth = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(Stealth, 0);
}

void RenderGame(RenderWindow &game,int &score, List lst) {
	std::cout << "Entered RenderGame Method" << std::endl;
	srand((unsigned int)time(NULL));

	game.setVerticalSyncEnabled(true);

	Font font;
	font.loadFromFile("fonts/CaviarDreams_Italic.ttf");
	Text scoretext, scorevalue;
	scoretext.setFont(font);
	scorevalue.setFont(font);

	SoundBuffer jumpbuffer, crashbuffer, springbuffer;
	jumpbuffer.loadFromFile("audio/poink.wav");
	crashbuffer.loadFromFile("audio/crash.wav");
	springbuffer.loadFromFile("audio/spring.wav");
	Sound jump(jumpbuffer), crash(crashbuffer), springs(springbuffer);

	Texture background, cherry, platform, badplatform, spring, trampoline;
	background.loadFromFile("images/background.png");
	cherry.loadFromFile("images/doublecherry.png");
	platform.loadFromFile("images/platform.png");
	badplatform.loadFromFile("images/badplatform.png");
	spring.loadFromFile("images/spring.png");
	trampoline.loadFromFile("images/trampoline.png");

	Sprite sbackground(background), scherry(cherry), splatform(platform), sbadplatform(badplatform),
		sspring(spring), strampoline(trampoline);

	sbackground.setPosition(0, 0);
	scherry.setTextureRect(IntRect(0, 0, 75, 80));
	scherry.setPosition(162, 420);

	point plat[20];
	point badplat[4];
	point pruzh[2];

	int randplat = rand() % 49 + 0;
	std::cout << randplat;

	plat[0].x = 200; plat[0].y = 520;

	for (int i = 1; i < 10; i++)
	{
			plat[i].x = rand() % 400;
			plat[i].y = rand() % 533;
	}

	pruzh[0].x = plat[randplat].x;
	pruzh[0].y = plat[randplat].y + 14;

	for (int i = 0; i < 2; i++)
	{
		badplat[i].x = rand() % 300;
		badplat[i].y = rand() % 533;
	}

	int x = 200, y = 430, h = 200;

	float dy = 0;
	
	
	while (isGame) {
		Event event;
		while (game.pollEvent(event)) {
			if (event.type == Event::Closed) {
				isGame = false;
				save_to_txt(lst);
				game.close();
				
			}
		}

		RectangleShape rectangle(Vector2f(400.f, 60.f));
		rectangle.move(0, 0);
		rectangle.setFillColor(Color(153, 204, 255, 225));

		if (Keyboard::isKeyPressed(Keyboard::Right)) { x += 4; scherry.setTextureRect(IntRect(75, 0, 75, 80)); }
		if (Keyboard::isKeyPressed(Keyboard::Left)) { x -= 4; scherry.setTextureRect(IntRect(0, 0, 75, 80)); }

		dy += 0.2f;
		y += dy;
		if (y > 500) {
			isGame = false; 
			std::cout << "#2#" << std::endl;
		}
		else if (x > 400)
			x = 0;
		else if (x < 0)
			x = 400;

		if (dy < 0)
			score++;
		else if (dy > 0)
			score--;

		if (y < h) {
			while (randplat > 10) {
				for (int i = 0; i < 10; i++)
				{
					y = h;
					plat[i].y = plat[i].y - dy;
					if (plat[i].y > 533) {
						plat[i].y = -50;
						plat[i].x = rand() % 300;
					}

				}
				randplat -= 10;
			}

			for (int i = 0; i < 10; i++)
			{
				y = h;
				plat[i].y = plat[i].y - dy;
				pruzh[0].y = pruzh[0].y - dy;
				pruzh[0].x = plat[randplat].x;
				pruzh[0].y = plat[randplat].y - 14;
				if (plat[i].y > 533) {
					plat[i].y = 0;
					plat[i].x = rand() % 300;
				}
			}
			
			for (int i = 0; i < 2; i++) {
				y = h;
				badplat[i].y = badplat[i].y - dy;
				if (badplat[i].y > 533) {
					badplat[i].y = 0;
					badplat[i].x = rand() % 300;
				}
			}
		}

		for (int i = 0; i < 10; i++)
			if ((x + 50 > plat[i].x)
				&& (x + 20 < plat[i].x + 68)
				&& (y + 70 > plat[i].y)
				&& (y + 70 < plat[i].y + 14)
				&& (dy > 0)) {
				dy = -10;
				jump.play();
			}

		for (int i = 0; i < 2; i++)
			if ((x + 50 > badplat[i].x)
				&& (x + 20 < badplat[i].x + 68)
				&& (y + 70 > badplat[i].y)
				&& (y + 70 < badplat[i].y + 14)
				&& (dy > 0)) {
				badplat[i].y = 0;
				crash.play();
			}


		if ((x + 50 > pruzh[0].x)
			&& (x + 20 < pruzh[0].x + 20)
			&& (y + 70 > pruzh[0].y)
			&& (y + 70 < pruzh[0].y + 29)
			&& (dy > 0)) {
			dy = -17;
			springs.play();
		}

		scherry.setPosition(x, y);

		game.draw(sbackground);
		game.draw(scherry);

		for (int i = 0; i < 10; i++)
		{
			splatform.setPosition(plat[i].x, plat[i].y);
			game.draw(splatform);
		}

		for (int i = 0; i < 2; i++)
		{
			sspring.setPosition(pruzh[0].x, pruzh[0].y);
			game.draw(sspring);
		}

		for (int i = 0; i < 2; i++)
		{
			sbadplatform.setPosition(badplat[i].x, badplat[i].y);
			game.draw(sbadplatform);
		}

		scoretext.setString("Score:");
		scoretext.setCharacterSize(35);
		scoretext.setFillColor(Color(0, 0, 0, 255));
		scoretext.setPosition(10, 3);

		scorevalue.setString(std::to_string(score));
		scorevalue.setCharacterSize(35);
		scorevalue.setFillColor(Color(0, 0, 0, 255));
		scorevalue.setPosition(110, 3);

		game.draw(rectangle);
		game.draw(scoretext);
		game.draw(scorevalue);
		game.display();
	}
	std::cout << "Exit from RenderGame Method" << std::endl;
}

int main() {
	std::cout << "Entered main.cpp" << std::endl;
	Stealth();//Скрывает консоль
	RenderWindow game(VideoMode(400, 533), "Cherry Jump!");
	int score = 0; 
	isMenu = true;
	bool firstwhile = true;
	while (firstwhile) {
		if (isHigh == false) {
			StartMenu(game,firstwhile);
		}
		else if (isHigh) {
			Highboards(game,firstwhile);
		}
	}
	Player tmp;
	List lst;
	while(game.isOpen()){
		if (isGame && isHigh == false) {
			std::cout << "Started new game" << std::endl;
			score = 0;
			RenderGame(game,score,lst);
		}
		else if (isGame == false) {
			EnterName(game, score, lst);
			firstwhile = true;
			while (firstwhile) {
				if (isHigh == false) {
					Menu(game, score, lst, firstwhile);
				}
				else if (isHigh) {
					Highboards(game,firstwhile);
				}
			}
		}
		else { break; }
	}
	
	
	std::cout << "Exited from main.cpp" << std::endl;
	return 0;
}