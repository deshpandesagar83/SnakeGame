#pragma once
#include <tuple>
#include <vector>


class gameLogic
{
private:
	/*Playable Pixels (42x62 Grid) :
	* Start: x(30), y(70)
	* End: x(450), y(690)
	*/
	int minX = 30, maxX = 450, minY = 70, maxY = 690;
	int score=0;
	// Spawn position of the snake, current position and the length of the snake
	int snakeSpawnX=100, snakeSpawnY=100, snakePosX=100,snakePosY=100;
	
	std::vector<std::tuple<int, int>> prevSnakePos;
	// Spawn positon of the fruit
	int fruitSpawnX=200, fruitSpawnY=200;
	
	// The current state of the snake (direction it is going in)
	enum stateDir {STOP = 0, LEFT, RIGHT, UP, DOWN };
	stateDir direction;

	//Randomly spawn the snake
	void spawnSnake();
	//Randomly spawn the fruit
	void spawnFruit();
	

public:
	// Getting the current position of the snake head
	std::tuple<int,int> getSnakePosition();
	// Getting the current position of the snake head
	std::tuple<int, int> getFruitPosition();
	// Input direction depending of the key input
	void inputDirection(int key);
	// Update the Snake position according to the direction
	std::tuple<int, int> updateSnakePosition();
	//Check if snake ate the fruit
	bool isFruitEat();
	// Get function for Score
	int getScore();
	//Get all Previous X and Y values
	std::vector<std::tuple<int, int>> updatePrevSnakePos();
	//Function to detect collision with itself
	bool onCollision();
	// Class constructor
	gameLogic();
};

