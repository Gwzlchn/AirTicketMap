#include <cmath>
#include<Python.h>

using namespace std;


int PYmain()
{
	//cout << "hello Python!" << endl;

	Py_Initialize();
	if (!Py_IsInitialized())
	{
		return -1;
	}
	PyRun_SimpleString("import matplotlib.pyplot as plt");
	PyRun_SimpleString("plt.plot(range(5))");
	PyRun_SimpleString("plt.show()");
	Py_Finalize();

	getchar();

	return 0;
}