// "The Ultimate Cheat" version 3.1: "Set/Recall Beacon" function

void main( void )
{
  wait(1);

  int &[ult]beacondata;
  int &[ult]datawk;

// note: &result is set by key-## script before this script is spawned

  // encode map, x, & y in one variable -- algorithm courtesy ManaUser:
  &[ult]beacondata = &player_map;
  &[ult]beacondata *= 1000;
  &[ult]beacondata += sp_x(1, -1)
  &[ult]beacondata *= 1000;
  &[ult]beacondata += sp_y(1, -1)

  // Set beacon 1
  if (&result == 3)
  {
    make_global_int("&[ult]beacon1", 1);
    &[ult]beacon1 = &[ult]beacondata;
    // null out old beacon if extant:
    &screen1_number = 0;
    &screen1_xlocation = 0;
    &screen1_xlocation = 0;
    &screen1[ult]xloc = 0;
    &screen1[ult]yloc = 0;
  }
  // Set beacon 2
  if (&result == 6)
  {
    make_global_int("&[ult]beacon2", 1);
    &[ult]beacon2 = &[ult]beacondata;
    // null out old beacon if extant:
    &screen2_number = 0;
    &screen2_xlocation = 0;
    &screen2_xlocation = 0;
    &screen2[ult]xloc = 0;
    &screen2[ult]yloc = 0;
  }
  // Set beacon 3
  if (&result == 9)
  {
    make_global_int("&[ult]beacon3", 1);
    &[ult]beacon3 = &[ult]beacondata;
    // null out old beacon if extant:
    &screen3_number = 0;
    &screen3_xlocation = 0;
    &screen3_xlocation = 0;
    &screen3[ult]xloc = 0;
    &screen3[ult]yloc = 0;
  }
  // Set beacon 4
  if (&result == 12)
  {
    make_global_int("&[ult]beacon4", 1);
    &[ult]beacon4 = &[ult]beacondata;
  }
  // Set beacon 5
  if (&result == 14)
  {
    make_global_int("&[ult]beacon5", 1);
    &[ult]beacon5 = &[ult]beacondata;
  }

  if (&result == 4)
  // recall version 1.2 / 2.0 beacon 1
  {
    if (&screen1[ult]xloc)
    {
      sp_x(1, &screen1[ult]xloc);
      sp_y(1, &screen1[ult]yloc);
    }
    if (&screen1_xlocation)
    {
      sp_x(1, &screen1_xlocation);
      sp_y(1, &screen1_ylocation);
    }
    &player_map = &screen1_number;
    goto load_beacon;
  }
  if (&result == 7)
  // recall version 1.2 / 2.0 beacon 2
  {
    if (&screen2[ult]xloc)
    {
      sp_x(1, &screen2[ult]xloc);
      sp_y(1, &screen2[ult]yloc);
    }
    if (&screen2_xlocation)
    {
      sp_x(1, &screen2_xlocation);
      sp_y(1, &screen2_ylocation);
    }
    &player_map = &screen2_number;
    goto load_beacon;
  }
  if (&result == 10)
  // recall version 1.2 / 2.0 beacon 3
  {
    if (&screen3[ult]xloc)
    {
      sp_x(1, &screen3[ult]xloc);
      sp_y(1, &screen3[ult]yloc);
    }
    if (&screen3_xlocation)
    {
      sp_x(1, &screen3_xlocation);
      sp_y(1, &screen3_ylocation);
    }
    &player_map = &screen3_number;
    goto load_beacon;
  }

  if (&result == 5)
  // recall version 3.0 beacon 1
  {
    &[ult]beacondata = &[ult]beacon1;
    goto recall_beacon;
  }

  if (&result == 8)
  // recall version 3.0 beacon 2
  {
    &[ult]beacondata = &[ult]beacon2;
    goto recall_beacon;
  }

  if (&result == 11)
  // recall version 3.0 beacon 3
  {
    &[ult]beacondata = &[ult]beacon3;
    goto recall_beacon;
  }

  if (&result == 13)
  // recall version 3.0 beacon 4
  {
    &[ult]beacondata = &[ult]beacon4;
    goto recall_beacon;
  }

  if (&result == 15)
  // recall version 3.0 beacon 5
  {
    &[ult]beacondata = &[ult]beacon5;
    goto recall_beacon;
  }

  goto unfreeze_quit;

recall_beacon:

  // ManaUser's algorithm to decode map, x, & y from one variable:
  &[ult]datawk = &[ult]beacondata;
  &[ult]datawk / 1000000;
  &player_map = &[ult]datawk;
  &[ult]datawk * 1000000;
  &[ult]beacondata -= &[ult]datawk;

  &[ult]datawk = &[ult]beacondata;
  &[ult]datawk / 1000;
  sp_x(1, &[ult]datawk);
  &[ult]datawk * 1000;
  &[ult]beacondata -= &[ult]datawk;

  sp_y(1, &[ult]beacondata);

load_beacon:
  sp_dir(1, 2);
  load_screen();
  draw_screen();
  draw_status();

unfreeze_quit:
  unfreeze(1);
  kill_this_task();
}
