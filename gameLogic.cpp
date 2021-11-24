#include "gameLogic.h"
#include <ctime>

// Calculate the postion of Snake spawn X and Y
void gameLogic::spawnSnake(){
	/*Playable Pixels (42x62 Grid) :
	* Start: x(30), y(70)
	* End: x(450), y(690)
	* 
	* Randomly Spawn the snake head inside the playable area
	*/
	srand((int)time(0));
	snakeSpawnX = rand() % (maxX - minX + 1) + minX;
	snakeSpawnY = rand() % (maxY - minX + 1) + minY;
	//Clamp values to nearest 10
	snakeSpawnX = (snakeSpawnX / 10) * 10;
	snakeSpawnY = (snakeSpawnY / 10) * 10;
	

}
// Calculate the postion of Fruit spawn X and Y
void gameLogic::spawnFruit(){
	// Spawn the fruit such that it is not equal to snake position
	do {
		fruitSpawnX = rand() % (maxX - minX + 1) + minX;
		fruitSpawnY = rand() % (maxY - minY + 1) + minY;
	} while ((snakePosX == fruitSpawnX) || (snakePosY == fruitSpawnY));
	//Clamp values to nearest 10
	fruitSpawnX = (fruitSpawnX / 10) * 10;
	fruitSpawnY = (fruitSpawnY / 10) * 10;
}
// Public getter for Fruit position
std::tuple<int, int> gameLogic::getFruitPosition() {
	return { fruitSpawnX,fruitSpawnY };
}
// Public getter for Snake position
std::tuple<int, int> gameLogic::getSnakePosition() {
	
	return {snakePosX,snakePosY};
}
// Update the Snake position according to the direction
std::tuple<int, int> gameLogic::updateSnakePosition() {
	switch (direction){
	case LEFT: snakePosX -= 10; break;
	case RIGHT: snakePosX += 10; break;
	case UP: snakePosY -= 10; break;
	case DOWN: snakePosY += 10; break;
	case STOP: break;
	}

	if (snakePosX < minX) snakePosX = maxX;
	if (snakePosX > maxX) snakePosX = minX;
	if (snakePosY < minY) snakePosY = maxY;
	if (snakePosY > maxY) snakePosY = minY;

	return {snakePosX , snakePosY};
}
// Input direction depending of the key input
void gameLogic::inputDirection(int key) {
	switch (key) {
	// ASCII values for A and a
	case 65:
	case 97:  direction = LEFT; break;
	// ASCII values for D and d
	case 68:
	case 100: direction = RIGHT; break;
	// ASCII values for W and w
	case 87:
	case 119: direction = UP; break;
	// ASCII values for S and s
	case 83:
	case 115:  direction = DOWN; break;
	// ASCII values for esc
	case 27: direction = STOP; break;

	default: break;
	}
}
// To check if the fruit has been eaten
bool gameLogic::isFruitEat() {
	if ((snakePosX == fruitSpawnX) && (snakePosY == fruitSpawnY)) {
		score += 10;
		prevSnakePos.push_back(std::make_tuple(snakePosX, snakePosY));
		spawnFruit();
		return true;
	} 
	else return false;
	
}
// Getter function for score value
int gameLogic::getScore() {
	return score;
}
//Get all Previous X and Y values
std::vector<std::tuple<int, int>> gameLogic::updatePrevSnakePos() {
	if (!prevSnakePos.empty()) {
		auto maxSize = prevSnakePos.size();
		maxSize--;
		for (std::size_t i = maxSize; i >0; --i) {
			std::swap(prevSnakePos.data()[i], prevSnakePos.data()[i -1]);
		}
		prevSnakePos.data()[0] = std::make_tuple(snakePosX, snakePosY);
	}
	return prevSnakePos;
}
//Function to detect collision with itself
bool gameLogic::onCollision() {
	if (!prevSnakePos.empty()) {
		auto maxSize = prevSnakePos.size();
		for (std::size_t i = 1; i < maxSize; ++i) {
			int prevXPos = std::get<0>(prevSnakePos.data()[i]);
			int prevYPos = std::get<1>(prevSnakePos.data()[i]);
			if (prevXPos == snakePosX && prevYPos == snakePosY) {
				return false;
			}
		}
	}
	return true;
	
}
//Constructor for game Logic class
gameLogic::gameLogic(){
	score = 0;
	spawnSnake();
	// Initially set the current position as the spawn position
	snakePosX = snakeSpawnX;
	snakePosY = snakeSpawnY;
	spawnFruit();
	direction = STOP;
}

