#include <iostream>
#include <list>
#include <vector>
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

struct Edge{
	int child_node;
	int weight;
};

list<int> findChildNodes(vector<vector <Edge> > &graph, int id){
	vector<Edge> childList = graph[id];
	list<int> ans;
	for(int i=0; i< childList.size(); i++){
		ans.push_back(childList[i].child_node);
	}
	return ans;
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

void removeFromList(list<State> &alist, State element){
	alist.remove(element);
}

void addToList(list<State> &alist, State element){
	list<State>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		if (it->getFcost() > element.getFcost())
			break;
	}
	alist.insert(it,element);
}
void aStar(vector<vector<Edge> >& graph, int start_node, int finish_node );
void printList(list<State> alist){
	list<State>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		cout<< it->state_id << ":" << it->getFcost()<< " ";
	}
	cout<< endl;
}
int main(){
	//graph input
	int nodeNum = 10, cost;
	vector< vector <Edge> > graph;
	for(int i=0; i< nodeNum; i++){
		vector<Edge> temp;
		Edge dummy;
		dummy.child_node = (i + 1)%10;
		dummy.weight = i;
		temp.push_back(dummy);
		dummy.child_node = (i + 5)%10;
		dummy.weight = i + 2;
		temp.push_back(dummy);
		graph.push_back(temp);
	}
	aStar(graph, 0, 9);	
}

void aStar(vector<vector<Edge> >& graph, int start_node, int finish_node )
{
	list<State > openlist;
	list<State > closedlist;

	State dummy_node = State(start_node,-1,0,0);
	openlist.push_back(dummy_node);
	bool found = false;
	while(!openlist.empty()){
		State current_node = openlist.front();
		openlist.pop_front();
		closedlist.push_back(current_node);
		if(current_node.state_id == finish_node){
			found = true;
			break;
		}
		list<int> children = findChildNodes(graph, current_node.state_id);//to be done
		for(list<int>::iterator it = children.begin(); it!= children.end(); it++){
			if(*it!=current_node.parent_id){
				if(inList(openlist, *it)){
					State element = getFromList(openlist,*it);
					if(element.getFcost() > current_node.g_cost + 1){ //generalize
						removeFromList(openlist,element);
						element.parent_id = current_node.state_id;
						element.g_cost = current_node.g_cost + 1; //generalize						
						addToList(openlist,element);
					}
				} //to be done
				else if(inList(closedlist,*it)){
					continue;
				} else {
					State dummy_node(*it,current_node.state_id,current_node.g_cost +  1,0);
					addToList(openlist,dummy_node);
				}
			}			
		}
		cout<<"printing open list:";
		printList(openlist);
		cout<<"printing closed list:";
		printList(closedlist);		
		cout<<"\n";	
	}
	if(found){
		cout<<"found"<<endl;
	} else{
		cout << "not found" <<endl;
	}
}