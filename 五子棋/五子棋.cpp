#include <iostream>
#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")  //添加的背景音乐

using namespace std;

int chess[16][16] = { 0 };  //棋盘的数组
int color = 1;  //1 黑棋 2 白棋 3 红棋

//绘制棋盘
void drawChessboard() {   
	initgraph(600, 400);
	setbkcolor(0x708090);
	cleardevice();
	//绘制棋盘线
	setlinecolor(BLACK);
	for (int i = 25; i <= 375; i+=25) {
		line(i, 25, i, 375);
		line(25, i, 375, i);
	}
	//绘制棋盘上的五个点
	setfillcolor(BLACK);
	solidcircle(100, 100, 4);
	solidcircle(100, 300, 4);
	solidcircle(300, 100, 4);
	solidcircle(300, 300, 4);
	solidcircle(200, 200, 4);
	//功能栏
	settextcolor(BLACK);          //设置字体颜色
	settextstyle(30, 0, "华文新魏"); //设置文字样式
	setbkmode(TRANSPARENT);       //文字背景透明
	outtextxy(420, 50, "人人对战");
	outtextxy(420, 100, "人机对战");
	outtextxy(420, 150, "设置障碍");
	outtextxy(420, 200, "退出游戏");
	outtextxy(410, 300, "悔棋");
	outtextxy(500, 300, "加障");
}

//绘制棋
void drawChess(int x, int y,int color) {
	switch (color) {
	case 1:
		setfillcolor(BLACK);
		break;
	case 2:
		setfillcolor(WHITE);
		break;

	case 3:
		setfillcolor(RED);
		break;
	}
	solidcircle(x*25, y*25, 8);
}


//输出结束
void inputOver(int color) {
	settextcolor(RED);          //设置字体颜色
	settextstyle(30, 0, "华文新魏"); //设置文字样式
	setbkmode(TRANSPARENT);       //文字背景透明
	switch (color) {
	case 1:
		outtextxy(200, 150, "黑棋获胜");
		break;
	case 2:
		outtextxy(200, 150, "白棋获胜");
		break;
	}
	_getch();
}

