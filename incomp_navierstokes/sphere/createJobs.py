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

with open("jobs","w") as jobsfile:
	jobsfile.write("g++ -std=c++11 -Iinclude sphere.cpp -o try -lgmsh\n")

for dist_idx in range(0,ndists):
	dist= params.min_sep+dist_idx*params.inc_sep

	for ang_idx in range(0,nangles):
		ang= params.min_angle+ang_idx*params.inc_angle
		with open("jobs","a") as jobsfile:
			jobsfile.write("python createDirPlusSU2.py {} {} {} {}\n".format(dia,far,dist,ang))
			jobsfile.write("cd data/dia_{}_len_{}_sep_{}_ang_{}\n".format(dia,far,dist,ang))
			jobsfile.write("../.././try {} {} {} {}\n".format(dia,far,dist,ang))
			#jobsfile.write("SU2_CFD lam_sphere.cfg\n")
			jobsfile.write("cd ../..\n\n")
