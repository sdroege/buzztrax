/* Buzztrax
 * Copyright (C) 2006-2008 Buzztrax team <buzztrax-devel@lists.sf.net>
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
/**
 * SECTION:btwaveformviewer
 * @short_description: the waveform viewer widget
 * @see_also: #BtWave, #BtMainPageWaves
 *
 * Provides an viewer for audio waveforms. It can handle multi-channel
 * waveforms, show loop-markers and a playback cursor.
 */
/* TODO(ensonic): add seletion support
 * - export the selection as two properties
 */

#define BT_EDIT
#define BT_MAIN_PAGE_WAVES_C

#include "bt-edit.h"

enum
{
  WAVE_VIEWER_LOOP_START = 1,
  WAVE_VIEWER_LOOP_END,
  WAVE_VIEWER_PLAYBACK_CURSOR
};

#define MARKER_BOX_W 6
#define MARKER_BOX_H 5

//-- the class

G_DEFINE_TYPE (BtWaveformViewer, bt_waveform_viewer, GTK_TYPE_WIDGET);


static void
bt_waveform_viewer_realize (GtkWidget * widget)
{
  GdkWindowAttr attributes;
  gint attributes_mask;

  gtk_widget_set_realized (widget, TRUE);
  attributes.x = widget->allocation.x;
  attributes.y = widget->allocation.y;
  attributes.width = widget->allocation.width;
  attributes.height = widget->allocation.height;
  attributes.wclass = GDK_INPUT_OUTPUT;
  attributes.window_type = GDK_WINDOW_CHILD;
  attributes.event_mask = gtk_widget_get_events (widget) |
      GDK_EXPOSURE_MASK | GDK_SCROLL_MASK | GDK_KEY_PRESS_MASK |
      GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK |
      GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK;
  attributes.visual = gtk_widget_get_visual (widget);
  attributes.colormap = gtk_widget_get_colormap (widget);
  attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;

  widget->window =
      gdk_window_new (gtk_widget_get_parent_window (widget), &attributes,
      attributes_mask);
  widget->style = gtk_style_attach (widget->style, widget->window);
  gdk_window_set_user_data (widget->window, widget);
  gtk_style_set_background (widget->style, widget->window, GTK_STATE_NORMAL);

}

