inline bool Chessboard::IsAttack(int x, int y, bool Color)
{
//	cout << "point = " << x << " " << y << endl;

	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] -> Color == Color)
		{
		//	cout << "trying to attack: " << a[i] -> x << " " << a[i] -> y << endl;

		//	cout << a[i] -> IsAttack(x, y) << " " << mt.FreeWay(Point(x, y), Point(a[i] -> x, a[i] -> y)) << endl;

			if (a[i] -> IsAttack(x, y) && mt.FreeWay(Point(x, y), Point(a[i] -> x, a[i] -> y)))
			{
				return 1;
			}
		}
	}
	return 0;
}

inline bool Chessboard::IsCheck(bool Color)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] -> Color == Color && a[i] -> type == 6)
		{
			if (IsAttack(a[i] -> x, a[i] -> y, (Color ^ 1)))
				return 1;
			return 0;
		}
	}
	return 0;
}

inline bool Chessboard::IsValid(bool Color)
{
	return !IsCheck(Color);
}

/*bool Chessboard::CheckMate(bool Color)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] -> Color == Color && a[i] -> type == 6)
		{
//			cout << a[i] -> x << " " << a[i] -> y << endl;
			if (!IsAttack(a[i] -> x, a[i] -> y, (Color ^ 1)))
				return 0;
//			cerr << "zahodit";
			for (int j = 0; j < a[i] -> moves.size(); j++) {
				if (!IsAttack(a[i] -> moves[j].x, a[i] -> moves[j].y, (Color ^ 1))) {
//					cerr << "ne atakuut : " << a[i] -> moves[j].x << " " << a[i] -> moves[j].y << endl;
					Chessboard *tek = new Chessboard(*this);					
					tek -> Delete(Point(a[i] -> moves[j].x, a[i] -> moves[j].y));
					tek -> Delete(Point(a[i] -> x, a[i] -> y));
					tek -> Insert(CreateFigureFromPoint(Point(a[i] -> moves[j].x, a[i] -> moves[j].y), Color, 6));
					if (!tek -> IsCheck(Color)) return 0;
				}
			}

			for (int j = 0; j < (int)a[i] -> captures.size(); ++ j) {
				Point nxtMove = a[i] -> captures[j];
				if (mt.IsDifferent(Point(a[i] -> x, a[i] -> y), nxtMove)) {
					Chessboard *tek = new Chessboard(*this);
					tek -> Delete(Point(a[i] -> moves[j].x, a[i] -> moves[j].y));
					tek -> Delete(Point(a[i] -> x, a[i] -> y));
					tek -> Insert(CreateFigureFromPoint(Point(a[i] -> moves[j].x, a[i] -> moves[j].y), Color, 6));
					if (!tek -> IsCheck(Color)) return 0;
				}
			}

			return 1;
		}
	}
//	cerr << "v koncee";
	return 0;
}*/

