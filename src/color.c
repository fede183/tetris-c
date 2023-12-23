#include "classes/color.h"

enum point_color intToEnum(int value) {
	switch(value) {
		case blue:
			return blue;
		case violet:
			return violet;
		case red:
			return red;
		case green:
			return green;
		case yellow:
			return yellow;
		case light_blue:
			return light_blue;
		case orange:
			return orange;
		default:
			return medium_blue;
	
	}
}
