
FUNCTION_BLOCK tmCore (*Core Track Master Function Block*)
	VAR_INPUT
		Enable : BOOL; (*Enables the core functionality*)
		ErrorRest : BOOL; (*Reset any present errors*)
		Assembly : REFERENCE TO McAssemblyType; (*Assembly reference to monitor*)
		ShuttleMon : REFERENCE TO McAcpTrakAssemblyMonData; (*Shuttle Monitor structure for the assembly*)
		ViewBoxCfg : tmCoreViewBoxCfgTyp; (*View box configuration for the SVG*)
	END_VAR
	VAR_OUTPUT
		Error : BOOL; (*Error present on FB*)
		ErrorID : tmCoreErrorEnum; (*Error ID of current error*)
		Active : BOOL; (*Function block is active*)
		SvgContent : STRING[tmCORE_MAX_STR_LEN]; (*SVG Content string to tie to a Paper widget*)
		SvgTransform : STRING[tmCORE_MAX_STR_LEN]; (*SVG Transform string to tie to a paper widget*)
		StrLengths : tmCoreSvgLengthsTyp; (*Diagnostic viewer to see current lengths of SVG Content/Transform*)
		Handle : UDINT; (*Handle used for other Track Master Function Blocks*)
	END_VAR
	VAR
		Internal : tmCoreInternalTyp; (*Internal data type*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK tmShuttleControl (*Shuttle Control Function Block*)
	VAR_INPUT
		Enable : BOOL; (*Enables the shuttle controller*)
		Handle : UDINT; (*Handle of the Core Track Master Function Block*)
		SelectedElem : STRING[80]; (*Selected Element String that is populated from a Paper Widget*)
		ElasticMoveAbs : BOOL; (*Command to send shuttle on Elastic Move Absolute*)
		Parameters : REFERENCE TO tmShuttleControlParsTyp; (*Parameters for movement commands*)
	END_VAR
	VAR_OUTPUT
		Active : BOOL; (*Function block is currently Active*)
		MovementActive : BOOL; (*Controlled Shuttle is currently moving*)
		MovementDone : BOOL; (*Controlled Shuttle has completed movement*)
		Valid : BOOL; (*Input Selected Element is a valid controllable shuttle*)
		ShInfo : McAcpTrakShInfoType; (*Selected shuttle's current info. Only is Valid when Valid flag is set*)
		Error : BOOL; (*Error Present on FB*)
		ErrorID : DINT; (*Error ID of current Error*)
	END_VAR
	VAR
		Internal : tmShuttleControlInternalTyp; (*Internal data type*)
	END_VAR
END_FUNCTION_BLOCK
