#pragma once
#ifndef _MENU_H
#define _MENU_H

#include "player.h"

bool isGame = false;
bool isHigh = false;
bool isMenu = false;

using namespace sf;

void EnterName(RenderWindow& game, int score, List& lst);

void Highboards(RenderWindow& game, bool& firstwhile);

void StartMenu(RenderWindow& game, bool& firstwhile) {

	std::cout << "Entered StartMenu method" << std::endl;
	Texture buttonTexture, backgroundTexture, rbuttonTexture;
	buttonTexture.loadFromFile("images/GreenButton.png");
	rbuttonTexture.loadFromFile("images/RedButton.png");
	backgroundTexture.loadFromFile("images/background.png");
	Sprite sbackground(backgroundTexture), sbutton(buttonTexture), srbutton(rbuttonTexture);
	sbackground.setPosition(0, 0);

	Font font;
	font.loadFromFile("fonts/CaviarDreams_Italic.ttf");
	Text New_game, Highboard, Exit;
	New_game.setFont(font);
	Highboard.setFont(font);
	Exit.setFont(font);

	isMenu = true;

	int menutmp = 1;

	while (isMenu) {
		Event event;
		while (game.pollEvent(event)) {

			switch (event.type) {
			case Event::Closed:
				game.close();
				firstwhile = false;
				isMenu = false;
				break;

			case Event::KeyPressed:

				if (event.key.code == Keyboard::Enter) {
					switch (menutmp) {
					case 1:
						isGame = true;
						isMenu = false;
						firstwhile = false;
						break;
					case 2:
						isGame = false;
						isHigh = true;
						isMenu = false;
						break;
					case 3:
						isMenu = false;
						firstwhile = false;
						game.close();
						break;
					}
				}
				else if (event.key.code == Keyboard::Down) {
					if (menutmp < 3)
						menutmp++;
					else if (menutmp == 3)
						menutmp = 1;
				}
				else if (event.key.code == Keyboard::Up) {
					if (menutmp > 1)
						menutmp--;
					else if (menutmp == 1)
						menutmp = 3;
				}


			default:
				break;
			}

		}
		game.draw(sbackground);

		

		/*int menuNum = 0;
		if (IntRect(100, 100, 206, 56).contains(Mouse::getPosition(game))) { menuNum = 1; }
		if (IntRect(100, 230, 206, 56).contains(Mouse::getPosition(game))) { menuNum = 2; }
		if (IntRect(100, 360, 206, 56).contains(Mouse::getPosition(game))) { menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (menuNum == 1) { isGame = true; firstwhile = false; isMenu = false; }
			if (menuNum == 2) { isHigh = true; isMenu = false; }
			if (menuNum == 3) { game.close();  isMenu = false; firstwhile = false; }
		}*/

		sbutton.setPosition(100, 100);
		game.draw(sbutton);

		New_game.setString("New Game!");
		New_game.setCharacterSize(30);
		New_game.setFillColor(Color(0, 0, 0, 255));
		New_game.setPosition(125, 105);

		sbutton.setPosition(100, 230);
		game.draw(sbutton);

		Highboard.setString("Highboard");
		Highboard.setCharacterSize(30);
		Highboard.setFillColor(Color(0, 0, 0, 255));
		Highboard.setPosition(125, 235);

		sbutton.setPosition(100, 360);
		game.draw(sbutton);

		Exit.setString("Exit");
		Exit.setCharacterSize(30);
		Exit.setFillColor(Color(0, 0, 0, 255));
		Exit.setPosition(180, 365);

		switch (menutmp) {
		case 1:
			srbutton.setPosition(100, 100);
			game.draw(srbutton);
			break;
		case 2:
			srbutton.setPosition(100, 230);
			game.draw(srbutton);
			break;
		case 3:
			srbutton.setPosition(100, 360);
			game.draw(srbutton);
			break;
		default:
			break;
		}

		game.draw(New_game);
		game.draw(Highboard);
		game.draw(Exit);

		game.display();
	}
	std::cout << "Exited from StartMenu method" << std::endl;
}
	
