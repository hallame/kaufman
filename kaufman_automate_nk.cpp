
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

//Vector printing
void print(vector<int> &v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " "<< endl;
}

//Matrix printing
void print(vector<vector<int>> &matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++)
            cout << matrix[i][j] << " ";
            cout << endl;
    }
    cout << endl;
}

//Output of state vectors
void print_state(const vector<vector<int>> &sv){
    for(int i = 0; i < sv.size(); i++){
        cout << i << " State" << ": ";                                           // state number
        for(int j = 0; j < sv[i].size(); j++)
            cout << sv[i][j] <<" ";
            cout << endl;
    }
    cout << endl;
}

// Output of all vectors with the length n
void all_nvectors(int n, vector<vector<int>> &v){
    for(int i = 0; i < pow(2, n); i++){
        vector<int> Vec;                                                         // we create a vector
        int k = i;
        while(k > 0){
            Vec.push_back(k % 2);                                                // bin
            k /= 2;                                                              //convert a decimal number to binary
        }
        if(Vec.size() < n){
            int t = n - Vec.size();                                              //how many zero should
            for(int j = 0; j < t; j++)
                Vec.push_back(0);
        }
        reverse(Vec.begin(), Vec.end());
        v.push_back(Vec);
    }
}

//Boolean operation OR function description:
bool OR(int n, int i, vector<int> &v0, vector<vector<int>> &sv){                 //we pass the size of the vector, the line number,the initial vector and the connection matrix
    bool boolean = false;                                                        //  similar arguments for all following Boolean operation
    for(int j = 0; j < n; j++){
        if(sv[i][j] == 1){
            if(v0[j] == 1){
                return true;
            }
            else
                boolean = false;
        }
    }
    return boolean;
}

//boolean operation _OR function description:
bool _OR(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
    bool boolean = false;
    for(int j = 0; j < n; j++){
        if(sv[i][j] == 1){
            if(v0[j] == 0){
                return true;
            }
            else
                boolean = false;
        }
    }
    return boolean;
}

//Boolean operation AND function description:
bool AND(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
    bool boolean = false;
    for(int j = 0; j < n; j++){
        if(sv[i][j] == 1){
            if(v0[j] == 1){
                boolean = true;
            }
            else{
                return false;
            }
        }
    }
    return boolean;
}

//boolean operation _AND function description:
bool _AND(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
    bool boolean = false;
    for(int j = 0; j < n; j++){
        if(sv[j][i] == 1){
            if(v0[i] == 0){
                boolean = true;
            }
            else
                return false;
        }
    }
    return boolean;
}


int main(){
    srand(time(NULL));
    int n, k;
    cout << "Enter the number N:" << endl ;
    cin >> n;
    cout << "Enter the number K:" << endl ;
    cin >> k;
    int L = 0;                                                                   // we initialize the length L to zero
    vector<int> v0(n,0);                                                         // initial vector
    vector<vector<int>> mv;                                                      //vectors matrix
    vector<vector<int>> con_v(n,vector<int>(n,0));                               //connection vector
    vector<vector<int>> attractors;                                              //attractor matrix
    vector<vector<int>> all_attractors;                                          //matrix of all attractors
    vector<int> l;

    cout << "\nAll possible input vectors of the length "<< n << ":\n" << endl ;

    all_nvectors(n,mv);                                                          // generating of all these possible vectors using the function we wrote
    print(mv);                                                                   //vectors printing (vectors matrix)
    cout << "Connected matrix:\n";

    //generating a communication matrix

    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){                                              //there should be K units in each line
            int k = i;
            while(k == i || con_v[i][k] == 1){                                      //it is important to check that the element does not enter itself (the main diagonal)
                k = rand()%n;
            }
            con_v[i][k]=1;                                                          //we arrange the ones
        }
    }

    print(con_v);                                                                //printing the communication matrix

    //vector<vector<int>> matrix;                                                  //creating a matrix of states  mmatrix
   // bool check = true;                                                           //pr1=true;

   // matrix.push_back(v0);                                                        //addition of initial vector

    for(int ind = 0; ind < con_v.size(); ind++){
        v0 = con_v[ind];
        vector<vector<int>> matrixx;                                             //creating a matrix of states  mmatrix
        matrixx.push_back(v0);                                                    //addition of initial vector
        bool check = true;
        bool pr = true;
        while(check){
            vector<int> v1(n,0);                                                  //last vector
            for(int i = 0; i < n; i++){
                switch(i % 4){                                                    //we arrange Boolean operators: we apply cases depending on the position of the element
                    case 0:
                        for(int i = 0; i < n; i++){
                            v1[i] = OR(n, i, v0, con_v);                         //calling a function of the corresponding Boolean operator
                        }
                        break;
                    case 1:
                        for(int i = 0; i < n; i++){
                            v1[i] = AND(n, i, v0, con_v);
                        }
                        break;
                    case 2:
                        for(int i = 0; i < n; i++){
                            v1[i] = _OR(n, i, v0, con_v);
                        }
                        break;
                    case 3:
                        for(int i = 0; i < n; i++){
                            v1[i] = _AND(n, i, v0, con_v);
                        }
                        break;
                }
            }                                                                    //the arrangement of Boolean operators is over
            v0 = v1;                                                             //now the subsequent vector is the initial vector
            for(int i = 0; i < matrixx.size(); i++){                             //attractors searching
                if(matrixx[i] == v1){
                    check = false;
                    l.push_back(matrixx.size() - i);                             //we write down the length of the attractor (taking away the position we are at)
                    for(int k = 0; k < all_attractors.size(); k++){              //let's see if such an attractor has already been recorded
                        if(matrixx[i] == all_attractors[k]){
                            pr = false;
                            break;
                        }
                    }
                    if(pr){
                        for(int j = i; j < matrixx.size(); j++){
                            all_attractors.push_back(matrixx[j]);
                            //if such an attractor has not been encountered, we write it into the attractor matrix
                        }
                        attractors.push_back(matrixx[i]);
                                                                                 //writing down the attractor
                    }
                    break;
                }
            }
            matrixx.push_back(v1);                                               //we write the resulting vector
        }
        print_state(matrixx);
    }


    for(int i = 0; i < l.size(); i++){
        L += l[i];                                                               //sum for the length
    }
    L /= l.size();                                                               //divide by the number of attractors, getting the arithmetic mean (typical length of the attractor L)
    cout << "Typical length of the attractors L: " << L << endl;
    cout << "Number of the attractors M: " << attractors.size() << endl;
    print(all_attractors);                                                       //we derive unique attractors
    cout << "\n";
    print(attractors);
    //print(l);

    return 0;


}
