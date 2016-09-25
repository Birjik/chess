class Queen : public Figure
{	
	public:
		Queen() 
		{
			type = 5;
			moves.clear();
			captures.clear();
		}
		Queen(int x, int y, int Color) : Figure(x, y, 5, Color) 
		{
			moves.clear();
			captures.clear();
			for (int x1 = 1; x1 <= 8; x1++)
			{
				for (int y1 = 1; y1 <= 8; y1++)
				{
					if (x == x1 && y == y1)
						continue;
					if (x == x1 || y == y1)
					{
						moves.pb(Point(x1, y1));
						captures.pb(Point(x1, y1));
					}
					else if (x - y == x1 - y1 || x + y == x1 + y1)
					{
						moves.pb(Point(x1, y1));
						captures.pb(Point(x1, y1));
					}
				}
			}						
		}
		inline bool IsAttack(int x, int y);
};

inline bool Queen::IsAttack(int x, int y)
{
	if (x == this -> x || y == this -> y)
		return 1;
	if (x - y == this -> x - this -> y || x + y == this -> x + this -> y)
		return 1;
	return 0;
}



