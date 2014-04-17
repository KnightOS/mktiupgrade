#include <stdlib.h>
#include "devices.h"

char *device_type_str(device_type_t type) {
	switch (type) {
		case TI73:
			return "TI-73";
		case TI83p:
			return "TI-83+";
		case TI83pSE:
			return "TI-83+ Silver Edition";
		case TI84p:
			return "TI-84+";
		case TI84pSE:
			return "TI-84+ Silver Edition";
		case TI84pCSE:
			return "TI-84+ Color Silver Edition";
	}
	return NULL;
}
