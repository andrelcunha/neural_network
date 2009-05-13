#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "neuron.h"



using namespace std;
int main(int argc, char * argv[]){
    bool deb=false;
	if (argc == 2)
		if (atoi(argv[1])==1)
			deb=true;
	/*forcing debug mode*/   // deb=true;
	//declaring variables
	int N, aux,*S;
    float lambda;
    //test debug mode
    if(deb)
        cout << "##DEBUGGING MODE ON##" << endl;
    cout << "Type \"1\" to populate network or \"0\" to use XOR example:";
    cin >> aux;
    if (!aux){
        N=2;
        aux = pow((double)2,N);
        S = new int[aux];
        S[0] = 0;
        S[1] = 1;
        S[2] = 1;
        S[3] = 0;
        cout << "Informe o valor de Lambda" << endl;
        cin >> lambda;
    }
    else{
        //populating neuron
        cout << "Informe a quantidade de entradas" << endl;
        cin >> N;
        aux = pow((double)2,N);
        if(deb)
            cout << "aux: " << aux << endl;
        cout << "Informe o valor de Lambda" << endl;
        cin >> lambda;
        S = new int[aux];
        for (int i=0;i<aux;i++){
            bool flag_ok=false;
            while (!flag_ok){
                cout << "Digite a saida #" << (i+1) << endl;
                cin >> S[i];
                if ((S[i]==1)||(S[i]==0)){
                    flag_ok=true;
                }
                else{cout << "Valor invalido!" << endl;}
            }
        }
    }
    Cneuron My_neuron (N, S, lambda);
    My_neuron.set_debug(deb);
    My_neuron.teach();
    My_neuron.~Cneuron();
    delete []S;
    S = NULL;
    cin>>aux;
    return 0;

}
