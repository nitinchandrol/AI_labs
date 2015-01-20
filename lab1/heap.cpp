#include <iostream>
#include <string>
#include <unordered_map>
#include "state.h"

#define DEBUG false

using namespace std;
string getBitmap(int pos);
struct Node{
	State* state;
	Node* left;
	Node* right;
	Node* parent;	
	Node(State* state, Node* parent){
		this->state = state;
		this->parent = parent;
		left = NULL;
		right = NULL;		
	}	

};
struct MinHeap{
	Node* start_node;
	int size;
	unordered_map<int,Node*> state_map;
	MinHeap(){
		start_node  = NULL;
		size = 0;
	}
	void insert(State* state){
		if(DEBUG){
			cout << "inserting " << state->state_id << " " << state->getFcost() << " in ";		
			this->print(start_node);
			cout << endl;
		}		
		if(this->empty()){
			this->start_node = new Node(state, NULL);
		} else {
			int pos = size+1;
			string bm = getBitmap(pos);
			string next = bm.substr(1);
			Node* last_node = start_node;
			Node* new_node;
			while(next != ""){
				char ch = next[0];				
				if(ch == '0'){
					if(last_node->left == NULL){
						new_node = new Node(state,last_node);						
						last_node->left = new_node;						
						break;
					} else {
						last_node = last_node->left;
					}
				} else {
					if(last_node->right == NULL){
						new_node = new Node(state,last_node);
						last_node->right = new_node;
						break;
					} else {
						last_node = last_node->right;
					}
				}
				next = next.substr(1);								
			}
			state_map[state->state_id] = new_node;
			this->balance(new_node);
		}
		size++;	
		if(DEBUG){
			this->print(start_node);
			cout << endl;
		}			

	}
	bool empty(){
		return size == 0;
	}
	State* findMin(){
		if(this->empty()){
			return NULL;
		} else {
			return start_node->state;
		}
	}
	void deleteMin(){
		if(DEBUG){
			cout << "deleting min from ";
			this->print(start_node);
			cout << endl;
		}
		string bm = getBitmap(size);
		string next = bm.substr(1);
		Node* last_node = start_node;
		char ch;
		while(next != ""){
			ch = next[0];				
			if(ch == '0'){
				last_node = last_node->left;
				//cout << "left";
			} else {
				last_node = last_node->right;
				//cout << "right";
			}
			next = next.substr(1);
		}
		state_map.erase(start_node->state->state_id);
		if(last_node == start_node){			
			delete start_node;
			start_node = NULL;
			this->size = 0;
			return;
		}
		if(ch == '0'){
			last_node->parent->left = NULL ;
			start_node->state = last_node->state;
			delete last_node;
		} else {			
			last_node->parent->right = NULL ;
			start_node->state = last_node->state;
			delete last_node;
		}
		this->size--;				
		Node* current_node = start_node;
		Node* node_to_check = (current_node->right == NULL) ? (current_node->left) : 
			(current_node->right->state->getFcost() < current_node->left->state->getFcost() ? current_node->right : 
				current_node->left);
		while(node_to_check != NULL && node_to_check->state->getFcost() < current_node->state->getFcost()){			
			swap(state_map[current_node->state->state_id],state_map[node_to_check->state->state_id]);
			swap(current_node->state,node_to_check->state);
			current_node = node_to_check;
			node_to_check = (current_node->right == NULL) ? (current_node->left) : 
				(current_node->right->state->getFcost() < current_node->left->state->getFcost() ? current_node->right : 
					current_node->left);
		}
		if(DEBUG){
			this->print(start_node);
			cout << endl;
		}		
	}
	State* find(int state_id){
		if(state_map.count(state_id)){
			return state_map[state_id]->state;
		} else{
			return NULL;
		}
	}
	void update(int state_id, int parent_id, int g_cost){
		if(DEBUG){
			cout << "updating" << endl;
		}		
		if(state_map.count(state_id)){
			Node* node = state_map[state_id];
			if (node->state->g_cost < g_cost){
				node->state->g_cost = g_cost; 
				node->state->parent_id = parent_id;
				this->balance(node);
			}
		}	
	}
	void balance(Node* new_node){
		if(DEBUG){
			cout << "balancing" << endl;
		}		
		while(new_node->parent != NULL && new_node->state->getFcost() < new_node->parent->state->getFcost()){
			swap(state_map[new_node->state->state_id],state_map[new_node->parent->state->state_id]);
			swap(new_node->state,new_node->parent->state);
			new_node = new_node->parent;
			//cout << new_node->parent << endl;
		}
	}
	void remove(){
		
	}
	void print( Node* node){
		if(node != NULL){
			cout << node->state->getFcost() << " ";
			print(node->left);
			print(node->right);
		}
	}


};
 
string getBitmap(int pos){
	string bm = "";
	while(pos != 0){		
		bm = to_string(pos%2) + bm;
		pos /= 2;
	}
	return bm;
} 