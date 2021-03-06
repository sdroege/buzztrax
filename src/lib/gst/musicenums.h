/* Buzztrax
 * Copyright (C) 2007 Stefan Kost <ensonic@users.sf.net>
 *
 * musicenums.h: enum types for gstreamer elements
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GSTBT_MUSICENUMS_H__
#define __GSTBT_MUSICENUMS_H__

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * GstBtTriggerSwitch:
 * @GSTBT_TRIGGER_SWITCH_OFF: turn switch off
 * @GSTBT_TRIGGER_SWITCH_ON: turn switch on
 * @GSTBT_TRIGGER_SWITCH_EMPTY: do not change switch
 *
 * Switch event commands.
 */
typedef enum {
  GSTBT_TRIGGER_SWITCH_OFF=0,
  GSTBT_TRIGGER_SWITCH_ON=1,
  GSTBT_TRIGGER_SWITCH_EMPTY=255,
} GstBtTriggerSwitch;

#define GSTBT_TYPE_TRIGGER_SWITCH   (gstbt_trigger_switch_get_type())

extern GType gstbt_trigger_switch_get_type(void);


/**
 * GstBtNote:
 * @GSTBT_NOTE_OFF: turn note off
 * @GSTBT_NOTE_NONE: no note
 * @GSTBT_NOTE_C_0: c-0
 * @GSTBT_NOTE_CIS_0: c#0
 * @GSTBT_NOTE_D_0: d-0
 * @GSTBT_NOTE_DIS_0: d#0
 * @GSTBT_NOTE_E_0: e-0
 * @GSTBT_NOTE_F_0: f-0
 * @GSTBT_NOTE_FIS_0: f#0
 * @GSTBT_NOTE_G_0: G-0
 * @GSTBT_NOTE_GIS_0: g#0
 * @GSTBT_NOTE_A_0: a-0
 * @GSTBT_NOTE_AIS_0: a#0
 * @GSTBT_NOTE_B_0: b-0
 * @GSTBT_NOTE_C_1: c-1
 * @GSTBT_NOTE_CIS_1: c#1
 * @GSTBT_NOTE_D_1: d-1
 * @GSTBT_NOTE_DIS_1: d#1
 * @GSTBT_NOTE_E_1: e-1
 * @GSTBT_NOTE_F_1: f-1
 * @GSTBT_NOTE_FIS_1: f#1
 * @GSTBT_NOTE_G_1: G-1
 * @GSTBT_NOTE_GIS_1: g#1
 * @GSTBT_NOTE_A_1: a-1
 * @GSTBT_NOTE_AIS_1: a#1
 * @GSTBT_NOTE_B_1: b-1
 * @GSTBT_NOTE_C_2: c-2
 * @GSTBT_NOTE_CIS_2: c#2
 * @GSTBT_NOTE_D_2: d-2
 * @GSTBT_NOTE_DIS_2: d#2
 * @GSTBT_NOTE_E_2: e-2
 * @GSTBT_NOTE_F_2: f-2
 * @GSTBT_NOTE_FIS_2: f#2
 * @GSTBT_NOTE_G_2: G-2
 * @GSTBT_NOTE_GIS_2: g#2
 * @GSTBT_NOTE_A_2: a-2
 * @GSTBT_NOTE_AIS_2: a#2
 * @GSTBT_NOTE_B_2: b-2
 * @GSTBT_NOTE_C_3: c-3
 * @GSTBT_NOTE_CIS_3: c#3
 * @GSTBT_NOTE_D_3: d-3
 * @GSTBT_NOTE_DIS_3: d#3
 * @GSTBT_NOTE_E_3: e-3
 * @GSTBT_NOTE_F_3: f-3
 * @GSTBT_NOTE_FIS_3: f#3
 * @GSTBT_NOTE_G_3: G-3
 * @GSTBT_NOTE_GIS_3: g#3
 * @GSTBT_NOTE_A_3: a-3
 * @GSTBT_NOTE_AIS_3: a#3
 * @GSTBT_NOTE_B_3: b-3
 * @GSTBT_NOTE_C_4: c-4
 * @GSTBT_NOTE_CIS_4: c#4
 * @GSTBT_NOTE_D_4: d-4
 * @GSTBT_NOTE_DIS_4: d#4
 * @GSTBT_NOTE_E_4: e-4
 * @GSTBT_NOTE_F_4: f-4
 * @GSTBT_NOTE_FIS_4: f#4
 * @GSTBT_NOTE_G_4: G-4
 * @GSTBT_NOTE_GIS_4: g#4
 * @GSTBT_NOTE_A_4: a-4
 * @GSTBT_NOTE_AIS_4: a#4
 * @GSTBT_NOTE_B_4: b-4
 * @GSTBT_NOTE_C_5: c-5
 * @GSTBT_NOTE_CIS_5: c#5
 * @GSTBT_NOTE_D_5: d-5
 * @GSTBT_NOTE_DIS_5: d#5
 * @GSTBT_NOTE_E_5: e-5
 * @GSTBT_NOTE_F_5: f-5
 * @GSTBT_NOTE_FIS_5: f#5
 * @GSTBT_NOTE_G_5: G-5
 * @GSTBT_NOTE_GIS_5: g#5
 * @GSTBT_NOTE_A_5: a-5
 * @GSTBT_NOTE_AIS_5: a#5
 * @GSTBT_NOTE_B_5: b-5
 * @GSTBT_NOTE_C_6: c-6
 * @GSTBT_NOTE_CIS_6: c#6
 * @GSTBT_NOTE_D_6: d-6
 * @GSTBT_NOTE_DIS_6: d#6
 * @GSTBT_NOTE_E_6: e-6
 * @GSTBT_NOTE_F_6: f-6
 * @GSTBT_NOTE_FIS_6: f#6
 * @GSTBT_NOTE_G_6: G-6
 * @GSTBT_NOTE_GIS_6: g#6
 * @GSTBT_NOTE_A_6: a-6
 * @GSTBT_NOTE_AIS_6: a#6
 * @GSTBT_NOTE_B_6: b-6
 * @GSTBT_NOTE_C_7: c-7
 * @GSTBT_NOTE_CIS_7: c#7
 * @GSTBT_NOTE_D_7: d-7
 * @GSTBT_NOTE_DIS_7: d#7
 * @GSTBT_NOTE_E_7: e-7
 * @GSTBT_NOTE_F_7: f-7
 * @GSTBT_NOTE_FIS_7: f#7
 * @GSTBT_NOTE_G_7: G-7
 * @GSTBT_NOTE_GIS_7: g#7
 * @GSTBT_NOTE_A_7: a-7
 * @GSTBT_NOTE_AIS_7: a#7
 * @GSTBT_NOTE_B_7: b-7
 * @GSTBT_NOTE_C_8: c-8
 * @GSTBT_NOTE_CIS_8: c#8
 * @GSTBT_NOTE_D_8: d-8
 * @GSTBT_NOTE_DIS_8: d#8
 * @GSTBT_NOTE_E_8: e-8
 * @GSTBT_NOTE_F_8: f-8
 * @GSTBT_NOTE_FIS_8: f#8
 * @GSTBT_NOTE_G_8: G-8
 * @GSTBT_NOTE_GIS_8: g#8
 * @GSTBT_NOTE_A_8: a-8
 * @GSTBT_NOTE_AIS_8: a#8
 * @GSTBT_NOTE_B_8: b-8
 * @GSTBT_NOTE_C_9: c-9
 * @GSTBT_NOTE_CIS_9: c#9
 * @GSTBT_NOTE_D_9: d-9
 * @GSTBT_NOTE_DIS_9: d#9
 * @GSTBT_NOTE_E_9: e-9
 * @GSTBT_NOTE_F_9: f-9
 * @GSTBT_NOTE_FIS_9: f#9
 * @GSTBT_NOTE_G_9: G-9
 * @GSTBT_NOTE_GIS_9: g#9
 * @GSTBT_NOTE_A_9: a-9
 * @GSTBT_NOTE_AIS_9: a#9
 * @GSTBT_NOTE_B_9: b-9
 * @GSTBT_NOTE_LAST: upper note value limmit
 *
 * Note numbers.
 */
