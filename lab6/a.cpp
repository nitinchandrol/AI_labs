#include <iostream>
#include <map>
#include <string>
#include <math.h>
#include <vector>

using namespace std;
int longest,input_length, output_length, hidden_length;

map<char,vector<int> > graphene_map;
map<string,vector<int> > phoneme_map;
void initialize(){
	graphene_map['a']={0,0,0,0,0};
	graphene_map['b']={0,0,0,0,1};
	graphene_map['c']={0,0,0,1,0};
	graphene_map['d']={0,0,0,1,1};
	graphene_map['e']={0,0,1,0,0};
	graphene_map['f']={0,0,1,0,1};
	graphene_map['g']={0,0,1,1,0};
	graphene_map['h']={0,0,1,1,1};
	graphene_map['i']={0,1,0,0,0};
	graphene_map['j']={0,1,0,0,1};
	graphene_map['k']={0,1,0,1,0};
	graphene_map['l']={0,1,0,1,1};
	graphene_map['m']={0,1,1,0,0};
	graphene_map['n']={0,1,1,0,1};
	graphene_map['o']={0,1,1,1,0};
	graphene_map['p']={0,1,1,1,1};
	graphene_map['q']={1,0,0,0,0};
	graphene_map['r']={1,0,0,0,1};
	graphene_map['s']={1,0,0,1,0};
	graphene_map['t']={1,0,0,1,1};
	graphene_map['u']={1,0,1,0,0};
	graphene_map['v']={1,0,1,0,1};
	graphene_map['w']={1,0,1,1,0};
	graphene_map['x']={1,0,1,1,1};
	graphene_map['y']={1,1,0,0,0};
	graphene_map['z']={1,1,0,0,1};

    phoneme_map["AA"]={0,0,0,0,0,0,1};
    phoneme_map["AA0"]={0,0,0,0,0,1,0};
    phoneme_map["AA1"]={0,0,0,0,0,1,1};
    phoneme_map["AA2"]={0,0,0,0,1,0,0};
    phoneme_map["AE"]={0,0,0,0,1,0,1};
    phoneme_map["AE0"]={0,0,0,0,1,1,0};
    phoneme_map["AE1"]={0,0,0,0,1,1,1};
    phoneme_map["AE2"]={0,0,0,1,0,0,0};
    phoneme_map["AH"]={0,0,0,1,0,0,1};
    phoneme_map["AH0"]={0,0,0,1,0,1,0};
    phoneme_map["AH1"]={0,0,0,1,0,1,1};
    phoneme_map["AH2"]={0,0,0,1,1,0,0};
    phoneme_map["AO"]={0,0,0,1,1,0,1};
    phoneme_map["AO0"]={0,0,0,1,1,1,0};
    phoneme_map["AO1"]={0,0,0,1,1,1,1};
    phoneme_map["AO2"]={0,0,1,0,0,0,0};
    phoneme_map["AW"]={0,0,1,0,0,0,1};
    phoneme_map["AW0"]={0,0,1,0,0,1,0};
    phoneme_map["AW1"]={0,0,1,0,0,1,1};
    phoneme_map["AW2"]={0,0,1,0,1,0,0};
    phoneme_map["AY"]={0,0,1,0,1,0,1};
    phoneme_map["AY0"]={0,0,1,0,1,1,0};
    phoneme_map["AY1"]={0,0,1,0,1,1,1};
    phoneme_map["AY2"]={0,0,1,1,0,0,0};
    phoneme_map["B"]={0,0,1,1,0,0,1};
    phoneme_map["CH"]={0,0,1,1,0,1,0};
    phoneme_map["D"]={0,0,1,1,0,1,1};
    phoneme_map["DH"]={0,0,1,1,1,0,0};
    phoneme_map["EH"]={0,0,1,1,1,0,1};
    phoneme_map["EH0"]={0,0,1,1,1,1,0};
    phoneme_map["EH1"]={0,0,1,1,1,1,1};
    phoneme_map["EH2"]={0,1,0,0,0,0,0};
    phoneme_map["ER"]={0,1,0,0,0,0,1};
    phoneme_map["ER0"]={0,1,0,0,0,1,0};
    phoneme_map["ER1"]={0,1,0,0,0,1,1};
    phoneme_map["ER2"]={0,1,0,0,1,0,0};
    phoneme_map["EY"]={0,1,0,0,1,0,1};
    phoneme_map["EY0"]={0,1,0,0,1,1,0};
    phoneme_map["EY1"]={0,1,0,0,1,1,1};
    phoneme_map["EY2"]={0,1,0,1,0,0,0};
    phoneme_map["F"]={0,1,0,1,0,0,1};
    phoneme_map["G"]={0,1,0,1,0,1,0};
    phoneme_map["HH"]={0,1,0,1,0,1,1};
    phoneme_map["IH"]={0,1,0,1,1,0,0};
    phoneme_map["IH0"]={0,1,0,1,1,0,1};
    phoneme_map["IH1"]={0,1,0,1,1,1,0};
    phoneme_map["IH2"]={0,1,0,1,1,1,1};
    phoneme_map["IY"]={0,1,1,0,0,0,0};
    phoneme_map["IY0"]={0,1,1,0,0,0,1};
    phoneme_map["IY1"]={0,1,1,0,0,1,0};
    phoneme_map["IY2"]={0,1,1,0,0,1,1};
    phoneme_map["JH"]={0,1,1,0,1,0,0};
    phoneme_map["K"]={0,1,1,0,1,0,1};
    phoneme_map["L"]={0,1,1,0,1,1,0};
    phoneme_map["M"]={0,1,1,0,1,1,1};
    phoneme_map["N"]={0,1,1,1,0,0,0};
    phoneme_map["NG"]={0,1,1,1,0,0,1};
    phoneme_map["OW"]={0,1,1,1,0,1,0};
    phoneme_map["OW0"]={0,1,1,1,0,1,1};
    phoneme_map["OW1"]={0,1,1,1,1,0,0};
    phoneme_map["OW2"]={0,1,1,1,1,0,1};
    phoneme_map["OY"]={0,1,1,1,1,1,0};
    phoneme_map["OY0"]={0,1,1,1,1,1,1};
    phoneme_map["OY1"]={1,0,0,0,0,0,0};
    phoneme_map["OY2"]={1,0,0,0,0,0,1};
    phoneme_map["P"]={1,0,0,0,0,1,0};
    phoneme_map["R"]={1,0,0,0,0,1,1};
    phoneme_map["S"]={1,0,0,0,1,0,0};
    phoneme_map["SH"]={1,0,0,0,1,0,1};
    phoneme_map["T"]={1,0,0,0,1,1,0};
    phoneme_map["TH"]={1,0,0,0,1,1,1};
    phoneme_map["UH"]={1,0,0,1,0,0,0};
    phoneme_map["UH0"]={1,0,0,1,0,0,1};
    phoneme_map["UH1"]={1,0,0,1,0,1,0};
    phoneme_map["UH2"]={1,0,0,1,0,1,1};
    phoneme_map["UW"]={1,0,0,1,1,0,0};
    phoneme_map["UW0"]={1,0,0,1,1,0,1};
    phoneme_map["UW1"]={1,0,0,1,1,1,0};
    phoneme_map["UW2"]={1,0,0,1,1,1,1};
    phoneme_map["V"]={1,0,1,0,0,0,0};
    phoneme_map["W"]={1,0,1,0,0,0,1};
    phoneme_map["Y"]={1,0,1,0,0,1,0};
    phoneme_map["Z"]={1,0,1,0,0,1,1};
    phoneme_map["ZH"]={1,0,1,0,1,0,0};
    phoneme_map["ZH"]={1,0,1,0,1,0,1};

}

