inline int Calculate(Chessboard *cur, int level) {
    HowMany++;
    int State = 1;
    if (cur -> IsCheck(level % 2)) {
        State = 2;
    }
    
    if (level > 5 || (level == 5 && State != 2)) {
        return -1;
    }
    
    if (!was[cur -> mt.hash]) was[cur -> mt.hash] = ++vn;
    
    int index = was[cur -> mt.hash];
    
    if (dp[level][index] != -1) {
        return dp[level][index];
    }
    
    if (level % 2 == 0) dp[level][index] = -1;
    else dp[level][index] = 0;
    ///	Delaem Move

    for (int i = 0; i < (int)cur -> a.size(); ++ i) {
        if (cur -> a[i] -> Color == (level % 2)) {
            for (int j = 0; j < cur -> a[i] -> moves.size(); ++ j) {
                Point nxtMove = cur -> a[i] -> moves[j];
 
// 				cout << "level = " << level << endl;
//				cout << cur -> a[i] -> x << " " << cur -> a[i] -> y << " " << cur -> a[i] -> type << " " << cur -> a[i] -> type << endl;
//				cout << nxtMove.x << " " << nxtMove.y << endl;
//				continue;

/*
				if (nxtMove == Point(2, 7)) {
					cerr << "lvl = " << level << " " << i << endl;
					cerr << cur -> a[i] -> x << " " << cur -> a[i] -> y << " " << cur -> a[i] -> type << "\n";
					exit(0);
				}
  */             
                if (cur -> mt.board[nxtMove.x][nxtMove.y] == 0 && cur -> mt.FreeWay(Point(cur -> a[i] -> x, cur -> a[i] -> y), nxtMove)) {
                    if (cur -> a[i] -> type == 1 && ((cur -> a[i] -> Color == 0 && cur -> a[i] -> y == 7) || (cur -> a[i] -> Color == 1 && cur -> a[i] -> y == 2))) {
                        // Pewka prevrawaetsya
                        Chessboard *nxtBoard = new Chessboard(*cur);
                        nxtBoard -> Delete(Point(cur -> a[i] -> x, cur -> a[i] -> y));
                        nxtBoard -> Insert(CreateFigureFromPoint(cur -> a[i] -> moves[j], cur -> a[i] -> Color, 5));
                        if (nxtBoard -> IsValid(level % 2)) {
                            State = 0;
                            if (level == 5)
                                return -1;
                            if (level % 2 == 0) {
                                int val = Calculate(nxtBoard, level + 1) ;
                                if (val != -1)
                                {
                                    if (dp[level][index] == -1 || dp[level][index] > val + 1)
                                    {
                                        dp[level][index] = val + 1;
										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                        if (!val)
                                            return dp[level][index];
                                    }
                                }
                            }
                            else {
                                int val = Calculate(nxtBoard, level + 1);
                                if (val == -1)
                                {
                                    dp[level][index] = -1;
                                    return dp[level][index];
                                }
                                else
                                {
                                    if (dp[level][index] != -1 && dp[level][index] < val + 1)
                                    {
                                        dp[level][index] = val + 1;
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                   }
                                }
                            }
                        }
                        
                        Chessboard *Board = new Chessboard(*cur);
                        Board -> Delete(Point(cur -> a[i] -> x, cur -> a[i] -> y));
                        Board -> Insert(CreateFigureFromPoint(cur -> a[i] -> moves[j], cur -> a[i] -> Color, 2));
                        if (Board -> IsValid(level % 2)) {
                            State = 0;
                            if (level == 5)
                                return -1;
                            if (level % 2 == 0) {
                                int val = Calculate(nxtBoard, level + 1);
                                if (val != -1)
                                {
                                    if (dp[level][index] == -1 || dp[level][index] > val + 1)
                                    {
                                        dp[level][index] = val + 1;
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                       if (!val)
                                            return dp[level][index];
                                    }
                                }
                            }
                            else {
                                int val = Calculate(nxtBoard, level + 1);
                                if (val == -1)
                                {
                                    dp[level][index] = -1;
                                    return dp[level][index];
                                }
                                else
                                {
                                    if (dp[level][index] != -1 && dp[level][index] < val + 1)
                                    {
                                        dp[level][index] = val + 1;
										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                   }
                                }
                            }
						}
                    }
                    else {
                        Chessboard *nxtBoard = new Chessboard(*cur);
                        nxtBoard -> Delete(Point(cur -> a[i] -> x, cur -> a[i] -> y));
                        nxtBoard -> Insert(CreateFigureFromPoint(cur -> a[i] -> moves[j], cur -> a[i] -> Color, cur -> a[i] -> type));
                        
                        //						if (ss) cerr << "tut on\n";
                        if (nxtBoard -> IsValid(level % 2)) {
                            //We will do move (cur -> nxtBoard)
                            State = 0;
                            if (level == 5)
                                return -1;
                            if (level % 2 == 0) {
                                int val = Calculate(nxtBoard, level + 1);
                                if (val != -1)
                                {
                                    if (dp[level][index] == -1 || dp[level][index] > val + 1)
                                    {
                                        dp[level][index] = val + 1;
										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}

										if (!val)
                                            return dp[level][index];
                                    }
                                }
                            }
                            else {
                                int val = Calculate(nxtBoard, level + 1) ;
                                if (val == -1)
                                {
                                    dp[level][index] = -1;
                                    return dp[level][index];
                                }
                                else
                                {
                                    if (dp[level][index] != -1 && dp[level][index] < val + 1)
                                    {
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                       dp[level][index] = val + 1;
                                    }
                                }
                            }
						}
                    }
                }
            }
        }
    }
    ///	Sdelali Move
    
	
    // Delaem Capture
    for (int i = 0; i < (int)cur -> a.size(); ++ i) {
        if (cur -> a[i] -> Color == (level % 2)) {
            for (int j = 0; j < (int)cur -> a[i] -> captures.size(); ++ j) {
                Point nxtMove = cur -> a[i] -> captures[j];
                if (cur -> mt.board[nxtMove.x][nxtMove.y] != 0 && cur -> mt.IsDifferent(Point(cur -> a[i] -> x, cur -> a[i] -> y), cur -> a[i] -> captures[j])
                    && cur -> mt.FreeWay(Point(cur -> a[i] -> x, cur -> a[i] -> y), nxtMove)) {
                    // Suda idet norm pacan nxtMove nado havat'
                    
                    if (cur -> a[i] -> type == 1 && ((cur -> a[i] -> Color == 0 && cur -> a[i] -> y == 7) || (cur -> a[i] -> Color == 1 && cur -> a[i] -> y == 2))) {
                        // Pewka havaet
                        Chessboard *nxtBoard = new Chessboard(*cur);
                        nxtBoard -> Delete(Point(cur -> a[i] -> x, cur -> a[i] -> y));
                        nxtBoard -> Delete(nxtMove);
                        nxtBoard -> Insert(CreateFigureFromPoint(cur -> a[i] -> captures[j], cur -> a[i] -> Color, 5));
                        
                        if (nxtBoard -> IsValid(level % 2)) {
                            State = 0;
                            if (level == 5)
                                return -1;
                            if (level % 2 == 0) {
                                int val = Calculate(nxtBoard, level + 1) ;
                                if (val != -1)
                                {
                                    if (dp[level][index] == -1 || dp[level][index] > val + 1)
                                    {
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                       dp[level][index] = val + 1;
                                        if (!val)
                                            return dp[level][index];
                                    }
                                }
                            }
                            else {
                                int val = Calculate(nxtBoard, level + 1);
                                if (val == -1)
                                {
                                    dp[level][index] = -1;
                                    return dp[level][index];
                                }
                                else
                                {
                                    if (dp[level][index] != -1 && dp[level][index] < val + 1)
                                    {
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                       dp[level][index] = val + 1;
                                    }
                                }
                            }
                       	} 
                        Chessboard *Board = new Chessboard(*cur);
                        Board -> Delete(Point(cur -> a[i] -> x, cur -> a[i] -> y));
                        Board -> Delete(nxtMove);
                        Board -> Insert(CreateFigureFromPoint(cur -> a[i] -> captures[j], cur -> a[i] -> Color, 2));
                        if (Board -> IsValid(level % 2)) {
                            State = 0;
                            if (level == 5)
                                return -1;
                            if (level % 2 == 0) {
                                int val = Calculate(nxtBoard, level + 1) ;
                                if (val != -1)
                                {
                                    if (dp[level][index] == -1 || dp[level][index] > val + 1)
                                    {
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                       dp[level][index] = val + 1;
                                        if (!val)
                                            return dp[level][index];
                                    }
                                }
                            }
                            else {
                                int val = Calculate(nxtBoard, level + 1);
                                if (val == -1)
                                {
                                    dp[level][index] = -1;
                                    return dp[level][index];
                                }
                                else
                                {
                                    if (dp[level][index] != -1 && dp[level][index] < val + 1)
                                    {
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                       dp[level][index] = val + 1;
                                    }
                                }
                            }
						}
                    }
                    else {
                        Chessboard *nxtBoard = new Chessboard(*cur);	
                        nxtBoard -> Delete(Point(cur -> a[i] -> x, cur -> a[i] -> y));
                        nxtBoard -> Delete(nxtMove);
                        nxtBoard -> Insert(CreateFigureFromPoint(cur -> a[i] -> captures[j], cur -> a[i] -> Color, cur -> a[i] -> type));
                        if (nxtBoard -> IsValid(level % 2)) {
                            State = 0;
                            if (level == 5)
                                return -1;
                            if (level % 2 == 0) {
                                int val = Calculate(nxtBoard, level + 1) ;
                                if (val != -1)
                                {
                                    if (dp[level][index] == -1 || dp[level][index] > val + 1)
                                    {
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                       dp[level][index] = val + 1;
                                        if (!val)
                                            return dp[level][index];
                                    }
                                }
                            }
                            else	 
                            {
                                int val = Calculate(nxtBoard, level + 1);
                                if (val == -1)
                                {
                                    dp[level][index] = -1;
                                    return dp[level][index];
                                }
                                else
                                {
                                    if (dp[level][index] != -1 && dp[level][index] < val + 1)
                                    {
 										if (level == 0) {
											From = Point(cur -> a[i] -> x, cur -> a[i] -> y); 
											To = nxtMove;
										}
                                       dp[level][index] = val + 1;
                                    }
                                }
                            }
						}
                    }				
                }
            }
        }
    }
    
	if (State == 1)
    {
        //		cur -> show();
        //		cout << "\ndp = Draw\n";
        dp[level][index] = -1;
    }
    if (State == 2)
    {
        //		cur -> show();
        //		cout << "\nCheckMate\n";
        dp[level][index] = 0;
    }
    // Sdelali capture
  /*  
     for (int i = 1; i <= 8; ++ i) {
     for (int j = 1; j <= 8; ++ j) {
     cout << cur -> mt.board[i][j] << " ";
     }
     cout << endl;
     }
     cout << "dp : " << dp[level][index] << " , level = " << level << endl << endl;
*/     
    return dp[level][index];
}
