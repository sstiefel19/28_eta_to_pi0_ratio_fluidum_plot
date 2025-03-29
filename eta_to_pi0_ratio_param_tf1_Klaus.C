#include "/Users/stephanstiefelmaier/analysisSoftware/utils_sstiefel_2024/myStyle.h"
//
// This macro contains the eta/pi0 parameterizations for Pb-Pb collisions at 5.02 TeV 
// for the 2015 analysis (0-20%, 20-40%, 40-60%, and 60-80%) and the 2018 analysis (0-10% and 30-50%).
// 
// The macro contains
// - the eta/pi0 parameterizations (TF1)
// - the eta/pi0 parameterization error bands (TGraphErrors)
// - the predicted eta/pi0 values (from data+FluiduM) used to obtain the eta/pi0 parameterizations
//
// Klaus Reygers
//

void eta_to_pi0_ratio_param_tf1_Klaus() {
    
    const double m_pi0 = 0.135; // in GeV
    const double m_eta = 0.547862; // in GeV

    //
    // parameterization of the eta/pi0 ratio
    //
    TString sBW_eta_over_pi0 = Form("exp((- sqrt(x*x+%f*%f) + sqrt(x*x+%f*%f)) / sqrt(1-[1]*[1])/[2])", m_eta, m_eta, m_pi0, m_pi0);
    TString si = "(0.5 * (1. + ROOT::Math::erf((x - [3])/[4])))";
    TString ratio = "(1. - " + si + ") * [0] * " + sBW_eta_over_pi0 + " + " + si + " * [5]";

    // Parameters for the eta/pi0 ratio in Pb-Pb collisions at 5.02 TeV for 
    // the four centrality classes 0-20%, 20-40%, 40-60%, and 60-80%.
    // for 0-10%, 30-50%: using 0010_CutStudiesOverview_2024-11-29.root, 3050_CutStudiesOverview_2024-11-29.root
    double pars_00_20[6] = {0.977721, 0.618195, 0.117933, 3.37214, 0.500039, 0.487};
    double pars_20_40[6] = {0.920456, 0.595247, 0.121594, 3.24199, 0.855145, 0.487};
    double pars_40_60[6] = {0.844084, 0.601972, 0.130577, 3.17672, 1.49528, 0.487};
    double pars_60_80[6] = {0.763115, 0.616487, 0.145168, 3.0322, 0.500007, 0.487};
    double pars_00_10[6] = {0.97796, 0.618552, 0.117521, 3.32354, 0.500002, 0.487};
    double pars_30_50[6] = {0.885422, 0.617961, 0.128659, 3.32688, 0.72903, 0.487};
    double pars_pp[6] = {0.4828412883910595, 0., 0.09905518928551621, 3.5412800248011624, 2.6541672047505935, 0.487};

    auto f_eta_to_pi0_00_20 = new TF1("f_eta_to_pi0_00_20", ratio, 0., 200.);
    f_eta_to_pi0_00_20->SetParameters(pars_00_20);

    auto f_eta_to_pi0_20_40 = new TF1("f_eta_to_pi0_20_40", ratio, 0., 200.);
    f_eta_to_pi0_20_40->SetParameters(pars_20_40);

    auto f_eta_to_pi0_40_60 = new TF1("f_eta_to_pi0_40_60", ratio, 0., 200.);
    f_eta_to_pi0_40_60->SetParameters(pars_40_60);

    auto f_eta_to_pi0_60_80 = new TF1("f_eta_to_pi0_60_80", ratio, 0., 200.);
    f_eta_to_pi0_60_80->SetParameters(pars_60_80);

    auto f_eta_to_pi0_00_10 = new TF1("f_eta_to_pi0_00_10", ratio, 0., 200.);
    f_eta_to_pi0_00_10->SetParameters(pars_00_10);

    auto f_eta_to_pi0_30_50 = new TF1("f_eta_to_pi0_30_50", ratio, 0., 200.);
    f_eta_to_pi0_30_50->SetParameters(pars_30_50);

    auto f_eta_to_pi0_pp = new TF1("f_eta_to_pi0_pp", ratio, 0., 200.);
    f_eta_to_pi0_pp->SetParameters(pars_pp);

    //
    // parameterization of the eta/pi0 ratio absolute uncertainty
    //
    TString sG1 = "([0]+[1]/(sqrt(2.*TMath::Pi())*[2])*exp(-0.5*(x/[2])**2))";
    TString sG2 = "(0.05+[3]/(sqrt(2.*TMath::Pi())*[5])*exp(-0.5*((x-[4])/[5])**2))";
    TString si2 = "0.5 * (1. + ROOT::Math::erf(x - 3.))";
    TString ratio_err = "(1. - " + si2 + ") * " + sG1 + " + " + si2 + " * " + sG2; 

    // for 0-10%, 30-50%: using 0010_CutStudiesOverview_2024-11-29.root, 3050_CutStudiesOverview_2024-11-29.root
    double pars_errfun_00_20[6] = {0.0342168, 0.114004, 0.416835, 6.49309, 0.00168754, 1.08525};
    double pars_errfun_20_40[6] = {0.0379397, 0.0942153, 0.413325, 4.43503, 0.00244873, 1.14762};
    double pars_errfun_40_60[6] = {0.0384199, 0.0884536, 0.42096, 4.15613, 0.00306472, 1.14425};
    double pars_errfun_60_80[6] = {0.0356787, 0.107729, 0.440188, 4.6321, 0.00273897, 1.12341};
    double pars_errfun_00_10[6] = {0.0332156, 0.119844, 0.41766, 7.01387, 0.00161107, 1.08365};
    double pars_errfun_30_50[6] = {0.0381912, 0.0907566, 0.420325, 4.25488, 0.00278988, 1.15198};


    auto f_eta_to_pi0_err_00_20 = new TF1("f_eta_to_pi0_err_00_20", ratio_err, 0., 200.);
    f_eta_to_pi0_err_00_20->SetParameters(pars_errfun_00_20);

    auto f_eta_to_pi0_err_20_40 = new TF1("f_eta_to_pi0_err_20_40", ratio_err, 0., 200.);
    f_eta_to_pi0_err_20_40->SetParameters(pars_errfun_20_40);

    auto f_eta_to_pi0_err_40_60 = new TF1("f_eta_to_pi0_err_40_60", ratio_err, 0., 200.);
    f_eta_to_pi0_err_40_60->SetParameters(pars_errfun_40_60);

    auto f_eta_to_pi0_err_60_80 = new TF1("f_eta_to_pi0_err_60_80", ratio_err, 0., 200.);
    f_eta_to_pi0_err_60_80->SetParameters(pars_errfun_60_80);

    auto f_eta_to_pi0_err_00_10 = new TF1("f_eta_to_pi0_err_00_10", ratio_err, 0., 200.);
    f_eta_to_pi0_err_00_10->SetParameters(pars_errfun_00_10);

    auto f_eta_to_pi0_err_30_50 = new TF1("f_eta_to_pi0_err_30_50", ratio_err, 0., 200.);
    f_eta_to_pi0_err_30_50->SetParameters(pars_errfun_30_50);

    // create TGraphErrors representing the error band around the eta/pi0 parameterizations
    const int n_points = 1000;
    double pt[n_points];
    double eta_to_pi0_00_20[n_points], eta_to_pi0_err_00_20[n_points];
    double eta_to_pi0_20_40[n_points], eta_to_pi0_err_20_40[n_points];
    double eta_to_pi0_40_60[n_points], eta_to_pi0_err_40_60[n_points];
    double eta_to_pi0_60_80[n_points], eta_to_pi0_err_60_80[n_points];
    double eta_to_pi0_00_10[n_points], eta_to_pi0_err_00_10[n_points];
    double eta_to_pi0_30_50[n_points], eta_to_pi0_err_30_50[n_points];

    double pt_min = f_eta_to_pi0_00_20->GetXmin();
    double pt_max = f_eta_to_pi0_00_20->GetXmax();
    double step = (pt_max - pt_min) / (n_points - 1);

    for (int i = 0; i < n_points; ++i) {

        pt[i] = pt_min + i * step;
        
        eta_to_pi0_00_20[i] = f_eta_to_pi0_00_20->Eval(pt[i]);
        eta_to_pi0_20_40[i] = f_eta_to_pi0_20_40->Eval(pt[i]);
        eta_to_pi0_40_60[i] = f_eta_to_pi0_40_60->Eval(pt[i]);
        eta_to_pi0_60_80[i] = f_eta_to_pi0_60_80->Eval(pt[i]);
        eta_to_pi0_00_10[i] = f_eta_to_pi0_00_10->Eval(pt[i]);
        eta_to_pi0_30_50[i] = f_eta_to_pi0_30_50->Eval(pt[i]);

        eta_to_pi0_err_00_20[i] = eta_to_pi0_00_20[i] * f_eta_to_pi0_err_00_20->Eval(pt[i]);
        eta_to_pi0_err_20_40[i] = eta_to_pi0_20_40[i] * f_eta_to_pi0_err_20_40->Eval(pt[i]);
        eta_to_pi0_err_40_60[i] = eta_to_pi0_40_60[i] * f_eta_to_pi0_err_40_60->Eval(pt[i]);
        eta_to_pi0_err_60_80[i] = eta_to_pi0_60_80[i] * f_eta_to_pi0_err_60_80->Eval(pt[i]);
        eta_to_pi0_err_00_10[i] = eta_to_pi0_00_10[i] * f_eta_to_pi0_err_00_10->Eval(pt[i]);
        eta_to_pi0_err_30_50[i] = eta_to_pi0_30_50[i] * f_eta_to_pi0_err_30_50->Eval(pt[i]);

    }

    // Create a TGraphErrors for the error band
    auto g_eta_to_pi0_error_band_00_20 = new TGraphErrors(n_points, pt, eta_to_pi0_00_20, nullptr, eta_to_pi0_err_00_20);
    auto g_eta_to_pi0_error_band_20_40 = new TGraphErrors(n_points, pt, eta_to_pi0_20_40, nullptr, eta_to_pi0_err_20_40);
    auto g_eta_to_pi0_error_band_40_60 = new TGraphErrors(n_points, pt, eta_to_pi0_40_60, nullptr, eta_to_pi0_err_40_60);
    auto g_eta_to_pi0_error_band_60_80 = new TGraphErrors(n_points, pt, eta_to_pi0_60_80, nullptr, eta_to_pi0_err_60_80);
    auto g_eta_to_pi0_error_band_00_10 = new TGraphErrors(n_points, pt, eta_to_pi0_00_10, nullptr, eta_to_pi0_err_00_10);
    auto g_eta_to_pi0_error_band_30_50 = new TGraphErrors(n_points, pt, eta_to_pi0_30_50, nullptr, eta_to_pi0_err_30_50);

    g_eta_to_pi0_error_band_00_20->SetFillColorAlpha(kRed, 0.3);  // Semi-transparent red error band
    g_eta_to_pi0_error_band_20_40->SetFillColorAlpha(kOrange, 0.3);  // Semi-transparent orange error band
    g_eta_to_pi0_error_band_40_60->SetFillColorAlpha(kBlue, 0.3);  // Semi-transparent blue error band
    g_eta_to_pi0_error_band_60_80->SetFillColorAlpha(kBlack, 0.3);  // Semi-transparent black error band
    g_eta_to_pi0_error_band_00_10->SetFillColorAlpha(kAzure, 0.3);  // Semi-transparent azure error band
    g_eta_to_pi0_error_band_30_50->SetFillColorAlpha(kCyan, 0.3);  // Semi-transparent cyan error band

    g_eta_to_pi0_error_band_00_20->SetLineWidth(0);
    g_eta_to_pi0_error_band_20_40->SetLineWidth(0);
    g_eta_to_pi0_error_band_40_60->SetLineWidth(0);
    g_eta_to_pi0_error_band_60_80->SetLineWidth(0);
    g_eta_to_pi0_error_band_00_10->SetLineWidth(0);
    g_eta_to_pi0_error_band_30_50->SetLineWidth(0);
    
    //
    // Here we provide the eta/pi0 values as predicted with the help of FluiduM (+ data)
    // and which are used to obtain the eta/pi0 parameterizations
    //

    // Centrality class 0-20%:
    double eta_to_pi0_predicted_00_20[] = {0.0311997, 0.0392724, 0.0442586, 0.0535506, 0.0642473, 0.0784368, 0.0939543, 0.107721, 0.123157, 0.135399, 0.148764, 0.165187, 0.182871, 0.199335, 0.212247, 0.227712, 0.249586, 0.287404, 0.300101, 0.325733, 0.351506, 0.377361, 0.403812, 0.425581, 0.442681, 0.459794, 0.501249, 0.525111, 0.552412, 0.563631, 0.574083, 0.572864};

    double eta_to_pi0_predicted_err_00_20[] = {0.00093599, 0.00117817, 0.00132776, 0.00160652, 0.00192742, 0.0023531, 0.00281863, 0.00323164, 0.00369472, 0.00406196, 0.00446292, 0.0049556, 0.00548613, 0.00598004, 0.00636742, 0.00683136, 0.00748759, 0.00862213, 0.00900303, 0.00977198, 0.0105452, 0.0113208, 0.0121144, 0.0127674, 0.0132804, 0.0137938, 0.0150375, 0.0157533, 0.0165724, 0.0169089, 0.0172225, 0.0171859};

    // Centrality class 20-40%:
    double eta_to_pi0_predicted_20_40[] = {0.0324406, 0.0412224, 0.0484699, 0.0584987, 0.0706159, 0.085446, 0.0995194, 0.113975, 0.128991, 0.14842, 0.158626, 0.177029, 0.192111, 0.20787, 0.223047, 0.237661, 0.256101, 0.294495, 0.30422, 0.326479, 0.345997, 0.372355, 0.389262, 0.408629, 0.42412, 0.43939, 0.477048, 0.495588, 0.518112, 0.52877, 0.539397, 0.539777};

    double eta_to_pi0_predicted_err_20_40[] = {0.000973219, 0.00123667, 0.0014541, 0.00175496, 0.00211848, 0.00256338, 0.00298558, 0.00341925, 0.00386973, 0.0044526, 0.00475878, 0.00531087, 0.00576333, 0.00623611, 0.0066914, 0.00712983, 0.00768302, 0.00883485, 0.00912661, 0.00979438, 0.0103799, 0.0111706, 0.0116779, 0.0122589, 0.0127236, 0.0131817, 0.0143114, 0.0148676, 0.0155434, 0.0158631, 0.0161819, 0.0161933};

    // Centrality class 40-60%:
    double eta_to_pi0_predicted_40_60[] = {0.0350825, 0.0452672, 0.0541552, 0.0650085, 0.0799015, 0.0961683, 0.110709, 0.126038, 0.140318, 0.158936, 0.1715, 0.187442, 0.204715, 0.218907, 0.232458, 0.24584, 0.266814, 0.301666, 0.306019, 0.323133, 0.342065, 0.360455, 0.375451, 0.390362, 0.402741, 0.421389, 0.455315, 0.472617, 0.480878, 0.500294, 0.507239, 0.524155};

    double eta_to_pi0_predicted_err_40_60[] = {0.00105248, 0.00135802, 0.00162465, 0.00195026, 0.00239704, 0.00288505, 0.00332126, 0.00378115, 0.00420954, 0.00476807, 0.00514501, 0.00562326, 0.00614146, 0.00656722, 0.00697374, 0.00737521, 0.00800442, 0.00904997, 0.00918058, 0.00969399, 0.0102619, 0.0108137, 0.0112635, 0.0117109, 0.0120822, 0.0126417, 0.0136594, 0.0141785, 0.0144263, 0.0150088, 0.0152172, 0.0157246};

    // Centrality class 60-80%:
    double eta_to_pi0_predicted_60_80[] = {0.038251, 0.0484757, 0.0605527, 0.0727566, 0.0884783, 0.106464, 0.12374, 0.137742, 0.153617, 0.168105, 0.180818, 0.190388, 0.211287, 0.2213, 0.231751, 0.248145, 0.265347, 0.292987, 0.294187, 0.303283, 0.323027, 0.338594, 0.353076, 0.379286, 0.381492, 0.399614, 0.42417, 0.438952, 0.453572, 0.468267, 0.495844, 0.490778};

    double eta_to_pi0_predicted_err_60_80[] = {0.00114753, 0.00145427, 0.00181658, 0.0021827, 0.00265435, 0.00319393, 0.00371219, 0.00413227, 0.00460852, 0.00504316, 0.00542453, 0.00571164, 0.00633861, 0.00663901, 0.00695252, 0.00744435, 0.0079604, 0.00878961, 0.00882561, 0.0090985, 0.00969082, 0.0101578, 0.0105923, 0.0113786, 0.0114448, 0.0119884, 0.0127251, 0.0131686, 0.0136072, 0.014048, 0.0148753, 0.0147233};

    // Centrality class 0-10%:
    double eta_to_pi0_predicted_00_10[] = {0.0311589, 0.0390224, 0.0437121, 0.052979, 0.0636666, 0.0775345, 0.0935798, 0.107122, 0.122246, 0.133816, 0.147024, 0.163819, 0.180947, 0.197675, 0.210872, 0.225855, 0.247648, 0.285569, 0.298764, 0.324883, 0.350681, 0.377175, 0.405201, 0.427988, 0.444572, 0.46235, 0.503232, 0.525035, 0.555853, 0.565237, 0.575989, 0.576023};

    double eta_to_pi0_predicted_err_00_10[] = {0.000934767, 0.00117067, 0.00131136, 0.00158937, 0.00191, 0.00232604, 0.0028074, 0.00321366, 0.00366739, 0.00401449, 0.00441071, 0.00491457, 0.0054284, 0.00593025, 0.00632615, 0.00677564, 0.00742943, 0.00856707, 0.00896291, 0.00974649, 0.0105204, 0.0113153, 0.012156, 0.0128396, 0.0133371, 0.0138705, 0.015097, 0.0157511, 0.0166756, 0.0169571, 0.0172797, 0.0172807};

    // Centrality class 30-50%:
    double eta_to_pi0_predicted_30_50[] = {0.0335726, 0.0430717, 0.0511784, 0.0612022, 0.0749101, 0.0903309, 0.105175, 0.119151, 0.134301, 0.156077, 0.164467, 0.185048, 0.198361, 0.213454, 0.227185, 0.241568, 0.261196, 0.29824, 0.303277, 0.325532, 0.34424, 0.368596, 0.38289, 0.397119, 0.416903, 0.431606, 0.470308, 0.488085, 0.511558, 0.526727, 0.531099, 0.547259};

    double eta_to_pi0_predicted_err_30_50[] = {0.00100718, 0.00129215, 0.00153535, 0.00183606, 0.0022473, 0.00270993, 0.00315524, 0.00357452, 0.00402902, 0.0046823, 0.00493402, 0.00555144, 0.00595083, 0.00640363, 0.00681554, 0.00724703, 0.00783589, 0.00894721, 0.00909831, 0.00976595, 0.0103272, 0.0110579, 0.0114867, 0.0119136, 0.0125071, 0.0129482, 0.0141092, 0.0146426, 0.0153467, 0.0158018, 0.015933, 0.0164178};

    double pt_predicted[] = {0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775, 0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3, 2.5, 2.7, 2.9, 3.1};

    int n_points_predicted = sizeof(pt_predicted) / sizeof(pt_predicted[0]);

    // graphs with predicted eta/pi0 value ()data
    auto g_eta_to_pi0_predicted_00_20 = new TGraphErrors(n_points_predicted, pt_predicted, eta_to_pi0_predicted_00_20, nullptr, eta_to_pi0_predicted_err_00_20);
    auto g_eta_to_pi0_predicted_20_40 = new TGraphErrors(n_points_predicted, pt_predicted, eta_to_pi0_predicted_20_40, nullptr, eta_to_pi0_predicted_err_20_40);
    auto g_eta_to_pi0_predicted_40_60 = new TGraphErrors(n_points_predicted, pt_predicted, eta_to_pi0_predicted_40_60, nullptr, eta_to_pi0_predicted_err_40_60);
    auto g_eta_to_pi0_predicted_60_80 = new TGraphErrors(n_points_predicted, pt_predicted, eta_to_pi0_predicted_60_80, nullptr, eta_to_pi0_predicted_err_60_80);
    auto g_eta_to_pi0_predicted_00_10 = new TGraphErrors(n_points_predicted, pt_predicted, eta_to_pi0_predicted_00_10, nullptr, eta_to_pi0_predicted_err_00_10);
    auto g_eta_to_pi0_predicted_30_50 = new TGraphErrors(n_points_predicted, pt_predicted, eta_to_pi0_predicted_30_50, nullptr, eta_to_pi0_predicted_err_30_50);


    //
    // first plot: all parameterizations with error bands 
    //

    gStyle->SetOptStat(kFALSE);

    // draw all parameterizations
    TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);

    TH2F* fr = new TH2F("fr", "eta/pi0 ratio, Pb-Pb, 5.02 TeV", 1, 0., 8., 1, 0., 0.7);
    fr->SetXTitle("pT (GeV/c)");
    fr->SetYTitle("ratio (GeV/c)");
    fr->Draw();

    auto legend = new TLegend(0.6,0.2,0.8,0.4);

    f_eta_to_pi0_00_20->SetLineColor(kRed);
    f_eta_to_pi0_00_20->SetNpx(10000);
    g_eta_to_pi0_error_band_00_20->Draw("3");
    f_eta_to_pi0_00_20->DrawCopy("same");
    
    legend->AddEntry(f_eta_to_pi0_00_20, "0-20%", "l");

    f_eta_to_pi0_20_40->SetLineColor(kOrange);
    f_eta_to_pi0_20_40->SetNpx(10000);
    g_eta_to_pi0_error_band_20_40->Draw("3");
    f_eta_to_pi0_20_40->DrawCopy("same");
    legend->AddEntry(f_eta_to_pi0_20_40, "20-40%", "l");

    f_eta_to_pi0_40_60->SetLineColor(kBlue);
    f_eta_to_pi0_40_60->SetNpx(10000);
    g_eta_to_pi0_error_band_40_60->Draw("3");
    f_eta_to_pi0_40_60->DrawCopy("same");
    legend->AddEntry(f_eta_to_pi0_40_60, "40-60%", "l");

    f_eta_to_pi0_60_80->SetLineColor(kBlack);
    f_eta_to_pi0_60_80->SetNpx(10000);
    g_eta_to_pi0_error_band_60_80->Draw("3");
    f_eta_to_pi0_60_80->DrawCopy("same");
    legend->AddEntry(f_eta_to_pi0_60_80, "60-80%", "l");

    f_eta_to_pi0_00_10->SetLineColor(kAzure);
    f_eta_to_pi0_00_10->SetNpx(10000);
    g_eta_to_pi0_error_band_00_10->Draw("3");
    f_eta_to_pi0_00_10->DrawCopy("same");
    legend->AddEntry(f_eta_to_pi0_00_10, "0-10%", "l");
    
    f_eta_to_pi0_30_50->SetLineColor(kCyan);
    f_eta_to_pi0_30_50->SetNpx(10000);
    g_eta_to_pi0_error_band_30_50->Draw("3");
    f_eta_to_pi0_30_50->DrawCopy("same");
    legend->AddEntry(f_eta_to_pi0_30_50, "30-50%", "l");

    f_eta_to_pi0_pp->SetLineColor(kBlack);
    f_eta_to_pi0_pp->SetNpx(10000);
    f_eta_to_pi0_pp->SetLineStyle(3);
    f_eta_to_pi0_pp->DrawCopy("same");
    legend->AddEntry(f_eta_to_pi0_pp, "pp", "l");

    legend->Draw();

    //
    // second plot: parameterizations for one centrality class with the predicted values
    // 

    float lLegendTextSize = 0.05;
    auto plotSingleCentralityClass = [&](std::string theCent){
        bool isCentral = theCent[0]=='0';

        TF1 &f_eta_to_pi0 = isCentral 
            ? *f_eta_to_pi0_00_10 
            : *f_eta_to_pi0_30_50;
        f_eta_to_pi0.SetNpx(1000);
        
        TGraphErrors &g_eta_to_pi0 = isCentral 
            ? *g_eta_to_pi0_predicted_00_10 
            : *g_eta_to_pi0_predicted_30_50;
        
        TGraphErrors &g_eta_to_pi0_error_band = isCentral 
            ? *g_eta_to_pi0_error_band_00_10 
            : *g_eta_to_pi0_error_band_30_50;

        std::string lName(Form("c_%s", theCent.data()));
        TCanvas* c2 = new TCanvas(lName.data(), lName.data(), 800, 600);
        TH2F* fr2 = new TH2F(Form("fr_%s", theCent.data()), 
                             Form("eta/pi0 ratio (%s), Pb-Pb, 5.02 TeV;p_#text{T} (GeV/c);#eta / #pi^{0}", 
                                  theCent.data()), 
                             1, 0., 8., 1, 0., 0.7);
        fr2->Draw();
        auto leg = utils_plotting::GetLegend(0.5, 0.2, 0.90, 0.4, true /*theDrawAlready*/); // this already removes the boarder

        // error band, dont add to Lege
        utils_plotting::DrawAndAdd(g_eta_to_pi0_error_band,"same3", kAzure, 1.0,
                                   leg, "Ratio param. uncertainty", "lep", lLegendTextSize, true /*theDrawLegAlready*/, 
                                   3 /*theMarkerStyle*/, 1.0 /*theMarkerSize*/);

        utils_plotting::DrawAndAdd(f_eta_to_pi0,"same", kAzure, 1.0, 
                                   leg, theCent.data(), "l", lLegendTextSize, true /*theDrawLegAlready*/, 
                                   3 /*theMarkerStyle*/, 1.0 /*theMarkerSize*/);

        utils_plotting::DrawAndAdd(g_eta_to_pi0,"sameP", kAzure, 1.0, 
                                   leg, Form("%s (predicted, data+FluiduM)", theCent.data()), "p", lLegendTextSize, true /*theDrawLegAlready*/, 
                                   20 /*theMarkerStyle*/, 1.0 /*theMarkerSize*/);
    };

    plotSingleCentralityClass("0-10%");
    plotSingleCentralityClass("30-50%");

    //
    // save parameterizations to file
    //

    TFile *f = new TFile("eta_to_pi0_ratio_param_tf1_PbPb_5020TeV_2024_12_18.root", "recreate");
    f_eta_to_pi0_00_20->Write();
    f_eta_to_pi0_20_40->Write();
    f_eta_to_pi0_40_60->Write();
    f_eta_to_pi0_60_80->Write();
    f_eta_to_pi0_00_10->Write();
    f_eta_to_pi0_30_50->Write();
    f_eta_to_pi0_pp->Write();

    f_eta_to_pi0_err_00_20->Write();
    f_eta_to_pi0_err_20_40->Write();
    f_eta_to_pi0_err_40_60->Write();
    f_eta_to_pi0_err_60_80->Write();
    f_eta_to_pi0_err_00_10->Write();
    f_eta_to_pi0_err_30_50->Write();

    g_eta_to_pi0_error_band_00_20->Write();
    g_eta_to_pi0_error_band_20_40->Write();
    g_eta_to_pi0_error_band_40_60->Write();
    g_eta_to_pi0_error_band_60_80->Write();
    g_eta_to_pi0_error_band_00_10->Write();
    g_eta_to_pi0_error_band_30_50->Write();

    g_eta_to_pi0_predicted_00_20->Write();
    g_eta_to_pi0_predicted_20_40->Write();
    g_eta_to_pi0_predicted_40_60->Write();
    g_eta_to_pi0_predicted_60_80->Write();
    g_eta_to_pi0_predicted_00_10->Write();
    g_eta_to_pi0_predicted_30_50->Write();

    f->Close();
  

}