struct CBackProp{
//        double **out; //      output of each neuron
//        double **delta;//      delta error value for each neuron
//        double ***weight;//      3-D array to store weights for each neuron
//        int numl;//      no of layers in net including input layer
//        int *lsize;//      array of numl elements to store size of each layer
//        double beta;//      learning rate
//        double ***prevDwt;//      storage for weight-change made in previous epoch
//
    vector<vector<double> > *out, *delta;
    vector<vector<vector<double> > > *weight, *prevDwt;
    vector<int> *lsize;
    double beta;
    int numl;

    ~CBackProp();

//      initializes and allocates memory

    void printWeight(){
        vector<vector<vector<double> > > w = *weight;
        for(int i = 0; i < w.size(); i++){
            for(int j = 0; j < w[i].size(); j++){
                for(int k = 0; k < w[i][j].size(); k++){
                    cout<<"weight in row:"<<i<< "from:"<<j<<"<< to: "<<k<<" is:"<<w[i][j][k]<<endl;
                }
            }
        }
    }

    CBackProp(int nl,int *sz,double b){

        // Note that the following are unused delta[0], weight[0],prevDwt[0]
        //    set no of layers and their sizes
        numl=nl;
        (*lsize).resize(numl);

        for(int i=0;i<numl;i++){
            (*lsize)[i]=sz[i];
        }

        //    allocate memory for output of each neuron
        (*out).resize(numl);
        int i;
        for( i=0;i<numl;i++){
            (*out)[i].resize((*lsize)[i]);
        }

        //    allocate memory for delta
        (*delta).resize(numl);

        for(i=1;i<numl;i++){
            (*delta)[i].resize((*lsize)[i]);
        }

        //    allocate memory for weights
        (*weight).resize(numl);

        for(i=1;i<numl;i++){
            (*weight)[i].resize((*lsize)[i]);
        }
        for(i=1;i<numl;i++){
            for(int j=0;j<(*lsize)[i];j++){
                (*weight)[i][j].resize((*lsize)[i-1]+1);
            }
        }

        //    allocate memory for previous weights
        (*prevDwt).resize(numl);

        for(i=1;i<numl;i++){
            (*prevDwt)[i].resize((*lsize)[i]);

        }
        for(i=1;i<numl;i++){
            for(int j=0;j<(*lsize)[i];j++){
                (*prevDwt)[i][j].resize((*lsize)[i-1]+1);
            }
        }

        //    seed and assign random weights
        srand((unsigned)(time(NULL)));
        for(i=1;i<numl;i++)
            for(int j=0;j<(*lsize)[i];j++)
                for(int k=0;k<(*lsize)[i-1]+1;k++)
                    (*weight)[i][j][k]=0.0;

        //    initialize previous weights to 0 for first iteration
        for(i=1;i<numl;i++)
            for(int j=0;j<(*lsize)[i];j++)
                for(int k=0;k<(*lsize)[i-1]+1;k++)
                    (*prevDwt)[i][j][k]=0.0;
    }

