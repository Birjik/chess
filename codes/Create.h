inline Figure* Create(const Figure &T) {
	Figure *ret;
	if (T.type == 1) ret = new Pawn(T.x, T.y, T.Color);
	if (T.type == 2) ret = new Knight(T.x, T.y, T.Color);
	if (T.type == 3) ret = new Bishop(T.x, T.y, T.Color);
	if (T.type == 4) ret = new Rook(T.x, T.y, T.Color);
	if (T.type == 5) ret = new Queen(T.x, T.y, T.Color);
	if (T.type == 6) ret = new King(T.x, T.y, T.Color);
	return ret;
}

inline Figure* CreateFigureFromPoint(Point A, bool Color, int type) {
	Figure *ret;
	if (type == 1) ret = new Pawn(A.x, A.y, Color);
	if (type == 2) ret = new Knight(A.x, A.y, Color);
	if (type == 3) ret = new Bishop(A.x, A.y, Color);
	if (type == 4) ret = new Rook(A.x, A.y, Color);
	if (type == 5) ret = new Queen(A.x, A.y, Color);
	if (type == 6) ret = new King(A.x, A.y, Color);
	return ret;
}
