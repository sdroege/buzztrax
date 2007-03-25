/* $Id: sequence-view.h,v 1.5 2007-03-25 14:18:33 ensonic Exp $
 *
 * Buzztard
 * Copyright (C) 2006 Buzztard team <buzztard-devel@lists.sf.net>
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
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef BT_SEQUENCE_VIEW_H
#define BT_SEQUENCE_VIEW_H

#include <glib.h>
#include <glib-object.h>

#define BT_TYPE_SEQUENCE_VIEW            (bt_sequence_view_get_type ())
#define BT_SEQUENCE_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), BT_TYPE_SEQUENCE_VIEW, BtSequenceView))
#define BT_SEQUENCE_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), BT_TYPE_SEQUENCE_VIEW, BtSequenceViewClass))
#define BT_IS_SEQUENCE_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), BT_TYPE_SEQUENCE_VIEW))
#define BT_IS_SEQUENCE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), BT_TYPE_SEQUENCE_VIEW))
#define BT_SEQUENCE_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), BT_TYPE_SEQUENCE_VIEW, BtSequenceViewClass))

/* type macros */

typedef struct _BtSequenceView BtSequenceView;
typedef struct _BtSequenceViewClass BtSequenceViewClass;
typedef struct _BtSequenceViewPrivate BtSequenceViewPrivate;

/**
 * BtSequenceView:
 *
 * the sequence widget view
 */
struct _BtSequenceView {
  GtkTreeView parent;
  
  /*< private >*/
  BtSequenceViewPrivate *priv;
};
/* structure of the sequence-view class */
struct _BtSequenceViewClass {
  GtkTreeViewClass parent;
  
};

/* used by SEQUENCE_VIEW_TYPE */
GType bt_sequence_view_get_type(void) G_GNUC_CONST;

#endif // BT_SEQUENCE_VIEW_H
