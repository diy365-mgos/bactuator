/*
 * Copyright (c) 2021 DIY356
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MGOS_BACTUATOR_H_
#define MGOS_BACTUATOR_H_

#include <stdbool.h>
#include "mgos_bthing.h"
#include "mgos_bsensor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MGOS_BACTUATOR_TYPE 256 // [][][][][][][][1]-[][][][][][][R[R]

struct mg_bthing_actu;
typedef struct mg_bthing_actu *mgos_bactuator_t;

mgos_bthing_t MGOS_BACTUATOR_THINGCAST(mgos_bactuator_t actuator);

mgos_bsensor_t MGOS_BACTUATOR_SENSCAST(mgos_bactuator_t actuator);

mgos_bactuator_t mgos_bactuator_create(const char *id, enum mgos_bthing_pub_state_mode pub_state_mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_BACTUATOR_H_ */