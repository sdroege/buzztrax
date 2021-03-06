/* Buzztrax
 * Copyright (C) 2008 Buzztrax team <buzztrax-devel@buzztrax.org>
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

#ifndef BT_CORE_PRIVATE_H
#define BT_CORE_PRIVATE_H

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

//-- ansi c
#include <string.h>
//-- i18n
#ifndef _
#ifdef ENABLE_NLS
  #include <langinfo.h>
  #include <libintl.h>

  #define _(String) gettext(String)
  #ifdef gettext_noop
    #define N_(String) gettext_noop(String)
  #else
    #define N_(String) (String)
  #endif
#else /* NLS is disabled */
  #define _(String) (String)
  #define __(String) (String)
  #define N_(String) (String)
  #ifdef gettext
    #undef gettext
  #endif
  #define gettext(String) (String)
  #ifdef dgettext
    #undef dgettext
  #endif
  #define dgettext(Domain,String) (String)
  #define textdomain(Domain)
  #define bindtextdomain(Package, Directory)
#endif
#endif

#include "core.h"
#include "version.h"
#include "persistence.h"

#include "marshal.h"

/**
 * bt_default_caps:
 *
 * Default caps to avoid plugging converters. Used in #BtWires and #BtMachines.
 */
extern GstCaps *bt_default_caps;

//-- defines for workarounds ---------------------------------------------------

/**
 * XML_CHAR_PTR:
 * @str: the string to cast
 *
 * Cast to xmlChar*
 */
#define XML_CHAR_PTR(str) ((xmlChar *)(str))

#define GST_CAT_DEFAULT bt_core_debug
#ifndef BT_CORE_C
  GST_DEBUG_CATEGORY_EXTERN(GST_CAT_DEFAULT);
#endif

//-- legacy helper -------------------------------------------------------------

BtCmdPattern *bt_machine_get_pattern_by_id(const BtMachine * const self, const gchar * const id);

//-- debug helper --------------------------------------------------------------

GList *bt_machine_get_element_list(const BtMachine * const self);
void bt_machine_dbg_print_parts(const BtMachine * const self);

GList *bt_wire_get_element_list(const BtWire *self);
void bt_wire_dbg_print_parts(const BtWire *self);


#endif // BT_CORE_PRIVATE_H