//判断游戏是否结束
void judgeWin(int x,int y,int color) {
	int count = 0;
	for (int i = x - 4; i <= x + 4; i++) {  //垂直方向
		if (i < 0 || i > 15) continue;
		if (chess[i][y] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = y - 4; i <= y + 4; i++) {  //水平方向
		if (i < 0 || i > 15) continue;
		if (chess[x][i] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = x - 4, j = y - 4; i <= x + 4; i++,j++) {   //正对角线
		if (i < 0 || i > 15 || j < 0 || j > 15) continue;
		if (chess[i][j] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = x - 4, j = y + 4; i <= x + 4; i++, j--) {   //反对角线
		if (i < 0 || i > 15 || j < 0 || j > 15) continue;
		if (chess[i][j] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
}

//记录上一步
void lastGame(int a[][16]) {
	for(int i=0;i <= 15;i++)
		for (int j = 0; j <= 15; j++) {
			a[i][j] = chess[i][j];
		}
}

//悔棋
void regret(int a[][16]) {
	for (int i = 0; i <= 15; i++)
		for (int j = 0; j <= 15; j++) {
			chess[i][j] = a[i][j];
		}

	drawChessboard();
	for (int i = 0; i <= 15; i++)
		for (int j = 0; j <= 15; j++) {
			if (chess[i][j] != 0) drawChess(i, j, chess[i][j]);
		}
}




//人机对战
/*
黑棋为玩家  白棋为电脑

黑棋下一子电脑会对黑棋周围的8个方向进行判断，找到一种最优先要解决的，然后在比如有四个连续的，我们就要在这段连续棋子的一端或另一端用白棋堵住，
如果四个连续的8个方向都没有，就继续往下找，找3个的，找2个依次类推。
*/
int PCGame(int x,int y,int n) {
	int color = 1;
	int count = 0;
	int m =  n + 1;
	for (int i = x - n; i <= x; i++) {  //水平方向
		if (i < 0) break;  //出界判断
		if (chess[i][y] != color) break; 
		else {
			count++;
			if (count == m) {  //连续个数满足   在两头进行堵塞
				if(i <= 14)
					if (chess[i + 1][y] == 0) {
						drawChess(i + 1, y, 2);
						chess[i + 1][y] = 2;
						return 1;
					}
				if (i >= m)
					if (chess[i - m][y] == 0) {
						drawChess(i - m, y, 2);
						chess[i - m][y] = 2;
						return 1;
					}
			}
		}
	}
	count = 0;
	for (int i = x; i <= x + n; i++) {  //水平方向
		if (i > 15) break;
		if (chess[i][y] != color) break;
		else {
			count++;
			if (count == m) {  //连续个数满足   在两头进行堵塞
				if (i <= 14)
					if (chess[i + 1][y] == 0) {
						drawChess(i + 1, y, 2);
						chess[i + 1][y] = 2;
						return 1;
					}
				if (i >= m)
					if (chess[i - m][y] == 0) {
						drawChess(i - m, y, 2);
						chess[i - m][y] = 2;
						return 1;
					}
			}
		}
	}
	count = 0;
	for (int i = y - n; i <= y; i++) {  //垂直方向
		if (i < 0 ) break;
		if (chess[x][i] != color) break;
		else {
			count++;
			if (count == m) {
				if (i <= 14)
					if (chess[x][i + 1] == 0) {
						drawChess(x, i + 1, 2);
						chess[x][i + 1] = 2;
						return 1;
					}
				if (i >= m)
					if (chess[x][i - m] == 0) {
						drawChess(x, i - m, 2);
						chess[x][i - m] = 2;
						return 1;
					}
			}
		}
	}
	count = 0;
	for (int i = y; i <= y + n; i++) {  //垂直方向
		if (i > 15) break;
		if (chess[x][i] != color) break;
		else {
			count++;
			if (count == m) {
				if (i <= 14)
					if (chess[x][i + 1] == 0) {
						drawChess(x, i + 1, 2);
						chess[x][i + 1] = 2;
						return 1;
					}
				if (i >= m)
					if (chess[x][i - m] == 0) {
						drawChess(x, i - m, 2);
						chess[x][i - m] = 2;
						return 1;
					}
			}
		}
	}
	count = 0;
	for (int i = x - n,j = y - n; i <= x; i++,j++) {   //主对角线
		if (i < 0 || j < 0) break;;
		if (chess[i][j] != color) break;
		else {
			count++;
			if (count == m) {
				if (i <= 14 && j <= 14)
					if (chess[i + 1][j + 1] == 0) {
						drawChess(i + 1, j + 1, 2);
						chess[i + 1][j + 1] = 2;
						return 1;
					}
				if (i >= m && j >= m)
					if (chess[i - m][j - m] == 0) {
						drawChess(i - m, j - m, 2);
						chess[i - m][j - m] = 2;
						return 1;
					}
						
			}
		}
	}
	count = 0;
	for (int i = x, j = y; i <= x + n; i++, j++) {   //主对角线
		if (i > 15 || j > 15) break;
		if (chess[i][j] != color) break;
		else {
			count++;
			if (count == m) {
				if (i <= 14 && j <= 14)
					if (chess[i + 1][j + 1] == 0) {
						drawChess(i + 1, j + 1, 2);
						chess[i + 1][j + 1] = 2;
						return 1;
					}
				if (i >= m && j >= m)
					if (chess[i - m][j - m] == 0) {
						drawChess(i - m, j - m, 2);
						chess[i - m][j - m] = 2;
						return 1;
					}
			}
		}
	}
	count = 0;
	for (int i = x - n, j = y + n; i <= x; i++, j--) {   //副对角线
		if (i < 0 || j < 0) break;
		if (chess[i][j] != color) break;
		else {
			count++;
			if (count == m) {
				if (i <= 14 && j >= 1)
					if (chess[i + 1][j - 1] == 0) {
						drawChess(i + 1, j - 1, 2);
						chess[i + 1][j - 1] = 2;
						return 1;
					}
				if (i >= m && j <= 15 - m)
					if (chess[i - m][j + m] == 0) {
						drawChess(i - m, j + m, 2);
						chess[i - m][j + m] = 2;
						return 1;
					}
			}
		}
	}
	count = 0;
	for (int i = x , j = y; i <= x + n; i++, j--) {   //副对角线
		if (i > 15 || j > 15) break;
		if (chess[i][j] != color) break;
		else {
			count++;
			if (count == m) {
				if (i <= 14 && j >= 1)
					if (chess[i + 1][j - 1] == 0) {
						drawChess(i + 1, j - 1, 2);
						chess[i + 1][j - 1] = 2;
						return 1;
					}
				if (i >= m && j <= 15 - m)
					if (chess[i - m][j + m] == 0) {
						drawChess(i - m, j + m, 2);
						chess[i - m][j + m] = 2;
						return 1;
					}
			}
		}
	}
	return 0;
}

//鼠标点击  
void mouseClick() {
	MOUSEMSG m;
	boolean beginSet = false;   //开始时设置障碍的标志
	boolean addSetflg = false;  //加障的标志
	int addSet1 = 1;  //黑棋加障的标志
	int addSet2 = 1;  //白起加障的标志
	int pcFlg = 0;  //是否进行
	boolean choose = false;
	int chess1[16][16] = { 0 };  //记录黑棋
	int chess2[16][16] = { 0 };  //记录白棋
	int regretFlg = false;  //是否悔棋的标志
	while (true) {
		m = GetMouseMsg();
		int flg = 1;
		if (m.uMsg == WM_LBUTTONDOWN) {  //鼠标左键按下
			if(choose || beginSet)
			for (int i = 25; i <= 400; i+=25) {
				for (int j = 25; j <= 400; j += 25) {
					if (m.x >= i - 8 && m.x <= i + 8 && m.y >= j - 8 && m.y <= j + 8 ) {
						if (addSet1 == 0) {   //黑棋加障
							addSet1--;
							chess[i / 25][j / 25] = 3;
							drawChess(i / 25, j / 25, 3);
							flg = 0;
							break;
						}
						else if (addSet2 == 0) {  //白棋加障
							addSet2--;
							chess[i / 25][j / 25] = 3;
							drawChess(i / 25, j / 25, 3);
							flg = 0;
							break;
						}
						else if (chess[i / 25][j / 25] != 0) {  //该位置已有棋
								flg = 0;
								break;
						}
						int x = i / 25;
						int y = j / 25;
						drawChess(x, y, color);
						switch (color)	
						{
						case 1:
							regretFlg = true;
							lastGame(chess1);
							chess[x][y] = 1;
							judgeWin(x, y, color);
							color = 2;
							if (pcFlg == 1) {   //机器下棋
								lastGame(chess2);
								for (int t = 4; t >= 0; t--) {  //循环判断  寻找最急的一种  4、3、2、1、0
									if (PCGame(x, y, t)) break;
								}
								judgeWin(x, y, 2);
								Sleep(100);
								color = 1;
							}
							break;
						case 2:
							regretFlg = true;
							lastGame(chess2);
							chess[x][y] = 2;
							judgeWin(x, y, color);
							color = 1;
							break;
						case 3:
							chess[x][y] = 3;
							break;
						}
						flg = 0;
						break;
					}
				}
				if (flg == 0) break;
			}
			if (m.x >= 420 && m.x <= 540 && m.y >= 50 && m.y <= 80) {  //人人对战
				choose = true;    //选择完了模式
				beginSet = true;  //不可以设置障碍
				color = 1; //黑棋开始游戏
				//PPGame();
			}
			else if (m.x >= 420 && m.x <= 540 && m.y >= 100 && m.y <= 130) {  //人机对战
				choose = true;    //选择完了模式
				beginSet = true;  //不可以设置障碍
				color = 1; //黑棋开始游戏
				pcFlg = 1;
			}
			else if (m.x >= 420 && m.x <= 540 && m.y >= 150 && m.y <= 180 && !beginSet) {  //设置障碍
				beginSet = true;  //不能再进行设置
				color = 3; //变为红棋
			}
			else if (m.x >= 410 && m.x <= 470 && m.y >= 300 && m.y <= 330 && regretFlg) {  //悔棋
				if (color == 1) regret(chess1);  //回到上一步
				else regret(chess2);
				regretFlg = false;
			}
			else if (m.x >= 500 && m.x <= 560 && m.y >= 300 && m.y <= 330 && (color == 1 && addSet1 == 1 || color == 2 && addSet2 == 1)) {  //加障
				if (color == 1) addSet1--;
				else if (color == 2) addSet2--;
			}
		}
	}
}



int main() {
	//游戏背景音乐
	mciSendString("open music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	//绘制棋盘
	drawChessboard(); 
	mouseClick();
	_getch();
}