(*Track Master Core Types*)

TYPE
	tmCoreInternalTyp : 	STRUCT  (*Internal Datatype*)
		TypeID : UDINT; (*TypeID to help with handle application*)
		State : USINT; (*State of execution*)
		Axes : ARRAY[0..tmMAX_SHUTLE_ARRAY]OF tmCoreAxisLookupTyp; (*Axis Lookup table based on the current Shuttle Index*)
		Fbs : tmCoreFbTyps;
		ShCount : USINT;
	END_STRUCT;
	tmCoreStateEnum : 
		(
		tmCORE_OFF, (*Waiting for enable command*)
		tmCORE_INIT, (*Initialization state*)
		tmCORE_GET_SH, (*Get the shuttle in the assembly*)
		tmCORE_GET_NEXT, (*Set the next command*)
		tmCORE_RUNNING, (*Running state*)
		tmCORE_RESET,
		tmCORE_ERROR (*Error state*)
		);
	tmCoreErrorEnum : 
		(
		tmCORE_ERR_OK := 0,
		tmCORE_ERR_INVALID_ASSEMBLY := -61000,
		tmCORE_ERR_SH_COUNT_EXCEEDED
		);
	tmCoreSvgLengthsTyp : 	STRUCT 
		ContentLength : UDINT;
		TransformLength : UDINT;
	END_STRUCT;
	tmCoreFbTyps : 	STRUCT 
		AsmGetShuttle : MC_BR_AsmGetShuttle_AcpTrak;
	END_STRUCT;
	tmCoreAxisLookupTyp : 	STRUCT 
		Present : BOOL;
		Axis : McAxisType;
	END_STRUCT;
END_TYPE

(*Track Master Shuttle Control Types*)

TYPE
	tmShuttleControlParsTyp : 	STRUCT 
		Position : LREAL;
		Vel : REAL;
		Accel : REAL;
		Decel : REAL;
	END_STRUCT;
	tmShuttleControlInternalTyp : 	STRUCT 
		State : tmShuttleControlStatesEnum;
		CoreInt : REFERENCE TO tmCoreInternalTyp;
		CurrentAxis : McAxisType;
		Fbs : tmShuttleControlFbTyp;
		Idx : USINT;
	END_STRUCT;
	tmShuttleControlFbTyp : 	STRUCT 
		ShGetInfo : MC_BR_ShReadInfo_AcpTrak;
		ElMoveAbs : MC_BR_ElasticMoveAbs_AcpTrak;
	END_STRUCT;
	tmShuttleControlErrorEnum : 
		(
		tmSH_CONTROL_ERR_OK := 0, (*No error currently*)
		tmSH_CONTROL_WARN_SH_NOT_AVAIL := -52000, (*Shuttle Currently not listed as available*)
		tmSH_CONTROL_WARN_NO_ELEM_FND := -52001, (*Input selected element did not return a shuttle*)
		tmSH_CONTROL_ERR_INVALID_HANDLE := -62000, (*Invalid input handle*)
		tmSH_CONTROL_ERR_EL_MOVE := -62001
		);
	tmShuttleControlStatesEnum : 
		(
		tmSH_CONTROL_OFF,
		tmSH_CONTROL_INIT,
		tmSH_CONTROL_IDLE,
		tmSH_CONTROL_EL_MOVE_ABS,
		tmSH_CONTROL_MOVE_DONE,
		tmSH_CONTROL_GET_SH_DATA,
		tmSH_CONTROL_ERROR
		);
END_TYPE