static gboolean
bt_waveform_viewer_expose (GtkWidget * widget, GdkEventExpose * event)
{
  BtWaveformViewer *self = BT_WAVEFORM_VIEWER (widget);
  const gint ox = 1, oy = 1;
  const gint sx = widget->allocation.width - 2, sy =
      widget->allocation.height - 2;
  gint i, ch;
  cairo_t *c;
  GdkColor sc = { 0, 0, 0, 0 };

  g_return_val_if_fail (BT_IS_WAVEFORM_VIEWER (widget), FALSE);
  g_return_val_if_fail (event != NULL, FALSE);

  if (event->count > 0)
    return FALSE;

  c = gdk_cairo_create (widget->window);

  gdk_cairo_set_source_color (c, &sc);
  cairo_rectangle (c, ox, oy, sx, sy);
  cairo_fill (c);

  if (self->peaks) {
    GdkColor sc2 = { 0, 0, 65535, 65535 };
    GdkColor sc3 = { 0, 0, 24575 / 2, 24575 / 2 };
    cairo_set_line_join (c, CAIRO_LINE_JOIN_ROUND);
    cairo_set_line_width (c, 0.5);

    for (ch = 0; ch < self->channels; ch++) {
      gint lsy = sy / self->channels;
      gint loy = oy + ch * sy / self->channels;
      for (i = 0; i < 4 * sx; i++) {
        gint imirror = i < 2 * sx ? i : 4 * sx - 1 - i;
        gint item = imirror * self->peaks_size / (2 * sx);
        gint sign = i < 2 * sx ? +1 : -1;
        gdouble y =
            (loy + lsy / 2 - (lsy / 2 -
                1) * sign * self->peaks[item * self->channels + ch]);
        if (y < loy)
          y = loy;
        if (y >= loy + lsy)
          y = loy + lsy - 1;
        if (i)
          cairo_line_to (c, ox + imirror * 0.5, y);
        else
          cairo_move_to (c, ox, y);
      }

      gdk_cairo_set_source_color (c, &sc3);
      cairo_fill_preserve (c);
      gdk_cairo_set_source_color (c, &sc2);
      cairo_stroke (c);
    }
    if (self->loop_start != -1) {
      gint x;

      cairo_set_source_rgba (c, 1, 0, 0, 0.75);
      cairo_set_line_width (c, 1.0);
      // casting to double loses precision, but we're not planning to deal with multiterabyte waveforms here :)
      x = (gint) (ox + self->loop_start * (gdouble) sx / self->wave_length);
      cairo_move_to (c, x, oy + sy);
      cairo_line_to (c, x, oy);
      cairo_stroke (c);
      cairo_line_to (c, x + MARKER_BOX_W, oy);
      cairo_line_to (c, x + MARKER_BOX_W, oy + MARKER_BOX_H);
      cairo_line_to (c, x, oy + MARKER_BOX_H);
      cairo_line_to (c, x, oy);
      cairo_fill (c);

      x = (gint) (ox + self->loop_end * (gdouble) sx / self->wave_length) - 1;
      cairo_move_to (c, x, oy + sy);
      cairo_line_to (c, x, oy);
      cairo_stroke (c);
      cairo_line_to (c, x - MARKER_BOX_W, oy);
      cairo_line_to (c, x - MARKER_BOX_W, oy + MARKER_BOX_H);
      cairo_line_to (c, x, oy + MARKER_BOX_H);
      cairo_line_to (c, x, oy);
      cairo_fill (c);
    }
    if (self->playback_cursor != -1) {
      gint x;
      cairo_set_source_rgba (c, 1, 1, 0, 0.75);
      cairo_set_line_width (c, 1.0);
      x = (gint) (ox +
          self->playback_cursor * (gdouble) sx / self->wave_length) - 1;
      cairo_move_to (c, x, oy + sy);
      cairo_line_to (c, x, oy);
      cairo_stroke (c);
      cairo_move_to (c, x, oy + sy / 2 - MARKER_BOX_H);
      cairo_line_to (c, x, oy + sy / 2 + MARKER_BOX_H);
      cairo_line_to (c, x + MARKER_BOX_W, oy + sy / 2);
      cairo_line_to (c, x, oy + sy / 2 - MARKER_BOX_H);
      cairo_fill (c);
    }
  }

  cairo_destroy (c);

  gtk_paint_shadow (widget->style, widget->window, GTK_STATE_NORMAL,
      GTK_SHADOW_IN, NULL, widget, NULL, ox - 1, oy - 1, sx + 2, sy + 2);
  // printf("exposed %p %d+%d\n", widget->window, widget->allocation.x, widget->allocation.y);

  return FALSE;
}

static void
bt_waveform_viewer_size_allocate (GtkWidget * widget,
    GtkAllocation * allocation)
{
  g_assert (BT_IS_WAVEFORM_VIEWER (widget));
  g_return_if_fail (allocation != NULL);

  GTK_WIDGET_CLASS (bt_waveform_viewer_parent_class)->size_allocate (widget,
      allocation);

  widget->allocation = *allocation;
}

