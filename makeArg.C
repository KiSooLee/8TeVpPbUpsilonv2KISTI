#include <TROOT.h>
#include <fstream>

void makeArg()
{
	FILE* ftxt;
	ftxt = fopen("ArglistCorr11.txt", "w");

	for(Int_t i = 0; i < 11; i++)
	{
		fprintf(ftxt, "%d \n", i);
	}
	fclose(ftxt);
}
