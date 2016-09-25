class Point {
	public:
		int x, y;
		Point() {
			x = y = 0;
		}
		Point(int x, int y) : x(x), y(y) {}

		inline bool operator == (const Point &T) {
			return (x == T.x && y == T.y);
		}
		inline bool operator != (const Point &T) {
			return (x != T.x || y != T.y);
		}

		~Point(){}
};
