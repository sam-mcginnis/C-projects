// Sean Szumlanski
// COP 3502, Summer 2018

// ==================================
// TriePrediction: UnitTestLauncher.c
// ==================================
// This code simply calls the unit_test() function in whatever test case is
// compiled with the program. This only works if TriePrediction.h is set to
// re-define main() as __hidden_main__(). Otherwise, compiling this with
// TriePrediction.h will result in two definitions of the main() function: one
// in TriePrediction.c, and one in this file.


int unit_test(int argc, char **argv);

int main(int argc, char **argv)
{
	unit_test(argc, argv);
	return 0;
}
