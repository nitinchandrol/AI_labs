#include <iostream>
using namespace std;
string getBitmap(int pos){
	string bm = "";
	while(pos != 0){		
		bm = to_string(pos%2) + bm;
		pos /= 2;
	}
	return bm;
} 
int main(){
	cout << getBitmap(1);
}