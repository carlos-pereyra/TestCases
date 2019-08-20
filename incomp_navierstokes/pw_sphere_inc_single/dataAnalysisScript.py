import ROOT
from ROOT import TTree,TFile,gROOT,gStyle,gPad
from ROOT import TCanvas,TGraph,TPad,TBrowser
from ROOT import TLegend,kAurora,kRainBow,kRust,kFall
from ROOT import TPaveText,TStyle,TMultiGraph
import numpy as np
import argparse

#user input
parser = argparse.ArgumentParser(description='Process simulation data')
parser.add_argument('-x', dest='xaxis', action='store', help='x-axis (on plot)')
parser.add_argument('-y', dest='yaxis', action='store', help='y-axis (on plot)')
args = parser.parse_args()

if not args.xaxis and not args.yaxis:
        print("Error: provide -x <xaxis> and -y <yaxis>\n")
        print("Choices: [Iteration] [CL] [CD] [CSF]")
        exit()

#set axis
x_label=args.xaxis
y_label=args.yaxis
tree=TTree("tree", "my tree")
datafile=tree.ReadFile("history.dat","Iteration:CL:CD:CSF",',')

#Canvas 1
c1=TCanvas("c", "canvas 1", 800, 800)
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
ylimit=10
tree.SetLineColor(1)
tree.SetTitle('normalized values')
tree.Draw("{}:Iteration".format(y_label),"".format(ylimit),"")
g0=TGraph(tree.GetSelectedRows(),tree.GetV2(),tree.GetV1())
g0.SetName("g0")
g0.SetMarkerStyle(2)
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
g0.Draw("LA")

#Update canvas
c1.SetGrid()
c1.Modified()
c1.Update()

#Keep window open
text= raw_input()
