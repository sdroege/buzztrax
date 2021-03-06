/* Buzztrax
 * Copyright (C) 2006 Buzztrax team <buzztrax-devel@buzztrax.org>
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

#include "m-bt-core.h"

//-- globals

static BtApplication *app;
static BtSong *song;

//-- fixtures

static void
case_setup (void)
{
  BT_CASE_START;
}

static void
test_setup (void)
{
  app = bt_test_application_new ();
  song = bt_song_new (app);
}

static void
test_teardown (void)
{
  ck_g_object_final_unref (song);
  ck_g_object_final_unref (app);
}

static void
case_teardown (void)
{
}

//-- tests

static void
test_bt_machine_add_pattern (BT_TEST_ARGS)
{
  BT_TEST_START;
  GST_INFO ("-- arrange --");
  BtMachine *gen1 = BT_MACHINE (bt_source_machine_new (song, "gen",
          "buzztrax-test-mono-source", 0L, NULL));
  check_init_error_trapp ("", "BT_IS_CMD_PATTERN (pattern)");

  GST_INFO ("-- act --");
  bt_machine_add_pattern (gen1, NULL);

  GST_INFO ("-- assert --");
  fail_unless (check_has_error_trapped (), NULL);

  GST_INFO ("-- cleanup --");
  BT_TEST_END;
}

// FIXME(ensonic): is this really testing something?
static void
test_bt_machine_names (BT_TEST_ARGS)
{
  BT_TEST_START;
  GST_INFO ("-- arrange --");
  BtMachine *gen1 = BT_MACHINE (bt_source_machine_new (song, "gen",
          "buzztrax-test-mono-source", 0L, NULL));
  BtMachine *gen2 = BT_MACHINE (bt_source_machine_new (song, "gen2",
          "buzztrax-test-mono-source", 0L, NULL));
  BtMachine *sink = BT_MACHINE (bt_sink_machine_new (song, "sink", NULL));

  GST_INFO ("-- act --");
  g_object_set (gen1, "id", "beep1", NULL);
  g_object_set (gen2, "id", "beep2", NULL);
  bt_wire_new (song, gen1, sink, NULL);
  bt_wire_new (song, gen2, sink, NULL);

  GST_INFO ("-- assert --");
  mark_point ();

  GST_INFO ("-- cleanup --");
  BT_TEST_END;
}

TCase *
bt_machine_test_case (void)
{
  TCase *tc = tcase_create ("BtMachineTests");

  tcase_add_test (tc, test_bt_machine_add_pattern);
  tcase_add_test (tc, test_bt_machine_names);
  tcase_add_checked_fixture (tc, test_setup, test_teardown);
  tcase_add_unchecked_fixture (tc, case_setup, case_teardown);
  return (tc);
}
