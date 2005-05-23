/* $Id: wire-methods.h,v 1.10 2005-05-23 20:54:24 ensonic Exp $
 * defines all public methods of the wire class
 */

#ifndef BT_WIRE_METHODS_H
#define BT_WIRE_METHODS_H

#include "wire.h"

extern BtWire *bt_wire_new(const BtSong *song, const BtMachine *src_machine, const BtMachine *dst_machine);

extern gboolean bt_wire_reconnect(BtWire *self);

#endif // BT_WIRE_METHDOS_H
