// "The Ultimate Cheat" version 3.1: "Save/Load Menu"

void main( void )
{
  wait(1);

  int &[ult]sv-ld = 0;
  //  (0 = save, 1 = load)
  int &[ult]slset = 0;
  //  (0 = slots 1-10, 1 = slots 11-20)
  int &[ult]titl1;
  int &[ult]titl2;

save_load_choice:
  if (&[ult]sv-ld == 0)
  {
    &[ult]titl1 = say_xy("`0S A V E   G A M E", 12, 30);
    if (&[ult]slset == 0)
      &[ult]titl2 = say_xy("`0(standard slots, 1-10)", 12, 48);
    else
      &[ult]titl2 = say_xy("`0(extra slots, 11-20)", 12, 48);
  }
  else
  {
    &[ult]titl1 = say_xy("`#L O A D   G A M E", 12, 30);
    if (&[ult]slset == 0)
      &[ult]titl2 = say_xy("`#(standard slots, 1-10)", 12, 48);
    else
      &[ult]titl2 = say_xy("`#(extra slots, 11-20)", 12, 48);
  }
  sp_kill(&[ult]titl1, 0);
  sp_kill(&[ult]titl2, 0);
  wait(1);
  stop_entire_game(1);
  choice_start();
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 0) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]slset == 1) "&savegameinfo"
    (&[ult]sv-ld == 0) "/SAVE\  Nevermind Save  /SAVE\"
    (&[ult]sv-ld == 1) "/LOAD\  Nevermind Load  /LOAD\"
    (&[ult]sv-ld == 0) (&[ult]slset == 1) "\GAME/ Save, slots  1-10 \GAME/"
    (&[ult]sv-ld == 1) (&[ult]slset == 1) "\GAME/ Load, slots  1-10 \GAME/"
    (&[ult]sv-ld == 0) (&[ult]slset == 0) "\GAME/ Save, slots 11-20 \GAME/"
    (&[ult]sv-ld == 1) (&[ult]slset == 0) "\GAME/ Load, slots 11-20 \GAME/"
    (&[ult]sv-ld == 1) "Save, slots  1-10"
    (&[ult]sv-ld == 1) "Save, slots 11-20"
    (&[ult]sv-ld == 0) "Load, slots  1-10"
    (&[ult]sv-ld == 0) "Load, slots 11-20"
  choice_end();
  wait(1);
  sp_active(&[ult]titl1, 0);
  sp_active(&[ult]titl2, 0);
  if (&result <= 20)
  {
    if (&[ult]sv-ld) goto do_load;
    save_game(&result);
    say_xy("`%Game saved to SAVE&result.DAT", 0, 30);
  }

  if (&result <= 22) kill_this_task();

  if (&result <= 24)
  {
    &[ult]slset = 0;
    goto save_load_choice;
  }
  if (&result <= 26)
  {
    &[ult]slset = 1;
    goto save_load_choice;
  }
  if (&result == 27)
  {
    &[ult]sv-ld = 0;
    &[ult]slset = 0;
    goto save_load_choice;
  }
  if (&result == 28)
  {
    &[ult]sv-ld = 0;
    &[ult]slset = 1;
    goto save_load_choice;
  }
  if (&result == 29)
  {
    &[ult]sv-ld = 1;
    &[ult]slset = 0;
    goto save_load_choice;
  }
  &[ult]sv-ld = 1;
  &[ult]slset = 1;
  goto save_load_choice;

    do_load:
  if (game_exist(&result) == 0)
  {
    wait(2000);
    say("Wow, this loaded game looks so familiar.", 1);
    kill_this_task();
  }

  say_xy("`%Loading SAVE&result.DAT", 1, 30);
  wait(1);

  init("load_sequence_now graphics\dink\walk\ds-w1- 71 43 38 72 -14 -9 14 9");
  init("load_sequence_now graphics\dink\walk\ds-w2- 72 43 37 69 -13 -9 13 9");
  init("load_sequence_now graphics\dink\walk\ds-w3- 73 43 38 72 -14 -9 14 9");
  init("load_sequence_now graphics\dink\walk\ds-w4- 74 43 38 72 -12 -9 12 9");

  init("load_sequence_now graphics\dink\walk\ds-w6- 76 43 38 72 -13 -9 13 9");
  init("load_sequence_now graphics\dink\walk\ds-w7- 77 43 38 72 -12 -10 12 10");
  init("load_sequence_now graphics\dink\walk\ds-w8- 78 43 37 69 -13 -9 13 9");
  init("load_sequence_now graphics\dink\walk\ds-w9- 79 43 38 72 -14 -9 14 9");

  init("load_sequence_now graphics\dink\idle\ds-i2- 12 250 33 70 -12 -9 12 9");
  init("load_sequence_now graphics\dink\idle\ds-i4- 14 250 30 71 -11 -9 11 9");
  init("load_sequence_now graphics\dink\idle\ds-i6- 16 250 36 70 -11 -9 11 9");
  init("load_sequence_now graphics\dink\idle\ds-i8- 18 250 32 68 -12 -9 12 9");

  init("load_sequence_now graphics\dink\hit\normal\ds-h2- 102 75 60 72 -19 -9 19 9");
  init("load_sequence_now graphics\dink\hit\normal\ds-h4- 104 75 61 73 -19 -10 19 00");
  init("load_sequence_now graphics\dink\hit\normal\ds-h6- 106 75 58 71 -18 -10 18 10");
  init("load_sequence_now graphics\dink\hit\normal\ds-h8- 108 75 61 71 -19 -10 19 10");

  load_game(&result);
  &update_status = 1;
  draw_status();
  kill_this_task();

