/* $Id: sequence.h,v 1.5 2004-07-13 16:52:11 ensonic Exp $
 * class for the pattern sequence
 */

#ifndef BT_SEQUENCE_H
#define BT_SEQUENCE_H

#include <glib.h>
#include <glib-object.h>

/**
 * BT_TYPE_SEQUENCE:
 *
 * #GType for BtSequence instances
 */
#define BT_TYPE_SEQUENCE		        (bt_sequence_get_type ())
#define BT_SEQUENCE(obj)		        (G_TYPE_CHECK_INSTANCE_CAST ((obj), BT_TYPE_SEQUENCE, BtSequence))
#define BT_SEQUENCE_CLASS(klass)	  (G_TYPE_CHECK_CLASS_CAST ((klass), BT_TYPE_SEQUENCE, BtSequenceClass))
#define BT_IS_SEQUENCE(obj)	        (G_TYPE_CHECK_TYPE ((obj), BT_TYPE_SEQUENCE))
#define BT_IS_SEQUENCE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), BT_TYPE_SEQUENCE))
#define BT_SEQUENCE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), BT_TYPE_SEQUENCE, BtSequenceClass))

/* type macros */

typedef struct _BtSequence BtSequence;
typedef struct _BtSequenceClass BtSequenceClass;
typedef struct _BtSequencePrivate BtSequencePrivate;

/**
 * BtSequence:
 *
 * Startingpoint for the BtSong timeline data-structures.
 * Holds a series of BtTimeLine objects, which define the events that are
 * sent to a BtMachine at a time.
 */
struct _BtSequence {
  GObject parent;
  
  /* private */
  BtSequencePrivate *private;
};
/* structure of the sequence class */
struct _BtSequenceClass {
  GObjectClass parent_class;
  
};

/* used by SEQUENCE_TYPE */
GType bt_sequence_get_type(void);


#endif // BT_SEQUENCE_H

