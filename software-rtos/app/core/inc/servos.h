#ifndef SERVOS_H
#define SERVOS_H

#include <stdint.h>

void servos_init();

void servos_set_signal_us(uint16_t *);
void servos_set_state(uint8_t *);

#endif
