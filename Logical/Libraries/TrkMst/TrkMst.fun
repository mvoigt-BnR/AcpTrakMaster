
FUNCTION_BLOCK tmCore
	VAR_INPUT
		Enable : BOOL;
		ErrorRest : BOOL;
		Assembly : REFERENCE TO McAssemblyType;
		ShuttleMon : REFERENCE TO McAcpTrakAssemblyMonData;
	END_VAR
	VAR_OUTPUT
		Error : BOOL;
		ErrorID : tmCoreErrorEnum;
		Active : BOOL;
		SvgContent : STRING[tmCORE_MAX_STR_LEN];
		SvgTransform : STRING[tmCORE_MAX_STR_LEN];
		StrLengths : tmCoreSvgLengthsTyp;
		Handle : UDINT;
	END_VAR
	VAR
		Internal : tmCoreInternalTyp;
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK tmShuttleControl
	VAR_INPUT
		Enable : BOOL;
		Handle : UDINT;
		SelectedElem : STRING[80];
		ElasticMoveAbs : BOOL;
		Parameters : REFERENCE TO tmShuttleControlParsTyp;
	END_VAR
	VAR_OUTPUT
		Active : BOOL;
		MovementActive : BOOL;
		MovementDone : BOOL;
		ShInfo : McAcpTrakShInfoType;
		Error : BOOL;
		ErrorID : DINT;
		Valid : BOOL;
	END_VAR
	VAR
		Internal : tmShuttleControlInternalTyp;
	END_VAR
END_FUNCTION_BLOCK
