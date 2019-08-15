#
# usage: 
#       python createJobs.py --dir <mesh directory>
#

import os,sys,argparse,imp,params

#input arguments
parser= argparse.ArgumentParser(prog='simResults.py', description='Process simulation CL,CD,CSF results.')
parser.add_argument('--dir',dest='dirpath',action='store',help='file directory to use (relative to working directory)')
args= parser.parse_args()

if not args.dirpath:
        print("Error: provide --dir <create mesh>")
	exit()

dirpath= args.dirpath

#update this to make single sphere arrangement

dia=params.min_dia

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

if params.inc_sp is not 0:
        nsp= int((params.max_sp-params.min_sp)/params.inc_sp)+1
else:
        nsp= 1

if params.inc_bsp is not 0:
        nbsp= int((params.max_bsp-params.min_bsp)/params.inc_bsp)+1
else:
        nbsp= 1

#open job file
with open("job","w") as jobsfile:
    jobsfile.write("#!/bin/bash\n")
    jobsfile.write("PW=/Users/pereyra3/Applications/Gmsh/Applications/Pointwise/PointwiseV18.2R2/pointwise\n\n")

#open("job","w")
for sep_idx in range(0,nseps):
	sep= params.min_sep+sep_idx*params.inc_sep
   
	if sep>2:
		layers=10
	else:
		layers=1
 
	for ang_idx in range(0,nangles):
		ang= params.min_angle+ang_idx*params.inc_angle
        
        	for far_idx in range(0,nfar):
            		far= params.min_far+far_idx*params.inc_far
          
			for sp_idx in range(0,nsp):
 				sp= params.min_sp+sp_idx*params.inc_sp

				for bsp_idx in range(0,nsp):
					bsp= params.min_bsp+bsp_idx*params.inc_bsp

	            			with open("job","a") as jobsfile:
        	        			jobsfile.write("python createDirSlurm.py -d {} -l {} -s {} -a {} --dir {} --sp {}\n".format(dia,far,sep,ang,dirpath,sp))
                				jobsfile.write("cd {}/sp_{}_dia_{}_len_{}_sep_{}_ang_{}\n".format(dirpath,sp,dia,far,sep,ang))
                				jobsfile.write("$PW -b ../../spheres2_inc.glf {} {} {} {} {} {} {}\n".format(sep,ang,dia,far,sp,bsp,layers))
                				jobsfile.write("cp ../../dataAnalysisScript.py .\n")
                				jobsfile.write("cp ../../lam_sphere_inc.cfg .\n")
                				jobsfile.write("cd ../..\n\n")

with open("job","a") as jobsfile:
	jobsfile.write("cd double_sphere_meshes_inc/\n")
	jobsfile.write("cp ../params.py .\n")
	jobsfile.write("cd ../\n")
	jobsfile.close()

print("nseps={} nangles={} nfar={} DONE".format(nseps,nangles,nfar))

