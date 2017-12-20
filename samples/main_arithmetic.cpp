// реализация пользовательского приложения

#include "arithmetic.h"
#include <string>

int main()
{
	string str;
	bool f;
	double res;
    do {
		cout << "Your arithmetic expression:\n";
		getline(cin, str);	
		ariphmetic pvr(str);
		f = pvr.check();
       } while (f==false);
	str=minus(str);
	ariphmetic vr(str);
	vr.getpolish();
	vr.setvars();
	res = vr.calculate();
	cout << res << endl;
	return 0;
}
