#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define X 0
#define Y 1
int key;						//입력받은 키의 아스키 코드 값
int life = 12;				//라이프 갯수
int y_p = 40;				//막대의 위치지정 (y좌표)
int x_p = 38;				//막대의 위치지정 (x좌표)
int x_b = 48;				//공의 위치지정 (x좌표)
int y_b = 20;				//공의 위치지정 (y좌표)
int speed = 10;			//공의 속도 (작을수록 빠름)
int ball_x = 1;			//공의 x축 방향 지정 (1 == 오른쪽, 0 == 왼쪽)
int ball_y = 1;			//공의 y축 방향 지정 (1 == 아래쪽, 0 == 위쪽)
int ball_x_pas[4];		//공의 잔상을 남기면서 4번째 전의 문자를 지우기 위한 x배열
int ball_y_pas[4];		//공의 잔상을 남기면서 4번째 전의 문자를 지우기 위한 y배열
int turn_ball = 0;		//공이 입력된 횟수를 저장하기 위한 변수
int stage = 0;			//속도 조절을 위한 변수
int t = 0;					//속도 조절을 위한 변수
int p = 0;					//여러 횟수제어에 사용
int puse = 0;				//제거된 블럭의 갯수를 세는데 사용
int a = 1;					//게임의 종료를 위한 변수

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


//블럭 유형 및 생성
void block() {
	int x, y;

	if (t == 0 && p == 0) {
		//블럭의 존재여부설정 및 위치지정
		for (y = 0; y < 5; y++) {
			for (x = 0; x < 50; x++) {
				box[x][y].on_off = 1;
				box[x][y].location[X] = 2 * x;
				box[x][y].location[Y] = 2 * y;
			}
		}

		//블럭의 처음 설정
		go_xy(0, 0);
		for (y = 0; y < 10; y++) {
			for (x = 0; x < 50; x++) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
				printf("□");
			}
			printf("\n");
		}

		//스테이지 선택에 따른 블럭의 모양 결정
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
							printf("□");
							go_xy(2 * x, (2 * y) + 1);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
							printf("□");
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
					printf("□");
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
					printf("□");
					go_xy(4 * x, (2 * y) + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("□");
					go_xy(4 * x + 2, 2 * y);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("□");
					go_xy(4 * x + 2, (2 * y) + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("□");
				}
				else if (x % 5 == 1) {
					for (y = 1; y < 4; y++) {
						box[2 * x][y].on_off = 1;
						box[2 * x + 1][y].on_off = 1;
						go_xy(4 * x, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x + 2, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x + 2, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
					}
				}
				else if (x % 5 == 2) {
					for (y = 0; y < 5; y++) {
						box[2 * x][y].on_off = 1;
						box[2 * x + 1][y].on_off = 1;
						go_xy(4 * x, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x + 2, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x + 2, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
					}
				}
				else if (x % 5 == 3) {
					for (y = 1; y < 4; y++) {
						box[2 * x][y].on_off = 1;
						box[2 * x + 1][y].on_off = 1;
						go_xy(4 * x, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x + 2, 2 * y);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
						go_xy(4 * x + 2, (2 * y) + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
						printf("□");
					}
				}
				if (x % 5 == 4) {
					y = 2;
					box[2 * x][y].on_off = 1;
					box[2 * x + 1][y].on_off = 1;
					go_xy(4 * x, 2 * y);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("□");
					go_xy(4 * x, (2 * y) + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("□");
					go_xy(4 * x + 2, 2 * y);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("□");
					go_xy(4 * x + 2, (2 * y) + 1);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + 14);
					printf("□");
				}
			}
			break;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
		}
	}
	//블럭에 공 부딪혔을때 공의 방향 전환 및 블럭 지우기
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
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("□");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("□");
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
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("□");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("□");
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
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("□");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("□");
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
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("□");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("□");
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
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("□");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("□");
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
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("□");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("□");
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
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("□");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("□");
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
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y]);
						printf("□");
						go_xy(box[x][y].location[X], box[x][y].location[Y] + 1);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
						printf("□");
						go_xy(box[x][y].location[X] + 2, box[x][y].location[Y] + 1);
						printf("□");
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
		printf("점수 : %d", puse / 4);
	}
}

//공 지우기
void erase() {
	if (turn_ball >= 4) {
		go_xy(ball_x_pas[(turn_ball - 4) % 4], ball_y_pas[(turn_ball - 4) % 4]);
		printf("□");
	}
}

