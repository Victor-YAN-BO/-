#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include <Windows.h>

using namespace sf;


#define High 768 //窗口宽度
#define Wide 832 //窗口高度

#define Size 10
#define only_Size 64

int mineDate[Size + 2][Size + 2];
int showDate[Size + 2][Size + 2];

enum {
	no_mine = 0,
	mine = 9,
	ground=10,
	flag=11
};

void initMine(){
	srand(time(0));

	for (int i = 1; i <= Size;i++) {
		for (int j = 1; j <= Size; j++) {
			showDate[i][j] = ground;

			if (rand() % 5 == 0) {
				mineDate[i][j] = mine;
			}
			else{
				mineDate[i][j] = no_mine;
			}
		}

	}
	
	for (int i = 1; i <= Size;i++) {
		for (int j = 1; j <= Size;j++) {
			if (mineDate[i][j]==mine) {
				continue;
			}

			int n = 0;
			if (mineDate[i+1][j] == mine) n++;
			if (mineDate[i-1][j] == mine) n++;
			if (mineDate[i][j+1] == mine) n++;
			if (mineDate[i][j-1] == mine) n++;
			if (mineDate[i+1][j+1] == mine) n++;
			if (mineDate[i+1][j-1] == mine) n++;
			if (mineDate[i-1][j+1] == mine) n++;
			if (mineDate[i-1][j-1] == mine) n++;
			mineDate[i][j] = n;
			
		}
	}
}

void failed(void) {
	RenderWindow windows(VideoMode(362, 259), "Minesweeper-Failed");
	
	Vector2i pos2 = Mouse::getPosition(windows);
	int x2 = pos2.x;
	int y2 = pos2.y;
	Event ee;

	while (windows.isOpen()) {
		Texture tt;
		tt.loadFromFile("images/失败.png");
		Sprite s2(tt);
		while (windows.pollEvent(ee)) {
			if (ee.type == Event::MouseButtonPressed) {
				if (ee.key.code == Mouse::Left) {
					if ((x2>= 134 || x2 <= 335) && (y2 >= 178 || y2 <= 228)) {
						windows.close();
					}
				}
			}
		}
		
		windows.draw(s2);
		windows.display();
	}
	initMine();
}
void help(void){
	std::cout << "你想得美" << std::endl;
	system("pause");
}


	

int main(void) {

	RenderWindow window(VideoMode(High, Wide), "Minesweeper");
	initMine();

	Texture t;
	t.loadFromFile("images/图片.png");
	Sprite s(t);

	Texture t2;
	t2.loadFromFile("images/全部.png");
	Sprite s3(t2);

	Texture ssmile;
	ssmile.loadFromFile("images/smile.png");
	Sprite smile(ssmile);

	/*Texture scry;
	scry.loadFromFile("images/cry.png");
	Sprite cry(scry);*/


	while (window.isOpen()){
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / only_Size;
		int y = -1+pos.y / only_Size;

		Event e;
		while(window.pollEvent(e)){
			if (e.type == Event::Closed) {
				window.close();
			}
			if (e.type == Event::KeyPressed) {
				if (e.KeyPressed == 'H') {
					help();
				}
			}
			if (e.type==Event::MouseButtonPressed) {

				if (e.key.code==Mouse::Left) {
					showDate[x][y] = mineDate[x][y];
					if (mineDate[x][y] == 0 && x >= 1 && x <= Size && y >= 1 && y <= Size) {
						showDate[x + 1][y - 1] = mineDate[x + 1][y - 1];
						showDate[x - 1][y + 1] = mineDate[x - 1][y + 1];
						showDate[x + 1][y + 1] = mineDate[x + 1][y + 1];
						showDate[x - 1][y - 1] = mineDate[x - 1][y - 1];
						showDate[x][y - 1] = mineDate[x][y - 1];
						showDate[x][y + 1] = mineDate[x][y + 1];
						showDate[x + 1][y] = mineDate[x + 1][y];
						showDate[x - 1][y] = mineDate[x - 1][y];
					}
				}
				else if(e.key.code==Mouse::Right){
					showDate[x][y] == flag;
				}
			}
		}
		window.clear(Color::White);

		for (int i = 1; i <= Size; i++) {
			for (int j = 1; j <= Size;j++) {
				if (showDate[x][y] == 9) {
					showDate[i][j] = mineDate[i][j];
				}
				s.setTextureRect(IntRect(showDate[i][j] * only_Size,0,only_Size,only_Size));
				s.setPosition(i* only_Size, (j+1) * only_Size);
				smile.setPosition(5.6 * only_Size, 0.8855 * only_Size);
				window.draw(s);
				window.draw(s3);
				window.draw(smile);
								
			}
		}
		window.display();
		if (showDate[x][y] == 9) {
			//cry.setPosition(5.6 * only_Size, 0.8855 * only_Size);
			failed();
		}
	}
	return 0;
}