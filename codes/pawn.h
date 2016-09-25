class Pawn : public Figure {
	public:
		Pawn() {
			type = 1;
			moves.clear();
			captures.clear();
		}
		Pawn(int x, int y, bool Color) : Figure(x, y, 1, Color) 
		{
			moves.clear();
			captures.clear();
			/*
			if (!Color)
			{
				if (y < 8)
				{
					moves.pb(Point(x, y + 1));
					if (x < 8)
						captures.pb(Point(x + 1, y + 1));
					if (x > 1)
						captures.pb(Point(x - 1, y + 1));
				}
				if (y == 2)
					moves.pb(Point(x, y + 2));

			}
			else
			{
				if (y > 1)
				{
					moves.pb(Point(x, y - 1));
					if (x < 8)
						captures.pb(Point(x + 1, y - 1));
					if (x > 1)	
						captures.pb(Point(x - 1, y - 1));
				}
				if (y == 7)
					moves.pb(Point(x, y - 2));
			}
			*/
			if (Color)
			{
				if (x != 1)
				{
					moves.pb(Point(x - 1, y));
					if (y < 8)
						captures.pb(Point(x - 1, y + 1));
					if (y > 1)
						captures.pb(Point(x - 1, y - 1));
				}
				if (x == 7)
					moves.pb(Point(x - 2, y));

			}
			else
			{
				if (x < 8)
				{
					moves.pb(Point(x + 1, y));
					if (y < 8)
						captures.pb(Point(x + 1, y + 1));
					if (y > 1)	
						captures.pb(Point(x + 1, y - 1));
				}
				if (x == 2)
					moves.pb(Point(x + 2, y));
			}

		}
		~Pawn() {}
		inline bool IsAttack(const int &x, const int &y) {
			if (Color == 0) {
				if (this -> x + 1 == x && (this -> y + 1 == y || this -> y - 1 == y)) return 1;
				return 0;
			}
			else {
				if (this -> x - 1 == x && (this -> y + 1 == y || this -> y - 1 == y)) return 1;
				return 0;
			}
		}
};