//커서의 위치 이동
void go_xy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//키보드 입력에 의한 커서의 이동 및 잔류 문자 지우기
int input_key() {
	if (_kbhit())
	{
		key = _getch();
		switch (key)
		{
			/*		case 72:
			//			printf("위쪽 화살표\n");
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
			//			printf("왼쪽 화살표\n");
			x_p -= 2;
			go_xy(x_p + 2 * life, y_p);
			printf("□");
			break;
		case 77:
			if (stage == 0 || stage == 50) {
				puts("\a");
				break;
			}
			//			printf("오른쪽 화살표\n");
			x_p += 2;
			go_xy(x_p - 2, y_p);
			printf("□");
			break;
			/*		case 80:
			//			printf("아래쪽 화살표\n");
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
				printf("속도 : %d", speed);
			}
			break;
		case 100:
			speed++;
			go_xy(0, 41);
			printf("                                 \r");
			printf("속도 : %d", speed);
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


//공의 구동부
void ball() {
	//물체에 부딪혔을 때 방향을 틀기 위한 조건문
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
			printf("☆★재시작☆★");
			go_xy(44, 22);
			printf("LIFE   :   - 1");
			go_xy(80, 41);
			printf("- LIFE : %d", life / 2);
			Sleep(2000);
			go_xy(44, 21);
			printf("□□□□□□□");
			go_xy(44, 22);
			printf("□□□□□□□");
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
				printf("□");
		}
		turn_ball = 0;
		x_b = 48;
		y_b = 20;
		srand(time(NULL));
		ball_x = (rand() % 2);
		ball_y = (rand() % 2);
		p = 30;
	}

	//막대가 공 받는 조건
/*	if (x_b >= x_p && x_b < (x_p + 2 * life) && y_b == (y_p - 1)) {
		ball_y = 0;
	}*/
	if (y_b == (y_p - 1))
		ball_y = 0;

	//공의 잔상 남기기 및 4번째 전 위치의 문자 지우기, 이동부분
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
		printf("●");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 47);
		Sleep(5);
		erase();
	}
	p = 1;
}


//메인 함수
void main() {
	system("color 2f");		//콘솔 창의 색깔 지정
	CONSOLE_CURSOR_INFO curif;		//커서의 환경설정을 위한 구조체 선언

	//커서 숨기기
	curif.dwSize = 1;
	curif.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curif);

	a = 1;		//게임의 종료를 위한 변수
	const char* object = "▣";		//막대의 각 개체
	system("Title 공튀기기");		//창 제목
	system("mode con: cols=100 lines=42");		//창 크기 조절 100, 41

	//첫 방향 랜덤 설정
	srand(time(NULL));
	ball_x = (rand() % 2);
	ball_y = (rand() % 2);

	//스페이스바를 누르면 시작
	p = 0;
	while (input_key()) {
		go_xy(34, 15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + (p % 3));
		printf("☆★☆★☆★공튀기기☆★☆★☆★");
		go_xy(42, 22);
		printf("PRESS SPACE BAR");
		Sleep(200);
		p++;
	}
	system("cls");

	//블록 스테이지 선택
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

	//화면 채우기
	for (int k = 0; k <= 40; k++)
	{
		if (k % 2 == 0)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + (k % 3));
		for (int z = 0; z <= 49; z++)
			printf("□");
		printf("\n");
		Sleep(50);
	}
	Sleep(300);
	system("color 2f");
	p = 0;

	//블록 생성 및 설정
	block();

	go_xy(80, 41);
	printf("- LIFE : %d", life / 2);
	Sleep(500);

	//구동부
	while (a) {
		if (life <= 0) {
			Sleep(1000);
			go_xy(0, 0);
			for (int k = 0; k <= 40; k++)
			{
				if (k % 2 == 0)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 45 + (k % 3));
				for (int z = 0; z <= 49; z++)
					printf("□");
				printf("\n");
				Sleep(50);
			}
			Sleep(1000);
			system("cls");
			go_xy(36, 15);
			printf("아쉽게도 패배하였습니다..");
			go_xy(36, 16);
			Sleep(1300);
			a = 0;
			break;
		}
		p = 1;
		go_xy(x_p, y_p);
		for (int i = life; i > 0; i--)		//막대 개체 생성
			printf("%s", object);
		input_key();		//키보드 입력받기
		Sleep(4);
		ball();
		block();				//블럭 설정
		t++;
		if (y_b >= 40)
			t = 0;

		//창 밖으로 벗어나지 않게 하기 위한 변수 최대, 최소 설정
		if (x_p > 100 - 2 * life)
			x_p = 100 - 2 * life;
		else if (x_p < 0)
			x_p = 0;
	}
	if (stage == 1) {
		if (puse == 500) {
			system("cls");
			go_xy(36, 15);
			printf("축하합니다!!! 승리하셨습니다!!!");
			Sleep(2200);
			go_xy(36, 16);
		}
	}
	else if (stage == 2) {
		if (puse == 344) {
			system("cls");
			go_xy(36, 15);
			printf("축하합니다!!! 승리하셨습니다!!!");
			Sleep(2200);
			go_xy(36, 16);
		}
	}
	else if (stage == 3) {
		if (puse == 260) {
			system("cls");
			go_xy(36, 15);
			printf("축하합니다!!! 승리하셨습니다!!!");
			Sleep(2200);
			go_xy(36, 16);
		}
	}
}