class Rook : public Figure
{
	public:
		Rook()
		{
			type = 4;	
			moves.clear();
			captures.clear();
		}
		Rook(int x, int y, bool color) : Figure(x, y, 4, color) 
		{
			moves.clear();
			captures.clear();
			for (int x1 = 1; x1 <= 8; x1++)
			{
				for (int y1 = 1; y1 <= 8; y1++)
				{	
					if (x1 == x && y1 == y)
						continue;
					if (x1 == x || y1 == y)
					{
						moves.pb(Point(x1, y1));
						captures.pb(Point(x1, y1));
					}
				}
			}
		}
		inline bool IsAttack(int x, int y);
};

inline bool Rook::IsAttack(int x, int y)
{
	return (x == this -> x || y == this -> y);
}

