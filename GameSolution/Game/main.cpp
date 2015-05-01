#include "core.h"
#include <iostream>

using::std::cout;
using::std::endl;

int baseX = 0;
int baseY = 2;

static bool moveUp = false;
static bool moveDown = false;
static bool moveLeft = false;
static bool moveRight = false;
static bool gameStarting = true;

static float frogX = 20;
static float frogY = 20;

struct Point
{
	float x;
	float y;
	Point(float x = 0.0f, float y = 0.0f) :
		x(x), y(y) {}
};

Point operator+(const Point& left, const Point& right)
{
	return Point(left.x + right.x, left.y + right.y);
}

void drawLine(Core::Graphics& g, const Point& left, const Point& right)
{
	g.DrawLine(left.x, left.y, right.x, right.y);
}

struct car
{
	Point topLeft;
	Point topRight;
	Point bottomLeft;
	Point bottomRight;
	
	Point meBase;
	Point velocity;


	car(Point topleft, Point topright, Point bottomleft, Point bottomright){
		meBase = (400, 400);
		topLeft = topleft;
		topRight = topright;
		bottomLeft = bottomleft;
		bottomRight = bottomright;
	}

	void drawthyself(Core::Graphics& g){
		g.SetColor(RGB(255, 0, 0));
		drawLine(g, meBase + topLeft, meBase + topRight);
		drawLine(g, meBase + topRight, meBase + bottomRight);
		drawLine(g, meBase + bottomRight, meBase + bottomLeft);
		drawLine(g, meBase + bottomLeft, meBase + topLeft);
	}
	void integrate(){
		meBase + velocity;
	}
};

struct Frog
{
	
	Point leftUpLegUpper;
	Point leftUpLegLower;
	Point leftDownLegUpper;
	Point leftDownLegLower;
	Point BodyTopLeft;
	Point BodyTopRight;
	Point BodyBottomLeft;
	Point BodyBottomRight;
	Point rightUpLegUpper;
	Point rightUpLegLower;
	Point rightDownLegUpper;
	Point rightDownLegLower;

	Point connectUpLeft;
	Point connectUpRight;
	Point connectDownLeft;
	Point connectDownRight;

	Point meBase;
	Point velocity;
	Point eyeY;
	Point eyeX;

	Frog() :
		
		meBase(frogX, frogY),

		leftUpLegUpper(625, 775 + 70),
		leftUpLegLower(625, 750 + 70),
		leftDownLegUpper(625, 725 + 70),
		leftDownLegLower(625, 700 + 70),
		rightUpLegUpper(675, 775 + 70),
		rightUpLegLower(675, 750 + 70),
		rightDownLegLower(675, 725 + 70),
		rightDownLegUpper(675, 700 + 70),

		BodyTopLeft(640, 720 + 70),
		BodyTopRight(660, 720 + 70),
		BodyBottomLeft(640, 755 + 70),
		BodyBottomRight(660, 755 + 70)


	{}
		void drawThyself(Core::Graphics& g)
		{
			g.SetColor(RGB(100, 255, 100));
			drawLine(g, meBase + leftUpLegUpper, meBase + leftUpLegLower);
			drawLine(g, meBase + leftDownLegUpper, meBase + leftDownLegLower);
			drawLine(g, meBase + rightUpLegUpper, meBase + rightUpLegLower);
			drawLine(g, meBase + rightDownLegUpper, meBase + rightDownLegLower);
			drawLine(g, meBase + BodyBottomLeft, meBase + BodyBottomRight);
			drawLine(g, meBase + BodyBottomLeft, meBase + BodyTopLeft);
			drawLine(g, meBase + BodyBottomRight, meBase + BodyTopRight);
			drawLine(g, meBase + BodyTopLeft, meBase + BodyTopRight);
			drawLine(g, meBase + leftUpLegLower, meBase + BodyBottomLeft);
			drawLine(g, meBase + leftDownLegUpper, meBase + BodyTopLeft);
			drawLine(g, meBase + rightUpLegLower, meBase + BodyBottomRight);
			drawLine(g, meBase + rightDownLegLower, meBase + BodyTopRight);
			
			
		}
		void Integrate()
		{
			meBase = velocity;
			
		}
};

Frog frog;

void checkKeyInput()
{
	
	float vAcceleration = 85;
	float hAcceleration = 75;
	Point jumpX(10, 0);
	if (Core::Input::IsPressed(Core::Input::KEY_UP) && moveUp == false && (frog.velocity.y > -700))
	{
		frog.velocity.y -= vAcceleration;
		frogY -= vAcceleration;
		moveUp = true;
	}
	else if (!Core::Input::IsPressed(Core::Input::KEY_UP) && moveUp == true)
		moveUp = false;

	if (Core::Input::IsPressed(Core::Input::KEY_DOWN) && moveDown == false && (frog.velocity.y < 0))
	{
		frog.velocity.y += vAcceleration;
		moveDown = true;
	}
	else if (!Core::Input::IsPressed(Core::Input::KEY_DOWN) && moveDown == true)
		moveDown = false;

	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT) && moveRight == false && (frog.velocity.x < 500))
	{
		frog.velocity.x += hAcceleration;
		moveRight = true;
	}
	else if (!Core::Input::IsPressed(Core::Input::KEY_RIGHT) && moveRight == true)
		moveRight = false;

	if (Core::Input::IsPressed(Core::Input::KEY_LEFT) && moveLeft == false && (frog.velocity.x > -600))
	{
		frog.velocity.x -= hAcceleration;
		moveLeft = true;
	}
	else if (!Core::Input::IsPressed(Core::Input::KEY_LEFT) && moveLeft == true)
		moveLeft = false;
}

bool myUpdate(float dt)
{
	frog.Integrate();
	checkKeyInput();
	
	return false;
}

void gameBackground(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(255, 255, 255));
	graphics.DrawLine(0, 765, 1250, 765);

	graphics.SetColor(RGB(0, 0, 205));
	int i = 0;
	for (i; i > -175; i--)
	graphics.DrawLine(0, 255 + i, 1250, 255 + i);
	
	graphics.SetColor(RGB(85, 107, 47));
	int j = 0;
	for (j; j > -85; j--)
		graphics.DrawLine(0, 85 + j, 1250, 85 + j);
	
}

void myDraw(Core::Graphics & graphics)
{
	gameBackground(graphics);
	frog.drawThyself(graphics);
	
}

void main()
{
	Core::Init("My Game", 1210, 850);
	Core::RegisterUpdateFn(myUpdate);
	Core::RegisterDrawFn(myDraw);
	Core::GameLoop();
}

