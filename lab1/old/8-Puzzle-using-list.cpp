#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stdlib.h>
using namespace std;

struct State {
	int state_id;
	int parent_id;
	int g_cost;
	int h_cost;
	State (int id, int parent_id, int g_cost, int h_cost){
		state_id = id;
		this->parent_id = parent_id;
		this->g_cost = g_cost;
		this->h_cost = h_cost;
	}
	int getFcost(){
		return g_cost + h_cost;
	}
	bool operator==(const State& node) const{
		return state_id == node.state_id;
	}
};

vector<int> findNextStates(int current_state); 
int computeH_normal(int stateId);
int computeH_manhatten(int stateId);
int computeH(int state_id,int final_state_id);

bool inList(list<State>& alist,int element);
State getFromList(list<State>& alist, int element);
void addToList(list<State> &alist, State element);
void removeFromList(list<State> &alist, State element);
void aStar(int start_node, int finish_node );
void printList(list<State> alist);
void printList(list<int> alist);
vector< vector<int> > convertIdToVector(int start);
int convertVectorToId(vector< vector<int> > stateVector );
void printVector(vector< vector<int> > inputVector);

int main(){
	//graph input	
	int start_state = 867254301;
	//cin>>start_state;
	int goal_state = 123456780;
	aStar(start_state,goal_state);	
}

void aStar(int start_node, int finish_node ){
	list<State > openlist;
	list<State > closedlist;
	unordered_map<int,int> parent;	
	State dummy_node = State(start_node,-1,0,computeH(start_node,finish_node));
	openlist.push_back(dummy_node);
	bool found = false;
	int iteration = 0;
	while(!openlist.empty()){
		State current_node = openlist.front();
		openlist.pop_front();
		closedlist.push_back(current_node);
		if(current_node.state_id == finish_node){
			found = true;
			int parent_node = current_node.parent_id;
			list<int> optimal_path;
			optimal_path.push_front(current_node.state_id);
			while(parent_node != -1){
				optimal_path.push_front(parent_node);
				if(parent.count(parent_node))
					parent_node = parent.at(parent_node);
				else
					parent_node = -1;
			}
			cout<<"optimal path is:\n";
			printList(optimal_path);
			cout<< "path length:" << optimal_path.size() - 1 <<endl;
			cout<<"iteration number:" << iteration <<endl;			
			break;
		}		

		vector<int> children = findNextStates(current_node.state_id);//to be done
		for(vector<int>::iterator it = children.begin(); it!= children.end(); it++){			
			if(*it!=current_node.parent_id){
				if(inList(openlist, *it)){
					State element = getFromList(openlist,*it);
					if(element.g_cost > current_node.g_cost + 1){ //generalize						
						removeFromList(openlist,element);
						element.parent_id = current_node.state_id;
						parent[element.state_id] = current_node.state_id;
						element.g_cost = current_node.g_cost + 1; //generalize						
						addToList(openlist,element);
					}
				} //to be done
				else if(parent.count(*it)){
					continue;
				} else {
					State dummy_node(*it,current_node.state_id,current_node.g_cost +  1,computeH(*it,finish_node));
					parent[*it] = current_node.state_id;
					addToList(openlist,dummy_node);
				}
			}			
		}
		// cout<<"printing open list:\t";
		// printList(openlist);
		// cout<<"printing closed list:\t";
		// printList(closedlist);		
		// cout<<endl;	
		iteration++;
	}
	if(!found){
		cout << "not found" <<endl;
	}
}

int computeH(int state_id,int final_state_id){
	return 0;//computeH_manhatten(state_id);

}

bool inList(list<State>& alist,int element){
	for(list<State>::iterator  it = alist.begin(); it!= alist.end(); it++){
		if (it->state_id == element)
			return true;
	}
	return false;
}

State getFromList(list<State>& alist, int element){
	for(list<State>::iterator it = alist.begin(); it!= alist.end(); it++){
		if (it->state_id == element)
			return *it;
	}
	cout<< "galat ho rha h";
}

