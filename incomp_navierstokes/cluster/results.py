#
# usage:
#	 python simResults.py -d <directory>  -f <file>
#

import itertools,os,sys,argparse,imp #,params
import ROOT
from ROOT import TTree,TFile,gROOT,gStyle,gPad
from ROOT import TCanvas,TGraph,TPad,TBrowser
from ROOT import TLegend,kAurora,kRainBow,kRust,kFall
from ROOT import TPaveText,TStyle,TMultiGraph
from array import array

#output file
file=TFile("test.root","recreate")
tree=TTree("simRes", "simulation results")
#create vars
separation=array('f',[0])
angle=array('f',[0])
farfield=array('f',[0])
cl1=array('f',[0])
cd1=array('f',[0])
csf1=array('f',[0])
cl2=array('f',[0])
cd2=array('f',[0])
csf2=array('f',[0])
#root tree settings
tree.Branch('separation',separation,'separation/F')
tree.Branch('angle',angle,'angle/F')
tree.Branch('farfield',farfield,'farfield/F')
tree.Branch('cl1',cl1,'cl1/F')
tree.Branch('cd1',cd1,'cd1/F')
tree.Branch('csf1',csf1,'csf1/F')
tree.Branch('cl2',cl2,'cl2/F')
tree.Branch('cd2',cd2,'cd2/F')
tree.Branch('csf2',csf2,'csf2/F')

#input arguments
parser= argparse.ArgumentParser(prog='results.py', description='Process simulation CL,CD,CSF results.')
parser.add_argument('--dir',dest='dirname',action='store',help='file directory to use (relative to working directory)')
#parser.add_argument('-f',dest='filename',action='store',help='name (of file to read)')
#parser.add_argument('-p',dest='paramfile',action='store',help='parameter file (for looping)')

filename= "forces_breakdown.dat"
args = parser.parse_args()

if not args.dirname:
	print("Error: provide --dir <results parent directory> and -f <forces_breakdown.dat>")
	exit()

#print("file dir= {}\n".format(args.dirname))
#print("file name= {}\n".format(args.filename))
#print("parameters= {}\n".format(args.paramfile))

#read parameters of interest
params= imp.load_source('', str(args.dirname)+'/params.py')
inc_sep= params.inc_sep

#create new simulation results file
#with open('simulation_results.dat','w') as fileout:
#	fileout.write("CL1\tCD1\tCSF1\tCL2\tCD2\tCSF2\tSEP\n")
#        fileout.write("===\t===\t====\t===\t===\t====\t===\n")

diameter= str(params.min_dia)
length= str(params.min_far)
sep= str(params.min_sep)
ang= str(params.min_angle)

storage_path= str(args.dirname)+"/dia_"+diameter+"_len_"+length+"_sep_"+sep+"_ang_"+ang+"/"
path_exists_bool= os.path.exists(storage_path)

print(storage_path)

#determine parameter n-combinations
if params.inc_far is not 0:
    nfar= int((params.max_far-params.min_far)/params.inc_far)+1
else:
    nfar= 1

if params.inc_sep is not 0:
        nseps= int((params.max_sep-params.min_sep)/params.inc_sep)+1
else:
        nseps= 1

if params.inc_angle is not 0:
        nangles= int((params.max_angle-params.min_angle)/params.inc_angle)+1
else:
        nangles= 1

#cycle through parameters
for sep_idx in range(0,nseps):
        sep= params.min_sep+sep_idx*params.inc_sep

        for ang_idx in range(0,nangles):
                ang= params.min_angle+ang_idx*params.inc_angle

                for far_idx in range(0,nfar):
                        far= params.min_far+far_idx*params.inc_far

#idx_sep=0
#while path_exists_bool:

			separation[0]= float(sep)
			angle[0]= float(ang)
			farfield[0]= float(far)

			diameter= str(params.min_dia)
                        length= str(far)
			ang= str(ang)
			sep= str(sep)
			#{:.1f}
			storage_path= str(args.dirname)+"/dia_"+diameter+"_len_"+length+"_sep_{}".format(sep)+"_ang_"+ang+"/"
			file_path= storage_path+filename
			path_exists_bool= os.path.exists(storage_path)

			if path_exists_bool is not True:
				print(file_path)
				print("DONE\n")
				break
			else:
#				print("sep= {} separation= {} inc_sep= {} idx= {}".format(sep[0],separation,inc_sep, idx))	
				print(file_path)

			#read 'forces_breakdown.dat' file
			with open(file_path,'r') as f:
				lines_after_skips = f.readlines()[106:]

			count=0
			countcl=0
			countcd=0
			countcsf=0
			#readlines
			for stuff in lines_after_skips:
				contents=stuff[23:33]
				realcontents=stuff[0:34]
				angle[0]= float(params.min_angle)

				if realcontents.startswith("Total CL  ") and countcl==0:
					print("test: {}".format(realcontents))
					cl1[0] = float(realcontents.split(':')[-1].strip())
					countcl=countcl+1
        				print cl1[0]
				elif realcontents.startswith("Total CL  ") and countcl==1:
                        		print("test: {}".format(realcontents))
                       			cl2[0] = float(realcontents.split(':')[-1].strip())
                		        print cl2[0]

                		if realcontents.startswith("Total CD  ") and countcd==0:
                        		print("test: {}".format(realcontents))
                        		cd1[0] = float(realcontents.split(':')[-1].strip())
                        		countcd=countcd+1
                        		print cd1[0]
                		elif realcontents.startswith("Total CD  ") and countcd==1:
                        		print("test: {}".format(realcontents))
                        		cd2[0] = float(realcontents.split(':')[-1].strip())
                        		print cd2[0]

                		if realcontents.startswith("Total CSF  ") and countcsf==0:
                        		print("test: {}".format(realcontents))
                        		csf1[0] = float(realcontents.split(':')[-1].strip())
                        		countcsf=countcsf+1
                        		print csf1[0]
                		elif realcontents.startswith("Total CSF  ") and countcsf==1:
                        		print("test: {}".format(realcontents))
                        		csf2[0] = float(realcontents.split(':')[-1].strip())
                        		print csf2[0]

			count=count+1
			tree.Fill()

			#idx_sep=idx_sep+1
#			with open('simulation_results.dat','a') as fileout:
#				fileout.write("{:.2e} {:.2e} {:.2e} {:.2e} {:.2e} {:.2e} {:.1e}\n".format(cl1[0],cd1[0],csf1[0],cl2[0],cd2[0],csf2[0],separation[0]))

tree.Write()
file.Close()

