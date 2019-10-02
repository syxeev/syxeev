#include "gg.h"
#include "ss.h"
#include <iostream>
using namespace std;

int func(gg & D, ss & Q){
	int max = D.S;
	if ( Q.D > max) {
		max = Q.D;
	}
	if ( Q.Q > max) {
		max = Q.Q;
	}
	return max;
}
int main()
{
	int P;
	cin >> P;
	gg ob1{P};
	ss ob2;
	int a, b;
	cin >>a>>b;
	ob2.input(a, b);
	int max = func(ob1, ob2);
	cout << "max = " << max;
	return(0);
}
