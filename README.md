# bActuators Library
## Overview
A *bActuator* offers a common set of APIs for managing any kind of physical actuator. This allows your firmware interacting with actuators without take care of their hardware caratteristics.

![bActuator blocks diagram](docs/bactuator_blocks_diagram.png)
## Features
- **Universal value-types** - You can set or read any actuator state value within the supported [bVariant](https://github.com/diy365-mgos/bvar) data-types.
<!-- - **GPIO as actuators** - You can easily read and write GPIO as actuators. Just include the [bThings GPIO Library](https://github.com/diy365-mgos/bthing-gpio) in your project. -->
## Get Started
Include the library in your `mos.yml` file.
```yaml
libs:
  - origin: https://github.com/diy365-mgos/bactuator
```
**C/C++ firmware samples** - Copy and paste one of the following examples in your `main.c` project file.

Example #1 - Create a *bActuator* for setting a GPIO value.
```c
```
## C/C++ APIs Reference
### Inherited *bThing* APIs
A *bActuator* inherits [bThing](https://github.com/diy365-mgos/bthing) APIs.
- [mgos_bthing_get_id()](https://github.com/diy365-mgos/bthing#mgos_bthing_get_id)
- [mgos_bthing_on_get_state](https://github.com/diy365-mgos/bthing#mgos_bthing_on_get_state)
- [mgos_bthing_get_state()](https://github.com/diy365-mgos/bthing#mgos_bthing_get_state)
- [mgos_bthing_on_set_state](https://github.com/diy365-mgos/bthing#mgos_bthing_on_set_state)
- [mgos_bthing_set_state()](https://github.com/diy365-mgos/bthing#mgos_bthing_set_state)
- All other [bThings Core Library](https://github.com/diy365-mgos/bthing) APIs...
### Inherited *bSensor* APIs
A *bActuator* inherits [bSensor](https://github.com/diy365-mgos/bsensor) APIs.
- [mgos_bsensor_polling_set](https://github.com/diy365-mgos/bsensor#mgos_bsensor_polling_set)

*WARNING*: [mgos_bsensor_interrupt_set()](https://github.com/diy365-mgos/bsensor#mgos_bsensor_interrupt_set) doesn't support *bActuators*. If invoked passing a *bActuator* it returns `false`.
### MGOS_BACTUATOR_THINGCAST
```c
mgos_bthing_t MGOS_BACTUATOR_THINGCAST(mgos_bactuator_t actuator);
```
Casts a *bActuator* to a generic *bThing* to be used with [inherited bThing APIs](#inherited-bthing-apis).

|Parameter||
|--|--|
|sensor|A *bActuator*.|

Example:
```c
mgos_bactuator_t actu = mgos_bactuator_create(...);
printf("Actuator %s successfully created", mgos_bthing_get_id(MGOS_BACTUATOR_THINGCAST(actu)));
```
### MGOS_BACTUATOR_DOWNCAST
```c
mgos_bsensor_t MGOS_BACTUATOR_DOWNCAST(mgos_bactuator_t actuator);
```
Casts a *bActuator* to a *bSensor* to be used with [inherited bSensor APIs](#inherited-bsensor-apis).

|Parameter||
|--|--|
|actuator|A *bActuator*.|

Example:
```c
mgos_bactuator_t actu = mgos_bactuator_create(...);
mgos_bsensor_interrupt_set(MGOS_BACTUATOR_DOWNCAST(actu), gpio_pin,
  MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_ANY, 50);
```
### mgos_bactuator_create
```c
mgos_bactuator_t mgos_bactuator_create(const char *id, enum mgos_bthing_notify_state notify_state);
```
Creates a *bActuator*. Returns `NULL` on error.

|Parameter||
|--|--|
|id|The *bActuator* ID.|
|notify_state|The [notify-state mode](https://github.com/diy365-mgos/bthing#enum-mgos_bthing_notify_state).|
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).