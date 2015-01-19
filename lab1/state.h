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
