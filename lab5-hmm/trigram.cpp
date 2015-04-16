#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

struct triplet{
    string str1,str2,str3;
};

unordered_map< string, int > src_count; // this is used for count(si-1, si)
unordered_map< string, int > state_count; // this is used for count(si-1,si,sj,a)
unordered_map< string, int > states; //count(si)
vector<string> state_map; // int to string map
vector<vector <float>> seqscore; // table values
vector<vector <int>> backptr; // back pointers

int main(){
    string line,first,last, second_last;
    string triple_str; // string with concentanation of si,sj,a
    ifstream infile("output.txt");
   
    vector<string> input_vec;
    vector<vector <string> > expected_output;
    vector<string> output;
    int count = 0;
    int match = 0, unmatch = 0;
    while (getline(infile, line))
    {
        istringstream iss(line);
        string a;
        count++;
        iss >> a;
        first = a;
        int itr = 0;
        if(count%5 == 0){
        	a = "^" + a;
        	input_vec.push_back(a);
        	while(iss >> a){
        		output.push_back(a);   
        	}
        	expected_output.push_back(output);
        	output.clear();
        }
        else{

	        while(iss >> a){
	            if(itr == 0){
	            	triple_str = "eps1/eps2/" + a + "/" + "^";
	                src_count["eps1/eps2"]++;
                    states["eps1"]++;
                    second_last = "eps1";
                    last = "eps2";
	            }
	            else{
	                triple_str = second_last + "/" + last + "/" + a + "/" + first[itr-1];
	                src_count[second_last + "/" + last]++;
                    states[second_last]++;
	            }
	            itr++;
	            state_count[triple_str]++;
                second_last = last;
	            last = a;
	        }
    	}
        triple_str = second_last + "/" + last + "/" + "." + "/" + first[itr-1];
        src_count[last]++;
        state_count[triple_str]++;
        states[second_last]++;
    }

    state_map.push_back("eps1");
    state_map.push_back("eps2");
    for ( auto it = states.begin(); it != states.end(); ++it ){
        if(it->first != "eps1" && it->first != "eps2"){
        state_map.push_back(it->first);
        }
    }
    cout << "size is " << state_map.size() << "\n";
    for ( auto it = state_count.begin(); it != state_count.end(); ++it ){
            //cout << it->first << " " << it->second << "\n";
    }

    string input;
    vector<float> next_col;
    vector<int> backptr_col;
    string state_str;
    float prob;
    float max_sofar;
    int backptr_sofar, row_sz, col_sz;
    
    for(int m= 0; m < input_vec.size(); m++){
    //for(int m= 0; m < 1; m++){
    	input = input_vec[m];
        row_sz = state_map.size();
        col_sz = input.size();
        vector<float> first_col;
        
        for(int j=0; j< row_sz; j++){
            if(j == 0) first_col.push_back(1);
            else first_col.push_back(0);
        }

        seqscore.push_back(first_col);
        //backptr.push_back(0);
        first_col.clear();
        for(int j=0; j< row_sz; j++){
            if(j == 1) first_col.push_back(1);
            else first_col.push_back(0);
        }

        seqscore.push_back(first_col);
        first_col.clear();
        for(int j=0; j< row_sz; j++){
            backptr_col.push_back(0);
        }

        backptr.push_back(backptr_col);
        backptr_col.clear();

        for(int t=1; t<=col_sz; t++){

        	if(t == col_sz){
        		state_str = state_map[backptr[t-1][0]] + "/" + state_map[0] + "/" + "." + "/" + input[t-1];
                cout << "state string is " << state_str << "\n";
                if(src_count[state_map[backptr[t-1][0]] + "/" + state_map[0]] == 0) prob = 0;
                else
                prob = 1.0 * state_count[state_str]/ src_count[state_map[backptr[t-1][0]] + "/" + state_map[0]];
                //cout << "state_str is " << state_str << "\n";

                cout << "porb is " <<prob << "\n";
                max_sofar = seqscore[t][0] * prob;
                backptr_sofar = 0;

                for(int j=1; j<row_sz; j++){
                    state_str = state_map[backptr[t-1][j]] + "/" + state_map[j] + "/" + "." + "/" + input[t-1];
                    if(src_count[state_map[backptr[t-1][j]] + "/" + state_map[j]] == 0) prob = 0;
                    else
                    prob = 1.0 * state_count[state_str]/ src_count[state_map[backptr[t-1][j]] + "/" + state_map[j]];
                    if(seqscore[t][j] * prob > max_sofar){
                        max_sofar = seqscore[t][j] * prob;
                        backptr_sofar = j;
                    }
        	    }
        	   next_col.push_back(max_sofar);
                backptr_col.push_back(backptr_sofar);
            }
            else {
                for(int i=0; i<row_sz; i++){
                    //starting case;

                    state_str = state_map[backptr[t-1][0]] + "/" + state_map[0] + "/" + state_map[i] + "/" + input[t-1];
                    //cout << "state string is " << state_str << "\n";
                    if(src_count[state_map[backptr[t-1][0]] + "/" + state_map[0]] == 0) prob = 0;
                    else
                    prob = 1.0 * state_count[state_str]/ src_count[state_map[backptr[t-1][0]] + "/" + state_map[0]];
                    //cout << "state_str is " << state_str << "\n";
                    //cout << "porb is " <<prob << "\n";
                    max_sofar = seqscore[t][0] * prob;
                    backptr_sofar = 0;

                    for(int j=1; j<row_sz; j++){
                        state_str = state_map[backptr[t-1][j]] + "/" + state_map[j] + "/" + state_map[i] + "/" + input[t-1];
                        //cout << "state string is " << state_str << "\n";
                        //cout << "i is " << i << "\n";
                        if(src_count[state_map[backptr[t-1][j]] + "/" + state_map[j]] == 0) prob = 0;
                        else
                        prob = 1.0 * state_count[state_str]/ src_count[state_map[backptr[t-1][j]] + "/" + state_map[j]];
                       // cout << "porb is " <<prob << "\n";
                        if(seqscore[t][j] * prob > max_sofar){
                            max_sofar = seqscore[t][j] * prob;
                            backptr_sofar = j;
                        }

                    }

                    //cout << "ith iteration " << i << " " << max_sofar << "\n";
                    next_col.push_back(max_sofar);
                    backptr_col.push_back(backptr_sofar);
                }
            }
            seqscore.push_back(next_col);
            backptr.push_back(backptr_col);
            next_col.clear();
            backptr_col.clear();
        }
        
        cout << input << "\n";
        int last_state = backptr_sofar;
        cout << "size is " << backptr.size()<< "\n";
        string test_output = "";
        vector<string> out = expected_output[m];
        int sz = out.size();
        for(int j= backptr.size() - 3; j>=0; j--){
        	test_output = "/" + state_map[last_state] + test_output;
            //cout << state_map[last_state] << "\n";
            //cout << "last_state " << last_state << "\n";
            if(state_map[last_state] == out[sz-1]) match++;
            else unmatch++;
            sz--;
            //cout << "j is " << j << "\n";
            //cout << "size " << backptr[j].size() << "\n";
            
            last_state = backptr[j][last_state];
            //cout << "last_state " << last_state << "\n";
        }
        cout << "output " << test_output << "\n";
        cout << "expected output ";
        for(int p=0; p< expected_output[m].size();p++){
        	cout << "/" + expected_output[m][p] ;
        	//output = "/" + expected_output[m][p] + output;
        }
        cout << "\n";
        //cout << "\n";
        //cout << match << "\n";
    	//cout << unmatch << "\n";
        seqscore.clear();
        backptr.clear();

    }
    cout << match << "\n";
    cout << unmatch << "\n";
    cout << "accuracy is " << match * 1.0 /(match + unmatch);
         
}
