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

void eta_to_pi0_ratio_param_tf1() {
    
    const double m_pi0 = 0.135; // in GeV
    const double m_eta = 0.547862; // in GeV

    //
    // parameterization of the eta/pi0 ratio
    //
    TString sBW_eta_over_pi0 = Form("exp((- sqrt(x*x+%f*%f) + sqrt(x*x+%f*%f)) / sqrt(1-[1]*[1])/[2])", m_eta, m_eta, m_pi0, m_pi0);
    TString si = "(0.5 * (1. + ROOT::Math::erf((x - [3])/[4])))";
    TString ratio = "(1. - " + si + ") * [0] * " + sBW_eta_over_pi0 + " + " + si + " * [5]";

    TString sG1 = "([0]+[1]/(sqrt(2.*TMath::Pi())*[2])*exp(-0.5*(x/[2])**2))";
    TString sG2 = "(0.05+[3]/(sqrt(2.*TMath::Pi())*[5])*exp(-0.5*((x-[4])/[5])**2))";
    TString si2 = "0.5 * (1. + ROOT::Math::erf(x - 3.))";
    TString ratio_err = "(1. - " + si2 + ") * " + sG1 + " + " + si2 + " * " + sG2; 

    // Parameters for the eta/pi0 ratio in Pb-Pb collisions at 5.02 TeV for 
    // the four centrality classes 0-20%, 20-40%, 40-60%, and 60-80%.
    // for 0-10%, 30-50%: using 0010_CutStudiesOverview_2024-11-29.root, 3050_CutStudiesOverview_2024-11-29.root

    // define parameters for the TF1s representing the parametrizations and their relative errors
    typedef  std::map<std::string, std::pair<std::vector<double>, std::vector<double>>> TMapStrPairVecVec;
    TMapStrPairVecVec lMapCentsParsPars = {
        { "0-20%", {{ 0.977721, 0.618195, 0.117933, 3.37214, 0.500039, 0.487 } , { 0.0342168, 0.114004, 0.416835, 6.49309, 0.00168754, 1.08525 }}  },
        { "20-40%", {{ 0.920456, 0.595247, 0.121594, 3.24199, 0.855145, 0.487 } , { 0.0379397, 0.0942153, 0.413325, 4.43503, 0.00244873, 1.14762 }} },
        { "40-60%", {{ 0.844084, 0.601972, 0.130577, 3.17672, 1.49528,  0.487 } , { 0.0384199, 0.0884536, 0.42096, 4.15613, 0.00306472, 1.14425 }}  },
        { "60-80%", {{ 0.763115, 0.616487, 0.145168, 3.0322, 0.500007,  0.487 } , { 0.0356787, 0.107729, 0.440188, 4.6321, 0.00273897, 1.12341 }}   },
        { "0-10%", {{ 0.97796, 0.618552, 0.117521, 3.32354, 0.500002,  0.487 } , { 0.0332156, 0.119844, 0.41766, 7.01387, 0.00161107, 1.08365 }}   },
        { "30-50%", {{ 0.885422, 0.617961, 0.128659, 3.32688, 0.72903,  0.487 } , { 0.0381912, 0.0907566, 0.420325, 4.25488, 0.00278988, 1.15198 }} },
        { "pp"   , {{ 0.4828412883910595, 0., 0.09905518928551621, 3.5412800248011624, 2.6541672047505935, 0.487} , { 0., 0., 0., 0., 0., 0., 0.}} }
    };

    // fill lMap_f_eta_to_pi0_func_and_f_rel_err 
    // contains <0-10%, <f_ratio, f_ratio_err>>
    std::map<std::string, std::pair<TF1*, TF1*>> lMap_f_eta_to_pi0_func_and_f_rel_err; 
    for (auto const &iPair : lMapCentsParsPars){
        auto const &lCent = iPair.first;
        auto const lCentNoSymb(lCent.substr(0, lCent.size()-1));
        auto const &lPairParsPars = iPair.second;

        auto createTF1andSetPars = [&](std::string const &theSuff){
            bool isErrors = theSuff.size();
            auto const &lPars = isErrors ? lPairParsPars.second : lPairParsPars.first;
            TF1 *f = new TF1(Form("f_eta_to_pi0_%s%s", theSuff.data(), 
                                   lCentNoSymb.data()), 
                             isErrors ? ratio_err : ratio, 0., 200.);
            if (f){
                f->SetTitle(f->GetName());
                f->SetParameters(lPars.data());
                f->SetNpx(10000);
            }
            return f;
        };
        lMap_f_eta_to_pi0_func_and_f_rel_err.insert({ lCent, { createTF1andSetPars(""), createTF1andSetPars("err") } });
    }
    // lMap_f_eta_to_pi0_func_and_f_rel_err is filled now

    std::map<std::string, Color_t> lMapColors({
        { "0-20%", kRed },
        { "20-40%", kOrange },
        { "40-60%", kBlue },
        { "60-80%", kBlack },
        { "0-10%", kAzure },
        { "30-50%", kCyan },
        { "pp"     , kGray }
    });
       cout << "SFS 94\n";


    // create TGraphErrors representing the error band around the eta/pi0 parameterizations
    auto createErrorBandGraph = [&](std::pair<std::string, std::pair<TF1*, TF1*>> const &thePairCentPairTF1s){
        const int n_points = 1000;
        std::vector<double> lVecPt;
        double pt_min = 0.;
        double pt_max = 200.;
        double step = (pt_max - pt_min) / (n_points - 1);

        double func[n_points], func_err[n_points];
        std::string const &lCent = thePairCentPairTF1s.first;
        TF1 &lF = *(thePairCentPairTF1s.second.first);
        TF1 &lFerr = *thePairCentPairTF1s.second.second;
        
        for (int i = 0; i < n_points; ++i) {
            double pt = pt_min + i * step;        
            func[i]     = lF.Eval(pt);
            func_err[i] = lF.Eval(pt) * lFerr.Eval(pt);
            lVecPt.push_back(pt);
        }
        auto &g_err_band = *new TGraphErrors(lVecPt.size(), lVecPt.data(), func, nullptr, func_err);
        g_err_band.SetName(Form("%s_g_err_band", lCent.substr(0, lCent.size()-1).data())); // remove %
        g_err_band.SetLineWidth(0);
        g_err_band.SetFillColorAlpha(lMapColors.at(lCent), 0.3);  // Semi-transparent red error band
        return &g_err_band;
    };

    
    // fill lMapGraphFunctionErrorbands
    // create map for bands
    std::map<std::string, TGraphErrors*> lMapGraphFunctionErrorbands;
    for (auto const &iPair : lMap_f_eta_to_pi0_func_and_f_rel_err){
        auto const &lCent = iPair.first;
        printf("SFS lCent = %s\n", lCent.data());
        lMapGraphFunctionErrorbands.insert(
            std::pair{ lCent, createErrorBandGraph(iPair) });
    }
    // lMapGraphFunctionErrorbands is filled now
    cout << "SFS 109\n";

    // fill lMapCentsPairVecsPointsErrors_fluidum
    // Here we provide the eta/pi0 values as predicted with the help of FluiduM (+ data)
    // and which are used to obtain the eta/pi0 parameterization
    TMapStrPairVecVec lMapCentsPairVecsPointsErrors_fluidum({
        { "0-20%", 
            { { 0.0311997, 0.0392724, 0.0442586, 0.0535506, 0.0642473, 0.0784368, 0.0939543, 0.107721, 0.123157, 0.135399, 0.148764, 0.165187, 0.182871, 0.199335, 0.212247, 0.227712, 0.249586, 0.287404, 0.300101, 0.325733, 0.351506, 0.377361, 0.403812, 0.425581, 0.442681, 0.459794, 0.501249, 0.525111, 0.552412, 0.563631, 0.574083, 0.572864 } , 
    { 0.00093599, 0.00117817, 0.00132776, 0.00160652, 0.00192742, 0.0023531, 0.00281863, 0.00323164, 0.00369472, 0.00406196, 0.00446292, 0.0049556, 0.00548613, 0.00598004, 0.00636742, 0.00683136, 0.00748759, 0.00862213, 0.00900303, 0.00977198, 0.0105452, 0.0113208, 0.0121144, 0.0127674, 0.0132804, 0.0137938, 0.0150375, 0.0157533, 0.0165724, 0.0169089, 0.0172225, 0.0171859 } }  },
        { "20-40%", { { 0.0324406, 0.0412224, 0.0484699, 0.0584987, 0.0706159, 0.085446, 0.0995194, 0.113975, 0.128991, 0.14842, 0.158626, 0.177029, 0.192111, 0.20787, 0.223047, 0.237661, 0.256101, 0.294495, 0.30422, 0.326479, 0.345997, 0.372355, 0.389262, 0.408629, 0.42412, 0.43939, 0.477048, 0.495588, 0.518112, 0.52877, 0.539397, 0.539777 } , 
    { 0.000973219, 0.00123667, 0.0014541, 0.00175496, 0.00211848, 0.00256338, 0.00298558, 0.00341925, 0.00386973, 0.0044526, 0.00475878, 0.00531087, 0.00576333, 0.00623611, 0.0066914, 0.00712983, 0.00768302, 0.00883485, 0.00912661, 0.00979438, 0.0103799, 0.0111706, 0.0116779, 0.0122589, 0.0127236, 0.0131817, 0.0143114, 0.0148676, 0.0155434, 0.0158631, 0.0161819, 0.0161933 } } },
        { "40-60%", { { 0.0350825, 0.0452672, 0.0541552, 0.0650085, 0.0799015, 0.0961683, 0.110709, 0.126038, 0.140318, 0.158936, 0.1715, 0.187442, 0.204715, 0.218907, 0.232458, 0.24584, 0.266814, 0.301666, 0.306019, 0.323133, 0.342065, 0.360455, 0.375451, 0.390362, 0.402741, 0.421389, 0.455315, 0.472617, 0.480878, 0.500294, 0.507239, 0.524155 } , 
    { 0.00105248, 0.00135802, 0.00162465, 0.00195026, 0.00239704, 0.00288505, 0.00332126, 0.00378115, 0.00420954, 0.00476807, 0.00514501, 0.00562326, 0.00614146, 0.00656722, 0.00697374, 0.00737521, 0.00800442, 0.00904997, 0.00918058, 0.00969399, 0.0102619, 0.0108137, 0.0112635, 0.0117109, 0.0120822, 0.0126417, 0.0136594, 0.0141785, 0.0144263, 0.0150088, 0.0152172, 0.0157246 } }  },
        { "60-80%", { { 0.038251, 0.0484757, 0.0605527, 0.0727566, 0.0884783, 0.106464, 0.12374, 0.137742, 0.153617, 0.168105, 0.180818, 0.190388, 0.211287, 0.2213, 0.231751, 0.248145, 0.265347, 0.292987, 0.294187, 0.303283, 0.323027, 0.338594, 0.353076, 0.379286, 0.381492, 0.399614, 0.42417, 0.438952, 0.453572, 0.468267, 0.495844, 0.490778 } , 
    { 0.00114753, 0.00145427, 0.00181658, 0.0021827, 0.00265435, 0.00319393, 0.00371219, 0.00413227, 0.00460852, 0.00504316, 0.00542453, 0.00571164, 0.00633861, 0.00663901, 0.00695252, 0.00744435, 0.0079604, 0.00878961, 0.00882561, 0.0090985, 0.00969082, 0.0101578, 0.0105923, 0.0113786, 0.0114448, 0.0119884, 0.0127251, 0.0131686, 0.0136072, 0.014048, 0.0148753, 0.0147233 } }   },
        { "0-10%", { { 0.0311589, 0.0390224, 0.0437121, 0.052979, 0.0636666, 0.0775345, 0.0935798, 0.107122, 0.122246, 0.133816, 0.147024, 0.163819, 0.180947, 0.197675, 0.210872, 0.225855, 0.247648, 0.285569, 0.298764, 0.324883, 0.350681, 0.377175, 0.405201, 0.427988, 0.444572, 0.46235, 0.503232, 0.525035, 0.555853, 0.565237, 0.575989, 0.576023 } , 
    { 0.000934767, 0.00117067, 0.00131136, 0.00158937, 0.00191, 0.00232604, 0.0028074, 0.00321366, 0.00366739, 0.00401449, 0.00441071, 0.00491457, 0.0054284, 0.00593025, 0.00632615, 0.00677564, 0.00742943, 0.00856707, 0.00896291, 0.00974649, 0.0105204, 0.0113153, 0.012156, 0.0128396, 0.0133371, 0.0138705, 0.015097, 0.0157511, 0.0166756, 0.0169571, 0.0172797, 0.0172807 } }   },
        { "30-50%", { { 0.0335726, 0.0430717, 0.0511784, 0.0612022, 0.0749101, 0.0903309, 0.105175, 0.119151, 0.134301, 0.156077, 0.164467, 0.185048, 0.198361, 0.213454, 0.227185, 0.241568, 0.261196, 0.29824, 0.303277, 0.325532, 0.34424, 0.368596, 0.38289, 0.397119, 0.416903, 0.431606, 0.470308, 0.488085, 0.511558, 0.526727, 0.531099, 0.547259 } , 
    { 0.00100718, 0.00129215, 0.00153535, 0.00183606, 0.0022473, 0.00270993, 0.00315524, 0.00357452, 0.00402902, 0.0046823, 0.00493402, 0.00555144, 0.00595083, 0.00640363, 0.00681554, 0.00724703, 0.00783589, 0.00894721, 0.00909831, 0.00976595, 0.0103272, 0.0110579, 0.0114867, 0.0119136, 0.0125071, 0.0129482, 0.0141092, 0.0146426, 0.0153467, 0.0158018, 0.015933, 0.0164178 } } },
        { "pp"   , { { 0.0 }, { 0.0 } } }});

    std::vector<double> lVecFluidumPts{0.225, 0.275, 0.325, 0.375, 0.425, 0.475, 0.525, 0.575, 0.625, 0.675, 0.725, 0.775, 0.825, 0.875, 0.925, 0.975, 1.05, 1.15, 1.25, 1.35, 1.45, 1.55, 1.65, 1.75, 1.85, 1.95, 2.1, 2.3, 2.5, 2.7, 2.9, 3.1};    
    
    typedef std::pair<std::vector<double> const &, std::vector<double> const &> TPairVecVec;
    auto createGraphFluidum = [&](std::pair<std::string, TPairVecVec> const &thePairCentPairVecs){
        std::string const &lCent = thePairCentPairVecs.first;
        TPairVecVec const &lPairPointsErrors = thePairCentPairVecs.second;
        std::string lName(Form("%s_GraphFluidum", lCent.substr(0, lCent.size()-1).data()));
        auto *g = new TGraphErrors(lVecFluidumPts.size(), lVecFluidumPts.data(), 
                                   lPairPointsErrors.first.data(), nullptr, lPairPointsErrors.second.data());
        if (!g){
            printf("ERROR: createGraphFluidum(): Graph %s could not be created!\n", lName.data());
        } else { g->SetName(lName.data()); }
        return g;
    };

    // fill lMap_g_eta_to_pi0_fluidum_points_w_errors
    std::map<std::string, TGraphErrors*> lMap_g_eta_to_pi0_fluidum_points_w_errors;
    for (auto const &iPairCentPairVecs : lMapCentsPairVecsPointsErrors_fluidum){
        std::string const &lCent = iPairCentPairVecs.first;
        lMap_g_eta_to_pi0_fluidum_points_w_errors.insert(
            std::make_pair(iPairCentPairVecs.first, createGraphFluidum(iPairCentPairVecs)));
    }

    // all elementary structures filled
    ///////////////////////////////////////////////////////////////////////////////

    // first plot: all parameterizations with error bands 
    gStyle->SetOptStat(kFALSE);
    cout << "SFS 142\n";

    // draw all parameterizations
    float lLegendTextSize = 0.05; // Removed duplicate declaration
    auto plotSingleCentralityClass = [&](std::string const &theCent){
        Color_t lColor = lMapColors.at(theCent);
        
        // TF1 function
        auto &f_eta_to_pi0 = *lMap_f_eta_to_pi0_func_and_f_rel_err.at(theCent).first;
        // graph with errorband for the TF1
        auto &g_eta_to_pi0_function_error_band = *lMapGraphFunctionErrorbands.at(theCent);
        // graph with fluidum points 
        auto &g_eta_to_pi0_fluidum_points_werr = *lMap_g_eta_to_pi0_fluidum_points_w_errors.at(theCent);
        
        printf("SFS f_eta_to_pi0.GetName() = %s\n, g_eta_to_pi0_function_error_band.GetName() = %s\n, g_eta_to_pi0_fluidum_points_werr.data() = %s\n\n", f_eta_to_pi0.GetName(), g_eta_to_pi0_function_error_band.GetName(), g_eta_to_pi0_fluidum_points_werr.GetName());

        std::string lNameCanvas(Form("c_%s\n", theCent.data()));
        TCanvas* c2 = new TCanvas(lNameCanvas.data(), lNameCanvas.data(), 800, 600);
        TH2F* fr2 = new TH2F(Form("fr_%s", theCent.data()), 
                             Form("eta/pi0 ratio (%s), Pb-Pb, 5.02 TeV;p_#text{T} (GeV/c);#eta / #pi^{0}", 
                                  theCent.data()), 
                             1, 0., 8., 1, 0., 0.7);
        fr2->Draw();
        auto leg = utils_plotting::GetLegend(0.5, 0.2, 0.90, 0.4, true /*theDrawAlready*/); // this already removes the boarder

        // the errorband for the parametrization
        utils_plotting::DrawAndAdd(g_eta_to_pi0_function_error_band,"same3", lColor, 1.0,
                                   leg, g_eta_to_pi0_function_error_band.GetName(), "lep", lLegendTextSize, true /*theDrawLegAlready*/, 
                                   3 /*theMarkerStyle*/, 1.0 /*theMarkerSize*/);
        
        // the actual parametrization
        utils_plotting::DrawAndAdd(f_eta_to_pi0,"same", lColor, 1.0, 
                                   leg, f_eta_to_pi0.GetName(), "l", lLegendTextSize, true /*theDrawLegAlready*/, 
                                   3 /*theMarkerStyle*/, 1.0 /*theMarkerSize*/);
        
        // the fluidum prediction as TGraphErrors
        utils_plotting::DrawAndAdd(g_eta_to_pi0_fluidum_points_werr,"sameP", lColor, 1.0, 
                                   leg, g_eta_to_pi0_fluidum_points_werr.GetName(), "p", lLegendTextSize, true /*theDrawLegAlready*/, 
                                   20 /*theMarkerStyle*/, 1.0 /*theMarkerSize*/);

        // save to file
        TFile &f = *new TFile("eta_to_pi0_ratio_param_tf1_PbPb_5020TeV_2025_03_30.root", "update");
        f_eta_to_pi0.Write();
        g_eta_to_pi0_fluidum_points_werr.Write();
        g_eta_to_pi0_function_error_band.Write();
        f.Close();
    };

    // plot all centralities and save to file
    for (auto const &iPair : lMapColors){
        std::string const &lCent = iPair.first;
        plotSingleCentralityClass(lCent);
    }
}
