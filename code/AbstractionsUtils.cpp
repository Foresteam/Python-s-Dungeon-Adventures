#include "AbstractionsUtils.h"

void SetCursorPos(int XPos, int YPos) {
	printf("\033[%d;%dH", YPos + 1, XPos + 1);
}

Vector::Vector(int x, int y) {
	this->x = x;
	this->y = y;
}
Vector::Vector() : Vector::Vector(0, 0) {}
Vector Vector::Normalized(Vector vec) {
	int x = vec.x + SCR_X / 2, y = vec.y + SCR_Y / 2;
	if (x < 0)
		x += SCR_X;
	if (y < 0)
		y += SCR_Y;
	if (x >= SCR_X)
		x -= SCR_X;
	if (y >= SCR_Y)
		y -= SCR_Y;
	return Vector(x, y);
}
Vector Vector::Random() {
	return Vector(distrx(gen), distry(gen));
}
std::random_device Vector::rd;
std::mt19937 Vector::gen = std::mt19937(rd());
std::uniform_int_distribution<> Vector::distrx = std::uniform_int_distribution<>(-SCR_X / 2, SCR_X / 2);
std::uniform_int_distribution<> Vector::distry = std::uniform_int_distribution<>(-SCR_Y / 2, SCR_Y / 2);

Representation::Representation(std::string chr, Color::Modifier color) {
	this->chr = chr;
	this->color = color;
}
Representation::Representation() : Representation::Representation(" ", Color::Modifier()) {} // ■

char getch() {
	char buf = 0;
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0)
		perror("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0)
		perror("tcsetattr ICANON");
	if (read(0, &buf, 1) < 0)
		perror("read()");
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
		perror("tcsetattr ~ICANON");
	return (buf);
}