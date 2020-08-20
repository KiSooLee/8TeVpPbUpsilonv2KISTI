//Headers{{{
#include <TROOT.h>
#include <TTree.h>
#include <TString.h>
#include <TClonesArray.h>
//}}}

//Basic info{{{
/*
//v1: Integrated{{{
Int_t multBinsArr[] = {0, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 30};
//}}}
*/
/*
//v2: pt distribution{{{
Int_t multBinsArr[] = {0, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 6.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 29, 32, 35, 56, 77, 98, 119};
//}}}
*/
/*
//v3: multiplicity distribution{{{
Int_t multBinsArr[] = {0, 50, 80, 110, 150, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 30};
//}}}
*/
/*
//v4: low multiplicity pt distribution{{{
Int_t multBinsArr[] = {0, 40};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 3.0, 6.0, 10.0, 30.0};
//}}}
*/
/*
//v5: multiplicity 200~1500 pt distribution{{{
Int_t multBinsArr[] = {200, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 6.0, 30.0};
//}}}
*/
/*
//v6: multiplicity 100~1500 pt distribution{{{
Int_t multBinsArr[] = {100, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 6.0, 30.0};
//}}}
*/
/*
//v7: multiplicity 200~1500{{{
Int_t multBinsArr[] = {200, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 6.0, 30.0};
//}}}
*/
/*
//v8: multiplicity 185~1500{{{
Int_t multBinsArr[] = {185, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 6.0, 30.0};
//}}}
*/
/*
//v9: multiplicity 150~1500{{{
Int_t multBinsArr[] = {150, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 6.0, 30.0};
//}}}
*/
/*
//v10: multiplicity 120~1500{{{
Int_t multBinsArr[] = {120, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 6.0, 30.0};
//}}}
*/
/*
//v11: multiplicity 120~1500{{{
Int_t multBinsArr[] = {120, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 4.0, 6.0, 10.0, 30.0};
//}}}
*/
/*
//v12: multiplicity 110~1500{{{
Int_t multBinsArr[] = {110, 1500};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 4.0, 6.0, 10.0, 30.0};
//}}}
*/
/*
//v13: multiplicity 110~300, Trk pT 1~3{{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 4.0, 6.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 29, 32, 35, 56, 77, 98, 120};
//}}}
*/
/*
//v14: multiplicity 110~300, Trk pT 0~3{{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0, 4.0, 6.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 29, 32, 35, 56, 77, 98, 120};
//}}}
*/
/*
//v15: new pt range, multiplicity 0~300{{{
Int_t multBinsArr[] = {0, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 29, 32, 35, 56, 77, 98, 120};
//}}}
*/
/*
//v16: new pt range, multiplicity 110~300, Trk pT 0~3{{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 29, 32, 35, 56, 77, 98, 120};
//}}}
*/
/*
//v17: new pt range, multiplicity 110~300, Trk pT 0~3, new mass bin{{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 77, 98, 120};
//}}}
*/
/*
//v18: new pt range, multiplicity 0~40, Trk pT 0~3, new mass bin{{{
Int_t multBinsArr[] = {0, 40};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 77, 98, 120};
//}}}
*/
/*
//v19: similar to v17 more mass bin in the high mass range{{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v20: similar to v18 more mass bin in the high mass range{{{
Int_t multBinsArr[] = {0, 40};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v21: new pt range, multiplicity 40~90, Trk pT 0~3, new mass bin{{{
Int_t multBinsArr[] = {40, 90};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v22: new pt range, multiplicity 90~110, Trk pT 0~3, new mass bin{{{
Int_t multBinsArr[] = {90, 110};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v24: Integrated. multiplicity 110~300{{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 30.0};
Int_t massBinsArr[] = {0, 120};
//}}}
*/
/*
//v25: side band test for v19{{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 10, 20, 90, 95, 100, 110, 120};
//}}}
*/
/*
//v26: test for new mass range at multiplicity 0~40{{{
Int_t multBinsArr[] = {0, 40};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 14, 20, 25, 30, 33, 42, 48, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v27: multiplciity 0~45 Trk pT 0~3{{{
Int_t multBinsArr[] = {0, 45};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0};
Int_t massBinsArr[] = {0, 9, 14, 20, 25, 30, 33, 42, 48, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v28: multiplciity 0~50 Trk pT 0~3{{{
Int_t multBinsArr[] = {0, 50};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 9, 14, 20, 25, 30, 33, 42, 48, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v29: multiplciity 0~55 Trk pT 0~3{{{
Int_t multBinsArr[] = {0, 55};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0};
Int_t massBinsArr[] = {0, 9, 14, 20, 25, 30, 33, 42, 48, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v30: multiplciity 0~60 Trk pT 0~3{{{
Int_t multBinsArr[] = {0, 60};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0};
Int_t massBinsArr[] = {0, 9, 14, 20, 25, 30, 33, 42, 48, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v31: multiplciity 0~40 Trk pT 0~3{{{
Int_t multBinsArr[] = {0, 40};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 9, 14, 20, 25, 30, 33, 42, 48, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v32: 110, 300 track pt 0.3 {{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v33: 110, 300 track pt 0.4 {{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v34: 110, 300 track pt 0.5 {{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v35: 120, 300 track pt 0.3 {{{
Int_t multBinsArr[] = {120, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v36: 100, 300 track pt 0.3 {{{
Int_t multBinsArr[] = {100, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v37: 90, 300 track pt 0.3 {{{
Int_t multBinsArr[] = {90, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v38: pt binnig for jet ratio 110~300 {{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 15.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v39: pt binnig for jet ratio 0~50 {{{
Int_t multBinsArr[] = {0, 50};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 15.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v40: pt binnig for jet ratio 110~300 with extended mass range{{{
Int_t multBinsArr[] = {110, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {9.0, 10.0, 12.0, 15.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v41: pt binnig for jet ratio 0~50 with extended mass range{{{
Int_t multBinsArr[] = {0, 50};
Double_t rapBinsArr[] = {-2.4, 2.4};
//Double_t ptBinsArr[] = {9.0, 10.0, 12.0, 15.0, 30.0};
Double_t ptBinsArr[] = {9.0, 12.0, 15.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v42: 0, 50 Trk pT 0.3{{{
Int_t multBinsArr[] = {0, 50};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 9, 14, 20, 25, 30, 33, 42, 48, 56, 64, 77, 89, 104, 120};
//}}}
*/
/*
//v43: 0, 40 Trk pT 0.3{{{
Int_t multBinsArr[] = {0, 40};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 9, 14, 20, 25, 30, 33, 42, 48, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v44: pt binnig for jet ratio 0~40 {{{
Int_t multBinsArr[] = {0, 40};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 15.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v45: pt binnig for jet ratio 0~40 with extended mass range{{{
Int_t multBinsArr[] = {0, 40};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 12.0, 15.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v46: pt binnig for jet ratio 90~300{{{
Int_t multBinsArr[] = {90, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {10.0, 12.0, 15.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v47: pt binnig for jet ratio 90~300 with extended mass range{{{
Int_t multBinsArr[] = {90, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
//Double_t ptBinsArr[] = {9.0, 10.0, 12.0, 15.0, 30.0};
Double_t ptBinsArr[] = {9.0, 12.0, 15.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v48: 90, 300 track pt 0.3, wide mass bin for S/B ratio plot{{{
Int_t multBinsArr[] = {90, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {20, 41};
//}}}
*/
/*
//v49: low-multiplicity scan for 9~10 mass range, track pt 0.3{{{
Int_t multBinsArr[] = {0, 10, 20, 30, 40, 50, 60, 70};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {20, 41};
//}}}
*/
/*
//v50: additional multiplicity for low-multiplicity scan for 9~10 mass range, track pt 0.3{{{
Int_t multBinsArr[] = {45, 55};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {20, 41};
//}}}
*/
/*
//v51: 0, 50 Trk pT 0.3, 13 mass bin{{{
Int_t multBinsArr[] = {0, 50};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 4.0, 7.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 8, 14, 20, 25, 30, 33, 42, 48, 65, 77, 89, 104, 120};
//}}}
*/
/*
//v52: 90, 300 Trk pT 10{{{
Int_t multBinsArr[] = {90, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {9.0, 10.0, 12.0, 15.0};
Int_t massBinsArr[] = {0, 8, 14, 20, 25, 30, 33, 42, 48, 65, 77, 89, 104, 120};
//}}}
*/
/*
//v53: 0, 50 Trk pT 10{{{
Int_t multBinsArr[] = {0, 50};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {9.0, 10.0, 12.0, 15.0};
Int_t massBinsArr[] = {0, 8, 14, 20, 25, 30, 33, 42, 48, 65, 77, 89, 104, 120};
//}}}
*/
/*
//v54: 90, 300 track pt 0.3, new Upsilon pT bin{{{
Int_t multBinsArr[] = {90, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 3.0, 6.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v55: 0, 50 Trk pT 0.3, new Upsilon pT bin{{{
Int_t multBinsArr[] = {0, 50};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 3.0, 6.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 9, 14, 20, 25, 30, 33, 42, 48, 56, 64, 77, 89, 104, 120};
//}}}
*/
/*
//v56: same with v54, new mass bin{{{
Int_t multBinsArr[] = {90, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 3.0, 6.0, 10.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 29, 30, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/

//v57: pt bin for MC reweight{{{
Int_t multBinsArr[] = {0, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 15.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 29, 30, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}

/*
//v58: pt binnig for jet ratio 185~250 (J/psi study multiplicity) with extended mass range{{{
Int_t multBinsArr[] = {185, 250};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {10.0, 12.0, 15.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v59: new pt binnig for jet ratio 90~300{{{
Int_t multBinsArr[] = {90, 300};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {12.0, 15.0, 20.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
/*
//v60: new pt binnig for jet ratio 0~50{{{
Int_t multBinsArr[] = {0, 50};
Double_t rapBinsArr[] = {-2.4, 2.4};
Double_t ptBinsArr[] = {12.0, 15.0, 20.0, 30.0};
Int_t massBinsArr[] = {0, 7, 15, 23, 26, 27, 28, 29, 32, 35, 38, 41, 44, 46, 50, 56, 66, 77, 89, 104, 120};
//}}}
*/
//}}}

