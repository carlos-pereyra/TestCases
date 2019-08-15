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
args= parser.parse_args()

if not args.dirpath:
        print("Error: provide --dir <create mesh>")
        exit()

#directory specific parameters
dirpath= args.dirpath
#dia= args.diameter
#far= args.far
sep= 0
ang= 0

#params= imp.load_source('', str(args.dirname)+'/params.py')
#dia=params.min_dia

#determine parameter n-combinations

#diameter
if params.inc_dia is not 0:
        ndia= int((params.max_dia-params.min_dia)/params.inc_dia)+1
else:
	dia= params.min_dia
        ndia= 1

#far field
if params.inc_far is not 0:
	nfar= int((params.max_far-params.min_far)/params.inc_far)+1
else:
	nfar= 1

#separation
if params.inc_sep is not 0: 
	nseps= int((params.max_sep-params.min_sep)/params.inc_sep)+1
else:
	nseps= 1

#angle
if params.inc_angle is not 0: 
	nangles= int((params.max_angle-params.min_angle)/params.inc_angle)+1
else:
	nangles= 1

#spacial resolution
if params.inc_sp is not 0:
        nsp= int((params.max_sp-params.min_sp)/params.inc_sp)+1
else:
        nsp= 1

#background spacial resolution
if params.inc_bsp is not 0:
        nbsp= int((params.max_bsp-params.min_bsp)/params.inc_bsp)+1
else:
        nbsp= 1

#boundary layers
#if params.inc_sp is not 0:
#        nsp= int((params.max_sp-params.min_sp)/params.inc_sp)+1
#else:
#        nsp= 1

#open job file
with open("job","w") as jobsfile:
	jobsfile.write("#!/bin/bash\n")
	jobsfile.write("PW=/Users/pereyra3/Applications/Gmsh/Applications/Pointwise/PointwiseV18.2R2/pointwise\n\n")

for dia_idx in range(0,ndia):
	dia= params.min_dia+dia_idx*params.inc_dia

	for far_idx in range(0,nfar):
		far= params.min_far+far_idx*params.inc_far

		for sp_idx in range(0,nsp):
			sp= params.min_sp+sp_idx*params.inc_sp
       
			for bsp_idx in range(0,nbsp):
				bsp= params.min_bsp+bsp_idx*params.inc_bsp

				with open("job","a") as jobsfile:
					jobsfile.write("python createDirSlurm.py -d {} -l {} --dir {} --sp {}\n".format(dia,far,dirpath,sp))
					storage= str("cd {}/sp_{}_dia_{}_len_{}_sep_{}_ang_{}\n".format(dirpath,sp,dia,far,sep,ang))
               				#jobsfile.write("cd {}/dia_{}_len_{}_sep_{}_ang_{}\n".format(dirpath,dia,far,sep,ang))
					jobsfile.write(storage)
                			jobsfile.write("$PW -b ../../spheres1.glf {} {} {} {}\n".format(dia,far,sp,bsp))
                			jobsfile.write("cp ../../dataAnalysisScript.py .\n")
                			jobsfile.write("cp ../../lam_sphere_inc.cfg .\n")
                			jobsfile.write("cd ../..\n\n")

with open("job","a") as jobsfile:
        jobsfile.write("cd {}/\n".format(dirpath))
        jobsfile.write("cp ../params.py .\n")
        jobsfile.write("cd ../\n")
        jobsfile.close()

print("nseps={} nangles={} nfar={} DONE".format(nseps,nangles,nfar))

