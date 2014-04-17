#ifndef DEVICES_H
#define DEVICES_H

typedef enum {
    TI73 = 1,
    TI83p = 2,
    TI83pSE = 3,
    TI84p = 4,
    TI84pSE = 5,
    TI84pCSE = 6
} device_type_t;

char *device_type_str(device_type_t type);

#endif