const Int_t rap_narr = sizeof(rapBinsArr)/sizeof(double);
const Int_t pt_narr = sizeof(ptBinsArr)/sizeof(double);
const Int_t mult_narr = sizeof(multBinsArr)/sizeof(int);
const Int_t mass_narr = sizeof(massBinsArr)/sizeof(int);

const Double_t U1S_mass = 9.460;
const Double_t U2S_mass = 10.023;
const Double_t U3S_mass = 10.355;
const Double_t U1S_sigma = 0.00026;
const Double_t U2S_sigma = 0.00031;
const Double_t U3S_sigma = 0.0005;
const Int_t Netabin1 = 32;
const Int_t Netabin2 = 16;
const Int_t Nphibin1 = 32;
const Int_t Nphibin2 = 16;

class DiMuon
{
//{{{
	public:

	UInt_t eventNb, LS;
	Float_t zVtx;
	Double_t mass, y, pt, phi, dphi, deta;
	Double_t mupl_eta, mupl_pt, mupl_phi;
	Double_t mumi_eta, mumi_pt, mumi_phi;
	Double_t trk_eta, trk_pt, trk_phi;
	Double_t weight;
	Int_t mult;
	Int_t Ntrg_Reco, Nass_Reco;
	Int_t Ntrg_Gen, Nass_Gen;
	TClonesArray* Vec_trg_Reco;
	TClonesArray* Vec_ass_Reco;
	TClonesArray* Vec_trg_Gen;
	TClonesArray* Vec_ass_Gen;

