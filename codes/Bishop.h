class Bishop : public Figure {
	public:
	Bishop() {
		type = 2;
		moves.clear();
		captures.clear();
	}
	Bishop(int x, int y, bool Color) : Figure(x, y, 2, Color) 
	{
		moves.clear();
		captures.clear();
		for (int x1 = 1; x1 <= 8; x1++)
		{
			for (int y1 = 1; y1 <= 8; y1++)
			{
				if (x == x1 && y == y1)
					continue;
				if (x1 - y1 == x - y || x1 + y1 == x + y)
				{
					moves.pb(Point(x1, y1));
					captures.pb(Point(x1, y1));
				}
			}
		}
	}
	~Bishop(){}

	inline bool IsAttack(const int &x, const int &y) {
		if (this -> x - this -> y == x - y || this -> x + this -> y == x + y) return 1;
		return 0;
	}
};
