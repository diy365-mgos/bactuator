#include "mgos.h"
#include "mg_bactuator_sdk.h"
#include "mgos_bactuator.h"

#ifdef MGOS_HAVE_MJS
#include "mjs.h"
#endif

mgos_bthing_t MGOS_BACTUATOR_THINGCAST(mgos_bactuator_t actuator) {
  return MG_BTHING_ACTU_CAST5(MG_BACTUATOR_CAST1(actuator));
}

mgos_bsensor_t MGOS_BACTUATOR_DOWNCAST(mgos_bactuator_t actuator) {
  return (mgos_bsensor_t)MG_BTHING_ACTU_CAST3(MG_BACTUATOR_CAST1(actuator));
}

mgos_bactuator_t mgos_bactuator_create(const char *id, enum mgos_bthing_pub_state_mode pub_state_mode) {
  mgos_bactuator_t MG_BACTUATOR_NEW(actu);
  if (mg_bthing_init(MG_BTHING_ACTU_CAST4(actu), id, MGOS_BACTUATOR_TYPE, pub_state_mode)) {
    struct mg_bactuator_cfg *cfg = calloc(1, sizeof(struct mg_bactuator_cfg));
    if (cfg) {
      if (mg_bactuator_init(actu, cfg)) {
        LOG(LL_INFO, ("bActuator '%s' successfully created.", id));
        return actu;
      }
      mg_bthing_reset(MG_BTHING_ACTU_CAST4(actu));
      free(cfg);
    } else {
      LOG(LL_ERROR, ("Unable to allocate memory for 'mg_bsensor_cfg'"));
    }
  }
  free(actu);
  LOG(LL_ERROR, ("Error creating bActuator '%s'. See above error message for more details.'", (id ? id : "")));
  return NULL; 
}

bool mgos_bactuator_init() {
  return true;
}