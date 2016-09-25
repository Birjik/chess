class Matrix {
	public:
		int board[N][N];
		ull hash;
		Matrix() {
			hash = 0;
			memset(board, 0, sizeof board);
		}
		inline void Clear() 
		{
			hash = 0;
			for (int i = 0; i <= 9; ++ i) {
				for (int j = 0; j <= 9; ++ j) {
					board[i][j] = 0;
				}
			}
		}
		inline void SetValue(const int &x, const int &y, const int &val) {
			board[x][y] = val;
			hash = 0;
			for (int i = 1; i <= 8; ++ i) {
				for (int j = 1; j <= 8; ++ j) {
					hash = hash * pw + (board[i][j] + 10);
				}
			}
		}
		
		inline bool IsDifferent(Point A, Point B) {
			if (board[A.x][A.y] > 0 && board[B.x][B.y] < 0) return 1;
			if (board[A.x][A.y] < 0 && board[B.x][B.y] > 0) return 1;
			return 0;
		}

		inline bool FreeWay(Point A, Point B) {

			if (A == B) {
				return 1;
			}

			int cnt = 0;
			if (A.x == B.x) {
				for (int i = min(A.y, B.y); i <= max(A.y, B.y); ++ i) {
					if (board[A.x][i] != 0 && Point(A.x, i) != A && Point(A.x, i) != B) ++cnt;
				}
			}
			else if (A.y == B.y) {
				for (int i = min(A.x, B.x); i <= max(A.x, B.x); ++ i) {
					if (board[i][A.y] != 0 && Point(i, A.y) != A && Point(i, A.y) != B) ++cnt;
				}
			}
			else if (A.x + A.y == B.x + B.y) {
				Point startA = A;
				while (1) {
					if (board[A.x][A.y] != 0 && A != startA && Point(A.x, A.y) != B) ++cnt;
					if (A == B) break;
					if (A.x < B.x) {
						A.x++;
						A.y--;
					}
					else {
						A.x--;
						A.y++;
					}
				}
			}
			else if (A.x - A.y == B.x - B.y) {
				Point startA = A;
				while(1) {
					if (board[A.x][A.y] != 0 && A != startA && A != B) ++cnt;
					if (A == B) break;
					if (A.x < B.x) {
						A.x++;
						A.y++;
					}
					else {
						A.x--;
						A.y--;
					}
				}
			}
//			cout << "kol-vo = " << cnt << endl;
			return (cnt == 0);
		}
		~Matrix(){}
};