static gboolean
bt_waveform_viewer_button_press (GtkWidget * widget, GdkEventButton * event)
{
  BtWaveformViewer *self = BT_WAVEFORM_VIEWER (widget);
  const gint ox = 1, oy = 1;
  const gint sx = widget->allocation.width - 2;

  if (event->y < oy + MARKER_BOX_H) {
    // check if we're over a loop-knob 
    if (self->loop_start != -1) {
      gint x =
          (gint) (ox + self->loop_start * (gdouble) sx / self->wave_length);
      if ((event->x >= x - MARKER_BOX_W) && (event->x <= x + MARKER_BOX_W)) {
        self->edit_loop_start = TRUE;
      }
    }
    if (self->loop_end != -1) {
      gint x = (gint) (ox + self->loop_end * (gdouble) sx / self->wave_length);
      if ((event->x >= x - MARKER_BOX_W) && (event->x <= x + MARKER_BOX_W)) {
        self->edit_loop_end = TRUE;
      }
    }
  }
  if (!self->edit_loop_start && !self->edit_loop_end) {
    self->edit_selection = TRUE;
  }
  return FALSE;
}

static gboolean
bt_waveform_viewer_button_release (GtkWidget * widget, GdkEventButton * event)
{
  BtWaveformViewer *self = BT_WAVEFORM_VIEWER (widget);
  self->edit_loop_start = self->edit_loop_end = self->edit_selection = FALSE;
  return FALSE;
}

static gboolean
bt_waveform_viewer_motion_notify (GtkWidget * widget, GdkEventMotion * event)
{
  BtWaveformViewer *self = BT_WAVEFORM_VIEWER (widget);
  const gint ox = 1;
  const gint sx = widget->allocation.width - 2;
  gint64 pos = (event->x - ox) * (gdouble) self->wave_length / sx;

  pos = CLAMP (pos, 0, self->wave_length);

  // if we're in loop or selection mode, map event->x to sample pos
  // clip loop/selection boundaries
  if (self->edit_loop_start) {
    if (pos >= self->loop_end) {
      pos = self->loop_end - 1;
    }
    if (pos != self->loop_start) {
      self->loop_start = pos;
      gtk_widget_queue_draw (GTK_WIDGET (self));
      g_object_notify ((GObject *) self, "loop-start");
    }
  } else if (self->edit_loop_end) {
    if (pos <= self->loop_start) {
      pos = self->loop_start + 1;
    }
    if (pos != self->loop_end) {
      self->loop_end = pos;
      gtk_widget_queue_draw (GTK_WIDGET (self));
      g_object_notify ((GObject *) self, "loop-end");
    }
  } else if (self->edit_selection) {

  }
  return FALSE;
}

static void
bt_waveform_viewer_finalize (GObject * object)
{
  BtWaveformViewer *self = BT_WAVEFORM_VIEWER (object);

  g_free (self->peaks);

  G_OBJECT_CLASS (bt_waveform_viewer_parent_class)->finalize (object);
}

