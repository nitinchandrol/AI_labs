#include <iostream>
#include <vector>
using namespace std;


vector< vector<int>> convertIdToVector(int start){
	vector< vector<int>> stateVector(3, vector<int>(3,0));

	for(int i = 2; i >=0; i--){

		for (int j  = 2; j >= 0; j--)
		{
			stateVector[i][j] = start%10;
			start = start/10;
		}
	}

	return stateVector;
}

int convertVectorToId(vector< vector<int>> stateVector ){
	int Id = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			Id = Id*10 + stateVector[i][j];
		}
	}
	return Id;
}


vector<int> findNextStates(int Id){


	vector< vector<int>> stateVector(convertIdToVector(Id));
	for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            stateVector[i][j]=stateArray[i][j];
        }
	}
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



	cout<<"position of 0 is"<<blankX<<','<<blankY<<'\n';

	int temp;
	vector< vector<int>> tempStateVector(stateVector);
	//swap with lower element
	if(blankY<2){
		temp = tempStateVector[blankX][blankY];
		tempStateVector[blankX][blankY] = stateArray[blankX][blankY+1];
		tempStateVector[blankX][blankY+1] = temp;
		nextStates.push_back(convertVectorToId(tempStateVector));
	}

	//swap with upper element
    tempStateVector = stateVector;
	if(blankY>0){
		temp = stateArray[blankX][blankY];
		tempStateVector[blankX][blankY] = stateArray[blankX][blankY-1];
		tempStateVector[blankX][blankY-1] = temp;
		nextStates.push_back(convertVectorToId(tempStateVector));
	}

	//swap from left
	tempStateVector = stateVector;
	if(blankX>0){
		temp = stateArray[blankX][blankY];
		tempStateVector[blankX][blankY] = stateArray[blankX-1][blankY];
		tempStateVector[blankX-1][blankY] = temp;
		nextStates.push_back(convertVectorToId(tempStateVector));
	}

	//swap from right
	tempStateVector = stateVector;
	if(blankX>0){
		temp = stateArray[blankX][blankY];
		tempStateVector[blankX][blankY] = stateArray[blankX+1][blankY];
		tempStateVector[blankX+1][blankY] = temp;
		nextStates.push_back(convertVectorToId(tempStateVector));
	}
	return nextStates;

}



int main(){
	int start = 173820456, goal = 123456780;

	int** temp = convertIdToVector(start);
	cout<< "the input state is :\n"
	for (int i = 0; i < 3; i++){
		for(int j = 0;  j < 3; j++){
			cout<<temp[i][j]<<' ';
		}
		cout<<'\n';
	}

}

