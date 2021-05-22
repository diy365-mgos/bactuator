#include "mgos.h"
#include "mg_bactuator_sdk.h"


/*****************************************
 * Cast Functions
 */

// Convert (mgos_bactuator_t) into (struct mg_bthing_actu *)
struct mg_bthing_actu *MG_BACTUATOR_CAST1(mgos_bactuator_t thing) {
  return (struct mg_bthing_actu *)thing;
}
/*****************************************/

bool mg_bactuator_init(mgos_bactuator_t actu,
                       struct mg_bsensor_cfg *sens_cfg,
                       struct mg_bactuator_cfg *actu_cfg) {
  if (sens_cfg && actu_cfg) {
    if (mg_bsensor_init(MG_BTHING_ACTU_CAST3(actu), sens_cfg)) {
      if (mg_bthing_actu_init(actu, actu_cfg)) {
        /* initalize overrides cfg */
        actu_cfg->overrides.setting_state_cb = NULL;

        return true;
      }
    }
    mg_bactuator_reset(actu);
  } else {
    LOG(LL_ERROR, ("Invalid NULL 'sens_cfg' or 'actu_cfg' parameter."));
  }

  LOG(LL_ERROR, ("Error initializing bActuator '%s'. See above error message for more details.", 
    mgos_bthing_get_id(MGOS_BACTUATOR_THINGCAST(actu))));
  return false; 
}

void mg_bactuator_reset(mgos_bactuator_t actu) {
  struct mg_bactuator_cfg *cfg = MG_BACTUATOR_CFG(actu);

  /* clear overrides cfg */
  if (cfg->overrides.setting_state_cb) {
    mg_bthing_on_setting_state(actu, cfg->overrides.setting_state_cb);
    cfg->overrides.setting_state_cb = NULL;
  }
  
  mg_bthing_actu_reset(MG_BACTUATOR_CAST1(actu));
  mg_bsensor_reset(MG_BTHING_ACTU_CAST3(MG_BACTUATOR_CAST1(actu)));
}