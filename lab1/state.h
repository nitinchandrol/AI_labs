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
};
