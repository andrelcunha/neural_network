#include <iostream>
#include <math.h>
#include <cstdlib>
#include <windows.h>
#include "neuron.h"
#include "my_random.h"
#ifdef _WIN32
        void my_sleep(int secs){
                Sleep(secs);
        }
#else
        void my_sleep(int secs){
                sleep(secs);
        }
#endif

using namespace std;
//******************************************************************************
Cneuron::Cneuron(int n, int *S, float lamb){
    Debugging=false;
	N = n + 1;					//N -> collums
	rows=pow(2,(N-1));				//total de combinações
	generate_table();
	populate_W();
	dendrites_i = new int[rows];
    S0 = new int[rows];
	for (int i=0;i<rows;i++){
		if (S[i]==0)
			S0[i]=-1;
		else
			S0[i]=S[i];
	}
	if(Debugging)
       debug();
    lambda = lamb;
	axon = 0;

}
//******************************************************************************
Cneuron::~Cneuron(){
	delete  [ ]S0;
	S0 = NULL;
	delete  [ ]matrix;
	matrix = NULL;
	delete  [ ]W;
	W = NULL;
	delete [ ]dendrites_i;
	dendrites_i = NULL;
}

//******************************************************************************
void Cneuron::teach(){
    bool with_error=0;
	int counter=1;
	do{
		for (int i=0;i<N;i++){
		    cout << "iteration " << counter <<endl;
			with_error=0;
			for (int j=0; j<rows;j++){
				dendrites_i[j]= matrix[i][j];
			}
			if (activation()!=S0[i]){
					learn(S0[i]);
					cout << "Learning!" <<endl;
					with_error=1;
            }
			counter ++;
        }
	}while (with_error);
	cout << "Aprendi!" << endl;
}
//******************************************************************************
void Cneuron::learn(int S){
	float *Wn = new float[N];
	for (int i=0;i<N;i++){
		if (Debugging)
			cout << "W1 = W0(" << W[i] << ") + lambda("<< lambda <<") * ["<< S << " - " << axon <<"] * x"<< i <<" " << dendrites_i[i] <<endl;
		Wn[i]=W[i] + lambda*(S - axon)*dendrites_i[i];
		W[i]=Wn[i];

	}

}
//******************************************************************************
int Cneuron::activation(){                      //Verificar se estah funcionando
	float temp=0;
	for (int i=0;i<N;i++){
        temp += float(dendrites_i[i]) * (W[i]);
		if(Debugging)
			cout << temp<<"+="<<dendrites_i[i]<<" * "<<W[i] << endl;
	}
	if (temp < 0) {
		axon = -1;
	}
	else {
		axon = 1;
	}
	if(Debugging)
        cout << "axon " << axon   <<endl;
	return axon;
}
//******************************************************************************
void Cneuron::generate_table(){            //working fine -- verificar
	matrix = new int*[N];
	for (int i=0;i<N;i++){
        matrix[i]= new int [rows];
	}
    for (int i=0;i<N;i++){
        int aux=0;
        for(int j=0;j<rows;j++){
            int variation=pow(2,(N-i-1));
            if(i==0){
                matrix[i][j]=1;
            }
            else{
                if(((j)%(variation))==0&&j!=0){
                    if(aux==0){
                        aux=1;
                    }else{
                        aux=0;
                    }
                }
                matrix[i][j]=aux;
            }
        }
    }
}
//******************************************************************************
void Cneuron::populate_W(){                     //working fine
    W = new float [N];
    cout<< "Randomizing ";
    for (int i=0;i<N;i++){
        W[i]=generate_random();
        my_sleep(250);
        cout << ".";
        my_sleep(250);
        cout << ".";
        //sleep((1));
        //cout << "#";
    }
    cout <<endl;

}
//******************************************************************************
float Cneuron::generate_random(){               //working fine
	BasicLCG rng(time(0));
	int x1=rng.inRange(0, 100), x2=rng.inRange(0, 100);
	//cout << x1<< "=x1 "<< x2 <<"=x2"<<endl;
	int aux = (x1 - x2);
	float out = (float)aux / 100;
	rng.~BasicLCG();
	return out;
}
//******************************************************************************
void Cneuron::debug(){
    for (int i=0; i<N;i++)
        cout<<"X"<<i<<"______";                           //header
    cout <<"..S0";
    cout<<endl;
    for (int i=0; i<N;i++)
        cout<<"--------";
    cout<<endl;
    //LOG Weights
    for (int i=0; i<N;i++){
        if (W[i] > 0)
            cout << "_";
        cout << W[i]<<"__";
    }
    cout <<"_________<-Weights"<<endl;
    //LOG true_table
    for (int j=0;j<rows;j++){
			//cout << i;
			for(int i=0;i<N;i++){
				//    cout << j << " ";
				cout << matrix[i][j] << "_______" ;
			}
			cout <<"__";
			if(S0[j]>0)
                cout <<"_";
			cout<< S0[j];    // LOG S0
			cout << endl;
    }
}
