#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define X 0
#define Y 1
int key;						//�Է¹��� Ű�� �ƽ�Ű �ڵ� ��
int life = 12;				//������ ����
int y_p = 40;				//������ ��ġ���� (y��ǥ)
int x_p = 38;				//������ ��ġ���� (x��ǥ)
int x_b = 48;				//���� ��ġ���� (x��ǥ)
int y_b = 20;				//���� ��ġ���� (y��ǥ)
int speed = 10;			//���� �ӵ� (�������� ����)
int ball_x = 1;			//���� x�� ���� ���� (1 == ������, 0 == ����)
int ball_y = 1;			//���� y�� ���� ���� (1 == �Ʒ���, 0 == ����)
int ball_x_pas[4];		//���� �ܻ��� ����鼭 4��° ���� ���ڸ� ����� ���� x�迭
int ball_y_pas[4];		//���� �ܻ��� ����鼭 4��° ���� ���ڸ� ����� ���� y�迭
int turn_ball = 0;		//���� �Էµ� Ƚ���� �����ϱ� ���� ����
int stage = 0;			//�ӵ� ������ ���� ����
int t = 0;					//�ӵ� ������ ���� ����
int p = 0;					//���� Ƚ����� ���
int puse = 0;				//���ŵ� ���� ������ ���µ� ���
int a = 1;					//������ ���Ḧ ���� ����

struct block_set {
	int on_off;
	int location[2];
};
struct block_set		box[50][10];

int input_key();
void go_xy(int x, int y);
void ball();
void erase();
void block();


