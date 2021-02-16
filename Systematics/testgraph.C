#include <TROOT.h>
#include <TGraphErrors.h>
#include <iostream>

void testgraph()
{
	const Double_t xval[4] = {1.0, 2.0, 3.0, 4.0};
	const Double_t yval[4] = {1.0, 2.0, 3.0, 4.0};
	const Double_t Exval[4] = {0.0001, 0.0001, 0.0001, 0.0001};
	const Double_t Eyval[4] = {0.0001, 0.0001, 0.0001, 0.0001};
	TGraphErrors* g1 = new TGraphErrors(4, xval, yval, Exval, Eyval);

	Double_t outx[4];
	Double_t outy[4];
	for(Int_t ibin = 0; ibin < 4; ibin++)
	{
		g1->GetPoint(ibin, outx[ibin], outy[ibin]);
		cout << "bin: " << ibin << ", val: " << outy[ibin] << endl;
	}
}
