/*
Link : https://vn.spoj.com/problems/STOCK/fbclid=IwAR2evcS-BIkHZ6vy64x-jmYciCFM3qrY-WZ4j7i9LQWkQjBvXgjPTl06MaY
*/
#include "iostream"
using namespace std;
#define MAX_N 1010
#define MAX_S 55
#define MAX_D 20

int stock_day[MAX_S][MAX_D];

int action[] = {0, 1};
//				k mua, bán, mua
int S, D, M;

int arrV[2];

int maxMoney;

void generator(int current_i)
{
	if (current_i<2)
		for (int i = 0; i<2;i++)
		{
			arrV[current_i] = action[i];
			generator(current_i+1);
		}
	else
	{
		for (int i =0; i<2;i++)
			cout << arrV[i] << " ";
		cout <<" hihi 1" << endl;
	}

}


void calculate(int day, int currentMoney, int status[MAX_S],bool visited[MAX_S], int current_iStock)
{
	/*
	cout << "\n -day:"<<day <<" currentMoney = "<<currentMoney<< " current i stock="<<current_iStock<<endl;
	for (int i = 1; i <= S; i++)
		cout <<status[i] <<" ";
	cout <<endl;
	for (int i = 1; i <= S; i++)
		cout <<visited[i] <<"~";
	cout <<endl;
	*/
	if (day == D)
	{
		for (int i =1;i<=S;i++)
			if (status[i] == 1)
			{
				status[i] = 0;
				currentMoney +=stock_day[i][D];
			}
			if (currentMoney >=maxMoney)
				maxMoney = currentMoney;

			//cout << " Max = " << maxMoney<<endl;
	}

	else if (day <=D)
	{
		if (current_iStock <=S)
		{
			if (visited[current_iStock] == false && status[current_iStock] == 1) // có mua từ trước đó
			{
				visited[current_iStock] = true; // mark ko thể đi vào đc nữa
				status[current_iStock] = 0;
				// check xem có thằng nào có thể mua không?
				for (int i =1;i<=S;i++)
				{
					if (visited[i]  == false && status[i] ==0 && currentMoney + stock_day[current_iStock][day]  >= stock_day[i][day])
					{
						visited[i] = true;
						status[i] = 1;
						
						calculate(day,currentMoney + stock_day[current_iStock][day] - stock_day[i][day],status,visited,i);
						status[i] = 0;
						visited[i] = false;
					}
				}
				status[current_iStock] = 1;
			}
			else if (visited[current_iStock] == false && status[current_iStock] == 0 && currentMoney >= stock_day[current_iStock][day])
			{
				status[current_iStock] = 1;
				visited[current_iStock] = true;
				calculate(day,currentMoney  - stock_day[current_iStock][day],status,visited,current_iStock);
				status[current_iStock] = 0;
			}

			if (current_iStock == S)
			{
				bool newVisited[MAX_S] = {false};
				calculate(day+1,currentMoney,status,newVisited,1);
			}
			else
				calculate(day,currentMoney,status,visited,current_iStock+1);
					
		}

	}

}


int main()
{
	freopen("input.txt","r", stdin);



	cin >> S >> D >> M;

	//cout << "S = "<<S <<" D = " << D <<" M = " << M<<endl;

	for (int i = 1; i <= S; i++)
	{
		for (int j = 1; j <=D; j++)
		{
			cin >> stock_day[i][j];
		}
	}

	/*
	for (int i = 1;i<=S;i++)
	{
	for (int j = 1; j<=D;j++)
	cout << stock_day[i][j] << " ";
	cout << endl;
	}
	*/
	maxMoney = M;


	int zeros_status[MAX_S]={0};
	bool visited[MAX_S] = {false};
	calculate(1,M,zeros_status,visited,1);

	//cout <<"\n hahahahA MAX = "<<maxMoney<<endl;
	cout <<maxMoney<<endl;
	return 0;
}