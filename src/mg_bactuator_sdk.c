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
                       struct mg_bactuator_cfg *actu_cfg,
                       struct mg_bsensor_cfg *sens_cfg) {
  if (actu_cfg) {
    // init sensor-base obj (if cfg is provided) and
    // init actuator-base obj
    if ((!sens_cfg || mg_bsensor_init(MG_BTHING_ACTU_CAST3(actu), sens_cfg)) &&
        mg_bthing_actu_init(actu, actu_cfg)) {
      /* initalize overrides cfg */
      actu_cfg->overrides.setting_state_cb = NULL;

      return true; // initialization successfully completed
    }
    mg_bactuator_reset(actu);
  } else {
    LOG(LL_ERROR, ("Invalid NULL 'actu_cfg' parameter."));
  }

  LOG(LL_ERROR, ("Error initializing bActuator '%s'. See above error message for more details.", 
    mgos_bthing_get_uid(MGOS_BACTUATOR_THINGCAST(actu))));
  return false; 
}

void mg_bactuator_reset(mgos_bactuator_t actu) {
  struct mg_bactuator_cfg *cfg = MG_BACTUATOR_CFG(actu);

  /* clear overrides cfg */
  if (cfg->overrides.setting_state_cb) {
    mg_bthing_on_setting_state(actu, cfg->overrides.setting_state_cb);
    cfg->overrides.setting_state_cb = NULL;
  }
  
  // reset actuator-base obj
  mg_bthing_actu_reset(MG_BACTUATOR_CAST1(actu));
  // reset sensor-base obj
  mg_bsensor_reset(MG_BTHING_ACTU_CAST3(MG_BACTUATOR_CAST1(actu)));
}