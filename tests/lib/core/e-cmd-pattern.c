/* Buzztard
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

#include "m-bt-core.h"

//-- globals

static BtApplication *app;
static BtSong *song;

//-- fixtures

static void
case_setup (void)
{
  GST_INFO
      ("================================================================================");
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
  g_object_checked_unref (song);
  g_object_checked_unref (app);
}

static void
case_teardown (void)
{
}


//-- tests

static void
test_bt_cmd_pattern_obj_mono1 (BT_TEST_ARGS)
{
  BT_TEST_START;
  /* arrange */
  BtMachine *machine = BT_MACHINE (bt_source_machine_new (song, "gen",
          "buzztard-test-mono-source", 0L, NULL));

  /* act */
  BtCmdPattern *pattern =
      bt_cmd_pattern_new (song, machine, BT_PATTERN_CMD_MUTE);

  /* assert */
  ck_assert_gobject_guint_eq (pattern, "command", BT_PATTERN_CMD_MUTE);

  /* cleanup */
  g_object_unref (pattern);
  g_object_unref (machine);
  BT_TEST_END;
}

static void
test_bt_cmd_pattern_obj_poly1 (BT_TEST_ARGS)
{
  BT_TEST_START;
  /* arrange */
  BtMachine *machine = BT_MACHINE (bt_source_machine_new (song, "gen",
          "buzztard-test-poly-source", 2L, NULL));

  /* act */
  BtCmdPattern *pattern =
      bt_cmd_pattern_new (song, machine, BT_PATTERN_CMD_MUTE);

  /* assert */
  ck_assert_gobject_guint_eq (pattern, "command", BT_PATTERN_CMD_MUTE);

  /* cleanup */
  g_object_unref (pattern);
  g_object_unref (machine);
  BT_TEST_END;
}

TCase *
bt_cmd_pattern_example_case (void)
{
  TCase *tc = tcase_create ("BtCmdPatternExamples");

  tcase_add_test (tc, test_bt_cmd_pattern_obj_mono1);
  tcase_add_test (tc, test_bt_cmd_pattern_obj_poly1);
  tcase_add_checked_fixture (tc, test_setup, test_teardown);
  tcase_add_unchecked_fixture (tc, case_setup, case_teardown);
  return (tc);
}