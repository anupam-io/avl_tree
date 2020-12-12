#include <iostream>
#include <math.h>
using namespace std;

int main(){
	int init_size = 1000000;
	int op_size = 10;

	for(int i = 1; i<=7; i++){
		system(string("./compare 1000000 "+ to_string(pow(10, i)) + " >> result.csv").c_str());
	}

	return 0;
}