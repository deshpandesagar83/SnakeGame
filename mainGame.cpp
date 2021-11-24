#include "gameLogic.h"
#include "drawGame.h"


int main() {

	gameLogic gameObject;
	drawGame gameFrame;
	std::tuple<int,int> snakePosition = gameObject.getSnakePosition();
	std::tuple<int, int> fruitPosition = gameObject.getFruitPosition();
	
	std::vector<std::tuple<int, int>> prevValue;
	bool isGamePlaying = true;
	while (isGamePlaying) {
		int score = gameObject.getScore();

		
		int key = gameFrame.renderFrame(snakePosition, fruitPosition,score, prevValue);
		gameObject.inputDirection(key);

		
		prevValue = gameObject.updatePrevSnakePos();
		isGamePlaying = gameObject.onCollision();
		snakePosition = gameObject.updateSnakePosition();
		
		if (gameObject.isFruitEat()) {
			fruitPosition = gameObject.getFruitPosition();
		}
		if (key == 27) {
			break;
		}
	}
	return 0;

}