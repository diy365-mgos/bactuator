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

bool mg_bactuator_init(mgos_bactuator_t actu) {
  if (mg_bsensor_init(MG_BTHING_ACTU_CAST3(actu))) {
    if (mg_bthing_actu_init(actu)) {
      struct mg_bactuator_cfg *cfg = actu->cfg = calloc(1, sizeof(struct mg_bactuator_cfg));
      if (actu->cfg) {
        /* initalize base-class cfg */
        cfg->overrides.setting_state_cb = NULL;
        return true;
      }
      LOG(LL_ERROR, ("Unable to allocate memory for 'mg_bactuator_cfg'"));
    }
    mg_bactuator_reset(actu);
  }
  LOG(LL_ERROR, ("Error creating bActuator '%s'. See above error message for more details.", 
    mgos_bthing_get_id(MGOS_BACTUATOR_THINGCAST(actu))));
  return false; 
}

void mg_bactuator_reset(mgos_bactuator_t actu) {
  struct mg_bactuator_cfg *cfg = MG_BACTUATOR_CFG(actu);

  /* clear base-class cfg */
  if (cfg->overrides.setting_state_cb) {
    mg_bthing_on_setting_state(actu, cfg->overrides.setting_state_cb);
    cfg->overrides.setting_state_cb = NULL;
  }
  
  mg_bthing_actu_reset(MG_BACTUATOR_CAST1(actu));
  mg_bsensor_reset(MG_BTHING_ACTU_CAST3(MG_BACTUATOR_CAST1(actu)));
}
