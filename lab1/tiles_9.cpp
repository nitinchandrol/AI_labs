#include <iostream>
#include <list>
using namespace std;
struct Node
{
	int state_id;
	int g;
	int h;	
	bool operator< (Node& node2){
		return (this->g + this->h) < (node2.g + node2.h); 
	}
	Node(int s, int g, int h){
		this->state_id = s;
		this->g = g;
		this->h = h;
	}
};
vector<int> findNextStates(int current_state); 
int main(){
	int start_state_id = 125634087;
	/*
		125
	 	634
	 	_87 
	*/
	int final_state_id = 123456780;	
	Node *start = new Node(start_state_id,0,computeH(start_state_id,final_state_id));
	list <Node*> open_list;
	list <Node*> closed_list;	
	insertIntoList(open_list,start);
	while(!open_list.empty()){
		Node* current_node = *(open_list.begin());
		closed_list.push_back(current_node);
		open_list.delete(current_node);		
	}

}
vector<int> findNextStates(int current_state_id){
	
}
int computeH(int state_id,int final_state_id){

}
