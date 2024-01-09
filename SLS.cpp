#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <unistd.h>

using namespace std;

const int max_iter = 2000, m = 10000;
int n, iter = 0;
float dis[10001][10001]={0};

int* GenerateRandomState(int n){
	int* arr = new int[n];
	for (int i=0;i<n;i++) arr[i] = i+1;
	random_shuffle(arr, arr+n);
	return arr;
}

float TotalDistance(int* arr){
	float totdis = 0;
	for (int i=0;i<n-1;i++) totdis += dis[arr[i]][arr[i+1]];
	return totdis;
} 

int main(){
	srand(time(NULL));
	FILE *infile = fopen("n=15.in","r");
	FILE *outfile = fopen("SLS.out","w");
	
	fscanf(infile, "%d", &n);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				fscanf(infile, "%f", &dis[i][j]);
		
	int* bestTour;
	float bestDis = 0;
	for (int i=1;i<=n;i++) bestDis += dis[1][i];  //INITIAL BEST DISTANCE
	
	while (iter<max_iter){
		int* curState = GenerateRandomState(n);
		int step = 0;
		float curBestTotDis = TotalDistance(curState);
		
		//OUTPUT INITIAL STATE
		//for (int i=0;i<n;i++) fprintf(outfile, "%d ", curState[i]);
		//fprintf(outfile, "%f\n", curBestTotDis);
		
		while (step<m){
			for (int i=0;i<n-1;i++){
				for (int j=i+1;j<n;j++){
					int* newState = new int[n];
					for (int k=0;k<n;k++) newState[k] = curState[k];
					swap(newState[i], newState[j]);
					float newDis = TotalDistance(newState);
					if (newDis < curBestTotDis){
						curState = newState;
						curBestTotDis = newDis;
						//OUTPUT EACH STEP
						//for (int k=0;k<n;k++) fprintf(outfile, "%d ", curState[k]);
						//fprintf(outfile, "%f\n", curBestTotDis);
						step++;
						continue;
					}
				}
			}
			break;
		}
		//OUTPUT BEST DISTANCE FOR A SINGLE TRIAL
		//fprintf(outfile, "%d %f\n", iter+1, curBestTotDis);
		if (curBestTotDis<bestDis){
			bestDis = curBestTotDis;
			bestTour = curState;
		}
		iter++;
	}
	
	//OUTPUT FINAL RESULT AFTER max_iter RERUNS
	for (int i=0;i<n;i++) fprintf(outfile, "%d ", bestTour[i]);
	fprintf(outfile, "\n%f\n", bestDis);
	return 0;
}
