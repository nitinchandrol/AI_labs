#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stdlib.h>
#include <utility>
#include "heap.cpp"
using namespace std;

vector<int> findNextStates(int current_state);
int computeH_normal(int stateId);
int computeH_manhatten(int stateId);
int computeH(int start_id,vector< vector<int> > &goal_vector);
int computeH_normal(int start_id, vector< vector<int> > &goal_vector);
int computeH_manhatten(int start_id, vector< vector<int> > &goal_vector);

void aStar(int start_node, int finish_node );
vector< vector<int> > convertIdToVector(int start);
int convertVectorToId(vector< vector<int> > stateVector );
void printVector(vector< vector<int> > inputVector);
void printList(list<int> alist);

int main(){
	//graph input
	int start_state = 867254301;
	//cin>>start_state;
	int goal_state = 123456780;
	aStar(start_state,goal_state);
}

void aStar(int start_node, int finish_node ){
	MinHeap openlist;
	MinHeap closedlist;
	unordered_map<int,int> parent;

    vector< vector<int> > goal_vector = convertIdToVector(finish_node), start_vector = convertIdToVector(start_node);
    printVector(goal_vector);
    printVector(start_vector);
    cout<<"----------------------------------------------------------";
	State* dummy_node = new State(start_node,-1,0,computeH(start_node,goal_vector));
	openlist.insert(dummy_node);
	bool found = false;
	int iteration = 0;
	while(!openlist.empty()){
		State* current_node = openlist.findMin();
		openlist.deleteMin();
		closedlist.insert(current_node);
		if(current_node->state_id == finish_node){
			found = true;
			int parent_node = current_node->parent_id;
			list<int> optimal_path;
			optimal_path.push_front(current_node->state_id);
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

		vector<int> children = findNextStates(current_node->state_id);//to be done
		for(vector<int>::iterator it = children.begin(); it!= children.end(); it++){
			if(*it!=current_node->parent_id){
				State* element = openlist.find(*it);
				if(element != NULL){
					if(element->g_cost > current_node->g_cost + 1){ //generalize
						parent[element->state_id] = current_node->state_id;
						openlist.update(element->state_id,current_node->state_id,current_node->g_cost+1);
					}
				} //to be done
				else if(parent.count(*it)){
					continue;
				} else {
					State* dummy_node = new State(*it,current_node->state_id,current_node->g_cost +  1,computeH(*it,goal_vector));
					parent[*it] = current_node->state_id;
					openlist.insert(dummy_node);
				}
			}
		}
		iteration++;
	}
	if(!found){
		cout << "not found" <<endl;
	}
}

int computeH(int start_id,vector< vector<int> > &goal_vector){
	return computeH_manhatten(start_id, goal_vector);
}

void printVector(vector< vector<int> > inputVector){
    for (int i = 0; i < 3; i++){
		for(int j = 0;  j < 3; j++){
			cout<<inputVector[i][j]<<' ';
		}
		cout<<'\n';
	}
}

void printList(list<int> alist){
	list<int>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		printVector(convertIdToVector(*it));
		cout <<endl;
	}
	cout<< endl;
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

int computeH_normal(int start_id, vector< vector<int> > &goal_vector){
	vector< vector<int> > startVector = convertIdToVector(start_id);
	int hvalue = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(startVector[i][j] != goal_vector[i][j]){
                hvalue++;
            }
        }
    }
    return hvalue;
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

int computeH_manhatten(int start_id, vector< vector<int> > &goal_vector){
	vector< vector<int> > start_vector = convertIdToVector(start_id);
	int hvalue = 0;
    int temp;
    pair<int,int> goal_position[9];

    for(int i = 0; i < 3; i++){                                                     //this calculation can be potentially cutted out
        for(int j = 0; j < 3; j++){
            goal_position[goal_vector[i][j]] = make_pair(i,j);
        }
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            temp = start_vector[i][j];
            if(temp==0)continue;
            hvalue = hvalue + abs(i-goal_position[temp].first)+abs(j-goal_position[temp].second);
        }
    }
    return hvalue;


}
