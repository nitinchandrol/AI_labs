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

unordered_map< string, int > src_count; // this is used for count(si)
unordered_map< string, int > state_count; // this is used for count(si,sj,a)
vector<string> state_map; // int to string map
vector<vector <float>> seqscore; // table values
vector<vector <int>> backptr; // back pointers

int main(){
    string line,first,last;
    string triple_str; // string with concentanation of si,sj,a
    ifstream infile("output.txt");
   
    vector<string> expected_output;
    vector<vector <string> > input_vec;
    vector<string> input_phoneme;
    int count = 0;
    int match = 0, unmatch = 0;
    while (getline(infile, line))
    {
        istringstream iss(line);
        string a;
        count++;
        iss >> a;
        first = a;
        int sz = first.size();
        int itr = 0;
        if(count%5 == 0){
        	//a = "^" + a;
            expected_output.push_back(a);
        	//input_vec.push_back(a);
            input_phoneme.push_back("^");
        	while(iss >> a){
               // cout << a << "\n";
        		input_phoneme.push_back(a);   
        	}
        	input_vec.push_back(input_phoneme);
        	input_phoneme.clear();
        }
        else{
            //cout << "first is " << first[itr] << "\n";
            string str = "";
            str = str + first[itr];
            triple_str = "eps/" + str + "/" + "^";
            //cout << triple_str << "\n";
            src_count["eps"]++;
            last = first[itr];
            itr++;
            state_count[triple_str]++;

            while(sz != 1){
                iss >> a;
                triple_str = last + "/" + first[itr] + "/" + a;
	            //triple_str = last + "/" + a + "/" + first[itr-1];
	            src_count[last]++;
	            

                last = first[itr];
	            itr++;
	            state_count[triple_str]++;
                //cout << triple_str << "\n";
	            sz--;
	        }
    	
            iss >> a;
            triple_str = last + "/" + "." + "/" + a;
            //cout << triple_str << "\n";
            src_count[last]++;
            state_count[triple_str]++;
           
        }
    }

    
    state_map.push_back("eps");
    for ( auto it = src_count.begin(); it != src_count.end(); ++it ){
        if(it->first != "eps"){
        state_map.push_back(it->first);
        }
    }
    
    for ( auto it = state_count.begin(); it != state_count.end(); ++it ){
            //cout << it->first << " " << it->second << "\n";
    }

    vector<string> input;
    vector<float> next_col;
    vector<int> backptr_col;
    string state_str;
    float prob;
    float max_sofar;
    int backptr_sofar, row_sz, col_sz;

    for(int m= 0; m < input_vec.size(); m++){
    	input = input_vec[m];
        row_sz = src_count.size();
        col_sz = input.size();
        vector<float> first_col;
        
        for(int j=0; j< row_sz; j++){
            if(j == 0) first_col.push_back(1);
            else first_col.push_back(0);
        }

        seqscore.push_back(first_col);
        //backptr.push_back(0);

        for(int t=1; t<=col_sz; t++){
        	if(t == col_sz){
        		state_str = state_map[0] + "/" + "." + "/" + input[t-1];
                //cout << "state string is " << state_str << "\n";
                prob = 1.0 * state_count[state_str]/ src_count[state_map[0]];
                //cout << "state_str is " << state_str << "\n";
                //cout << "porb is " <<prob << "\n";
                max_sofar = seqscore[t-1][0] * prob;
                backptr_sofar = 0;

                for(int j=1; j<row_sz; j++){
                    state_str = state_map[j] + "/" + "." + "/" + input[t-1];
                    prob = 1.0 * state_count[state_str]/ src_count[state_map[j]];
                    if(seqscore[t-1][j] * prob > max_sofar){
                        max_sofar = seqscore[t-1][j] * prob;
                        backptr_sofar = j;
                    }
        	    }
        	   next_col.push_back(max_sofar);
                backptr_col.push_back(backptr_sofar);
            }
            else {
                for(int i=0; i<row_sz; i++){
                    //starting case;
                    state_str = state_map[0] + "/" + state_map[i] + "/" + input[t-1];
                    //cout << "state string is " << state_str << "\n";
                    prob = 1.0 * state_count[state_str]/ src_count[state_map[0]];
                    //cout << "state_str is " << state_str << "\n";
                    //cout << "porb is " <<prob << "\n";
                    max_sofar = seqscore[t-1][0] * prob;
                    backptr_sofar = 0;

                    for(int j=1; j<row_sz; j++){
                        state_str = state_map[j] + "/" + state_map[i] + "/" + input[t-1];
                        prob = 1.0 * state_count[state_str]/ src_count[state_map[j]];
                        if(seqscore[t-1][j] * prob > max_sofar){
                            max_sofar = seqscore[t-1][j] * prob;
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
        cout << "input" << "\n";
        for(int p=0; p< input.size(); p++){
            cout << input[p] << "/";
        }
        cout << "\n";

        int last_state = backptr_sofar;
        string test_output = "";
        string out = expected_output[m];
        int sz = out.size();
        string str1;
        for(int j=col_sz-2; j>=0; j--){
        	test_output = "/" + state_map[last_state] + test_output;
           // cout << state_map[last_state] << " ";
            str1.clear();
            str1 = str1 + out[sz-1];
            if(str1 == state_map[last_state]) match++;
            else unmatch++;
            sz--;
            last_state = backptr[j][last_state];
        }
        cout << "output " << test_output << "\n";
        cout << "expected output " << expected_output[m] << "\n";
        for(int p=0; p< expected_output[m].size();p++){
        	//cout << "/" + expected_output[m][p] ;
        	//output = "/" + expected_output[m][p] + output;
        }
        //cout << "\n";
        //cout << "\n";
        cout << match << "\n";
    	cout << unmatch << "\n";
        seqscore.clear();
        backptr.clear();

    }
    cout << match << "\n";
    cout << unmatch << "\n";
    cout << "accuracy is " << match * 1.0 /(match + unmatch);
}
