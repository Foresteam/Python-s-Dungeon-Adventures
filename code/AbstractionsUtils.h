#pragma once
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <random>
#include "Config.h"

void SetCursorPos(int XPos, int YPos);

namespace Color {
	enum Code {
		FG_RED = 31,
		FG_GREEN = 32,
		FG_BLUE = 34,
		FG_MAGENTA = 35,
		FG_CYAN = 36,
		FG_DEFAULT = 39,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_BLUE = 44,
		BG_MAGENTA = 45,
		BG_CYAN = 46,
		BG_DEFAULT = 49
	};
	class Modifier {
		Code code;

	public:
		Modifier(Code pCode) { code = pCode; }
		Modifier() : Modifier(Code::FG_DEFAULT) {}
		friend std::ostream& operator<<(std::ostream& os, const Modifier& mod) {
			return os << "\033[" << mod.code << "m";
		}
	};
}

class Vector {
private:
	static std::random_device rd;						   // obtain a random number from hardware
	static std::mt19937 gen;						   // seed the generator
	static std::uniform_int_distribution<> distrx; // define the range
	static std::uniform_int_distribution<> distry; // define the range
public:
	int x, y;
	Vector(int x, int y);
	Vector();
	bool operator<(const Vector& v) const {
		if (std::min(x, y) < std::min(v.x, v.y))
			return true;
		else if (std::min(v.x, v.y) < std::min(x, y))
			return false;
		else
			return std::max(x, y) < std::max(v.x, v.y);
	}
	Vector operator+(const Vector& v2) {
		return Vector(x + v2.x, y + v2.y);
	}
	Vector operator-(const Vector& v2) {
		return Vector(x - v2.x, y - v2.y);
	}
	static Vector Normalized(Vector vec);
	static Vector Random();
};

class Representation {
private:
	std::string chr;
	Color::Modifier color;

public:
	Representation(std::string chr, Color::Modifier color);
	Representation();

	friend std::ostream& operator<<(std::ostream& os, const Representation& rpr) {
		return os << rpr.color << rpr.chr;
	}
};

template <typename Base, typename T>
inline bool instanceof (const T*) {
	return std::is_base_of<Base, T>::value;
}

char getch();