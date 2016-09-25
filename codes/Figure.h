#include <iostream>
using namespace std;

class Figure {
	public:
		int x, y, type;
		bool Color;
		vector <Point> moves;
		vector <Point> captures;
		Figure() {}
		Figure(int x, int y, int type, bool Color) : x(x), y(y), type(type), Color(Color) {}		
		~Figure(){}
		inline virtual bool IsAttack(int x, int y)
		{
			return 0;
		}

		inline bool operator == (const Figure &T) {
			if (x == T.x && y == T.y && type == T.type && Color == T.Color) return 1;
			return 0;
		}

		inline void Change(const int &x, const int &y);

		inline void out()
		{
			cout << x << " " << y;
		}
};

inline void Figure::Change(const int &x, const int &y)
{
	this -> x = x;
	this -> y = y;
}
