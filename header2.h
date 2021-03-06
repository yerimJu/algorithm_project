#include <ctime>
#include <cstdio>
#include <iostream>
#include <gl/glut.h>
#include <string.h>
#include <Windows.h>
using namespace std;

bool state = true;
int j=15;
char item[100]={0};
int W, N, temp;
bool s[100] = {0};
int profit;

int print_Karray(int* price, int* weight, int** K, int N, int W);
void knapsack();

void init(void){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 0.0f, 500.0f);
}
void draw_string(void* font,const char* str,int x, int y){
	unsigned int i;
	glRasterPos2i(x,y);
	for(i=0; i<strlen(str); i++){
		glutBitmapCharacter(font,str[i]);
	}
}

void draw(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(50,50,0);

	glColor3f(1.0f,1.0f,1.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2i(5,5);
	glVertex2i(200,5);
	glVertex2i(200,350);
	glVertex2i(5,350);
	glVertex2i(5,5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(120.0f,420.f,0.0f);
	glColor3f(1.0f,0.0f,1.0f);
	draw_string(GLUT_BITMAP_HELVETICA_18,"BAG",0,0);
	glPopMatrix();


	
	
	glColor3f(1.0f,1.0f,1.0f);
	int a;
	for (a=1;a<23;a++) {
		glPushMatrix();
		glTranslatef(300.0f,400.f-a*j,0.0f);
		sprintf(item,"Item %d",a);
		if (s[a]) { 
			glTranslatef(-220,0,0);
		}
		draw_string(GLUT_BITMAP_HELVETICA_10,item,0,0);
		glPopMatrix();
	}
	for (a;a<46;a++) {
		glPushMatrix();
		glTranslatef(350.0f,730.f-a*j,0.0f);
		sprintf(item,"Item %d",a);
		if (s[a]) { 
			glTranslatef(-220,0,0);
		}
		draw_string(GLUT_BITMAP_HELVETICA_10,item,0,0);
		glPopMatrix();
	}

	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glTranslatef(350,440,0);
	sprintf(item,"Max Profit : %d",profit);
	draw_string(GLUT_BITMAP_HELVETICA_18,item ,0,0);
	glPopMatrix();

	glFlush();
}

void idle(){
	if(state){
		draw();
		knapsack();
		state = false;
	}
}

void knapsack() {
	int i, w, selected, unselected;
	int **K; // K는 이중배열이므로 동적 할당 사용을 위한 double pointer 선언
	int *price, *weight; // price, weight도 동적 할당을 위한 pointer로 선언

	//test.txt에서 freopen함수를 이용하여 필요한 정보를 얻어옴
	freopen("test.txt","r",stdin);
	cin >> W >> N;
	K=new int*[N+1];
	price=new int[N+1];
	weight=new int[W+1];

	for (i=0;i<=N;i++) {
		K[i]=new int[W+1];
	}
	for (i=1;i<=N;i++) {
		cin >> temp >> weight[i] >> price[i];
	}

	// 시작할 때의 clock 측정
	clock_t startTime=clock();

	// 0번째 행과 0번째 열을 0으로 채워줌(초기값 설정)
	for (i = 0; i <= N; i++)
		K[i][0] = 0;
	for (w = 0; w <= W; w++)
		K[0][w] = 0;

	// K배열을 구하는 2중 for loop 구문.
	for (i = 1; i <= N; i++) {
		for (w = 1; w <= W; w++) {
			// i번째 item을 가방에 넣을 수 있을 때
			if (weight[i]<=w) {
				selected = K[i - 1][w - weight[i]] + price[i]; // i번째 item을 선택했을 때의 가치
				unselected = K[i - 1][w]; // i번째 item을 선택하지 않았을 때의 가치
				// 그 가치 중에 큰 것을 선택하여 K행렬에 삽입
				if (selected > unselected) {
					K[i][w] = selected;
				} else {
					K[i][w] = unselected;
				} 
				// i번째 item을 가방에 넣을 수 없을 때
			} else {
				K[i][w] = K[i - 1][w];
			}
		}
	}
	
	cout << "N is " << N << ", W is " << W << endl;
	// K array를 recursion을 이용하여 출력하는 함수 실행
	print_Karray(price,weight,K,N,W);

	// 함수 실행이 끝났을 때의 clock 측정
	clock_t finalTime=clock();

	profit=K[N][W];
	cout << "The best price is " << K[N][W] << endl;
	cout << "CPU clock 수 : " << finalTime-startTime << endl;
	cout << "이상 12141768 주예림의 프로젝트였습니다. " << endl;

}
int print_Karray(int* price, int* weight, int** K, int N, int W) {
	// item개수가 0이거나 가방의 무게가 0이하이면 recursion 중단
	if (N==0 || W<=0) return 0;
	// item개수가 1개이면 그 배열의 값만 출력하고 recursion 중단
	if (N==1) { 
		cout <<  "K[" << N << "][" << W << "] = " <<  K[N][W] << endl;
		return 0;
	}

	// 점화식 출력
	cout << "K[" << N << "][" << W << "] = max(" << "K[" << N-1 << "][" << W << "], ";
	cout << price[N] << "+K[" << N-1 << "][" << W-weight[N-1] << "]) = ";
	cout << "max(" << K[N-1][W] << "," << price[N] << "+" << K[N-1][W-weight[N-1]] << ")=" << K[N][W] << endl;

	Sleep(100);
	draw();

	// 위의 K배열을 구할 때와 같은 원리로 recursion해 준다.
	if (weight[N-1]>W) return print_Karray(price,weight,K,N-1,W);
	else {
		if (price[N-1]+K[N-1][W-weight[N-1]] > K[N-1][W]) {
			profit=price[N-1]+K[N-1][W-weight[N-1]];
			s[N]=1;
			return print_Karray(price,weight,K,N-1,W-weight[N-1]);
		}
		else {
			profit=K[N-1][W];
			s[N]=0;
			return print_Karray(price,weight,K,N-1,W);
		}
	}
}