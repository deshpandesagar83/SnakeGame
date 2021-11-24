#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <tuple>

class drawGame
{
private:
	// Max and Min height and width for the game window
	int height = 720, width = 480, startHeight = 0, startWidth = 0;
	//Basic color values for all visisble elements
	cv::Scalar backgroundColor = cv::Scalar(255, 255, 255);
	cv::Scalar scoreColor = cv::Scalar(190, 30, 15);
	cv::Scalar borderColor = cv::Scalar(10, 60, 140);
	cv::Scalar playerColor = cv::Scalar(10, 160, 60);
	cv::Scalar fruitColor = cv::Scalar(30, 30, 225);

	// Draw the Score and the Borders for the game
	void drawBorders(cv::Mat gameImage);
	//Draw the score value with the updated logic score value
	void updateScore(cv::Mat gameImage, int score);
	// Draw the snake at position
	void drawSnake(cv::Mat gameImage, std::tuple<int, int> snakePosition);
	// Draw the snake's tail
	void drawSnakeTail(cv::Mat gameImage, std::vector<std::tuple<int, int>> value);
	// Draw the Fruit at the target position
	void drawFruit(cv::Mat gameImage, std::tuple<int, int> fruitPosition);
	
	

public:
	int renderFrame(std::tuple<int, int> snakePosition, std::tuple<int, int> fruitPosition, int score, std::vector<std::tuple<int, int>>);
};

