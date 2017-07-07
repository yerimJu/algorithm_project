#include <iostream>
#include <ctime>
#include <cstdio>
using namespace std;

int print_Karray(int* price, int* weight, int** K, int N, int W);
int main(void) {
	int i, w, selected, unselected;
	int W, N, temp;
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
				K[i][w] = (selected > unselected ? selected : unselected); // 그 가치 중에 큰 것을 선택하여 K행렬에 삽입
				// i번째 item을 가방에 넣을 수 없을 때
			} else K[i][w] = K[i - 1][w];
		}
	}

	cout << "N is " << N << ", W is " << W << endl;
	// K array를 recursion을 이용하여 출력하는 함수 실행
	print_Karray(price,weight,K,N,W);
	
	// 함수 실행이 끝났을 때의 clock 측정
	clock_t finalTime=clock();

	cout << "The best price is " << K[N][W] << endl;
	cout << "CPU clock 수 : " << finalTime-startTime << endl;
	cout << "이상 12141768 주예림의 프로젝트였습니다. " << endl;

	return 0;
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
	
	// 위의 K배열을 구할 때와 같은 원리로 recursion해 준다.
	if (weight[N-1]>W) return print_Karray(price,weight,K,N-1,W);
	else {
		if (price[N-1]+K[N-1][W-weight[N-1]] > K[N-1][W])
			return print_Karray(price,weight,K,N-1,W-weight[N-1]);
		else return print_Karray(price,weight,K,N-1,W);
	}
}
