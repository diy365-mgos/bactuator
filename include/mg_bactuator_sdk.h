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

#ifndef MG_BACTUATOR_SDK_H_
#define MG_BACTUATOR_SDK_H_

#include <stdbool.h>
#include "mg_bthing_sdk.h"
#include "mg_bsensor_sdk.h"
#include "mgos_bactuator.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MG_BACTUATOR_NEW(a) MG_BTHING_ACTU_NEW(a);

/*****************************************
 * Cast Functions
 */

// Convert (mgos_bactuator_t) into (struct mg_bthing_actu *)
struct mg_bthing_actu *MG_BACTUATOR_CAST1(mgos_bactuator_t thing);
/*****************************************/

#define MG_BACTUATOR_CFG(s) ((struct mg_bactuator_cfg *)MG_BACTUATOR_CAST1(s)->cfg)

struct mg_bactuator_base_class {
  mg_bthing_setting_state_handler_t setting_state_cb;
};

struct mg_bactuator_cfg {
  struct mg_bactuator_base_class base_class; 
};

bool mg_bactuator_init(struct mg_bthing_actu *actu);

void mg_bactuator_reset(struct mg_bthing_actu *actu);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MG_BACTUATOR_SDK_H_ */