#ifndef __HMNWCTYPES_H__
#define __HMNWCTYPES_H__

enum ENUMHMNWCCONNECTSTATETYPE {
	EHMNWC_CONNSTATE_UNKNOWN = -1,
	EHMNWC_CONNSTATE_CONNECTING = 0,
	EHMNWC_CONNSTATE_CONNECTED,
	EHMNWC_CONNSTATE_DISCONNECTING,
	EHMNWC_CONNSTATE_DISCONNECTED,
};

#endif //__HMNWCTYPES_H__