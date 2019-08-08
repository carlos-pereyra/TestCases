#
# usage: 
#       python createDirSlurm.py --dir <mesh directory> -d <diam> -a <ang> -s <sep> -l <farfield>
#

import os,sys,argparse,imp

#input arguments
parser= argparse.ArgumentParser(prog='simResults.py', description='Process simulation CL,CD,CSF results.')
parser.add_argument('--dir',dest='dirname',action='store',help='mesh file directory to use (relative to working directory)')
parser.add_argument('-d',dest='diameter',action='store',help='sphere diameter')
parser.add_argument('-l',dest='length',action='store',help='far-field length (size of far-field)')
parser.add_argument('-s',dest='separation',action='store',help='sep (0 for single sphere)')
parser.add_argument('-a',dest='angle',action='store',help='angle (0 for single sphere)')
args = parser.parse_args()

path= args.dirname
diameter= args.diameter
length= args.length
separation= args.separation
angle= args.angle

if path is None:
	print ("please provide arguments")
	exit()

storage_path= path+"/dia_"+diameter+"_len_"+length+"_sep_"+separation+"_ang_"+angle+"/"
path_exists_bool= os.path.exists(storage_path)

if path_exists_bool is not True:
	os.makedirs(storage_path)
   
os.chdir(storage_path)

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
	slurmfile.write("echo 'Done'")

slurmfile.close()