    double sigmoid(double in){  // sigmoid function
        return (1/(1+exp(-in)));
    }


//      backpropogates error for one set of input
    void bpgt(vector<int> *in,vector<int> *tgt){
        double sum;

        //	update output values for each neuron
        ffwd(in);

        //	find delta for output layer
        for(int i=0;i<(*lsize)[numl-1];i++){
            (*delta)[numl-1][i]=(*out)[numl-1][i]*
            (1-(*out)[numl-1][i])*((*tgt)[i]-(*out)[numl-1][i]);
        }

        //	find delta for hidden layers
        for(int i=numl-2;i>0;i--){
            for(int j=0;j<(*lsize)[i];j++){
                sum=0.0;
                for(int k=0;k<(*lsize)[i+1];k++){
                    sum+=(*delta)[i+1][k]*(*weight)[i+1][k][j];
                }
                (*delta)[i][j]=(*out)[i][j]*(1-(*out)[i][j])*sum;
            }
        }


        //	adjust weights usng steepest descent
        for(int i=1;i<numl;i++){
            for(int j=0;j<(*lsize)[i];j++){
                for(int k=0;k<(*lsize)[i-1];k++){
                    (*prevDwt)[i][j][k]=beta*(*delta)[i][j]*(*out)[i-1][k];
                    (*weight)[i][j][k]+=(*prevDwt)[i][j][k];
                }
                (*prevDwt)[i][j][(*lsize)[i-1]]=beta*(*delta)[i][j];
                (*weight)[i][j][(*lsize)[i-1]]+=(*prevDwt)[i][j][(*lsize)[i-1]];
            }
        }
    }


//      feed forwards activations for one set of inputs
    void ffwd(vector<int> *in){
        double sum;

 // assign content to input layer

        for(int i=0;i < (*lsize)[0];i++)
            (*out)[0][i]=(*in)[i];


// assign output(activation) value
// to each neuron usng sigmoid func

        // For each layer
        for(int i=1;i < numl;i++){
            // For each neuron in current layer
            for(int j=0;j < (*lsize)[i];j++){
                sum=0.0;
                // For input from each neuron in preceding layer
                for(int k=0;k < (*lsize)[i-1];k++){
                        // Apply weight to inputs and add to sum
                        sum+= (*out)[i-1][k]*(*weight)[i][j][k];
                }
                // Apply bias
                sum+=(*weight)[i][j][(*lsize)[i-1]];
                // Apply sigmoid function
                (*out)[i][j]=sigmoid(sum);
            }
        }
    }

//      returns mean square error of the net
    double mse(vector<int> *tgt){
        double mse=0;
        for(int i=0;i<(*lsize)[numl-1];i++){
            mse+=((*tgt)[i]-(*out)[numl-1][i])*((*tgt)[i]-(*out)[numl-1][i]);
        }
        return mse/2;
    }


//      returns i'th output of the net
    double Out(int i) const;
};

void convertInputStringToBinary(string input, vector<int> &input_to_int){
    for(int i = 0; i < input.size(); i++){
       input_to_int.insert(input_to_int.end(),graphene_map[input[i]].begin(),graphene_map[input[i]].end());
    }
}

void convertOutputStringToBinary(vector<string> output, vector<int>& output_to_int){
    for(int i = 0; i < output.size(); i++){
        output_to_int.insert(output_to_int.end(),phoneme_map[output[i]].begin(),phoneme_map[output[i]].end());
    }
}

int main(){
	longest = 9;
    int layer_count = 3;
    int layer_size[] = {longest*5,longest*6, longest*7};
    int beta = 0.2;
    double thresh = 0.00001;
    CBackProp *bp = new CBackProp(layer_count, layer_size, beta);

    for(long i = 0 ; i < 10000000; i++){

        string input = "KUBENA";
        vector<string> output = {"K", "AH0" ,"B", "IY1", "N", "AH0"};
        vector<int> input_to_int, output_to_int;
        convertInputStringToBinary(input,input_to_int);
        convertOutputStringToBinary(output,output_to_int);
        bp->bpgt(&input_to_int,&output_to_int);
        double error = bp->mse(&output_to_int);
        if(error < thresh) {
            cout<<"accuracy of threshold acheived in iteration:"<<i<< " and error is"<<error<<'\n';
            break;
        }
        if(i%10==0){
            cout<<"error is "<<bp->mse(&output_to_int);
        }
    }
}
