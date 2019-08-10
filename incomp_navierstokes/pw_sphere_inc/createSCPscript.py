import os,sys,params

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

open("job_scp","w")
for sep_idx in range(0,nseps):
	sep= params.min_sep+sep_idx*params.inc_sep
    
	for ang_idx in range(0,nangles):
		ang= params.min_angle+ang_idx*params.inc_angle
        
        for far_idx in range(0,nfar):
            far= params.min_far+far_idx*params.inc_far
            
            with open("job_scp","a") as jobsfile:
                #jobsfile.write("python createDirSlurm.py {} {} {} {}\n".format(dia,far,sep,ang))
                jobsfile.write("cd meshes/dia_{}_len_{}_sep_{}_ang_{}\n".format(dia,far,sep,ang))
                jobsfile.write("scp lam_sphere_inc.cfg pereyra3@catalyst.llnl.gov:/p/lustre1/pereyra3\n")
                jobsfile.write("cd ../..\n\n")

print("nseps={} nangles={} nfar={} DONE".format(nseps,nangles,nfar))
