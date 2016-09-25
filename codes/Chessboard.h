class Chessboard
{
	public:
		vector <Figure*> a;
		bool turn;
		Matrix mt;
		Chessboard(){}
		Chessboard(const Chessboard *&last) {
			a.clear();
			mt.Clear();
			turn = last -> turn;
			for (int i = 1; i <= 8; ++ i) {
				for (int j = 1; j <= 8; ++ j) {
					mt.board[i][j] = last -> mt.board[i][j];
				}
			}
			
			mt.hash = last -> mt.hash;

			a.resize((int)last -> a.size());

			for (int i = 0; i < (int)a.size(); ++ i) {
				if (last -> a[i] -> type == 1) {
					a[i] = new Pawn(last -> a[i] -> x, last -> a[i] -> y, last -> a[i] -> Color);
				}
				if (last -> a[i] -> type == 2) {
					a[i] = new Knight(last -> a[i] -> x, last -> a[i] -> y, last -> a[i] -> Color);
				}
				if (last -> a[i] -> type == 3) {
					a[i] = new Bishop(last -> a[i] -> x, last -> a[i] -> y, last -> a[i] -> Color);
				}
				if (last -> a[i] -> type == 4) {
					a[i] = new Rook(last -> a[i] -> x, last -> a[i] -> y, last -> a[i] -> Color);
				}
				if (last -> a[i] -> type == 5) {
					a[i] = new Queen(last -> a[i] -> x, last -> a[i] -> y, last -> a[i] -> Color);
				}
				if (last -> a[i] -> type == 6) {
					a[i] = new King(last -> a[i] -> x, last -> a[i] -> y, last -> a[i] -> Color);
				}
			}
		}

		inline void Insert(Figure *now) {
			a.pb(now);
			if (!now -> Color) mt.SetValue(now -> x, now -> y, -now -> type);
			else mt.SetValue(now -> x, now -> y, now -> type);
		}

		inline void Delete(const Point P) {
			int id = -1;
			for (int i = 0; i < (int)a.size(); ++ i) {
				if (Point(a[i] -> x, a[i] -> y) == P) {
					id = i;
					break;
				}
			}
			if (id == -1) return;

			for (int i = id + 1; i < (int)a.size(); ++ i) {
				a[i - 1] = a[i];
			}
			a.resize((int)a.size() - 1);
			mt.SetValue(P.x, P.y, 0);
		}

		inline void show() {
			for (int i = 1; i <= 8; ++ i) {
				for (int j = 1; j <= 8; ++ j) {
					cout << mt.board[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}

		friend istream &operator>>(istream &in, Chessboard &a);
		inline bool IsAttack(int x, int y, bool Color);
		inline bool IsCheck(bool Color);
		inline bool IsValid(bool Color);
		inline bool CheckMate(bool Color);
};

istream &operator>>(istream &in, Chessboard &a)
{
	int x, y, type, color, turn;
	a.turn = 0;
	a.mt.Clear();
	a.a.clear();
	int num;
	Figure *tmp;
	for (int x = 1; x <= 8; x++)
	{
		for (int y = 1; y <= 8; y++)
		{
			in >> num;
			if (!num)
				continue;
			color = (num / 10) - 1;
			if (num % 10 == 0)
			{
				type = 1;
				tmp = new Pawn(x, y, color);
				a.a.pb(tmp);
				if (!color)
					a.mt.SetValue(x, y, -type);
				else
					a.mt.SetValue(x, y, type);
			}
			else if (num % 10 == 1)
			{
				type = 4;
				tmp = new Rook(x, y, color);
				a.a.pb(tmp);
				if (!color)
					a.mt.SetValue(x, y, -type);
				else
					a.mt.SetValue(x, y, type);
			}
			else if (num % 10 == 3)
			{
				type = 3;
				tmp = new Bishop(x, y, color);
				a.a.pb(tmp);
				if (!color)	
					a.mt.SetValue(x, y, -type);
				else
					a.mt.SetValue(x, y, type);
			}
			else if (num % 10 == 2)	
			{
				type = 2;
				tmp = new Knight(x, y, color);
				a.a.pb(tmp);
				if (!color)
					a.mt.SetValue(x, y, -type);
				else
					a.mt.SetValue(x, y, type);
			}
			else if (num % 10 == 4)
			{
				type = 5;
				tmp = new Queen(x, y, color);
				a.a.pb(tmp);
				if (!color)
					a.mt.SetValue(x, y, -type);
				else
					a.mt.SetValue(x, y, type);
			}
			else
			{
				type = 6;
				tmp = new King(x, y, color);
				a.a.pb(tmp);
				if (!color)
					a.mt.SetValue(x, y, -type);
				else
					a.mt.SetValue(x, y, type);
			}
		}
	}
	return in;
}


