import ROOT as r

r.gROOT.SetBatch(1)

configs = {}
configs['400_150_1'] = {
                       'file'  : 'output_400_150_1.root',
                       'color' : r.kRed+2,
                       }


nbins = 100
xmin  = 0.0
xmax  = 1.0


for point in configs.keys():

    _file = r.TFile(configs[point]['file'])
    _tree = _file.Get('Events')

    _histo = r.TH1F(point, '', nbins, xmin, xmax)

    for e in _tree:
        _histo.Fill(e.LLP1_Lprop)
        _histo.Fill(e.LLP2_Lprop)

    # Histogram tunning
    _histo.SetMarkerStyle(24)
    _histo.SetMarkerSize(0.8)
    _histo.SetMarkerColor(configs[point]['color'])
    _histo.SetLineColor(configs[point]['color'])

    # Histogram fitting
    _func = r.TF1('func_'+ point, '[0]*exp(-x/[1])', xmin, xmax)
    _func.SetParameters(histogram.GetMaximum()/2.0, 0.1)
    _func.SetLineColor(configs[point]['color'])
    _histo.Fit('func_' + point, '', '', xmin, xmax)


    configs[point]['histo'] = _histo
    configs[point]['function'] = _func
    info = point.split('_')
    configs[point]['mH'] = float(info[0])
    configs[point]['mX'] = float(info[1])
    configs[point]['ctau'] = float(info[2])



c1 = r.TCanvas('c1', '', 600, 500)
configs['400_150_1']['histo'].Draw('PE')
#c1.SetLogy(1)
c1.SetLogx(1)
c1.SaveAs('result.png')



