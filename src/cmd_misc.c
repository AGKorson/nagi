/*
_Rand                            cseg     0000753E 0000002D
CmdGetNum                        cseg     0000756B 0000007E
CmdObjStatusV                    cseg     000075E9 00000066
CmdShowPriScrn                   cseg     0000764F 00000021
CmdVersion                       cseg     00007670 00000016
*/

#include "agi.h"
#include "ui/msg.h"

#include "sys/drv_video.h"
#include "sys/gfx.h"

#include "view/obj_base.h"

u8 *cmd_obj_status_v(u8 *c) {
	char msg[256];
	u8 objnum = state.var[*(c++)];
	VIEW* v;
	v = &objtable[objnum];

	if (v >= objtable_tail) {
		// agi doesn't catch invalid objects and will
		// display meaningless data; we display all -1s
		snprintf(msg, sizeof(msg),
			"Object %d:\n"
			"x: %d  xsize: %d\n"
			"y: %d  ysize: %d\n"
			"pri: %d\n"
			"stepsize: %d",
			objnum,
			-1, -1,
			-1, -1,
			-1,
			-1);
	}
	else {
		snprintf(msg, sizeof(msg),
			"Object %d:\n"
			"x: %d  xsize: %d\n"
			"y: %d  ysize: %d\n"
			"pri: %d\n"
			"stepsize: %d",
			v->num,
			v->x, v->x_size,
			v->y, v->y_size,
			v->priority,
			v->step_size);
	}
	message_box(msg);
	return c;
}

u8 *cmd_version(u8 *c)
{
	message_box("             NAGI\n"
		        "      By Nick Sonneveld\n\n"
		        "  Reimplements Sierra's AGI");
	message_box(*config_game[0].s.ptr);
	return c;
}

u8 *cmd_shake_screen(u8 *c)
{
	gfx_shake(*(c++));
	return c;
}
