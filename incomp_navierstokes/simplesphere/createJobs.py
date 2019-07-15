import os,sys,params

'''
with open("params.txt",'r') as paramfile:
	params = paramfile.read()
	for lines in params:
        	lines.rstrip()
'''

if params.inc_sep is not 0: 
	ndists= (params.max_sep-params.min_sep)/params.inc_sep+1
else:
	ndists= 1

if params.inc_angle is not 0: 
	nangles= (params.max_angle-params.min_angle)/params.inc_angle+1
else:
	nangles= 1

print("ndists={} nangles={}".format(ndists,nangles))

with open("slurm","w") as jobsfile:
	jobsfile.write("g++ -std=c++11 -Iinclude spheres.cpp -o try -lgmsh\n")

for dist_idx in range(0,ndists):
	dist= params.min_sep+dist_idx*params.inc_sep

	for ang_idx in range(0,nangles):
		ang= params.min_angle+ang_idx*params.inc_angle
		with open("slurm","a") as jobsfile:
			jobsfile.write("python createDirPlusSU2.py 1 6 {} {}\n".format(dist,ang))
			jobsfile.write("cd data/dia_1_len_6_sep_{}_ang_{}\n".format(dist,ang))
			jobsfile.write("../.././try 1 6 {} {}\n".format(dist,ang))
			jobsfile.write("parallel_computation.py -n 1 -f lam_sphere_2body.cfg\n\n")
