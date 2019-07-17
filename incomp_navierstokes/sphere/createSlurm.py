import os,sys,params

dia=params.min_dia
far=params.min_far

if params.inc_sep is not 0: 
	ndists= int((params.max_sep-params.min_sep)/params.inc_sep)+1
else:
	ndists= 1

if params.inc_angle is not 0: 
	nangles= int((params.max_angle-params.min_angle)/params.inc_angle)+1
else:
	nangles= 1

print("ndists={} nangles={}".format(ndists,nangles))

with open("slurm","w") as jobsfile:
	#jobsfile.write("g++ -std=c++11 -Iinclude sphere.cpp -o meshexe -lgmsh\n")
	jobsfile.write("#!/bin/bash\n")
	jobsfile.write("#SBATCH --job-name=spheres\n")
	jobsfile.write("#SBATCH -N 2\n")
	jobsfile.write("#SBATCH -p pbatch\n")
	jobsfile.write("#SBATCH -A ppims\n")
	jobsfile.write("#SBATCH -t 00:30:00\n")
	jobsfile.write("#SBATCH -o screen.out\n")
	#jobsfile.write("srun -N 1 -n 30 comp_lam_sphere.cfg\n")

for dist_idx in range(0,ndists):
	dist= params.min_sep+dist_idx*params.inc_sep

	for ang_idx in range(0,nangles):
		ang= params.min_angle+ang_idx*params.inc_angle
		with open("slurm","a") as jobsfile:
			jobsfile.write("python createDirPlusSU2.py {} {} {} {}\n".format(dia,far,dist,ang))
			jobsfile.write("cd "+os.environ['LUST2']+"/data/dia_{}_len_{}_sep_{}_ang_{}\n".format(dia,far,dist,ang))
			jobsfile.write("srun -N 1 -n 30 comp_lam_sphere.cfg\n")
			#jobsfile.write("../.././meshexe {} {} {} {}\n".format(dia,far,dist,ang))
			#jobsfile.write("SU2_CFD comp_lam_sphere.cfg\n")
			#jobsfile.write("cd ../..\n\n")

