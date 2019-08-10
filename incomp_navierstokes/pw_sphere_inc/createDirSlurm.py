#
# usage: 
#       python createDirSlurm.py --dir <mesh directory> -d <diam> -a <ang> -s <sep> -l <farfield>
#

import os,sys,argparse,imp

#input arguments
parser= argparse.ArgumentParser(prog='simResults.py', description='Process simulation CL,CD,CSF results.')
parser.add_argument('--dir',dest='dirname',action='store',help='mesh file directory to use (relative to working directory)')
parser.add_argument('--sys',dest='system',action='store',help='system name on cluster')
parser.add_argument('-d',dest='diameter',action='store',help='sphere diameter')
parser.add_argument('-l',dest='length',action='store',help='far-field length (size of far-field)')
parser.add_argument('-s',dest='separation',action='store',help='sep (0 for single sphere)')
parser.add_argument('-a',dest='angle',action='store',help='angle (0 for single sphere)')
args = parser.parse_args()

if not args.dirname and not args.system:
	print ("Error: please provide --dir <make directory> --sys <las>")
	exit()

#variables
diameter= args.diameter
length= args.length
separation= args.separation
angle= args.angle
dirpath= args.dirname

#check if storage path already exists
storage_path= dirpath+"/dia_"+diameter+"_len_"+length+"_sep_"+separation+"_ang_"+angle+"/"
path_exists_bool= os.path.exists(storage_path)

if path_exists_bool is not True:
	os.makedirs(storage_path)
   
os.chdir(storage_path)

if args.system=="cata":
	with open("slurm",'w') as slurmfile:
		slurmfile.write("#!/bin/bash\n")
		jobname="D"+diameter+"F"+length+"S"+separation+"A"+angle
		slurmfile.write("#SBATCH --job-name={}\n".format(jobname))
		slurmfile.write("#SBATCH -N 1\n")
		slurmfile.write("#SBATCH -n 24\n")
		slurmfile.write("#SBATCH -p pbatch\n")
		slurmfile.write("#SBATCH -A ppims\n")
		slurmfile.write("#SBATCH -t 24:00:00\n")
		slurmfile.write("#SBATCH -o screen.out\n")
		slurmfile.write("srun SU2_CFD lam_sphere_inc.cfg\n")
		slurmfile.write("sbatch -d=singleton --job-name={}\n".format(jobname))
		slurmfile.write("SU2_SOL lam_sphere_inc.cfg\n")
#		slurmfile.write("echo 'Done'\n")

	slurmfile.close()

if args.system=="las":
	with open("lsf",'w') as lsf:
		lsf.write("#!/bin/tcsh\n")
		jobname="S"+separation+"A"+angle+"D"+diameter+"F"+length
		lsf.write("#BSUB -J {}\n".format(jobname))
		lsf.write("#BSUB -nnodes 4\n")
    		lsf.write("#BSUB -q pdebug\n")
    		lsf.write("#BSUB -G ppims\n")
    		lsf.write("#BSUB -W 0:01\n")
    		lsf.write("#BSUB -o show.err\n")
    		lsf.write("#BSUB -o show.out\n")
    		lsf.write("jsrun SU2_CFD lam_sphere_inc.cfg\n")

        with open("vislsf",'w') as lsfvis:
                lsfvis.write("#!/bin/tcsh\n")
                jobname="S"+separation+"A"+angle+"D"+diameter+"F"+length
                lsfvis.write("#BSUB -J visual\n")
                lsf.write("#BSUB -nnodes 1\n")
                lsfvis.write("#BSUB -q pdebug\n")
                lsfvis.write("#BSUB -G ppims\n")
                lsfvis.write("#BSUB -W 0:05\n")
                lsfvis.write("#BSUB -o screen.err\n")
                lsfvis.write("#BSUB -o screen.out\n")
		lsfvis.write("jsrun -w done(\"{}\") SU2_SOL lam_sphere_inc.cfg\n".format(jobname))
	
	lsf.close()
	lsfvis.close()

