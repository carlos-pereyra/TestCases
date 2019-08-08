#
# usage: 
#	python createSimJobs.py -d <mesh directory>
#

import os,sys,argparse,imp
  
#input arguments
parser= argparse.ArgumentParser(prog='simResults.py', description='Process simulation CL,CD,CSF results.')
parser.add_argument('--dir',dest='dirname',action='store',help='file directory to use (relative to working directory)')

args = parser.parse_args()

if not args.dirname:
        print("Error: provide --dir <mesh storage directory>")
        exit()

#directory specific parameters
params= imp.load_source('', str(args.dirname)+'/params.py')
dia= params.min_dia
dirpath= args.dirname

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

#open job file
with open("job","w") as jobsfile:
    jobsfile.write("#!/bin/bash\n")

for sep_idx in range(0,nseps):
        sep= params.min_sep+sep_idx*params.inc_sep

        for ang_idx in range(0,nangles):
                ang= params.min_angle+ang_idx*params.inc_angle

        	for far_idx in range(0,nfar):
            		far= params.min_far+far_idx*params.inc_far

            		with open("job","a") as jobsfile:
#               		jobsfile.write("python createDirSlurm.py {} {} {} {}\n".format(dia,far,sep,ang))
                		jobsfile.write("cd {}/dia_{}_len_{}_sep_{}_ang_{}\n".format(dirpath,dia,far,sep,ang))
				jobsfile.write("sbatch slurm\n")
#                		jobsfile.write("$PW -b ../../spheres2_inc.glf {} {} {} {}\n".format(sep,ang,dia,far))
#                		jobsfile.write("cp ../../dataAnalysisScript.py .\n")
#                		jobsfile.write("cp ../../lam_sphere_inc.cfg .\n")
                		jobsfile.write("cd ../../..\n\n")

print("nseps={} nangles={} nfar={} DONE".format(nseps,nangles,nfar))

