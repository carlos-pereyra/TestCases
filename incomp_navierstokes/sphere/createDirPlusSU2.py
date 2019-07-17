import os,sys

diameter= sys.argv[1]
length= sys.argv[2]
separation= sys.argv[3]
angle= sys.argv[4]

storage_path=os.environ['LUST2']+"/data/dia_"+diameter+"_len_"+length+"_sep_"+separation+"_ang_"+angle+"/"
path_exists_bool= os.path.exists(storage_path)

if path_exists_bool is not True:
	os.makedirs(storage_path)
   
os.chdir(storage_path)
	
with open("comp_lam_sphere.cfg",'w') as meshfile:
       	meshfile.write("% ------------- DIRECT, ADJOINT, AND LINEARIZED PROBLEM DEFINITION ------------%\n")
	meshfile.write("PHYSICAL_PROBLEM= NAVIER_STOKES\n")
	meshfile.write("KIND_TURB_MODEL= NONE\n")
	meshfile.write("MATH_PROBLEM= DIRECT\n")
	meshfile.write("RESTART_SOL= NO\n")
       	meshfile.write("% -------------------- COMPRESSIBLE FREE-STREAM DEFINITION --------------------%\n")
       	meshfile.write("MACH_NUMBER= 0.1\n")
	meshfile.write("AOA= 0.0\n")
	meshfile.write("FREESTREAM_TEMPERATURE= 288.15\n")
	meshfile.write("REYNOLDS_NUMBER= 50.0\n")
	meshfile.write("REYNOLDS_LENGTH= 1.0\n")
	meshfile.write("% ---------------------- REFERENCE VALUE DEFINITION ---------------------------%\n")
	meshfile.write("REF_ORIGIN_MOMENT_X = 0.25\n")
	meshfile.write("REF_ORIGIN_MOMENT_Y = 0.00\n")
	meshfile.write("REF_ORIGIN_MOMENT_Z = 0.00\n")
	meshfile.write("REF_LENGTH= 1.0\n")
	meshfile.write("REF_AREA= 1.0\n")
	meshfile.write("% -------------------- BOUNDARY CONDITION DEFINITION --------------------------%\n")
	meshfile.write("MARKER_ISOTHERMAL= ( shell1,0.0, shell2,0.0 )\n")
	meshfile.write("MARKER_FAR= ( far )\n")
	meshfile.write("MARKER_PLOTTING= ( shell1, shell2 )\n")
	meshfile.write("MARKER_MONITORING= ( shell1, shell2 )\n")
	meshfile.write("% ------------- COMMON PARAMETERS DEFINING THE NUMERICAL METHOD ---------------%\n")
	meshfile.write("NUM_METHOD_GRAD= WEIGHTED_LEAST_SQUARES\n")
	meshfile.write("CFL_NUMBER= 0.5\n")
	meshfile.write("CFL_ADAPT= NO\n")
	meshfile.write("CFL_ADAPT_PARAM= ( 1.5, 0.5, 0.6, 10.0 )\n")
	meshfile.write("RK_ALPHA_COEFF= ( 0.66667, 0.66667, 1.000000 )\n")
	meshfile.write("EXT_ITER= 99999\n")
	meshfile.write("% ------------------------ LINEAR SOLVER DEFINITION ---------------------------%\n")
	meshfile.write("LINEAR_SOLVER= FGMRES\n")	
	meshfile.write("LINEAR_SOLVER_PREC= LU_SGS\n")
	meshfile.write("LINEAR_SOLVER_ERROR= 1E-4\n")
	meshfile.write("LINEAR_SOLVER_ITER= 10\n")
	meshfile.write("% -------------------------- MULTIGRID PARAMETERS -----------------------------%\n")
	meshfile.write("MGLEVEL= 0\n")
	meshfile.write("MGCYCLE= V_CYCLE\n")
	meshfile.write("MG_PRE_SMOOTH= ( 1, 2, 3, 3 )\n")
	meshfile.write("MG_POST_SMOOTH= ( 0, 0, 0, 0 )\n")
	meshfile.write("MG_CORRECTION_SMOOTH= ( 0, 0, 0, 0 )\n")
	meshfile.write("MG_DAMP_RESTRICTION= 0.8\n")
	meshfile.write("MG_DAMP_PROLONGATION= 0.8\n")
	meshfile.write("% -------------------- FLOW NUMERICAL METHOD DEFINITION -----------------------%\n")
	meshfile.write("CONV_NUM_METHOD_FLOW= AUSMPLUSUP2\n")
	meshfile.write("MUSCL_FLOW= YES\n")
	meshfile.write("SLOPE_LIMITER_FLOW= VENKATAKRISHNAN\n")
	meshfile.write("VENKAT_LIMITER_COEFF= 10.0\n")
	meshfile.write("JST_SENSOR_COEFF= ( 0.5, 0.02 )\n")
	meshfile.write("TIME_DISCRE_FLOW= EULER_IMPLICIT\n")
	meshfile.write("% --------------------------- CONVERGENCE PARAMETERS --------------------------%\n")
	meshfile.write("CONV_CRITERIA= RESIDUAL\n")
	meshfile.write("RESIDUAL_REDUCTION= 6\n")
	meshfile.write("RESIDUAL_MINVAL= -12\n")
	meshfile.write("STARTCONV_ITER= 10\n")
	meshfile.write("CAUCHY_ELEMS= 100\n")
	meshfile.write("CAUCHY_EPS= 1E-6\n")
	meshfile.write("CAUCHY_FUNC_FLOW= DRAG\n")
	meshfile.write("% ------------------------- INPUT/OUTPUT INFORMATION --------------------------%\n")
	meshfile.write("MESH_FILENAME= mesh_sphere.su2\n")
	meshfile.write("MESH_FORMAT= SU2\n")
	meshfile.write("MESH_OUT_FILENAME= mesh_out.su2\n")
	meshfile.write("SOLUTION_FLOW_FILENAME= solution_flow.dat\n")
	meshfile.write("SOLUTION_ADJ_FILENAME= solution_adj.dat\n")
	meshfile.write("OUTPUT_FORMAT= PARAVIEW\n")
	meshfile.write("CONV_FILENAME= history\n")
	meshfile.write("RESTART_FLOW_FILENAME= restart_flow.dat\n")
	meshfile.write("RESTART_ADJ_FILENAME= restart_adj.dat\n")
	meshfile.write("VOLUME_FLOW_FILENAME= flow\n")
	meshfile.write("VOLUME_ADJ_FILENAME= adjoint\n")
	meshfile.write("GRAD_OBJFUNC_FILENAME= of_grad.dat\n")
	meshfile.write("SURFACE_FLOW_FILENAME= surface_flow\n")
	meshfile.write("SURFACE_ADJ_FILENAME= surface_adjoint\n")
	meshfile.write("WRT_SOL_FREQ= 100\n")
	meshfile.write("WRT_CON_FREQ= 1\n")
