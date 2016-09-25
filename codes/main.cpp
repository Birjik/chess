#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <ctime>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <map>

using namespace std;
#define fname ""
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define ll long long
#define ull unsigned long long
#define inf 1000000000
#define INF 1000000000000000000ll
const int N = 20;
using namespace std;
ull pw = 997;
static int pahan = 0;

#include "point.h"
#include "matrix.h"
#include "figure.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "Create.h"
#include "chessboard.h"
#include "attacks.h"

//map <pair<vector <Figure*>, int>, int> dp;
Point From, To;
bool check1, checkmate1;

int dp[7][6000000];

int vn;
map <ull, int> was;

static int HowMany = 0;

#include "calculate.h"

int main () {

	freopen(fname"input.txt", "r", stdin);
	freopen(fname"ai_move.txt", "w", stdout);

	memset(dp, -1, sizeof dp);

	Chessboard a;

	cin >> a;

	Chessboard *now = &a;
/*
	for (int i = 1; i <= 8; ++ i) {
		for (int j = 1; j <= 8; ++ j) {
			cout << now -> mt.board[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	*/

/*
	for (int i = 0; i < now -> a.size(); ++ i) {
		cout << now -> a[i] -> x << " " << now -> a[i] -> y << " " << now -> a[i] -> type <<  " " << now -> a[i] -> Color << endl;
		for (int j = 0; j < (int)now -> a[i] -> moves.size(); ++ j) {
			cout << now -> a[i] -> moves[j].x << " " << now -> a[i] -> moves[j].y << endl;
		}
		cout << endl;
	}
*/

	int Ans = Calculate(now, 0);
	if (Ans == -1) {
	//	cout << HowMany << endl;
		cout << "Impossible";
		return 0;
	}

//	cout << Calculate(now, 0) << endl;

	//cout << Ans << endl;
	
	cout << From.x << " " << From.y << " " << To.x << " " << To.y << endl;
	
	ofstream fout("checkmate.txt");
	if (checkmate1 == 1) {
		fout << "2";
	}
	else if (check1 == 1) {
		fout << "1";
	}
	else fout << "0";
	fout.close();
	                
//	cout << endl << "HowMany = " << HowMany << endl;
	
	cerr << "Execution Time -> " << double(clock()) / double(CLOCKS_PER_SEC) << endl;

	return 0;
}
