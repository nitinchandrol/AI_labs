#include <iostream>
#include <list>
#include <vector>
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

void removeFromList(list<Node_info> &alist, Node_info element){
	alist.remove(element);
}

void addToList(list<Node_info> &alist, Node_info element){
	list<Node_info>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		if (it->getFcost() > element.getFcost())
			break;
	}
	alist.insert(it,element);
}
void aStar(vector<vector<Edge> >& graph, int start_node, int finish_node );
void printList(list<Node_info> alist){
	list<Node_info>::iterator it;
	for(it = alist.begin(); it!= alist.end(); it++){
		cout<< it->node_num << ":" << it->getFcost()<< " ";
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
	list<Node_info > openlist;
	list<Node_info > closedlist;

	Node_info dummy_node = Node_info(start_node,-1,0,0);
	openlist.push_back(dummy_node);
	bool found = false;
	while(!openlist.empty()){
		Node_info current_node = openlist.front();
		openlist.pop_front();
		closedlist.push_back(current_node);
		if(current_node.node_num == finish_node){
			found = true;
			break;
		}
		list<int> children = findChildNodes(graph, current_node.node_num);//to be done
		for(list<int>::iterator it = children.begin(); it!= children.end(); it++){
			if(*it!=current_node.parent){
				if(inList(openlist, *it)){
					Node_info element = getFromList(openlist,*it);
					if(element.getFcost() > current_node.g_cost + 1){ //generalize
						removeFromList(openlist,element);
						element.parent = current_node.node_num;
						element.g_cost = current_node.g_cost + 1; //generalize						
						addToList(openlist,element);
					}
				} //to be done
				else if(inList(closedlist,*it)){
					continue;
				} else {
					Node_info dummy_node(*it,current_node.node_num,current_node.g_cost +  1,0);
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