	void clear()
	{
		eventNb = -99; LS = -99; zVtx = -99; dphi = -99, deta = -99;
		mass = -99; y = -99; pt = -99; phi = -99;
		mupl_eta = -99; mupl_pt = -99; mupl_phi = -99;
		mumi_eta = -99; mumi_pt = -99; mumi_phi = -99;
		trk_eta = -99; trk_pt = -99; trk_phi = -99;
		weight = -99; mult = -99;
		Ntrg_Reco = -99; Nass_Reco = -99;
		Ntrg_Gen = -99; Nass_Gen = -99;
		Vec_trg_Reco->Clear();
		Vec_ass_Reco->Clear();
		Vec_trg_Gen->Clear();
		Vec_ass_Gen->Clear();
	}

	void BuildBranch(TTree* tout)
	{
		tout->Branch("eventNb", &eventNb);
		tout->Branch("LS", &LS);
		tout->Branch("zVtx", &zVtx);
		tout->Branch("dphi", &dphi);
		tout->Branch("deta", &deta);
		tout->Branch("mass", &mass);
		tout->Branch("y", &y);
		tout->Branch("pt", &pt);
		tout->Branch("phi", &phi);
		tout->Branch("mupl_eta", &mupl_eta);
		tout->Branch("mupl_pt", &mupl_pt);
		tout->Branch("mupl_phi", &mupl_phi);
		tout->Branch("mumi_eta", &mumi_eta);
		tout->Branch("mumi_pt", &mumi_pt);
		tout->Branch("mumi_phi", &mumi_phi);
		tout->Branch("trk_eta", &trk_eta);
		tout->Branch("trk_pt", &trk_pt);
		tout->Branch("trk_phi", &trk_phi);
		tout->Branch("weight", &weight);
		tout->Branch("mult", &mult);
		tout->Branch("Ntrg_Reco", &Ntrg_Reco);
		tout->Branch("Nass_Reco", &Nass_Reco);
		tout->Branch("Ntrg_Gen", &Ntrg_Gen);
		tout->Branch("Nass_Gen", &Nass_Gen);
		Vec_trg_Reco = new TClonesArray("TLorentzVector", 250);
		Vec_ass_Reco = new TClonesArray("TLorentzVector", 1500);
		Vec_trg_Gen = new TClonesArray("TLorentzVector", 250);
		Vec_ass_Gen = new TClonesArray("TLorentzVector", 1500);
		tout->Branch("Vec_trg_Reco", "TClonesArray", &Vec_trg_Reco, 32000, 0);
		tout->Branch("Vec_ass_Reco", "TClonesArray", &Vec_ass_Reco, 32000, 0);
		tout->Branch("Vec_trg_Gen", "TClonesArray", &Vec_trg_Gen, 32000, 0);
		tout->Branch("Vec_ass_Gen", "TClonesArray", &Vec_ass_Gen, 32000, 0);
	}
//}}}
};
