#include "drawGame.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <tuple>


// Draw the Score and the Borders for the game
void drawGame::drawBorders(cv::Mat gameImage) {
	//HUD: Score
	putText(gameImage, "Score: ", cv::Point((width / 2) - 50, startHeight + 20), cv::FONT_ITALIC, 0.8, scoreColor, 2);

	//Draw Borders
	//Top border, 40 offset from top for Score (thickness: 20) 
	rectangle(gameImage, cv::Point(startWidth, startHeight + 40), cv::Point(width, startHeight + 60), borderColor, cv::FILLED);
	//Left Border, 40 (offset) + 20(top border thickness) = 60 (thickness: 20) 
	rectangle(gameImage, cv::Point(startWidth, startHeight + 40), cv::Point(startWidth + 20, height - 20), borderColor, cv::FILLED);
	//Right Border, 40 (offset) + 20(top border thickness) = 60 (thickness: 20) 
	rectangle(gameImage, cv::Point(width - 20, startHeight + 40), cv::Point(width, height - 20), borderColor, cv::FILLED);
	//Bottom Border (thickness: 20)
	rectangle(gameImage, cv::Point(startWidth, height - 20), cv::Point(width, height), borderColor, cv::FILLED);
}
// Draw the snake at position
void drawGame::drawSnake(cv::Mat gameImage, std::tuple<int, int> snakePosition) {
	
	//Draw snake (thickness: 8)
	circle(gameImage, cv::Point(std::get<0>(snakePosition),std::get<1>(snakePosition)), 8, playerColor, cv::FILLED);
}
// Draw the snake's tail
void drawGame::drawSnakeTail(cv::Mat gameImage, std::vector<std::tuple<int, int>> value) {
	if (!value.empty()) {
		for (std::size_t i = 0; i < value.size(); ++i) {
			int prevXPos = std::get<0>(value.data()[i]);
			int prevYPos = std::get<1>(value.data()[i]);
			circle(gameImage, cv::Point(prevXPos, prevYPos), 8, playerColor, cv::FILLED);
		}
	}
}

// Draw the Fruit at the target position
void drawGame::drawFruit(cv::Mat gameImage, std::tuple<int, int> fruitPosition) {
	//Draw fruit (thickness 8)
	cv::Point fruitPos = cv::Point(std::get<0>(fruitPosition), std::get<1>(fruitPosition));
	circle(gameImage, fruitPos, 8, fruitColor, cv::FILLED);
}
//Draw the score value with the updated logic score value
void drawGame::updateScore(cv::Mat gameImage, int score){
	//Erase and replace
	rectangle(gameImage, cv::Point((width / 2) + 30, startHeight), cv::Point(width, startHeight + 25), backgroundColor, cv::FILLED);
	putText(gameImage, std::to_string(score), cv::Point((width / 2) + 30, startHeight + 20), cv::FONT_ITALIC, 0.8, scoreColor, 2);
}
// Function called every frame renders the whole image
int drawGame::renderFrame(std::tuple<int, int> snakePosition, std::tuple<int, int> fruitPosition, int score, std::vector<std::tuple<int, int>> value) {
	cv::Mat gameImage(height, width, CV_8UC3, backgroundColor);

	drawBorders(gameImage);
	updateScore(gameImage,score);
	drawSnake(gameImage, snakePosition);
	drawSnakeTail(gameImage, value);
	drawFruit(gameImage, fruitPosition);

	imshow("Snake Game", gameImage);
	int key = cv::waitKey(120);

	if (key == 27) {
		cv::destroyAllWindows();
		return key;
	}
	return key;
}


