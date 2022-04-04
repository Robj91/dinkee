// "The Ultimate Cheat" by Gary Hertel
// version 3.1 by Ted Shutes, theo@ia4u.net,
//    Paul "ManaUser" Pliska, manauser@yahoo.com

void main( void )
{
  int &[ult]row;
  int &[ult]col;
  int &[ult]xloc;
  int &[ult]yloc;
  int &[ult]tmp1;
  int &[ult]tmp2;
  int &[ult]tmp3;
  int &[ult]sprite;

  wait(1);
  stop_entire_game(1);
  choice_start()
    "Change Dink's stats"
    "Restore all hitpoints"
    "Gold and Inventory"
    "Show information screen"
    "Detect scripted sprites"
    "Kill enemies"
    "Unlock screen"
    "Warps and Beacons"
    "Save/Load Game"
    "Leave"
  choice_end();
  wait(1);

  if (&result == 1)  goto change_stat_menu;
  if (&result == 2)  goto restore_hits;
  if (&result == 3)  goto inventory_menu;
  if (&result == 4)  goto show_info;
  if (&result == 5)  goto show_ss;
  if (&result == 6)  goto kill_menu;
  if (&result == 7)  goto unlock_screen;
  if (&result == 8)  goto warp_beacon_menu;
  if (&result == 9)  goto save_load_menu;
  kill_this_task();


change_stat_menu:
  stop_entire_game(1);
  choice_start()
    "Raise all attributes by 10"
    "Lower all attributes by 10"
    "Raise life by 10 hp"
    "Lower life by 10 hp"
    "Change speed to normal"
    "Change speed to fast"
    "Change speed to super fast"
    "Fly"
    "Don't fly"
    "Edit stats (variable editor)"
    "Nevermind"
  choice_end();
  wait(1);

  // Raise all attributes by 10
  if (&result == 1)
  {
    &magic += 10;
    &strength += 10;
    &defense += 10;
  }

  // Lower all attributes by 10
  if (&result == 2)
  {
    if (&magic >= 10)
    {
      if (&strength >= 10)
      {
        if (&defense >= 10)
        {
          &magic -= 10;
          &strength -= 10;
          &defense -= 10;
          kill_this_task();
        }
      }
    }
    stop_entire_game(1);
    choice_start()
      title_start();
      Can't lower all stats by 10:
      Attack, Defense, or Magic
      is already less than 10
      title_end();
      "ok"
    choice_end();
    kill_this_task();
  }

  // Raise life by 10 hp
  if (&result == 3)
  {
    &lifemax += 10;
    //&life = &lifemax;
  }

  // Lower life by 10 hp
  if (&result == 4)
  {
    if (&lifemax > 10)
    {
      &lifemax -= 10;
      if (&life > &lifemax)
      {
        &life = &lifemax;
      }
      wait(250);
      draw_status();
    } else
    {
      stop_entire_game(1);
      choice_start()
        title_start();
        Can't lower life by 10 hp:
        Current life is only &lifemax hp
        title_end();
        "ok"
      choice_end();
    }
    kill_this_task();
  }

  // Change speed to normal
  if (&result == 5)
  {
    set_dink_speed(3);
    sp_frame_delay(1, 0);
  }
  // Change speed to fast
  if (&result == 6)
  {
    set_dink_speed(2);
    sp_frame_delay(1, 45);
  }
  // Change speed to super fast
  if (&result == 7)
  {
    set_dink_speed(1);
    sp_frame_delay(1, 22);
  }

  // make Dink Fly
  if (&result == 8)
  {
    sp_flying(1, 1);
  }
  // don't fly
  if (&result == 9)
  {
    sp_flying(1, 0);
  }

  // edit stats (Variable Editor)
  if (&result == 10)
  {
    &result = 1;
    &[ult]tmp1 = spawn("[ult]ved");
    if (&[ult]tmp1 == 0)
    {
      choice_start()
        title_start();
      Error: missing file "[ult]ved.c" -- please see ReadMe
        title_end();
        "(unable to continue)"
      choice_end();
    }
  }

  kill_this_task();


restore_hits:
  &life = &lifemax;
  kill_this_task();


inventory_menu:
  stop_entire_game(1);
  choice_start()
    "Add 1000 gold"
    "Remove 1000 gold"
    "Take away all gold"
    "Edit gold or 'story' (Variable Editor)"
    "Edit Pack Items (Weapons)"
    "Edit Magic Items (Spells)"
    "Leave"
  choice_end();
  wait(1);

  // Add 1000 gold
  if (&result == 1)
  {
    &gold += 1000;
    kill_this_task();
  }

  // Remove 1000 gold
  if (&result == 2)
  {
    if (&gold >= 1000)
    {
      &gold -= 1000;
    } else
    {
      stop_entire_game(1);
      choice_start()
        title_start();
        Can't remove 1000 gold:
        Current gold is only &gold
        title_end();
        "ok"
      choice_end();
    }
    kill_this_task();
  }

  // Remove all gold
  if (&result == 3)
  {
    &gold = 0;
    kill_this_task();
  }

  // Invoke Variable Editor
  if (&result == 4)
  {
    &result = 6;
    &[ult]tmp1 = spawn("[ult]ved");
    if (&[ult]tmp1 == 0)
    {
      choice_start()
        title_start();
      Error: missing file "[ult]ved.c" -- please see ReadMe
        title_end();
        "(unable to continue)"
      choice_end();
    }
    kill_this_task();
  }

  // Invoke pack editor
  if (&result == 5)
  {
    &[ult]tmp1 = spawn("[ult]ped");
    if (&[ult]tmp1 == 0)
    {
      choice_start()
        title_start();
      Error: missing file "[ult]ped.c" -- please see ReadMe
        title_end();
        "(unable to continue)"
      choice_end();
    }
  }

  // Invoke magic editor
  if (&result == 6)
  {
    &[ult]tmp1 = spawn("[ult]med");
    if (&[ult]tmp1 == 0)
    {
      choice_start()
        title_start();
      Error: missing file "[ult]med.c" -- please see ReadMe
        title_end();
        "(unable to continue)"
      choice_end();
    }
  }

  kill_this_task();


show_info:
  stop_entire_game(1);

  &[ult]row = &player_map;
  &[ult]row -= 1;
  &[ult]col = &[ult]row;
  &[ult]row / 32;
  &[ult]tmp1 = &[ult]row;
  &[ult]tmp1 * 32;
  &[ult]col -= &[ult]tmp1;
  &[ult]row += 1;
  &[ult]col += 1;

  &[ult]xloc = sp_x( 1, -1 );
  &[ult]yloc = sp_y( 1, -1 );
  &[ult]tmp1 = sp_speed(1, -1);
  &[ult]tmp2 = sp_flying(1, -1);
  &[ult]tmp3 = scripts_used();

  choice_start()
    set_y 270
    title_start();
    Current screen &player_map, Vision &vision
    (screen &player_map = row &[ult]row, col. &[ult]col)
    X,Y location = &[ult]xloc,&[ult]yloc
    Health = &life out of &lifemax
    speed=&[ult]tmp1   flying=&[ult]tmp2 (0=no, 1=yes)
    Cur. Magic=&cur_magic   Cur. Weapon=&cur_weapon
    Scripts in use = &[ult]tmp3   Story = &story
    title_end();

  "ok (ver. 3.1, July 2002)"
  choice_end();

  kill_this_task();


show_ss:
  &[ult]tmp1 = spawn("[ult]ssd");
  if (&[ult]tmp1 == 0)
  {
    choice_start()
      title_start();
    Error: missing file "[ult]ssd.c" -- please see ReadMe
      title_end();
      "(unable to continue)"
    choice_end();
  }
  kill_this_task();


kill_menu:
  stop_entire_game(1);
  choice_start()
    title_start();
    Select attack option:
    title_end();

    "Medium fireball (burns trees)"
    "Large explosion (does not burn)"
    "Precision Attack (non-magical)"
    "cancel"
  choice_end();
  wait(1);

  if (&result <= 2)
  {
    if (&result == 1)
    {
      &[ult]tmp1 = 235;
      &[ult]tmp2 = 200;
      &[ult]tmp3 = 40;
    } else
    {
      &[ult]tmp1 = 200;
      &[ult]tmp2 = 700;
      &[ult]tmp3 = 200;
    }

    &[ult]sprite = create_sprite(320, &[ult]tmp1, 17, 70, 1);
    playsound(17, 22050,0,&[ult]sprite,0);

    sp_speed(&[ult]sprite, 6);
    sp_seq(&[ult]sprite, 70);
    sp_size(&[ult]sprite, &[ult]tmp2);
    sp_que(&[ult]sprite, 9999);
    sp_brain(&[ult]sprite, 17);
    sp_strength(&[ult]sprite, &[ult]tmp3);
    sp_range(&[ult]sprite, 999);
    sp_brain_parm(&[ult]sprite, 1);
    if (&result == 1)
      sp_script(&[ult]sprite, "[ult]fir");
    }
  }

  if (&result == 3)
  {
    &[ult]tmp1 = spawn("[ult]pak");
    if (&[ult]tmp1 == 0)
    {
      choice_start()
        title_start();
      Error: missing file "[ult]pak.c" -- please see ReadMe
        title_end();
        "(unable to continue)"
      choice_end();
    }
  }

