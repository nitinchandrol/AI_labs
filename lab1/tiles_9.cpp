#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Node_info {
	int node_num;
	int parent;
	int g_cost;
	int h_cost;
	Node_info (int id, int parent_id, int g_cost, int h_cost){
		node_num = id;
		parent = parent_id;
		this->g_cost = g_cost;
		this->h_cost = h_cost;
	}
	int getFcost(){
		return g_cost + h_cost;
	}
	bool operator==(const Node_info& node) const{
		return node_num == node.node_num;
	}
};

vector<int> findNextStates(int current_state); 
int computeH(int state_id,int final_state_id);

bool inList(list<Node_info>& alist,int element);
Node_info getFromList(list<Node_info>& alist, int element);
void addToList(list<Node_info> &alist, Node_info element);
void removeFromList(list<Node_info> &alist, Node_info element);
void aStar(int start_node, int finish_node );
void printList(list<Node_info> alist);


int main(){
	//graph input
	int start_state = 123654870;
	int goal_state = 123456780;
	aStar(start_state,goal_state);	
}

void aStar(int start_node, int finish_node )
{
	list<Node_info > openlist;
	list<Node_info > closedlist;
	vector<int> parent(1000000000,-1);	
	Node_info dummy_node = Node_info(start_node,-1,0,computeH(start_node,finish_node));
	openlist.push_back(dummy_node);
	bool found = false;
	while(!openlist.empty()){
		Node_info current_node = openlist.front();
		openlist.pop_front();
		closedlist.push_back(current_node);
		if(current_node.node_num == finish_node){
			found = true;
			parent_node = current_node.parent;
			list<int> optimal_path;
			optimal_path.push_front(current_node);
			while(parent_node != -1){
				optimal_path.push_front(parent_node);
				parent_node = parent.at(parent_node);
			}
			cout<<"optimal path is:\t";
			printList(optimal_path);				
			break;
		}
		vector<int> children = findNextStates(current_node.node_num);//to be done
		for(vector<int>::iterator it = children.begin(); it!= children.end(); it++){
			if(*it!=current_node.parent){
				if(inList(openlist, *it)){
					Node_info element = getFromList(openlist,*it);
					if(element.g_cost > current_node.g_cost + 1){ //generalize
						removeFromList(openlist,element);
						element.parent = current_node.node_num;
						parent.at(element.node_num) = current_node.node_num;
						element.g_cost = current_node.g_cost + 1; //generalize						
						addToList(openlist,element);
					}
				} //to be done
				else if(inList(closedlist,*it)){
					continue;
				} else {
					Node_info dummy_node(*it,current_node.node_num,current_node.g_cost +  1,computeH(*it,finish_node));
					parent.at(*it) = current_node.node_num;
					addToList(openlist,dummy_node);
				}
			}			
		}
		cout<<"printing open list:\t";
		printList(openlist);
		cout<<"printing closed list:\t";
		printList(closedlist);		
		cout<<"\n";	
	}
	if(found){
		cout<<"found"<<endl;
	} else{
		cout << "not found" <<endl;
	}
}

bool inList(list<Node_info>& alist,int element){
	for(list<Node_info>::iterator  it = alist.begin(); it!= alist.end(); it++){
		if (it->node_num == element)
			return true;
	}
	return false;
}

Node_info getFromList(list<Node_info>& alist, int element){
	for(list<Node_info>::iterator it = alist.begin(); it!= alist.end(); it++){
		if (it->node_num == element)
			return *it;
	}
	cout<< "galat ho rha h";
}

void addToList(list<Node_info> &alist, Node_info element){
	list<Node_info>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		if (it->getFcost() > element.getFcost())
			break;
	}
	alist.insert(it,element);
}

void removeFromList(list<Node_info> &alist, Node_info element){
	alist.remove(element);
}

void printList(list<Node_info> alist){
	list<Node_info>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		cout<< it->node_num << ":" << it->getFcost()<< " ";
	}
	cout<< endl;
}