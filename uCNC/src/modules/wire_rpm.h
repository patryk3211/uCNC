#ifndef WIRE_RPM_H
#define WIRE_RPM_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "../module.h"

	DECL_MODULE(wire_rpm);

  extern uint16_t wire_rpm_get_speed();

#ifdef __cplusplus
}
#endif

#endif
