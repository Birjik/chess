class King : public Figure
{
	public:
		King()
		{
			type = 6;
			moves.clear();
			captures.clear();
		}
		King(int x, int y, bool Color) : Figure(x, y, 6, Color)
		{
			moves.clear();
			captures.clear();
			for (int x1 = 1; x1 <= 8; x1++)
			{
				for (int y1 = 1; y1 <= 8; y1++)
				{
					if (abs(x - x1) <= 1 && abs(y - y1) <= 1 && (x != x1 || y != y1))
					{
						moves.pb(Point(x1, y1));
						captures.pb(Point(x1, y1));
					}
				}
			}
		}
		inline bool IsAttack(int x, int y);
		inline void Change(const int &x, const int &y);
};

inline bool King::IsAttack(int x, int y)
{
	return (abs(x - this -> x) <= 1 && abs(y - this -> y) <= 1);
}
	

