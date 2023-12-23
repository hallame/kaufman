#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

class NK_machine
{
public:
	NK_machine();
	NK_machine(const vector<vector<int>>& con_matr);
	NK_machine(const vector<vector<int>>& el_conmatr, int marker);

	void attractor();
	void print_con();
	void print_ellink();
	void print_gen();
	void print_curr_attr();
	int getK() { return k; }
	int getN() { return n; }
	int getAv_l() { return (L / l); }
	int getAv_d() { return l; }

	~NK_machine() {};

private:
	int n; int k; int L = 0; int M; int l = 0;
	vector<vector<int>> link_matrix;
	vector<vector<int>> elements_of_link_matr;
	vector<vector<int>> gen_vects;
	vector<vector<int>> current_attr;
	vector<vector<int>> all_attr;

	void elem();
	void con();
	void count_k();
	void generate_vectors();
};

NK_machine::NK_machine()	// Äëÿ n = 6
{
	link_matrix = {
		{ 0, 1, 0, 1, 0, 0 },
		{ 1, 0, 1, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 0 },
		{ 1, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 1, 1 },
		{ 0, 0, 1, 0, 1, 0 } };
	n = 6;
	count_k();
	elem();
	generate_vectors();
}

NK_machine::NK_machine(const vector<vector<int>>& con_matr)
{
	link_matrix = con_matr;
	n = link_matrix.size();
	count_k();
	elem();
	generate_vectors();
}

NK_machine::NK_machine(const vector<vector<int>>& el_conmatr, int marker)
{
	elements_of_link_matr = el_conmatr;
	n = elements_of_link_matr.size();
	k = elements_of_link_matr[0].size();
	con();
	generate_vectors();
}

void NK_machine::attractor()
{
	for (int help = 0; help < gen_vects.size(); help++)
	{
		current_attr.clear();
		current_attr.push_back(gen_vects[help]);
		int j = 1;
		bool check = true;
		while (check)
		{
			current_attr.push_back(vector<int>(n, 0));
			for (int i = 0; i < n; i++)
			{
				current_attr[j][i] = current_attr[j - 1][elements_of_link_matr[i][0]];
				switch (i % 5)
				{
				case 0:
					for (int s = 1; s < k; s++)
						current_attr[j][i] = (current_attr[j][i]) || (current_attr[j - 1][elements_of_link_matr[i][s]]);
					break;
				case 1:
					for (int s = 1; s < k; s++)
						current_attr[j][i] = !(current_attr[j][i]) && !(current_attr[j - 1][elements_of_link_matr[i][s]]);
					break;
				case 2:
					for (int s = 1; s < k; s++)
						current_attr[j][i] = !(current_attr[j][i]) || !(current_attr[j - 1][elements_of_link_matr[i][s]]);
					break;
				case 3:
					for (int s = 1; s < k; s++)
						current_attr[j][i] = (current_attr[j][i]) && (current_attr[j - 1][elements_of_link_matr[i][s]]);
					break;
				case 4:
					for (int s = 1; s < k; s++)
						current_attr[j][i] = !(current_attr[j][i]) && !(current_attr[j - 1][elements_of_link_matr[i][s]]);
					break;
				case 6:
					for (int s = 1; s < k; s++)
						current_attr[j][i] = (current_attr[j][i]) || (current_attr[j - 1][elements_of_link_matr[i][j]]);
					break;
				}
			}
			j++;

			for (int i = 0; i < current_attr.size() - 1; i++)
			{
				if (current_attr[current_attr.size() - 1] == current_attr[i])
				{
					check = false;
				}
			}
		}
		print_curr_attr();
		L += current_attr.size() - 2; l++;

		/*for (int i = 1; i < current_attr.size(); i++)
		{
			if (current_attr[1] in all_attr[i])
			{

			}
		}*/

		for (int i = 0; i < current_attr.size(); i++)
		{
			all_attr.push_back(current_attr[i]);
		}
		/*if (true)
		{
			M++;
		}*/
	}
}