void Menu(RenderWindow& game, int score, List& lst, bool& firstwhile) {
	
	std::cout << "Entered Menu Method" << std::endl;
	bool isMenu = true;


	Texture buttonTexture, backgroundTexture, redbuttonTexture;
	buttonTexture.loadFromFile("images/GreenButton.png");
	backgroundTexture.loadFromFile("images/background.png");
	redbuttonTexture.loadFromFile("images/RedButton.png");
	Sprite sbackground(backgroundTexture), sbutton(buttonTexture), srbutton(redbuttonTexture);
	sbackground.setPosition(0, 0);

	Font font;
	font.loadFromFile("fonts/CaviarDreams_Italic.ttf");
	Text New_game, Highboard, Exit, Score, ScoreS, question;
	New_game.setFont(font);
	Highboard.setFont(font);
	Exit.setFont(font);
	Score.setFont(font);
	ScoreS.setFont(font);
	
	Score.setString("Score:");
	Score.setCharacterSize(40);
	Score.setFillColor(Color(0, 0, 0, 255));
	Score.setPosition(100, 70);

	ScoreS.setString(std::to_string(score));
	ScoreS.setCharacterSize(40);
	ScoreS.setFillColor(Color(0, 0, 0, 255));
	ScoreS.setPosition(230, 70);

	question.setString("What is your name?:");
	question.setCharacterSize(25);
	question.setFillColor(Color(0, 0, 0, 255));
	question.setPosition(80, 110);

	
	isMenu = true;

	int menutmp = 1;

	while (isMenu) {
		Event event;
		while (game.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed: 
				save_to_txt(lst);
				game.close();
				firstwhile = false;
				isMenu = false;
				break;

			case Event::KeyPressed:
				
					if (event.key.code == Keyboard::Enter) {
						switch (menutmp) {
						case 1:
							isGame = true;
							isMenu = false;
							firstwhile = false;
							break;
						case 2:
							isGame = false;
							isHigh = true;
							isMenu = false;
							break;
						case 3:
							if(lst.GetSize() > 1)
								lst.comparison_bubble();
							save_to_txt(lst);
							isMenu = false;
							firstwhile = false;
							game.close();
							break;
						}
					}
					else if(event.key.code == Keyboard::Down) {
						if (menutmp < 3)
							menutmp++;
						else if (menutmp == 3)
							menutmp = 1;
					}
					else if (event.key.code == Keyboard::Up) {
						if (menutmp > 1)
							menutmp--;
						else if (menutmp == 1)
							menutmp = 3;
					}
				

			default:
				break;
			}
		}
		
		game.draw(sbackground);

		sbutton.setPosition(100, 150);
		game.draw(sbutton);

		New_game.setString("New Game!");
		New_game.setCharacterSize(30);
		New_game.setFillColor(Color(0, 0, 0, 255));
		New_game.setPosition(125, 155);

		sbutton.setPosition(100, 250);
		game.draw(sbutton);

		Highboard.setString("Highboard");
		Highboard.setCharacterSize(30);
		Highboard.setFillColor(Color(0, 0, 0, 255));
		Highboard.setPosition(125, 255);

		sbutton.setPosition(100, 350);
		game.draw(sbutton);

		Exit.setString("Exit");
		Exit.setCharacterSize(30);
		Exit.setFillColor(Color(0, 0, 0, 255));
		Exit.setPosition(180, 355);

		switch (menutmp) {
		case 1:
			srbutton.setPosition(100, 150);
			game.draw(srbutton);
			break;
		case 2:
			srbutton.setPosition(100, 250);
			game.draw(srbutton);
			break;
		case 3:
			srbutton.setPosition(100, 350);
			game.draw(srbutton);
			break;
		default:
			break;
		}

		game.draw(Score);
		game.draw(ScoreS);
		game.draw(New_game);
		game.draw(Highboard);
		game.draw(Exit);

		game.display();
	}
	std::cout << "Exited from Menu Method" << std::endl;
	
}

