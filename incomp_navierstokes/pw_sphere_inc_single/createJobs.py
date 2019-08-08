#
# usage: 
#       python createJobs.py --dir <mesh directory>
#

import os,sys,argparse,imp,params

#input arguments
parser= argparse.ArgumentParser(prog='simResults.py', description='Process simulation CL,CD,CSF results.')
parser.add_argument('--dir',dest='dirpath',action='store',help='file directory to use (relative to working directory)')
parser.add_argument('-d',dest='diameter',action='store',help='sphere diameter')
parser.add_argument('-l',dest='far',action='store',help='sphere far-field length')
parser.add_argument('-s',dest='separation',action='store',help='sphere separation')
parser.add_argument('-a',dest='angle',action='store',help='sphere angle')
parser.add_argument('--bsp',dest='backspacing',action='store',help='far field background spacing')
args= parser.parse_args()

if not args.dirpath and not args.diameter and not args.backspacing:
        print("Error: provide --dir <create mesh> and -d <diameter> and --bsp <back spacing>")
        exit()

#directory specific parameters
dirpath= args.dirpath
dia= args.diameter
#far= args.far
sep= 0
ang= 0

#params= imp.load_source('', str(args.dirname)+'/params.py')
#dia=params.min_dia

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

if params.inc_bsp is not 0:
        nsbp= int((params.max_bsp-params.min_bsp)/params.inc_bsp)+1
else:
        nbsp= 1

#open job file
with open("job","w") as jobsfile:
	jobsfile.write("#!/bin/bash\n")
	jobsfile.write("PW=/Users/pereyra3/Applications/Gmsh/Applications/Pointwise/PointwiseV18.2R2/pointwise\n\n")

for far_idx in range(0,nfar):
	far= params.min_far+far_idx*params.inc_far
       
	for bsp_idx in range(0,nbsp): 
		with open("job","a") as jobsfile:
			jobsfile.write("python createDirSlurm.py -d {} -l {} -s {} -a {} --dir {}\n".format(dia,far,sep,ang,dirpath))
                	jobsfile.write("cd {}/dia_{}_len_{}_sep_{}_ang_{}\n".format(dirpath,dia,far,sep,ang))
#                	jobsfile.write("$PW -b ../../spheres1.glf {} {}\n".format(dia,far, bsp))
                	jobsfile.write("cp ../../dataAnalysisScript.py .\n")
                	jobsfile.write("cp ../../lam_sphere_inc.cfg .\n")
                	jobsfile.write("cd ../..\n\n")

with open("job","a") as jobsfile:
        jobsfile.write("cd {}/\n".format(dirpath))
        jobsfile.write("cp ../params.py .\n")
        jobsfile.write("cd ../\n")
        jobsfile.close()

print("nseps={} nangles={} nfar={} DONE".format(nseps,nangles,nfar))

