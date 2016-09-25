class Knight : public Figure {
	public:
		Knight() {
			type = 3;
			moves.clear();
			captures.clear();
		}
		Knight(int x, int y, bool Color) : Figure(x, y, 3, Color) 
		{
			moves.clear();
			captures.clear();
			for (int x1 = 1; x1 <= 8; x1++)
			{
				for (int y1 = 1; y1 <= 8; y1++)
				{
					if (abs(x1 - x) == 1 && abs(y1 - y) == 2)
					{
						moves.pb(Point(x1, y1));
						captures.pb(Point(x1, y1));
					}
					if (abs(x1 - x) == 2 && abs(y1 - y) == 1)
					{
						moves.pb(Point(x1, y1));
						captures.pb(Point(x1, y1));
					}
				}
			}
		}
		~Knight(){}
		inline bool IsAttack(const int &x, const int &y) {
			if ((abs(this -> x - x) == 1 && abs(this -> y - y) == 2) || (abs(this -> x - x) == 2 && abs(this -> y - y) == 1)) return 1;
			return 0;
		}
};
