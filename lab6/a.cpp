#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
int longest,input_length, output_length, hidden_length;

map<char,array<int,5> > graphene_map;
map<string,array<int,7> > phoneme_map;
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
//        double sigmoid(double in);//      sigmoid function
        vector<vector<double> > *out, *delta;
        vector<vector<vector<double> > > *weight, *prevDwt;
        vector<int> *lsize;
        double beta;
        int numl;

        ~CBackProp();

//      initializes and allocates memory
        CBackProp(int nl,int *sz,double b,double a){

            // Note that the following are unused delta[0], weight[0],prevDwt[0]
            //    set no of layers and their sizes
            numl=nl;
            lsize.resize(numl);

            for(int i=0;i<numl;i++){
                lsize[i]=sz[i];
            }

            //    allocate memory for output of each neuron
            out.resize(numl);
            int i;
            for( i=0;i<numl;i++){
                out[i].resize(lsize[i]);
            }

            //    allocate memory for delta
            delta.resize(numl);

            for(i=1;i<numl;i++){
                delta[i].resize(lsize[i]);
            }

            //    allocate memory for weights
            weight.resize(numl);

            for(i=1;i<numl;i++){
                weight[i].resize(lsize[i]);
            }
            for(i=1;i<numl;i++){
                for(int j=0;j<lsize[i];j++){
                    weight[i][j].resize(lsize[i-1]+1);
                }
            }

            //    allocate memory for previous weights
            prevDwt.resize(numl);

            for(i=1;i<numl;i++){
                prevDwt[i].resize(lsize[i]);

            }
            for(i=1;i<numl;i++){
                for(int j=0;j<lsize[i];j++){
                    prevDwt[i][j].resize(lsize[i-1]+1);
                }
            }

            //    seed and assign random weights
            srand((unsigned)(time(NULL)));
            for(i=1;i<numl;i++)
                for(int j=0;j<lsize[i];j++)
                    for(int k=0;k<lsize[i-1]+1;k++)
                        weight[i][j][k]=0.0;

            //    initialize previous weights to 0 for first iteration
            for(i=1;i<numl;i++)
                for(int j=0;j<lsize[i];j++)
                    for(int k=0;k<lsize[i-1]+1;k++)
                        prevDwt[i][j][k]=0.0;
        }

//      backpropogates error for one set of input
        void bpgt(double *in,double *tgt);

//      feed forwards activations for one set of inputs
        void ffwd(double *in);

//      returns mean square error of the net
        double mse(double *tgt);

//      returns i'th output of the net
        double Out(int i) const;
};

int main(){
	longest = 9;
	input_length = longest*5;
	output_length = longest*7;
	hidden_length = (input_length + output_length)/2;




}
