/*
 * cli_conf.h
 *
 *  Created on: Feb 17, 2022
 *      Author: emozdzen
 */

#ifndef INC_CLI_CONF_H_
#define INC_CLI_CONF_H_

#define CLI_LINE_MAX_SIZE				256
#define CLI_LINE_TERMINATOR				'\r'

#define CLI_ARG_DELIMITERS				" \r\n"

#define CLI_PRINT_FORMAT_BUFFER_SIZE	1024
#define CLI_HELP_MESSAGE				"list of available commands:\n \
	help\n \
	reset\n \
	btconf\n \
		-n name       		str\n \
		-p password   		str\n \
	sett\n \
		-m mode:       		module | button | rc5 | bt\n \
		-d dyhlo color:		black | white | auto\n \
		-s strategy:		aggressive | defense | passive\n \
	prox\n \
		-i sensor index:	ll | fl | fr | rr | all\n \
	line\n \
		-i sensor index:	ll | lm | rm | rr | all\n \
	enc\n \
		-i sensor index:	lf | lb | rf | rb | all\n \
	mot\n \
		--get read\n \
		--set write\n \
		-i sensor index:	lf | lb | rf | rb | all\n \
		-v velocity [RPS]	float\n \
		-p position [R]		float\n"

#endif