void addToList(list<State> &alist, State element){
	list<State>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		if (it->getFcost() > element.getFcost())
			break;
	}
	alist.insert(it,element);
}

void removeFromList(list<State> &alist, State element){
	alist.remove(element);
}

void printList(list<State> alist){
	list<State>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		cout<< it->state_id << ":" << it->getFcost()<< " ";
	}
	cout<< endl;
}

void printList(list<int> alist){
	list<int>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		printVector(convertIdToVector(*it));
		cout <<endl;
	}
	cout<< endl;
}

void printVector(vector< vector<int> > inputVector){
    for (int i = 0; i < 3; i++){
		for(int j = 0;  j < 3; j++){
			cout<<inputVector[i][j]<<' ';
		}
		cout<<'\n';
	}
}


vector< vector<int> > convertIdToVector(int start){
	vector< vector<int> > stateVector(3, vector<int>(3,0));

	for(int i = 2; i >=0; i--){

		for (int j  = 2; j >= 0; j--)
		{
			stateVector[i][j] = start%10;
			start = start/10;
		}
	}

	return stateVector;
}

int convertVectorToId(vector< vector<int> > stateVector ){
	int Id = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			Id = Id*10 + stateVector[i][j];
		}
	}
	return Id;
}

vector<int> findNextStates(int Id){

    //vector< vector<int>> stateVector = convertIdToVector(Id)
	vector< vector<int> > stateVector(convertIdToVector(Id));
	int blankX, blankY;
	vector<int> nextStates;

	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			if(stateVector[x][y]==0){
				blankX = x;
				blankY = y;
				break;
			}
		}
	}



	//cout<<"position of 0 is"<<blankX<<','<<blankY<<'\n';

	int temp;
	vector< vector<int> > tempStateVector(stateVector);
	//swap with lower element
	if(blankY<2){
        //cout<<"lower\n";
		temp = tempStateVector[blankX][blankY];
		tempStateVector[blankX][blankY] = tempStateVector[blankX][blankY+1];
		tempStateVector[blankX][blankY+1] = temp;
		nextStates.push_back(convertVectorToId(tempStateVector));
	}

	//swap with upper element
    tempStateVector = stateVector;
	if(blankY>0){
        //cout<<"upper\n";
		temp = tempStateVector[blankX][blankY];
		tempStateVector[blankX][blankY] = tempStateVector[blankX][blankY-1];
		tempStateVector[blankX][blankY-1] = temp;
		nextStates.push_back(convertVectorToId(tempStateVector));
	}

	//swap from left
	tempStateVector = stateVector;
	if(blankX>0){
	//cout<<"left\n";
		temp = tempStateVector[blankX][blankY];
		tempStateVector[blankX][blankY] = tempStateVector[blankX-1][blankY];
		tempStateVector[blankX-1][blankY] = temp;
		nextStates.push_back(convertVectorToId(tempStateVector));
	}

	//swap from right
	tempStateVector = stateVector;
	if(blankX<2){
	//cout<<"right\n";
		temp = tempStateVector[blankX][blankY];
		tempStateVector[blankX][blankY] = tempStateVector[blankX+1][blankY];
		tempStateVector[blankX+1][blankY] = temp;
		nextStates.push_back(convertVectorToId(tempStateVector));
	}
	return nextStates;

}

int computeH_normal(int stateId){
    vector< vector<int> > stateVector = convertIdToVector(stateId);
    int hValue = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(stateVector[i][j] != (3*i+j+1)%9){
                hValue++;
            }
        }
    }
    return hValue;
}

int computeH_manhatten(int stateId){
    vector< vector<int> > stateVector = convertIdToVector(stateId);
    int hValue = 0;
    int temp;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            temp = stateVector[i][j];
            if(temp==0) continue;
            hValue = hValue + abs((temp-1)%3 - j) + abs( (temp-1)/3 -i);               //correct pos will be (temp-1)/3, (temp - 1) %3
        }
    }
    return hValue;
}