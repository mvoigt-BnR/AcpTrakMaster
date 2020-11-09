/* Automation Studio generated header file */
/* Do not edit ! */
/* LoggingLib 2.30.1 */

#ifndef _LOGGINGLIB_
#define _LOGGINGLIB_
#ifdef __cplusplus
extern "C" 
{
#endif
#ifndef _LoggingLib_VERSION
#define _LoggingLib_VERSION 2.30.1
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
#ifdef _SG4
		#include "runtime.h"
		#include "asstring.h"
		#include "snprintf.h"
		#include "ArEventLog.h"
		#include "AsTCP.h"
		#include "astime.h"
		#include "FileIO.h"
#endif
#ifdef _SG3
		#include "runtime.h"
		#include "asstring.h"
		#include "snprintf.h"
		#include "ArEventLog.h"
		#include "AsTCP.h"
		#include "astime.h"
		#include "FileIO.h"
#endif
#ifdef _SGC
		#include "runtime.h"
		#include "asstring.h"
		#include "snprintf.h"
		#include "ArEventLog.h"
		#include "AsTCP.h"
		#include "astime.h"
		#include "FileIO.h"
#endif

/* Constants */
#ifdef _REPLACE_CONST
 #define LOGGING_MAX_ARGUMENTS 8U
#else
 _GLOBAL_CONST unsigned char LOGGING_MAX_ARGUMENTS;
#endif




/* Datatypes and datatypes of function blocks */
typedef enum LogStatus
{	LOG_OK,
	LOG_NOT_VALID,
	LOG_ILLEGAL_LEVEL,
	LOG_INVALID_ARGUMENTS,
	LOG_DUPLICATE,
	LOG_BUSY = 65535
} LogStatus;

typedef enum LogLevel
{	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_FATAL
} LogLevel;

typedef enum ClientStatus_typ
{	CLIENT_NOT_USED,
	CLIENT_PENDING,
	CLIENT_SENDING,
	CLIENT_DONE,
	CLIENT_DROPPING
} ClientStatus_typ;

typedef enum AS_LOGGER_ERRORS
{	ASLOGGER_INTERNAL_ERROR = 30000,
	ASLOGGER_ILLEGAL_FILENAME = 33000,
	ASLOGGER_ILLEGAL_DEVICENAME
} AS_LOGGER_ERRORS;

typedef enum AS_FILE_LOGGER_STATE
{	AS_FILE_LOGGER_STATE_W_ENABLE,
	AS_FILE_LOGGER_STATE_MOVE_FILES,
	AS_FILE_LOGGER_STATE_DELETE_OLD,
	AS_FILE_LOGGER_STATE_CREATE_FILE,
	AS_FILE_LOGGER_STATE_MARSHALL,
	AS_FILE_LOGGER_STATE_OPEN,
	AS_FILE_LOGGER_STATE_WRITE,
	AS_FILE_LOGGER_STATE_CLOSE,
	AS_FILE_LOGGER_STATE_ERROR = 255
} AS_FILE_LOGGER_STATE;

typedef struct LoggerClient_typ
{	unsigned long ident;
	plcstring ipAddress[16];
	unsigned short port;
	enum ClientStatus_typ status;
	unsigned char wouldBlockCount;
	struct TcpClose close;
	struct TcpSend send;
} LoggerClient_typ;

typedef struct AsLoggerServerInternal_typ
{	unsigned char state;
	unsigned long ident;
	struct TcpOpen open;
	struct TcpClose close;
	struct TcpServer server;
	unsigned char clientsActive;
	struct LoggerClient_typ clients[8];
	unsigned short outputIndex;
	plcstring sendBuffer[5001];
	unsigned short sendBufferUsed;
} AsLoggerServerInternal_typ;

typedef struct AsLoggerFileInternal_typ
{	enum AS_FILE_LOGGER_STATE state;
	unsigned char fileNumber;
	unsigned long fileOffset;
	plcstring tempFileName[81];
	plcstring oldFileName[81];
	plcstring newFileName[81];
	plcstring tempString[501];
	unsigned short outputIndex;
	struct FileCreate FileCreate_0;
	struct FileOpen FileOpen_0;
	struct FileClose FileClose_0;
	struct FileWrite FileWrite_0;
	struct FileCopy FileCopy_0;
	struct FileDelete FileDelete_0;
	plcstring writeBuffer[10001];
	unsigned short writeBufferUsed;
} AsLoggerFileInternal_typ;

typedef struct AsLoggerLogBookInternal_typ
{	unsigned short outputIndex;
	struct ArEventLogWrite ArEventLogWrite_0;
	struct ArEventLogGetIdent ArEventLogGetIdent_0;
	plcbit outputIndexRegistered;
} AsLoggerLogBookInternal_typ;

typedef struct AsLoggerServer
{
	/* VAR_INPUT (analog) */
	unsigned short port;
	enum LogLevel level;
	/* VAR_OUTPUT (analog) */
	unsigned short status;
	/* VAR (analog) */
	struct AsLoggerServerInternal_typ internal;
	/* VAR_INPUT (digital) */
	plcbit disconnect;
} AsLoggerServer_typ;

typedef struct AsLoggerFile
{
	/* VAR_INPUT (analog) */
	plcstring device[81];
	plcstring fileName[81];
	unsigned long maxFileSize;
	unsigned char maxFiles;
	plcstring delimiter[3];
	plcstring fileExtension[5];
	enum LogLevel level;
	/* VAR_OUTPUT (analog) */
	unsigned short status;
	/* VAR (analog) */
	struct AsLoggerFileInternal_typ internal;
	/* VAR_INPUT (digital) */
	plcbit enable;
} AsLoggerFile_typ;

typedef struct AsLoggerLogBook
{
	/* VAR_INPUT (analog) */
	enum LogLevel level;
	/* VAR_OUTPUT (analog) */
	unsigned short status;
	/* VAR (analog) */
	struct AsLoggerLogBookInternal_typ internal;
} AsLoggerLogBook_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void AsLoggerServer(struct AsLoggerServer* inst);
_BUR_PUBLIC void AsLoggerFile(struct AsLoggerFile* inst);
_BUR_PUBLIC void AsLoggerLogBook(struct AsLoggerLogBook* inst);
_BUR_PUBLIC LogStatus logDebug(plcstring* name, plcstring* message, unsigned long pMsgData);
_BUR_PUBLIC LogStatus logInfo(plcstring* name, plcstring* message, unsigned long pMsgData);
_BUR_PUBLIC LogStatus logWarn(plcstring* name, plcstring* message, unsigned long pMsgData);
_BUR_PUBLIC LogStatus logError(plcstring* name, plcstring* message, unsigned long pMsgData);
_BUR_PUBLIC LogStatus logFatal(plcstring* name, plcstring* message, unsigned long pMsgData);
_BUR_PUBLIC unsigned long AsLoggerGetLastMessage(void);


#ifdef __cplusplus
};
#endif
#endif /* _LOGGINGLIB_ */

