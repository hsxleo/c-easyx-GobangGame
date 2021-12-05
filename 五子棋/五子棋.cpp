#include <iostream>
#include <graphics.h>
#include <conio.h>
#pragma comment(lib,"Winmm.lib")  //��ӵı�������

using namespace std;

int chess[16][16] = { 0 };  //���̵�����
int color = 1;  //1 ���� 2 ���� 3 ����

//��������
void drawChessboard() {   
	initgraph(600, 400);
	setbkcolor(0x708090);
	cleardevice();
	//����������
	setlinecolor(BLACK);
	for (int i = 25; i <= 375; i+=25) {
		line(i, 25, i, 375);
		line(25, i, 375, i);
	}
	//���������ϵ������
	setfillcolor(BLACK);
	solidcircle(100, 100, 4);
	solidcircle(100, 300, 4);
	solidcircle(300, 100, 4);
	solidcircle(300, 300, 4);
	solidcircle(200, 200, 4);
	//������
	settextcolor(BLACK);          //����������ɫ
	settextstyle(30, 0, "������κ"); //����������ʽ
	setbkmode(TRANSPARENT);       //���ֱ���͸��
	outtextxy(420, 50, "���˶�ս");
	outtextxy(420, 100, "�˻���ս");
	outtextxy(420, 150, "�����ϰ�");
	outtextxy(420, 200, "�˳���Ϸ");
	outtextxy(410, 300, "����");
	outtextxy(500, 300, "����");
}

//������
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


//�������
void inputOver(int color) {
	settextcolor(RED);          //����������ɫ
	settextstyle(30, 0, "������κ"); //����������ʽ
	setbkmode(TRANSPARENT);       //���ֱ���͸��
	switch (color) {
	case 1:
		outtextxy(200, 150, "�����ʤ");
		break;
	case 2:
		outtextxy(200, 150, "�����ʤ");
		break;
	}
	_getch();
}

