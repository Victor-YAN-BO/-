#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

using namespace sf;

#define High 768 //窗口宽度
#define Wide 768 //窗口高度

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


int main(void) {
	RenderWindow window(VideoMode(High, Wide),"234");
	

	initMine();

	Texture t;
	t.loadFromFile("images/图片.png");
	Sprite s(t);

	while (window.isOpen()) {
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / only_Size;
		int y = pos.y / only_Size;


		Event e;
		while(window.pollEvent(e)){
			if (e.type == Event::Closed) {
				window.close();
			}
			
			if (e.type==Event::MouseButtonPressed) {

				if (e.key.code==Mouse::Left) {
					showDate[x][y] = mineDate[x][y];
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
				s.setPosition(i * only_Size, j * only_Size);
				window.draw(s);
				
			}
		}
		window.display();
	}
	return 0;
}