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

bool mg_bactuator_init(struct mg_bthing_actu *actu,
                       const char *id, int type, 
                       enum mgos_bthing_notify_state notify_state) {
  if (mg_bsensor_init(MG_BTHING_ACTU_CAST3(actu), id, (type | MGOS_BACTUATOR_TYPE), notify_state)) {
    struct mg_bactuator_cfg *cfg =  actu->cfg = calloc(1, sizeof(struct mg_bactuator_cfg));
    if (actu->cfg) {
      cfg->base_class.setting_state_cb = NULL;
      return true;
    }
    LOG(LL_ERROR, ("Error creating bActuator '%s': unable to allocate memory for 'mg_bactuator_cfg'", id));
    mg_bactuator_reset(actu);
  }
  return false; 
}

void mg_bactuator_reset(struct mg_bthing_actu *actu) {
  struct mg_bactuator_cfg *cfg = MG_BACTUATOR_CFG(actu);
  if (cfg->base_class.setting_state_cb) {
    mg_bthing_on_setting_state(actu, cfg->base_class.setting_state_cb);
    cfg->base_class.setting_state_cb = NULL;
  }
  
  mg_bsensor_reset(MG_BTHING_ACTU_CAST3(actu));
}
