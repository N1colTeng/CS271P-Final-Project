#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <stack>
#include <list>

using namespace std;
int n;
float dis[10001][10001]={0};

struct Node{
	int num = -1;
	float* dis;
	
	bool operator<(const Node& other) const {
        return num < other.num;
    }
};Node pool[10001];

class state{
	public:
		list<Node>* vis;
		set<Node>* unvis;
		float curTotDis;
		
		state(): vis(new list<Node>), unvis(new set<Node>), curTotDis(0.0) {}
		
		bool isComplete(){
			return unvis->empty();
		}
		
		float h(){
			if (isComplete()) return 0;
			Node curNode = vis->back();
			float min = 999999.9;
			for (set<Node>::iterator it=unvis->begin();it!=unvis->end();++it){
				if(min>curNode.dis[it->num]) min=curNode.dis[it->num];
			}
			return min;
		}
		
		float f(){
			return h()+curTotDis;
		}
};

int main(){
	FILE *infile = fopen("n=15.in","r");
	FILE *outfile = fopen("BnBDFS.out","w");
	
	fscanf(infile, "%d", &n);
	for (int i=1;i<=n;i++){
		pool[i].num = i;
		pool[i].dis = new float[n+1];
		for (int j=1;j<=n;j++){
			fscanf(infile, "%f", &pool[i].dis[j]);
		}
	}
	
	/*	
	state* initialState = new state();
	initialState->vis->push_back(pool[1]);
	for (int i=2;i<=n;i++) initialState->unvis->insert(pool[i]);
	*/
	
	float U = 999999.9;
	state* bestTour = NULL;
	
	stack<state*> BnBDFS;
	for (int i=1;i<=n;i++){
		state* initialState = new state();
		initialState->vis->push_back(pool[i]);
		for (int j=1;j<=n;j++) 
			if (j!=i) initialState->unvis->insert(pool[j]); 
		BnBDFS.push(initialState);
	}
	//BnBDFS.push(initialState);
	
	while (!BnBDFS.empty()){
		state* curState = BnBDFS.top();
		BnBDFS.pop();
		
		//TEST OUTPUT
		/*
		fprintf(outfile, "vis: ");
		for (list<Node>::iterator it=curState->vis->begin();it!=curState->vis->end();++it) fprintf(outfile, "%d ", it->num);
		fprintf(outfile, "unvis: ");
		for (set<Node>::iterator it=curState->unvis->begin();it!=curState->unvis->end();++it) fprintf(outfile, "%d ", it->num);
		fprintf(outfile, "h(): %f f(): %f ", curState->h(), curState->f());
		fprintf(outfile, "totdis: %f\n", curState->curTotDis);
		*/
		
		if (curState->isComplete()){
			if(curState->curTotDis<U){
				bestTour = curState;
				U = curState->curTotDis;
			}
			continue;
		}
		if (curState->f()>U) continue;
		for (set<Node>::iterator nextNode=curState->unvis->begin();nextNode!=curState->unvis->end();++nextNode){
			state* newState = new state();
			for (list<Node>::iterator it=curState->vis->begin();it!=curState->vis->end();++it) newState->vis->push_back(*it);
			for (set<Node>::iterator it=curState->unvis->begin();it!=curState->unvis->end();++it) newState->unvis->insert(*it);
			newState->vis->push_back(*nextNode);
			newState->unvis->erase(*nextNode);
			newState->curTotDis = curState->curTotDis;
			newState->curTotDis += curState->vis->back().dis[nextNode->num];
			BnBDFS.push(newState);
		}
	}
	
	while (!bestTour->vis->empty()){
		fprintf(outfile, "%d ", bestTour->vis->front().num);
		bestTour->vis->pop_front();
	}
	fprintf(outfile, "\n%f\n", bestTour->curTotDis);
	return 0;
}
