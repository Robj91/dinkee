// "The Ultimate Cheat" version 3.1: "Pack Editor" function

void main( void )
{
  wait(1);

  int &[ult]count;

pack_editor:
  stop_entire_game(1);
  choice_start()
    "Give Sword..."
    "Give Bow..."
    "Give Elixer"
    "Give Bomb"
    "Give Throwing Axe"
    "Give Herb Boots"
    "Give ItemTest.c"
    "Fill pack with Nuts"
    "Drop all Nuts"
    "Kill currently armed weapon"
    "Nevermind"
  choice_end();
  wait(1);

  if (&result <= 8)
  {
    &[ult]count = free_items();
    if (&[ult]count < 1)
    {
      stop_entire_game(1);
      choice_start()
        set_title_color 10
        title_start();
        Pack is already full.
        title_end();
        "Ok"
      choice_end();
      kill_this_task();
    }
  }

  if (&result == 1)
  {
    stop_entire_game(1);
    choice_start()
      "Give Longsword"
      "Give Claw Sword"
      "Give Light Sword"
      "Nevermind"
    choice_end();
    if (&result == 1) add_item("item-sw1",438, 7);
    if (&result == 2) add_item("item-sw2",438, 20);
    if (&result == 3) add_item("item-sw3",438, 21);
    kill_this_task();
  }

  if (&result == 2)
  {
    stop_entire_game(1);
    choice_start()
      "Give Plain Bow"
      "Give Massive Bow"
      "Give Fire Bow"
      "Nevermind"
    choice_end();
    if (&result == 1) add_item("item-b1",438, 8);
    if (&result == 2) add_item("item-b2",438, 12);
    if (&result == 3) add_item("item-b3",438, 13);
    kill_this_task();
  }

  if (&result == 3) add_item("item-eli",438, 9);
  if (&result == 4) add_item("item-bom",438, 3);
  if (&result == 5) add_item("item-axe",438, 6);
  if (&result == 6) add_item("item-bt",438, 22);
  if (&result == 7) add_item("itemtest",437, 3);

  if (&result == 8)
  {
    &[ult]count = free_items();
  nutloop:
    if (&[ult]count > 0)
    {
      &[ult]count -= 1;
      add_item("item-nut", 438, 19);
      goto nutloop;
    }
  }

  if (&result == 9)
  {
    &[ult]count = count_item("item-nut");
  dropnutloop:
    if (&[ult]count > 0)
    {
      &[ult]count -= 1;
      kill_this_item("item-nut");
      goto dropnutloop;
    }
  }

  if (&result == 10)
  {
    if (compare_weapon("item-fst")
    {
      stop_entire_game(1);
      choice_start()
        set_title_color 10
        title_start();
        You can't (shouldn't) kill this item.
        title_end();
        "Ok"
      choice_end();       
      kill_this_task();
    }
    stop_entire_game(1);
    choice_start()
      set_title_color 10
      title_start();
    Are you sure you want to permanently delete this item?
      title_end();
      "Yes, get it outta my pack!"
      "No, I think I'll keep it"
    choice_end();
    if (&result == 1)
    {
      kill_cur_item();
      // also kills script...
    }
  }
  kill_this_task();
}
