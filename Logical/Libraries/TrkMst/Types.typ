(*Track Master Core Types*)

TYPE
	tmCoreInternalTyp : 	STRUCT  (*Internal Datatype*)
		TypeID : UDINT; (*TypeID to help with handle application*)
		State : USINT; (*State of execution*)
		Axes : ARRAY[0..tmMAX_SHUTLE_ARRAY]OF tmCoreAxisLookupTyp; (*Axis Lookup table based on the current Shuttle Index*)
		Fbs : tmCoreFbTyps; (*Internal Function blocks*)
		ShCount : USINT; (*Shuttle Count*)
	END_STRUCT;
	tmCoreViewBoxCfgTyp : 	STRUCT  (*Attributes of the SVG's viewbox*)
		MinX : REAL; (*Minimum x position*)
		MinY : REAL; (*minimum y position*)
		Width : REAL; (*Width of viewbox*)
		Height : REAL; (*Height of viewbox*)
	END_STRUCT;
	tmCoreStateEnum : 
		( (*State of execution*)
		tmCORE_OFF, (*Waiting for enable command*)
		tmCORE_INIT, (*Initialization state*)
		tmCORE_GET_SH, (*Get the shuttle in the assembly*)
		tmCORE_GET_NEXT, (*Set the next command*)
		tmCORE_RUNNING, (*Running state*)
		tmCORE_RESET, (*Resetting state*)
		tmCORE_ERROR (*Error state*)
		);
	tmCoreErrorEnum : 
		( (*Error Enumeration*)
		tmCORE_ERR_OK := 0, (*No error present*)
		tmCORE_ERR_INVALID_ASSEMBLY := -61000, (*Invalid input assembly reference*)
		tmCORE_ERR_SH_COUNT_EXCEEDED := -61001, (*Maximum shuttle count exceeded. Need to increase max shuttle count constant*)
		tmCORE_ERR_STR_LEN_EXCEEDED := -61002 (*The built string is too long, need to increase the maximum size to prevent page faulting*)
		);
	tmCoreSvgLengthsTyp : 	STRUCT  (*String lengths of SVGs*)
		ContentLength : UDINT; (*String Length of SVG Content string*)
		TransformLength : UDINT; (*String Length of SVG Transform string*)
	END_STRUCT;
	tmCoreFbTyps : 	STRUCT  (*Internal Function blocks*)
		AsmGetShuttle : MC_BR_AsmGetShuttle_AcpTrak;
	END_STRUCT;
	tmCoreAxisLookupTyp : 	STRUCT  (*Lookup table datatype*)
		Present : BOOL; (*Axis is present and a valid reference exists*)
		Axis : McAxisType; (*Axis information*)
	END_STRUCT;
END_TYPE

(*Track Master Shuttle Control Types*)

TYPE
	tmShuttleControlParsTyp : 	STRUCT  (*Input parameters for Shuttle Control*)
		Position : LREAL; (*Destination position for Absolute and Velocity commands*)
		Distance : LREAL; (*Distance for all relative commands*)
		Vel : REAL; (*Comanded Movement velocity*)
		Accel : REAL; (*Comanded Movement acceleration*)
		Decel : REAL; (*Comanded Movement deceleration*)
	END_STRUCT;
	tmShuttleControlInternalTyp : 	STRUCT  (*Internal data type*)
		State : tmShuttleControlStatesEnum; (*State of execution*)
		CoreInt : REFERENCE TO tmCoreInternalTyp; (*Internal data for the Core function block*)
		CurrentAxis : McAxisType; (*Current selected Axis*)
		Fbs : tmShuttleControlFbTyp; (*Internal function blocks*)
		Idx : USINT; (*Selected Index for the axis lookup table*)
		LastIdx : USINT; (*Last cycle selected index for the axis lookup table*)
	END_STRUCT;
	tmShuttleControlFbTyp : 	STRUCT  (*Internal Function Blocks*)
		ShGetInfo : MC_BR_ShReadInfo_AcpTrak; (*Shuttle Get info*)
		ElMoveAbs : MC_BR_ElasticMoveAbs_AcpTrak; (*Elastic move absolute command*)
		ElMoveAdd : MC_BR_ElasticMoveAdd_AcpTrak; (*Elastic move addtive command*)
	END_STRUCT;
	tmShuttleControlErrorEnum : 
		( (*Error enumeration*)
		tmSH_CONTROL_ERR_OK := 0, (*No error currently*)
		tmSH_CONTROL_WARN_SH_NOT_AVAIL := -52000, (*Shuttle Currently not listed as available*)
		tmSH_CONTROL_WARN_NO_ELEM_FND := -52001, (*Input selected element did not return a shuttle*)
		tmSH_CONTROL_ERR_INVALID_HANDLE := -62000, (*Invalid input handle*)
		tmSH_CONTROL_ERR_EL_MOVE := -62001 (*Error in an elastic movment*)
		);
	tmShuttleControlStatesEnum : 
		( (*State of execution*)
		tmSH_CONTROL_OFF, (*Off State*)
		tmSH_CONTROL_INIT, (*Init/Waiting for valid ShElement state*)
		tmSH_CONTROL_IDLE, (*Idle waiting for a command state*)
		tmSH_CONTROL_EL_MOVE_ABS, (*Move Elastic absoulte active state*)
		tmSH_CONTROL_EL_MOVE_ADD, (*Move Elastic Additive active state*)
		tmSH_CONTROL_MOVE_DONE, (*Move has completed*)
		tmSH_CONTROL_ERROR (*Error present on the FB*)
		);
END_TYPE