//�ж���Ϸ�Ƿ����
void judgeWin(int x,int y,int color) {
	int count = 0;
	for (int i = x - 4; i <= x + 4; i++) {  //��ֱ����
		if (i < 0 || i > 15) continue;
		if (chess[i][y] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = y - 4; i <= y + 4; i++) {  //ˮƽ����
		if (i < 0 || i > 15) continue;
		if (chess[x][i] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = x - 4, j = y - 4; i <= x + 4; i++,j++) {   //���Խ���
		if (i < 0 || i > 15 || j < 0 || j > 15) continue;
		if (chess[i][j] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
	count = 0;
	for (int i = x - 4, j = y + 4; i <= x + 4; i++, j--) {   //���Խ���
		if (i < 0 || i > 15 || j < 0 || j > 15) continue;
		if (chess[i][j] != color) count = 0;
		else {
			count++;
			if (count == 5) inputOver(color);
		}
	}
}

//��¼��һ��
void lastGame(int a[][16]) {
	for(int i=0;i <= 15;i++)
		for (int j = 0; j <= 15; j++) {
			a[i][j] = chess[i][j];
		}
}

//����
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




//�˻���ս
/*
����Ϊ���  ����Ϊ����

������һ�ӵ��Ի�Ժ�����Χ��8����������жϣ��ҵ�һ��������Ҫ����ģ�Ȼ���ڱ������ĸ������ģ����Ǿ�Ҫ������������ӵ�һ�˻���һ���ð����ס��
����ĸ�������8������û�У��ͼ��������ң���3���ģ���2���������ơ�
*/
int PCGame(int x,int y,int n) {
	int color = 1;
	int count = 0;
	int m =  n + 1;
	for (int i = x - n; i <= x; i++) {  //ˮƽ����
		if (i < 0) break;  //�����ж�
		if (chess[i][y] != color) break; 
		else {
			count++;
			if (count == m) {  //������������   ����ͷ���ж���
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
	for (int i = x; i <= x + n; i++) {  //ˮƽ����
		if (i > 15) break;
		if (chess[i][y] != color) break;
		else {
			count++;
			if (count == m) {  //������������   ����ͷ���ж���
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
	for (int i = y - n; i <= y; i++) {  //��ֱ����
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
	for (int i = y; i <= y + n; i++) {  //��ֱ����
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
	for (int i = x - n,j = y - n; i <= x; i++,j++) {   //���Խ���
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
	for (int i = x, j = y; i <= x + n; i++, j++) {   //���Խ���
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
	for (int i = x - n, j = y + n; i <= x; i++, j--) {   //���Խ���
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
	for (int i = x , j = y; i <= x + n; i++, j--) {   //���Խ���
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

//�����  
void mouseClick() {
	MOUSEMSG m;
	boolean beginSet = false;   //��ʼʱ�����ϰ��ı�־
	boolean addSetflg = false;  //���ϵı�־
	int addSet1 = 1;  //������ϵı�־
	int addSet2 = 1;  //������ϵı�־
	int pcFlg = 0;  //�Ƿ����
	boolean choose = false;
	int chess1[16][16] = { 0 };  //��¼����
	int chess2[16][16] = { 0 };  //��¼����
	int regretFlg = false;  //�Ƿ����ı�־
	while (true) {
		m = GetMouseMsg();
		int flg = 1;
		if (m.uMsg == WM_LBUTTONDOWN) {  //����������
			if(choose || beginSet)
			for (int i = 25; i <= 400; i+=25) {
				for (int j = 25; j <= 400; j += 25) {
					if (m.x >= i - 8 && m.x <= i + 8 && m.y >= j - 8 && m.y <= j + 8 ) {
						if (addSet1 == 0) {   //�������
							addSet1--;
							chess[i / 25][j / 25] = 3;
							drawChess(i / 25, j / 25, 3);
							flg = 0;
							break;
						}
						else if (addSet2 == 0) {  //�������
							addSet2--;
							chess[i / 25][j / 25] = 3;
							drawChess(i / 25, j / 25, 3);
							flg = 0;
							break;
						}
						else if (chess[i / 25][j / 25] != 0) {  //��λ��������
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
							if (pcFlg == 1) {   //��������
								lastGame(chess2);
								for (int t = 4; t >= 0; t--) {  //ѭ���ж�  Ѱ�����һ��  4��3��2��1��0
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
			if (m.x >= 420 && m.x <= 540 && m.y >= 50 && m.y <= 80) {  //���˶�ս
				choose = true;    //ѡ������ģʽ
				beginSet = true;  //�����������ϰ�
				color = 1; //���忪ʼ��Ϸ
				//PPGame();
			}
			else if (m.x >= 420 && m.x <= 540 && m.y >= 100 && m.y <= 130) {  //�˻���ս
				choose = true;    //ѡ������ģʽ
				beginSet = true;  //�����������ϰ�
				color = 1; //���忪ʼ��Ϸ
				pcFlg = 1;
			}
			else if (m.x >= 420 && m.x <= 540 && m.y >= 150 && m.y <= 180 && !beginSet) {  //�����ϰ�
				beginSet = true;  //�����ٽ�������
				color = 3; //��Ϊ����
			}
			else if (m.x >= 410 && m.x <= 470 && m.y >= 300 && m.y <= 330 && regretFlg) {  //����
				if (color == 1) regret(chess1);  //�ص���һ��
				else regret(chess2);
				regretFlg = false;
			}
			else if (m.x >= 500 && m.x <= 560 && m.y >= 300 && m.y <= 330 && (color == 1 && addSet1 == 1 || color == 2 && addSet2 == 1)) {  //����
				if (color == 1) addSet1--;
				else if (color == 2) addSet2--;
			}
		}
	}
}



int main() {
	//��Ϸ��������
	mciSendString("open music.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	//��������
	drawChessboard(); 
	mouseClick();
	_getch();
}