void NK_machine::print_con()
{
	for (int i = 0; i < link_matrix.size(); i++)
	{
		for (int j = 0; j < link_matrix[i].size(); j++)
			cout << link_matrix[i][j];
		cout << endl;
	}
	cout << endl;
}

void NK_machine::print_ellink()
{
	for (int i = 0; i < elements_of_link_matr.size(); i++)
	{
		for (int j = 0; j < elements_of_link_matr[i].size(); j++)
			cout << elements_of_link_matr[i][j];
		cout << endl;
	}
	cout << endl;
}

void NK_machine::print_gen()
{
	for (int i = 0; i < gen_vects.size(); i++)
	{
		for (int j = 0; j < gen_vects[i].size(); j++)
			cout << gen_vects[i][j];
		cout << endl;
	}
	cout << endl;
}

void NK_machine::print_curr_attr()
{
	for (int i = 0; i < current_attr.size(); i++)
	{
		cout << i << " state: ";
		for (int j = 0; j < current_attr[i].size(); j++)
		{
			cout << current_attr[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void NK_machine::elem()
{
	for (int i = 0; i < n; i++)
	{
		elements_of_link_matr.push_back(vector<int>());
		for (int j = 0; j < n; j++)
		{
			if (link_matrix[i][j] == 1)
				elements_of_link_matr[i].push_back(j);
		}
	}
}

void NK_machine::con()
{
	for (int i = 0; i < n; i++)
	{
		link_matrix.push_back(vector<int>());
		int l = 0;
		for (int j = 0; j < n; j++)
		{
			if (elements_of_link_matr[i][l] == j)
			{
				link_matrix[i].push_back(1);
				if (l != k - 1)
					l++;
			}
			else
				link_matrix[i].push_back(0);
		}
	}
}

void NK_machine::count_k()
{
	int k = 0;
	for (int i = 0; i < link_matrix[0].size(); i++)
		if (link_matrix[0][i] == 1)
			k++;
	this->k = k;
}

void NK_machine::generate_vectors()
{
	for (int i = 0; i < pow(2, n); i++)
	{
		vector<int> bin;
		int b = i;
		while (b > 0) {
			bin.push_back(b % 2);
			b /= 2;
		}
		if (bin.size() < n) {
			int temp = n - bin.size();
			for (int j = 0; j < temp; j++)
				bin.push_back(0);
		}
		reverse(bin.begin(), bin.end());
		gen_vects.push_back(bin);
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	/*vector<vector<int>> basic_vec{{1, 1, 0, 1, 0, 0}};

	vector<vector<int>> link_matrix{
		{ 0, 1, 0, 1, 0, 0},
		{ 1, 0, 1, 0, 0, 0},
		{ 0, 1, 0, 1, 0, 0},
		{ 1, 0, 0, 0, 0, 1},
		{ 0, 0, 0, 0, 1, 1},
		{ 0, 0, 1, 0, 1, 0}};

	NK_machine test(link_matrix);
	test.print_gen();
	test.print_con();
	test.print_ellink();
	cout << test.getK() << endl;
	cout << test.getN() << endl;

	cout << "========================================" << endl;

	test.attractor();
	cout << test.getAv_l() << endl;*/

	vector<vector<int>> tt{{2, 3, 4}, {0, 1, 6}, {1, 3, 5}, {0, 2, 3}, {0, 2, 4}, {0, 1, 2}, {0, 1, 2}};
	NK_machine test1(tt, 1);
	test1.print_gen();
	test1.print_con();
	test1.print_ellink();
	cout << test1.getK() << endl;
	cout << test1.getN() << endl;
	cout << "========================================" << endl;
	test1.attractor();
	cout << test1.getAv_l() << endl;
	cout << test1.getAv_d() << endl;

	//NK_machine test2;
	//test2.print_gen();
	//test2.print_con();
	//test2.print_ellink();
	//cout << test2.getK() << endl;
	//cout << test2.getN() << endl;

	return 0;
}