/* values follow the buzz numbering scheme.
 * Other schemes are:
 * MIDI Tuning Standard: numbers from 0 to 127 to represent C-1 to G+9
 */
typedef enum {
  GSTBT_NOTE_OFF=255,
  GSTBT_NOTE_NONE=0,
  GSTBT_NOTE_C_0=    1,GSTBT_NOTE_CIS_0,GSTBT_NOTE_D_0,GSTBT_NOTE_DIS_0,GSTBT_NOTE_E_0,GSTBT_NOTE_F_0,GSTBT_NOTE_FIS_0,GSTBT_NOTE_G_0,GSTBT_NOTE_GIS_0,GSTBT_NOTE_A_0,GSTBT_NOTE_AIS_0,GSTBT_NOTE_B_0,
  GSTBT_NOTE_C_1= 16+1,GSTBT_NOTE_CIS_1,GSTBT_NOTE_D_1,GSTBT_NOTE_DIS_1,GSTBT_NOTE_E_1,GSTBT_NOTE_F_1,GSTBT_NOTE_FIS_1,GSTBT_NOTE_G_1,GSTBT_NOTE_GIS_1,GSTBT_NOTE_A_1,GSTBT_NOTE_AIS_1,GSTBT_NOTE_B_1,
  GSTBT_NOTE_C_2= 32+1,GSTBT_NOTE_CIS_2,GSTBT_NOTE_D_2,GSTBT_NOTE_DIS_2,GSTBT_NOTE_E_2,GSTBT_NOTE_F_2,GSTBT_NOTE_FIS_2,GSTBT_NOTE_G_2,GSTBT_NOTE_GIS_2,GSTBT_NOTE_A_2,GSTBT_NOTE_AIS_2,GSTBT_NOTE_B_2,
  GSTBT_NOTE_C_3= 48+1,GSTBT_NOTE_CIS_3,GSTBT_NOTE_D_3,GSTBT_NOTE_DIS_3,GSTBT_NOTE_E_3,GSTBT_NOTE_F_3,GSTBT_NOTE_FIS_3,GSTBT_NOTE_G_3,GSTBT_NOTE_GIS_3,GSTBT_NOTE_A_3,GSTBT_NOTE_AIS_3,GSTBT_NOTE_B_3,
  GSTBT_NOTE_C_4= 64+1,GSTBT_NOTE_CIS_4,GSTBT_NOTE_D_4,GSTBT_NOTE_DIS_4,GSTBT_NOTE_E_4,GSTBT_NOTE_F_4,GSTBT_NOTE_FIS_4,GSTBT_NOTE_G_4,GSTBT_NOTE_GIS_4,GSTBT_NOTE_A_4,GSTBT_NOTE_AIS_4,GSTBT_NOTE_B_4,
  GSTBT_NOTE_C_5= 80+1,GSTBT_NOTE_CIS_5,GSTBT_NOTE_D_5,GSTBT_NOTE_DIS_5,GSTBT_NOTE_E_5,GSTBT_NOTE_F_5,GSTBT_NOTE_FIS_5,GSTBT_NOTE_G_5,GSTBT_NOTE_GIS_5,GSTBT_NOTE_A_5,GSTBT_NOTE_AIS_5,GSTBT_NOTE_B_5,
  GSTBT_NOTE_C_6= 96+1,GSTBT_NOTE_CIS_6,GSTBT_NOTE_D_6,GSTBT_NOTE_DIS_6,GSTBT_NOTE_E_6,GSTBT_NOTE_F_6,GSTBT_NOTE_FIS_6,GSTBT_NOTE_G_6,GSTBT_NOTE_GIS_6,GSTBT_NOTE_A_6,GSTBT_NOTE_AIS_6,GSTBT_NOTE_B_6,
  GSTBT_NOTE_C_7=112+1,GSTBT_NOTE_CIS_7,GSTBT_NOTE_D_7,GSTBT_NOTE_DIS_7,GSTBT_NOTE_E_7,GSTBT_NOTE_F_7,GSTBT_NOTE_FIS_7,GSTBT_NOTE_G_7,GSTBT_NOTE_GIS_7,GSTBT_NOTE_A_7,GSTBT_NOTE_AIS_7,GSTBT_NOTE_B_7,
  GSTBT_NOTE_C_8=128+1,GSTBT_NOTE_CIS_8,GSTBT_NOTE_D_8,GSTBT_NOTE_DIS_8,GSTBT_NOTE_E_8,GSTBT_NOTE_F_8,GSTBT_NOTE_FIS_8,GSTBT_NOTE_G_8,GSTBT_NOTE_GIS_8,GSTBT_NOTE_A_8,GSTBT_NOTE_AIS_8,GSTBT_NOTE_B_8,
  GSTBT_NOTE_C_9=144+1,GSTBT_NOTE_CIS_9,GSTBT_NOTE_D_9,GSTBT_NOTE_DIS_9,GSTBT_NOTE_E_9,GSTBT_NOTE_F_9,GSTBT_NOTE_FIS_9,GSTBT_NOTE_G_9,GSTBT_NOTE_GIS_9,GSTBT_NOTE_A_9,GSTBT_NOTE_AIS_9,GSTBT_NOTE_B_9,
  GSTBT_NOTE_LAST
} GstBtNote;

#define GSTBT_TYPE_NOTE   (gstbt_note_get_type())

extern GType gstbt_note_get_type(void);

/**
 * GstBtWaveIndex:
 *
 * The #BtWavetable index entries. A value of 0 means no wave in use.
 */
#if 0
typedef guint GstBtWaveIndex;
#endif

#define GSTBT_TYPE_WAVE_INDEX   (gstbt_wave_index_get_type())

extern GType gstbt_wave_index_get_type(void);


G_END_DECLS

#endif /* __GSTBT_MUSICENUMS_H__ */
