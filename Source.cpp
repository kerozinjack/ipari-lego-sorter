#include "MyForm.h"
using namespace baseform;
[STAThreadAttribute]
int main() {
	MyForm mf;
	mf.ShowDialog();
	return 0;
}