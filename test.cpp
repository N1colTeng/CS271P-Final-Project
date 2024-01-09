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
	FILE *infile = fopen("n=5.in","r");
	FILE *outfile = fopen("BnBDFS.out","w");
	
	fscanf(infile, "%d", &n);
	for (int i=1;i<=n;i++){
		pool[i].num = i;
		pool[i].dis = new float[n+1];
		for (int j=1;j<=n;j++){
			fscanf(infile, "%f", &pool[i].dis[j]);
		}
	}
		
	state* initialState = new state();
	initialState->vis->push_back(pool[1]);
	for (int i=2;i<=n;i++) initialState->unvis->insert(pool[i]); 
	float U = 999999.9;
	state* bestTour = NULL;
	
	stack<state*> BnBDFS;
	BnBDFS.push(initialState);
	
	state* test = new state();
	for (list<Node>::iterator it=initialState->vis->begin();it!=initialState->vis->end();++it) test->vis->push_back(*it);
	for (set<Node>::iterator it=initialState->unvis->begin();it!=initialState->unvis->end();++it) test->unvis->insert(*it);
	Node testNode = pool[2];
	test->vis->push_back(testNode);
	test->unvis->erase(testNode);
	fprintf(outfile, "%d\n", test->unvis->size());
	for (set<Node>::iterator it=test->unvis->begin();it!=test->unvis->end();++it) fprintf(outfile, "%d ", it->num);
	
	return 0;
}
