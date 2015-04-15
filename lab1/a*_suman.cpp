#include <iostream>
#include <vector>
using namespace std;


int** convertIdToArray(int start){
	int** stateArray = 0;

	stateArray = new int*[3];

	for(int i = 2; i >=0; i--){
		stateArray[i] = new int[3];

		for (int j  = 2; j >= 0; j--)
		{
			stateArray[i][j] = start%10;
			start = start/10;
		}
	}

	return stateArray;
}

int convertArrayToId(int** array){
	int Id = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			Id = Id*10 + array[i][j];
		}
	}
	return Id;
}


vector<int> findNextStates(int Id){

	int** stateArray = convertIdToArray(Id);

	vector< vector<int>> stateVector(3, vector<int>(3,0));
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
		temp = stateArray[blankX][blankY];
		tempStateVector[blankX][blankY] = stateArray[blankX][blankY+1];
		tempStateVector[blankX][blankY+1] = temp;
		nextStates.push_back(convertArrayToId(stateArray));
	}

	//swap with upper element
    stateArray = originalArray;
	if(blankY<2){
		temp = stateArray[blankX][blankY];
		stateArray[blankX][blankY] = stateArray[blankX][blankY+1];
		stateArray[blankX][blankY+1] = temp;
		nextStates.push_back(convertArrayToId(stateArray));
	}


}

int main(){
	int start = 173820456, goal = 123456780;

	int** temp = convertIdToArray(start);
	cout<< "the input state is :\n"
	for (int i = 0; i < 3; i++){
		for(int j = 0;  j < 3; j++){
			cout<<temp[i][j]<<' ';
		}
		cout<<'\n';
	}

}

