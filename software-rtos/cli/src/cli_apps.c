#include "cli_apps.h"

const CLI_Command_Definition_t __CLI_Command_Motor = {
	"motor",
	"motor <index> <power>: set motor power [-1; 1] in open-loop\n",
	__CLI_Callback_Motor,
	2
};

BaseType_t __CLI_Callback_Motor(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
	(void)pcWriteBuffer;
	(void)xWriteBufferLen;
	(void)pcCommandString;

	return pdFALSE;
}