//if (&result == 4)
//  spawn("[ult]pa9");

  kill_this_task();


unlock_screen:
  screenlock(0);
  kill_this_task();


warp_beacon_menu:
  freeze(1);
  choice_start()
    "Warp to a different screen"
    "Warp within this screen"
    "Set beacon 1"
    (&screen1_number) (&[ult]beacon1 == 0) "Return to beacon 1"
    (&screen1_number == 0) (&[ult]beacon1) "Return to beacon 1"
    "Set beacon 2"
    (&screen2_number) (&[ult]beacon2 == 0) "Return to beacon 2"
    (&screen2_number == 0) (&[ult]beacon2) "Return to beacon 2"
    "Set beacon 3"
    (&screen3_number) (&[ult]beacon3 == 0) "Return to beacon 3"
    (&screen3_number == 0) (&[ult]beacon3) "Return to beacon 3"
    "Set beacon 4"
               (&[ult]beacon4) "Return to beacon 4"
    "Set beacon 5"
               (&[ult]beacon5) "Return to beacon 5"
    "Leave"
  choice_end();

  // Warp to a different screen
  if (&result == 1)
  {
    &[ult]tmp1 = spawn("[ult]wds");
    if (&[ult]tmp1 == 0)
    {
      choice_start()
        title_start();
      Error: missing file "[ult]wds.c" -- please see ReadMe
        title_end();
        "(unable to continue)"
      choice_end();
    }
    kill_this_task();
  }

  // Warp within screen
  if (&result == 2)
  {
    &[ult]tmp1 = spawn("[ult]wws");
    if (&[ult]tmp1 == 0)
    {
      choice_start()
        title_start();
      Error: missing file "[ult]wws.c" -- please see ReadMe
        title_end();
        "(unable to continue)"
      choice_end();
    }
    kill_this_task();
  }

  // Set/Recall Beacon
  if (&result < 16)
  {
    &[ult]tmp1 = spawn("[ult]srb");
    if (&[ult]tmp1 == 0)
    {
      choice_start()
        title_start();
      Error: missing file "[ult]srb.c" -- please see ReadMe
        title_end();
        "(unable to continue)"
      choice_end();
    }
    kill_this_task();
  }

  unfreeze(1);
  kill_this_task();


save_load_menu:
  &[ult]tmp1 = spawn("[ult]svl");
  if (&[ult]tmp1 == 0)
  {
    choice_start()
      title_start();
    Error: missing file "[ult]svl.c" -- please see ReadMe
      title_end();
      "(unable to continue)"
    choice_end();
  }
  kill_this_task();
}