void EnterName(RenderWindow& game, int score, List& lst) {
	std::cout << "Entered EnterName Method" << std::endl;
	std::vector<std::string> names = { "Nagibator228", "pro100_dima", "111", "11_artem_11", "Jack", "John" };
	int randname = rand() % 6;
	std::string str = names[randname];
	
	///////////////////////////////////////// Œ“–»—Œ¬ ¿ //////////////////////////////////////////

	Texture buttonTexture, backgroundTexture;
	buttonTexture.loadFromFile("images/RedButton.png");
	backgroundTexture.loadFromFile("images/background.png");
	Sprite sbackground(backgroundTexture), sbutton(buttonTexture);
	sbackground.setPosition(0, 0);
	
	Font font;
	font.loadFromFile("fonts/CaviarDreams_Italic.ttf");
	Text Score, ScoreS, question, name, ok;
	Score.setFont(font);
	ScoreS.setFont(font);
	question.setFont(font);
	name.setFont(font);
	ok.setFont(font);

	Score.setString("Score:");
	Score.setCharacterSize(40);
	Score.setFillColor(Color(0, 0, 0, 255));
	Score.setPosition(100, 70);

	ScoreS.setString(std::to_string(score));
	ScoreS.setCharacterSize(40);
	ScoreS.setFillColor(Color(0, 0, 0, 255));
	ScoreS.setPosition(230, 70);

	question.setString("What is your name?:");
	question.setCharacterSize(25);
	question.setFillColor(Color(0, 0, 0, 255));
	question.setPosition(90, 150);

	name.setString(names[randname]);
	name.setCharacterSize(25);
	name.setFillColor(Color(0, 0, 0, 255));
	name.setPosition(180, 185);

	ok.setString("OK");
	ok.setCharacterSize(25);
	ok.setFillColor(Color(0, 0, 0, 255));
	ok.setPosition(190, 240);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool Player = true;
	while (Player) {
		Event event;
		while (game.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				game.close();
				isMenu = false;
				break;

			case Event::KeyPressed:
				std::cout << event.key.code << std::endl;
				{
					std::cout << "intrect" << std::endl;
					if (event.key.code == Keyboard::Enter) {
						std::cout << "Click!" << std::endl;
						lst.push_back(score, str);
						Player = false;
					}
				}

			default:
				break;
			}
		}

		game.draw(sbackground);
		sbutton.setPosition(110, 230);
		game.draw(sbutton);
		game.draw(Score);
		game.draw(ScoreS);
		game.draw(question);
		game.draw(name);
		game.draw(ok);

		game.display();
	}

	std::cout << std::endl << std::endl;
	save_to_bin(lst);
	read_from_bin(lst);
	std::cout << std::endl << std::endl;
}

void Highboards(RenderWindow& game, bool& firstwhile) {

	std::cout << "Entered Highboards Method" << std::endl;
	
	Texture background, button, bbutton;
	background.loadFromFile("images/background.png");
	button.loadFromFile("images/GreenButton.png");
	bbutton.loadFromFile("images/RedButton.png");
	Sprite sbackground(background), sbutton(button),sbbutton(bbutton);
	isMenu = true;

	Font font;
	font.loadFromFile("fonts/CaviarDreams_Italic.ttf");
	Text articletmp, article;

	article.setFont(font);
	article.setCharacterSize(30);
	article.setFillColor(Color(0, 0, 0, 255));

	articletmp.setFont(font);
	articletmp.setCharacterSize(30);
	articletmp.setFillColor(Color(0, 0, 0, 255));

	sbutton.setPosition(97, 430);

	while (isMenu) {

		Event event;
		while (game.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				game.close();
				isMenu = false;
				firstwhile = false;
				break;

			case Event::KeyPressed:
				std::cout << event.key.code << std::endl;
				 {
					std::cout << "intrect" << std::endl;
					if (event.key.code == Keyboard::Enter) {
						std::cout << "Click!" << std::endl;
						isMenu = false;
						isHigh = false;
					}
				}

			default:
				break;
			}
		}

		game.draw(sbackground);

		article.setString("[ID] _name_: _score_");
		article.setPosition(15, 20);
		game.draw(article);

		std::string str;
		std::ifstream outtxt;
		articletmp.setCharacterSize(20);
		outtxt.open("Highboards.txt");

		sbbutton.setPosition(100, 430);
		game.draw(sbbutton);

		if (outtxt.is_open()) {
			float j = 70;
			for (int i = 0; i < 10; i++) {
				std::getline(outtxt, str, '\n');
				articletmp.setString(str);
				articletmp.setPosition(20, j);
				game.draw(articletmp);
				j += 35;
			}
		}
		
		article.setString("Back");
		article.setPosition(170, 440);
		game.draw(article);
		game.display();
	}
	std::cout << "Exited from Highboards Method" << std::endl;

}

#endif _MENU_H