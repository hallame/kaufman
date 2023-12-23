

#include <iostream> //библиотека ввода вывода
#include <vector> //библиотека векторов
#include <cstdlib> //библиотека для рандома
#include <ctime> //библиотека времени для рандома
#include <cmath> //библиотека математики
#include <algorithm> //библиотека для корректного перебора векторов
using namespace std; //дабы не писать каждый раз std

//функция вывода для вектора
void print(vector<int> &v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

//функция вывода для матрицы
void print(vector<vector<int>> &matr){
    for(int i = 0; i < matr.size(); i++){
        for(int j = 0; j < matr[i].size(); j++)
            cout << matr[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

//функция для вывода векторов состояния
void print_state(const vector<vector<int>> &mm){
    for(int i = 0; i < mm.size(); i++){
        cout << i << " State" << ": "; //печатаем номер состояния
        for(int j = 0; j < mm[i].size(); j++)
            cout << mm[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

//функция вывода всех векторов длины N
void all_vectors(int n, vector<vector<int>> &v){
    for(int i = 0; i < pow(2, n); i++){
        vector<int> t; //создаем вектор
        int k = i;
        while(k > 0){
            t.push_back(k % 2);
            k /= 2; //аналогично переводу десятичного числа в двоичное
        }
        if(t.size() < n){
            int temp = n - t.size(); //определяем, сколько нужно добавить нулей
            for(int j = 0; j < temp; j++)
                t.push_back(0); //добавляем нули
        }
        reverse(t.begin(), t.end()); //переворачиваем строчку
        v.push_back(t);
    }
}

//описание функции булевой операции OR:
bool Or(int n, int i, vector<int> &v0, vector<vector<int>> &sv){ 
    //передаем размер вектора, номер строки, начальный вектора и матрицу связи
    //для всех последующих булевых операций аналогичные аргументы
    bool check = false;
    for(int j = 0; j < n; j++){
        if(sv[i][j] == 1){
            if(v0[j] == 1){
                return true;
            }
            else
                check = false;
        }
    }
    return check; //возвращаем значение
}

//описание функции булевой операции NOT OR:
bool _Or(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
    bool check = false;
    for(int j = 0; j < n; j++){
        if(sv[i][j] == 1){
            if(v0[j] == 0){
                return true;
            }
            else
                check = false;
        }
    }
    return check;
}

//описание функции булевой операции AND:
bool And(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
    bool check = false;
    for(int j = 0; j < n; j++){
        if(sv[i][j] == 1){
            if(v0[j] == 1){
                check = true;
            }
            else{
                return false;
            }
        }
    }
    return check;
}

//описание функции булевой операции NOT AND:
bool _And(int n, int i, vector<int> &v0, vector<vector<int>> &sv){
    bool check = false;
    for(int j = 0; j < n; j++){
        if(sv[j][i] == 1){
            if(v0[i] == 0){
                check = true;
            }
            else
                return false;
        }
    }
    return check;
}


int main(){
    srand(time(NULL));
    int n, k; //собственно N и K
    cout << "Введите N, нажмите Enter и введите K" << endl ;
    cin >> n >> k; 
    int L = 0; //инициализируем типичную длину L, пока что равную нулю
    vector<int> v0(n,0); //создаем начальный вектор
    vector<vector<int>> vv; //матрица векторов
    vector<vector<int>> sv(n,vector<int>(n,0)); //матрица связей
    vector<vector<int>> attractors; //матрица аттракторов
    vector<vector<int>> attractors_all; //матрица всех аттракторов
    vector<int> l;
    
    cout << endl ;
    
    cout << "Все возможные входные векторы заданной длины N:" << endl ;
    all_vectors(n,vv); //генерируем все эти возможные векторы при помощи написанной нами функции
    print(vv); //печатаем их
    
    
    cout << "Матрица связи:\n";
    //генерируем матрицу связи
    for(int i = 0; i < n; i++){
        for(int j = 0; j < k; j++){ //в каждой строке должно быть K едениц
            int k = i;
            while(k == i || sv[i][k] == 1){ //важно проверять, чтобы элемент не входил сам в себя (главная диагональ)
                k = rand()%n;
            }
            sv[i][k]=1; //расставляем еденички
        }
    }
    print(sv); //печатаем матрицу связи
    
    
    vector<vector<int>> matrix; //создаем матрицу состояний
    bool proverka = true, pr1=true;
    
    matrix.push_back(v0); //добавляем начальный вектор
    
    for(int var = 0; var < vv.size(); var++){
        v0 = vv[var];
        vector<vector<int>> mat;
        mat.push_back(v0);
        bool proverka = true;
        bool pr = true;
        while(proverka){
            vector<int> v1(n,0); //последующий вектор
            for(int i = 0; i < n; i++){
                switch(i % 4){ //расставляем булевые операторы: применяем кейсы в зависимости от позиции элемента
                    case 0:
                        for(int i = 0; i < n; i++){
                            v1[i] = Or(n, i, v0, sv); //вызов функции соотвествуеющего булевого оператора
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
            } //расстановка булевых операторов окончена
            v0 = v1; //теперь последубщий вектор является начальным вектором
            for(int i = 0; i < mat.size(); i++){ //поиск аттрактора
                if(mat[i] == v1){
                    proverka = false;
                    l.push_back(mat.size() - i); //записываем длину аттрактора (отнимая позицию, на которой находимся)
                    for(int k = 0; k < attractors_all.size(); k++){ //смотрим, был ли уже записан такой аттрактор
                        if(mat[i] == attractors_all[k]){
                            pr = false;
                            break;
                        }
                    }
                    if(pr){
                        for(int j = i; j < mat.size(); j++){
                            attractors_all.push_back(mat[j]);
                            //если такой атрактор не встречался, записываем его в матрицу аттракторов
                        }
                        attractors.push_back(mat[i]); 
                        //записываем атрактор
                    }
                    break;
                }
            }
            mat.push_back(v1); //записываем полученный вектор
        }
        print_state(mat); //печатаем состояние
    }
    
    
    for(int i = 0; i < l.size(); i++){
        L = L + l[i]; //суммируем длины аттракторов
    }
    L = L / l.size(); //делим на число аттракторов, получая среднее арифметическое (типичная длина аттрактора L)
    cout << "Типичная длина аттрактора L: " << L << endl;
    cout << "Число аттракторов M: " << attractors.size() << endl;
    print(attractors_all); //выводим уникальные аттракторы
    //cout << "\n\n\n";
    //print(attractors);
    
    return 0;
}