//�� ���� �� ����
void block() {
	int x, y;

	if (t == 0 && p == 0) {
		//���� ���翩�μ��� �� ��ġ����
		for (y = 0; y < 5; y++) {
			for (x = 0; x < 50; x++) {
				box[x][y].on_off = 1;
				box[x][y].location[X] = 2 * x;
				box[x][y].location[Y] = 2 * y;
			}
		}

		//���� ó�� ����
		go_xy(0, 0);
		for (y = 0; y < 10; y++) {
			for (x = 0; x < 50; x++) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
				printf("��");
			}
			printf("\n");
		}

		//�������� ���ÿ� ���� ���� ��� ����
		switch (stage) {
		case 1:

			break;
		case 2:
			for (y = 0; y < 5; y++) {
				if (y % 2 == 0) {
					for (int o = 0; o < 13; o++) {
						for (x = 4 * o; x < (4 * o) + 2; x++) {
							box[x][y].on_off = 0;
							go_xy(2 * x, 2 * y);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
							printf("��");
							go_xy(2 * x, (2 * y) + 1);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
							printf("��");
						}
					}
				}
			}
			break;
		case 3:
			for (y = 0; y < 5; y++) {
				for (x = 0; x < 50; x++) {
					box[x][y].on_off = 0;
					box[x][y].location[X] = 2 * x;
					box[x][y].location[Y] = 2 * y;
				}
			}
			go_xy(0, 0);
			for (y = 0; y < 10; y++) {
				for (x = 0; x < 50; x++) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
					printf("��");
				}
				printf("\n");
			}
			for (x = 0; x < 25; x++) {
				if (x % 5 == 0) {
					y = 2;
					box[2 * x][y].on_off = 1;
					box[2 * x + 1][y].on_off = 1;
					go_xy(4 * x, 2 * y);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("��");
					go_xy(4 * x, (2 * y) + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("��");
					go_xy(4 * x + 2, 2 * y);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("��");
					go_xy(4 * x + 2, (2 * y) + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("��");
				}
				else if (x % 5 == 1) {
					for (y = 1; y < 4; y++) {
						box[2 * x][y].on_off = 1;
						box[2 * x + 1][y].on_off = 1;
						go_xy(4 * x, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x + 2, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x + 2, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
					}
				}
				else if (x % 5 == 2) {
					for (y = 0; y < 5; y++) {
						box[2 * x][y].on_off = 1;
						box[2 * x + 1][y].on_off = 1;
						go_xy(4 * x, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x + 2, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x + 2, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
					}
				}
				else if (x % 5 == 3) {
					for (y = 1; y < 4; y++) {
						box[2 * x][y].on_off = 1;
						box[2 * x + 1][y].on_off = 1;
						go_xy(4 * x, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x + 2, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
						go_xy(4 * x + 2, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("��");
					}
				}
				if (x % 5 == 4) {
					y = 2;
					box[2 * x][y].on_off = 1;
					box[2 * x + 1][y].on_off = 1;
					go_xy(4 * x, 2 * y);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("��");
					go_xy(4 * x, (2 * y) + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("��");
					go_xy(4 * x + 2, 2 * y);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("��");
					go_xy(4 * x + 2, (2 * y) + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("��");
				}
			}
			break;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
		}
	}
	//���� �� �ε������� ���� ���� ��ȯ �� �� �����
	if (t % speed == 0) {
		for (y = 0; y < 5; y++) {
			for (x = 0; x < 50; x += 2) {
				if (x_b == (box[x][y].location[X] + 4) && y_b == (box[x][y].location[Y] + 2) && ball_x == 0 && ball_y == 0) {
					if (box[x][y].on_off == 1 && box[x + 2][y].on_off == 0 && box[x][y + 1].on_off == 0) {
						box[x][y].on_off = 0;
						box[x + 1][y].on_off = 0;
						ball_x = 1;
						ball_y = 1;
						go_xy(box[x][y].location[X], box[x][y].location[Y]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("��");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("��");
						puse += 4;
					}
				}
				else if (x_b == (box[x][y].location[X] - 2) && y_b == (box[x][y].location[Y] + 2) && ball_x == 1 && ball_y == 0) {
					if (box[x][y].on_off == 1 && box[x - 1][y].on_off == 0 && box[x][y - 1].on_off == 0) {
						box[x][y].on_off = 0;
						box[x + 1][y].on_off = 0;
						ball_x = 0;
						ball_y = 1;
						go_xy(box[x][y].location[X], box[x][y].location[Y]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("��");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("��");
						puse += 4;
					}
				}
				else if (x_b == (box[x][y].location[X] + 4) && y_b == (box[x][y].location[Y] - 1) && ball_x == 0 && ball_y == 1) {
					if (box[x][y].on_off == 1 && box[x + 2][y].on_off == 0 && box[x][y - 1].on_off == 0) {
						box[x][y].on_off = 0;
						box[x + 1][y].on_off = 0;
						ball_x = 1;
						ball_y = 0;
						go_xy(box[x][y].location[X], box[x][y].location[Y]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("��");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("��");
						puse += 4;
					}
				}
				else if (x_b == (box[x][y].location[X] - 2) && y_b == (box[x][y].location[Y] - 1) && ball_x == 1 && ball_y == 1) {
					if (box[x][y].on_off == 1 && box[x - 1][y].on_off == 0 && box[x][y - 1].on_off == 0) {
						box[x][y].on_off = 0;
						box[x + 1][y].on_off = 0;
						ball_x = 0;
						ball_y = 0;
						go_xy(box[x][y].location[X], box[x][y].location[Y]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("��");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("��");
						puse += 4;
					}
				}
				else if ((x_b == box[x][y].location[X] || x_b == (box[x][y].location[X] + 2)) && (y_b - 2) == box[x][y].location[Y]) {
					if (box[x][y].on_off == 1) {
						box[x][y].on_off = 0;
						box[x + 1][y].on_off = 0;
						ball_y = 1;
						go_xy(box[x][y].location[X], box[x][y].location[Y]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("��");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("��");
						puse += 4;
					}
				}
				else if (x_b == (box[x][y].location[X] + 4) && (y_b == box[x][y].location[Y] || y_b == (box[x][y].location[Y] + 1))) {
					if (box[x][y].on_off == 1) {
						box[x][y].on_off = 0;
						box[x + 1][y].on_off = 0;
						ball_x = 1;
						go_xy(box[x][y].location[X], box[x][y].location[Y]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("��");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("��");
						puse += 4;
					}
				}
				else if ((x_b == (box[x][y].location[X] - 2) && (y_b == box[x][y].location[Y] || y_b == (box[x][y].location[Y] + 1)))) {
					if (box[x][y].on_off == 1) {
						box[x][y].on_off = 0;
						box[x + 1][y].on_off = 0;
						ball_x = 0;
						go_xy(box[x][y].location[X], box[x][y].location[Y]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("��");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("��");
						puse += 4;
					}
				}
				else if ((x_b == box[x][y].location[X] || x_b == (box[x][y].location[X] + 2)) && (y_b + 1) == box[x][y].location[Y]) {
					if (box[x][y].on_off == 1) {
						box[x][y].on_off = 0;
						box[x + 1][y].on_off = 0;
						ball_y = 0;
						go_xy(box[x][y].location[X], box[x][y].location[Y]);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("��");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("��");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("��");
						puse += 4;
					}
				}
				if (stage == 1) {
					if (puse == 500) {
						a = 0;
					}
				}
				else if (stage == 2) {
					if (puse == 344) {
						a = 0;
					}
				}
				else if (stage == 3) {
					if (puse == 260) {
						a = 0;
					}
				}
			}
		}
		go_xy(20, 41);
		printf("���� : %d", puse / 4);
	}
}

//�� �����
void erase() {
	if (turn_ball >= 4) {
		go_xy(ball_x_pas[(turn_ball - 4) % 4], ball_y_pas[(turn_ball - 4) % 4]);
		printf("��");
	}
}

//Ŀ���� ��ġ �̵�
void go_xy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//Ű���� �Է¿� ���� Ŀ���� �̵� �� �ܷ� ���� �����
int input_key() {
	if (_kbhit())
	{
		key = _getch();
		switch (key)
		{
			/*		case 72:
			//			printf("���� ȭ��ǥ\n");
						y_p--;
						Sleep(10);
						system("cls");
						break;*/
		case 224:

			break;
		case 75:
			if (stage == 0 || stage == 50) {
				puts("\a");
				break;
			}
			//			printf("���� ȭ��ǥ\n");
			x_p -= 2;
			go_xy(x_p + 2 * life, y_p);
			printf("��");
			break;
		case 77:
			if (stage == 0 || stage == 50) {
				puts("\a");
				break;
			}
			//			printf("������ ȭ��ǥ\n");
			x_p += 2;
			go_xy(x_p - 2, y_p);
			printf("��");
			break;
			/*		case 80:
			//			printf("�Ʒ��� ȭ��ǥ\n");
						y_p++;
						Sleep(10);
						system("cls");
						break;*/
		case 32:
			if (stage == 0)
				return 0;
			else
				puts("\a");
			break;
		case 49:
			if (stage == 50) {
				stage = 1;
				return 0;
			}
			else
				puts("\a");
			break;
		case 50:
			if (stage == 50) {
				stage = 2;
				return 0;
			}
			else
				puts("\a");
			break;
		case 51:
			if (stage == 50) {
				stage = 3;
				return 0;
			}
			else
				puts("\a");
			break;
		case 99:
			if (speed > 1) {
				speed--;
				go_xy(0, 41);
				printf("                                 \r");
				printf("�ӵ� : %d", speed);
			}
			break;
		case 100:
			speed++;
			go_xy(0, 41);
			printf("                                 \r");
			printf("�ӵ� : %d", speed);
			break;
		case 109:
			speed = 15;
			break;
		case 110:
			speed = 1;
			break;
		default:
			puts("\a");
			break;
		}
	}
	return 1;
}


//���� ������
void ball() {
	//��ü�� �ε����� �� ������ Ʋ�� ���� ���ǹ�
	if (x_b >= 98) {
		ball_x = 0;
	}
	else if (x_b <= 0) {
		ball_x = 1;
	}
	if (y_b <= 0) {
		ball_y = 1;
	}
	else if (y_b >= 40) {
		life -= 2;
		if (life > 0) {
			go_xy(44, 21);
			printf("�١�����ۡ١�");
			go_xy(44, 22);
			printf("LIFE   :   - 1");
			go_xy(80, 41);
			printf("- LIFE : %d", life / 2);
			Sleep(2000);
			go_xy(44, 21);
			printf("��������");
			go_xy(44, 22);
			printf("��������");
			for (int k = 0; k < 3; k++) {
				ball_x_pas[turn_ball % 4] = x_b;
				ball_y_pas[turn_ball % 4] = y_b;
				turn_ball++;
				erase();
			}
			if (life % 2 == 0 && life >= 6 && speed > 1)
				speed -= 1;
			go_xy(0, y_p);
			for (int k = 0; k <= 49; k++)
				printf("��");
		}
		turn_ball = 0;
		x_b = 48;
		y_b = 20;
		srand(time(NULL));
		ball_x = (rand() % 2);
		ball_y = (rand() % 2);
		p = 30;
	}

	//���밡 �� �޴� ����
/*	if (x_b >= x_p && x_b < (x_p + 2 * life) && y_b == (y_p - 1)) {
		ball_y = 0;
	}*/
	if (y_b == (y_p - 1))
		ball_y = 0;

	//���� �ܻ� ����� �� 4��° �� ��ġ�� ���� �����, �̵��κ�
	if (t % speed == 0 && p == 1) {
		if (p > 0) {
			if (ball_x == 1) {
				x_b += 2;
			}
			else {
				x_b -= 2;
			}
			if (ball_y == 1) {
				y_b += 1;
			}
			else {
				y_b -= 1;
			}
		}
		go_xy(x_b, y_b);
		ball_x_pas[turn_ball % 4] = x_b;
		ball_y_pas[turn_ball % 4] = y_b;
		turn_ball++;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 46);
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
		Sleep(5);
		erase();
	}
	p = 1;
}


//���� �Լ�
void main() {
	system("color 2f");		//�ܼ� â�� ���� ����
	CONSOLE_CURSOR_INFO curif;		//Ŀ���� ȯ�漳���� ���� ����ü ����

	//Ŀ�� �����
	curif.dwSize = 1;
	curif.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curif);

	a = 1;		//������ ���Ḧ ���� ����
	const char* object = "��";		//������ �� ��ü
	system("Title ��Ƣ���");		//â ����
	system("mode con: cols=100 lines=42");		//â ũ�� ���� 100, 41

	//ù ���� ���� ����
	srand(time(NULL));
	ball_x = (rand() % 2);
	ball_y = (rand() % 2);

	//�����̽��ٸ� ������ ����
	p = 0;
	while (input_key()) {
		go_xy(34, 15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + (p % 3));
		printf("�١ڡ١ڡ١ڰ�Ƣ���١ڡ١ڡ١�");
		go_xy(42, 22);
		printf("PRESS SPACE BAR");
		Sleep(200);
		p++;
	}
	system("cls");

	//��� �������� ����
	stage = 50;
	while (input_key()) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + (p % 3));
		go_xy(35, 13);
		printf("- STAGE1  :  PRESS KEY < 1 > !");
		go_xy(35, 18);
		printf("- STAGE1  :  PRESS KEY < 2 > !");
		go_xy(35, 23);
		printf("- STAGE1  :  PRESS KEY < 3 > !");
		Sleep(200);
		p++;
	}

	system("cls");
	go_xy(43, 20);
	printf("- START -");
	go_xy(0, 0);
	Sleep(200);

	//ȭ�� ä���
	for (int k = 0; k <= 40; k++)
	{
		if (k % 2 == 0)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + (k % 3));
		for (int z = 0; z <= 49; z++)
			printf("��");
		printf("\n");
		Sleep(50);
	}
	Sleep(300);
	system("color 2f");
	p = 0;

	//��� ���� �� ����
	block();

	go_xy(80, 41);
	printf("- LIFE : %d", life / 2);
	Sleep(500);

	//������
	while (a) {
		if (life <= 0) {
			Sleep(1000);
			go_xy(0, 0);
			for (int k = 0; k <= 40; k++)
			{
				if (k % 2 == 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + (k % 3));
				for (int z = 0; z <= 49; z++)
					printf("��");
				printf("\n");
				Sleep(50);
			}
			Sleep(1000);
			system("cls");
			go_xy(36, 15);
			printf("�ƽ��Ե� �й��Ͽ����ϴ�..");
			go_xy(36, 16);
			Sleep(1300);
			a = 0;
			break;
		}
		p = 1;
		go_xy(x_p, y_p);
		for (int i = life; i > 0; i--)		//���� ��ü ����
			printf("%s", object);
		input_key();		//Ű���� �Է¹ޱ�
		Sleep(4);
		ball();
		block();				//�� ����
		t++;
		if (y_b >= 40)
			t = 0;

		//â ������ ����� �ʰ� �ϱ� ���� ���� �ִ�, �ּ� ����
		if (x_p > 100 - 2 * life)
			x_p = 100 - 2 * life;
		else if (x_p < 0)
			x_p = 0;
	}
	if (stage == 1) {
		if (puse == 500) {
			system("cls");
			go_xy(36, 15);
			printf("�����մϴ�!!! �¸��ϼ̽��ϴ�!!!");
			Sleep(2200);
			go_xy(36, 16);
		}
	}
	else if (stage == 2) {
		if (puse == 344) {
			system("cls");
			go_xy(36, 15);
			printf("�����մϴ�!!! �¸��ϼ̽��ϴ�!!!");
			Sleep(2200);
			go_xy(36, 16);
		}
	}
	else if (stage == 3) {
		if (puse == 260) {
			system("cls");
			go_xy(36, 15);
			printf("�����մϴ�!!! �¸��ϼ̽��ϴ�!!!");
			Sleep(2200);
			go_xy(36, 16);
		}
	}
}