#pragma once

#include "resource.h"

#define IDT_UPDATE_TIMER 1001	// completely arbitrary

#define MSG_TRAY_ICON   (WM_APP + 1)
#define MSG_LIST_NOTIFY (WM_APP + 2)
#define MSG_ITEM_NOTIFY (WM_APP + 3)
#define MSG_UPD_NOTIFY  (WM_APP + 4)
#define MSG_SHOW_NOTIFY (WM_APP + 5)
#define MSG_UNREAD		(WM_APP + 6)