static void
bt_waveform_viewer_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec)
{
  BtWaveformViewer *self = BT_WAVEFORM_VIEWER (object);

  switch (property_id) {
    case WAVE_VIEWER_LOOP_START:
      g_value_set_int64 (value, self->loop_start);
      break;
    case WAVE_VIEWER_LOOP_END:
      g_value_set_int64 (value, self->loop_end);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

static void
bt_waveform_viewer_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec)
{
  BtWaveformViewer *self = BT_WAVEFORM_VIEWER (object);

  switch (property_id) {
    case WAVE_VIEWER_LOOP_START:
      self->loop_start = g_value_get_int64 (value);
      if (gtk_widget_get_realized (GTK_WIDGET (self))) {
        gtk_widget_queue_draw (GTK_WIDGET (self));
      }
      break;
    case WAVE_VIEWER_LOOP_END:
      self->loop_end = g_value_get_int64 (value);
      if (gtk_widget_get_realized (GTK_WIDGET (self))) {
        gtk_widget_queue_draw (GTK_WIDGET (self));
      }
      break;
    case WAVE_VIEWER_PLAYBACK_CURSOR:
      self->playback_cursor = g_value_get_int64 (value);
      if (gtk_widget_get_realized (GTK_WIDGET (self))) {
        gtk_widget_queue_draw (GTK_WIDGET (self));
      }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
  /* printf("SetProperty: loop_start=%d loop_end=%d\n", (int)self->loop_start, (int)self->loop_end); */
}

static void
bt_waveform_viewer_class_init (BtWaveformViewerClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  widget_class->realize = bt_waveform_viewer_realize;
  widget_class->expose_event = bt_waveform_viewer_expose;
  widget_class->size_allocate = bt_waveform_viewer_size_allocate;
  widget_class->button_press_event = bt_waveform_viewer_button_press;
  widget_class->button_release_event = bt_waveform_viewer_button_release;
  widget_class->motion_notify_event = bt_waveform_viewer_motion_notify;

  gobject_class->set_property = bt_waveform_viewer_set_property;
  gobject_class->get_property = bt_waveform_viewer_get_property;
  gobject_class->finalize = bt_waveform_viewer_finalize;

  g_object_class_install_property (gobject_class, WAVE_VIEWER_LOOP_START,
      g_param_spec_int64 ("loop-start",
          "waveform loop start position",
          "First sample of the loop or -1 if there is no loop",
          -1, G_MAXINT64, -1, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, WAVE_VIEWER_LOOP_END,
      g_param_spec_int64 ("loop-end",
          "waveform loop end position",
          "First sample after the loop or -1 if there is no loop",
          -1, G_MAXINT64, -1, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property (gobject_class, WAVE_VIEWER_PLAYBACK_CURSOR,
      g_param_spec_int64 ("playback-cursor",
          "playback cursor position",
          "Current playback position within a waveform or -1 if sample is not played",
          -1, G_MAXINT64, -1, G_PARAM_WRITABLE | G_PARAM_STATIC_STRINGS));
}

static void
bt_waveform_viewer_init (BtWaveformViewer * self)
{
  GtkWidget *widget = GTK_WIDGET (self);

  widget->requisition.width = 40;
  widget->requisition.height = 40;

  self->channels = 2;
  self->peaks_size = 1000;
  self->peaks = g_malloc (sizeof (gfloat) * self->channels * self->peaks_size);
  self->wave_length = 0;
  self->loop_start = self->loop_end = self->playback_cursor = -1;
}

/**
 * bt_waveform_viewer_set_wave:
 * @self: the widget
 * @data: memory block of samples (interleaved for channels>1)
 * @channels: number channels
 * @length: number samples per channel
 *
 * Set wave data to show in the widget.
 */
void
bt_waveform_viewer_set_wave (BtWaveformViewer * self, gint16 * data,
    gint channels, gint length)
{
  gint i, c, p, cc = channels;
  gint64 len = length;

  self->channels = channels;
  self->wave_length = length;

  if (!data || !length) {
    memset (self->peaks, 0, sizeof (gfloat) * self->peaks_size);
    gtk_widget_queue_draw (GTK_WIDGET (self));
    return;
  }

  for (i = 0; i < self->peaks_size; i++) {
    gint p1 = len * i / self->peaks_size;
    gint p2 = len * (i + 1) / self->peaks_size;
    for (c = 0; c < self->channels; c++) {
      // get min max for peak slot
      gfloat vmin = data[p1 * cc + c], vmax = data[p1 * cc + c];
      for (p = p1 + 1; p < p2; p++) {
        gfloat d = data[p * cc + c];
        if (d < vmin)
          vmin = d;
        if (d > vmax)
          vmax = d;
      }
      if (vmin > 0 && vmax > 0)
        vmin = 0;
      else if (vmin < 0 && vmax < 0)
        vmax = 0;
      self->peaks[i * cc + c] = (vmax - vmin) / 32768.0;
    }
  }
  gtk_widget_queue_draw (GTK_WIDGET (self));
}

/**
 * bt_waveform_viewer_new:
 *
 * Create a new waveform viewer widget. Use bt_waveform_viewer_set_wave() to
 * pass wave data.
 *
 * Returns: the widget
 */
GtkWidget *
bt_waveform_viewer_new (void)
{
  return GTK_WIDGET (g_object_new (BT_TYPE_WAVEFORM_VIEWER, NULL));
}
