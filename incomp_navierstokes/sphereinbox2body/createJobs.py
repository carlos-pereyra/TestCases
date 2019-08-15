import os,sys,params, argparse

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

dirpath= args.dirpath

#from params
dia=params.min_dia
far=params.min_far

if params.inc_far is not 0: 
	nfar= int((params.max_far-params.min_far)/params.inc_far)+1
else:
	nfar= 1

if params.inc_node is not 0: 
	nnode= int((params.max_node-params.min_node)/params.inc_node)+1
else:
	nnode= 1

print("ndists={} nangles={}".format(ndists,nangles))

with open("job","w") as jobsfile:
	jobsfile.write("g++ -std=c++11 -Iinclude sphere2body.cpp -o run -lgmsh\n")

for far_idx in range(0,nfar):
	far= params.min_far+far_idx*params.inc_far

	for node_idx in range(0,nnode):
		node= params.min_node+node_idx*params.inc_node

		with open("job","a") as jobsfile:
			jobsfile.write("python createDirSlurm.py {} {} {}\n".format(dia,far,node))
			jobsfile.write("cd meshes/dia_{}_far_{}_nodes_{}\n".format(dia,far,node))
			jobsfile.write("../.././run {} {} {} {}\n".format(dia,far,dist,ang))
			jobsfile.write("cp ../../dataAnalysisScript.py .\n")
			jobsfile.write("cp ../../lam_sphere_inc.cfg .\n")
			jobsfile.write("cd ../..\n\n")

with open("job","a") as jobsfile:
        jobsfile.write("cd {}/\n".format(dirpath))
        jobsfile.write("cp ../params.py .\n")
        jobsfile.write("cd ../\n")
        jobsfile.close()
