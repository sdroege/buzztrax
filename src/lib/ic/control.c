/* $Id$
 *
 * Buzztard
 * Copyright (C) 2007 Buzztard team <buzztard-devel@lists.sf.net>
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
/**
 * SECTION:bticcontrol
 * @short_description: buzztards interaction controller single control
 *
 * Abstract base class for controls.
 */
#define BTIC_CORE
#define BTIC_CONTROL_C

#include "ic_private.h"

enum {
  CONTROL_DEVICE=1,
  CONTROL_NAME
};

struct _BtIcControlPrivate {
  /* used to validate if dispose has run */
  gboolean dispose_has_run;

  G_POINTER_ALIAS(BtIcDevice *,device);
  gchar *name;
};

static GObjectClass *parent_class=NULL;

//-- helper

//-- handler

//-- constructor methods

//-- methods

//-- wrapper

//-- class internals

/* returns a property for the given property_id for this object */
static void btic_control_get_property(GObject      * const object,
                               const guint         property_id,
                               GValue       * const value,
                               GParamSpec   * const pspec)
{
  const BtIcControl * const self = BTIC_CONTROL(object);
  return_if_disposed();
  switch (property_id) {
    case CONTROL_DEVICE: {
      g_value_set_object(value, self->priv->device);
    } break;
    case CONTROL_NAME: {
      g_value_set_string(value, self->priv->name);
    } break;
    default: {
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
    } break;
  }
}

/* sets the given properties for this object */
static void btic_control_set_property(GObject      * const object,
                              const guint         property_id,
                              const GValue * const value,
                              GParamSpec   * const pspec)
{
  const BtIcControl * const self = BTIC_CONTROL(object);
  return_if_disposed();
  switch (property_id) {
    case CONTROL_DEVICE: {
      g_object_try_weak_unref(self->priv->device);
      self->priv->device = BTIC_DEVICE(g_value_get_object(value));
      g_object_try_weak_ref(self->priv->device);
    } break;
    case CONTROL_NAME: {
      g_free(self->priv->name);
      self->priv->name = g_value_dup_string(value);
    } break;
    default: {
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
    } break;
  }
}

static void btic_control_dispose(GObject * const object) {
  const BtIcControl * const self = BTIC_CONTROL(object);

  return_if_disposed();
  self->priv->dispose_has_run = TRUE;

  GST_DEBUG("!!!! self=%p, self->ref_ct=%d",self,G_OBJECT(self)->ref_count);

  g_object_try_weak_unref(self->priv->device);

  GST_DEBUG("  chaining up");
  G_OBJECT_CLASS(parent_class)->dispose(object);
  GST_DEBUG("  done");
}

static void btic_control_finalize(GObject * const object) {
  const BtIcControl * const self = BTIC_CONTROL(object);

  GST_DEBUG("!!!! self=%p",self);

  g_free(self->priv->name);

  GST_DEBUG("  chaining up");
  G_OBJECT_CLASS(parent_class)->finalize(object);
  GST_DEBUG("  done");
}

static void btic_control_init(const GTypeInstance * const instance, gconstpointer const g_class) {
  BtIcControl * const self = BTIC_CONTROL(instance);

  self->priv = G_TYPE_INSTANCE_GET_PRIVATE(self, BTIC_TYPE_CONTROL, BtIcControlPrivate);
}

static void btic_control_class_init(BtIcControlClass * const klass) {
  GObjectClass * const gobject_class = G_OBJECT_CLASS(klass);

  parent_class=g_type_class_peek_parent(klass);
  g_type_class_add_private(klass,sizeof(BtIcControlPrivate));

  gobject_class->set_property = btic_control_set_property;
  gobject_class->get_property = btic_control_get_property;
  gobject_class->dispose      = btic_control_dispose;
  gobject_class->finalize     = btic_control_finalize;

  g_object_class_install_property(gobject_class,CONTROL_DEVICE,
                                  g_param_spec_object("device",
                                     "device prop",
                                     "parent device object",
                                     BTIC_TYPE_DEVICE, /* object type */
                                     G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY|G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(gobject_class,CONTROL_NAME,
                                  g_param_spec_string("name",
                                     "name prop",
                                     "device name",
                                     NULL, /* default value */
                                     G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY|G_PARAM_STATIC_STRINGS));
}

GType btic_control_get_type(void) {
  static GType type = 0;
  if (G_UNLIKELY(type == 0)) {
    const GTypeInfo info = {
      (guint16)(sizeof(BtIcControlClass)),
      NULL, // base_init
      NULL, // base_finalize
      (GClassInitFunc)btic_control_class_init, // class_init
      NULL, // class_finalize
      NULL, // class_data
      (guint16)(sizeof(BtIcControl)),
      0,   // n_preallocs
      (GInstanceInitFunc)btic_control_init, // instance_init
      NULL // value_table
    };
    // @bug: http://bugzilla.gnome.org/show_bug.cgi?id=417047
    //type = g_type_register_static(G_TYPE_OBJECT,"BtIcControl",&info,G_TYPE_FLAG_VALUE_ABSTRACT);
    type = g_type_register_static(G_TYPE_OBJECT,"BtIcControl",&info,0);
  }
  return type;
}
