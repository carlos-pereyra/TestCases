#
# usage:
#	python analysis -x <axis> -y <axis>
#

import ROOT
from ROOT import TTree,TFile,gROOT,gStyle,gPad
from ROOT import TCanvas,TGraph,TPad,TBrowser
from ROOT import TLegend,kAurora,kRainBow,kRust,kFall
from ROOT import TPaveText,TStyle,TMultiGraph
import numpy as np
import argparse

parser = argparse.ArgumentParser(description='Process simulation data')
parser.add_argument('-x', dest='xaxis', action='store', help='x-axis (on plot)')
parser.add_argument('-y', dest='yaxis', action='store', help='y-axis (on plot)')
args = parser.parse_args()

if not args.xaxis and not args.yaxis:
        print("Error: provide -x <xaxis> and -y <yaxis>")
        exit()

x_label=args.xaxis
y_label=args.yaxis
dbg=1

file=TFile("test.root", "read")
tree=file.Get("simRes")
tree.GetEntry()
if dbg: tree.Scan("{}:{}".format(y_label,x_label),"","colsize=20")
tree.GetEntry()

#Canvas 1
c1=TCanvas("c", "canvas 1", 600, 400)
c1.GetFrame().SetBorderMode(0);
c1.GetFrame().SetBorderMode(0);
c1.GetFrame().SetBorderSize(0);
c1.SetLeftMargin(0.15)
c1.SetRightMargin(0.15)
c1.SetBottomMargin(0.15)
c1.SetTopMargin(0.10)
#legend = TLegend(0.60, 0.60, .98, 0.78)
#legend.SetTextSize(0.04)
c1.cd()

#Plot1
tree.SetLineColor(1)
tree.SetTitle('normalized values')
tree.Draw("{}:{}".format(y_label,x_label),"","")
g0=TGraph(tree.GetSelectedRows(),tree.GetV2(),tree.GetV1())
g0.SetName("g0")
g0.SetMarkerStyle(2)
g0.SetMarkerColor(2)
g0.SetLineWidth(2)
g0.SetLineColor(1)
g0.SetLineStyle(1);
g0.GetXaxis().SetTitle('{}'.format(x_label))
g0.GetXaxis().SetTitleSize(0.06)
g0.GetXaxis().SetMaxDigits(3)
g0.GetYaxis().SetTitle('{}'.format(y_label))
g0.GetYaxis().SetTitleSize(0.06)
#g0.GetXaxis().SetLimits(0.6,2)
#g0.GetYaxis().SetLimits(-10,10)
g0.Draw("LAP")

#Update canvas
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
c1.SetGrid()
c1.Modified()
c1.Update()

#Keep window open
text= raw_input()
