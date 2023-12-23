#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
using namespace std;

//Vector printing
void show(vector<int> &v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " "<< endl;
}

//Matrix printing
void show(vector<vector<int>> &matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++)
            cout << matrix[i][j] << " " << endl;
    }
    cout << endl;
}

//Output of state vectors
void show_state(const vector<vector<int>> &sm){
    for(int i = 0; i < sm.size(); i++){
        cout << i << " State" << ": ";    // state number
        for(int j = 0; j < sm[i].size(); j++)
            cout << sm[i][j] <<" "<< endl;
    }
    cout << endl;
}

// Output of all vectors of length N
void all_Nvectors(int n, vector<vector<int>> &v){
    for(int i = 0; i < pow(2, n); i++){
        vector<int> Vec;        // we create a vector
        int k = i;
        while(k > 0){
            Vec.push_back(k % 2);       //convert a decimal number to binary
            k /= 2;
        }
        if(Vec.size() < n){
            int t = n - Vec.size();      //how many zero should
            for(int j = 0; j < t; j++)
                Vec.push_back(0);
        }
        reverse(Vec.begin(), Vec.end());   //turning to line over
        v.push_back(Vec);
    }
}

//Boolean operation OR function description:
bool Or(int n, int i, vector<int> &v0, vector<vector<int>> &sv){       //we pass the size of the vector, the line number,
                                                                        //the initial vector and the connection matrix
    bool boolean = false;                                                  //for all subsequent Boolean operations, similar arguments
    for(int j = 0; j < n; j++){
        if(sv[i][j] == 1){
            if(v0[j] == 1){
                return true;
            }
            else
                boolean = false;
        }
    }
    return boolean;       // returning value
}

//boolean operation _OR function description:
bool _Or(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
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
bool And(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
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
bool _And(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
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
    cout << "Enter N" << endl ;
    cin >> n;
    cout << "Enter K" << endl ;
    cin >> k;
    int L = 0;                         //initialize the length L to zero
    vector<int> v0(n,0);               // initial vector
    vector<vector<int>> mv;            //vectors matrix
    vector<vector<int>> sv(n,vector<int>(n,0)); //connection vector
    vector<vector<int>> attractors; //attractor matrix
    vector<vector<int>> all_attractors; //matrix of all attractors
    vector<int> l;

    cout << endl ;

    cout << "All possible input vectors of a given length N:" << endl ;
    all_Nvectors(n,mv); // generating of all these possible vectors using the function we wrote
    show(mv); //vectors printing
    cout << "Connected matrix:\n";
    //generating a communication matrix
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){ //there should be K units in each line
            int k = i;
            while(k == i || sv[i][k] == 1){ //it is important to check that the element does not enter itself (the main diagonal)
                k = rand()%n;
            }
            sv[i][k]=1; //we arrange the ones
        }
    }
    show(sv); //printing the communication matrix


    vector<vector<int>> matrix; //creating a matrix of states  mmatrix
    bool checking = true, pr1=true;

    matrix.push_back(v0); //addition of initial vector

    for(int var = 0; var < sv.size(); var++){
        v0 = sv[var];
        vector<vector<int>> mat;
        mat.push_back(v0);
        bool checking = true;
        bool pr = true;
        while(checking){
            vector<int> v1(n,0); //last vector
            for(int i = 0; i < n; i++){
                switch(i % 4){ //we arrange Boolean operators: we apply cases depending on the position of the element
                    case 0:
                        for(int i = 0; i < n; i++){
                            v1[i] = Or(n, i, v0, sv); //calling a function of the corresponding Boolean operator
                        }
                        break;
                    case 1:
                        for(int i = 0; i < n; i++){
                            v1[i] = And(n, i, v0, sv);
                        }
                        break;
                    case 2:
                        for(int i = 0; i < n; i++){
                            v1[i] = _Or(n, i, v0, sv);
                        }
                        break;
                    case 3:
                        for(int i = 0; i < n; i++){
                            v1[i] = _And(n, i, v0, sv);
                        }
                        break;
                }
            } //the arrangement of Boolean operators is over
            v0 = v1; //now the subsequent vector is the initial vector
            for(int i = 0; i < mat.size(); i++){ //attractors searching
                if(mat[i] == v1){
                    checking = false;
                    l.push_back(mat.size() - i); //we write down the length of the attractor (taking away the position we are at)
                    for(int k = 0; k < all_attractors.size(); k++){ //let's see if such an attractor has already been recorded
                        if(mat[i] == all_attractors[k]){
                            pr = false;
                            break;
                        }
                    }
                    if(pr){
                        for(int j = i; j < mat.size(); j++){
                            all_attractors.push_back(mat[j]);
                            //if such an attractor has not been encountered, we write it into the attractor matrix
                        }
                        attractors.push_back(mat[i]);
                        //writing down the attractor
                    }
                    break;
                }
            }
            mat.push_back(v1); //we write the resulting vector
        }
        show_state(mat);
    }


    for(int i = 0; i < l.size(); i++){
        L = L + l[i]; //sum for the length
    }
    L = L / l.size(); //divide by the number of attractors, getting the arithmetic mean (typical length of the attractor L)
    cout << "Length attractor L: " << L << endl;
    cout << "Number attractors M: " << attractors.size() << endl;
    show(all_attractors); //we derive unique attractors
    //cout << "\n\n\n";
    //show(attractors);

    return 0;
}



















