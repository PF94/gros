#include <common/stdio.h>
#include <common/types.h>

/** @file bouncy_ball.cpp
 *  @brief Bouncy ball code
 *
 *  @author ROllerozxa
 */

using namespace gros::common;

namespace gros {
	
uint8_t ballX = 1;
uint8_t ballY = 4;
int8_t ballXVel = 1;
int8_t ballYVel = 1;

void bouncyBall() {
	printf("#", ballX, ballY);

	if (ballX == 0) ballXVel = 1;
	if (ballY == 0) ballYVel = 1;
	if (ballX == 79) ballXVel = -1;
	if (ballY == 24) ballYVel = -1;
	ballX = ballX + ballXVel;
	ballY =	ballY + ballYVel;

	printf("O", ballX, ballY);
}

}
