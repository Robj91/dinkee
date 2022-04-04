// "The Ultimate Cheat" 3.1: "Magic Editor" function

void main( void )
{
  wait(1);

  int &[ult]count;

magic_editor:

  stop_entire_game(1);
  choice_start()
    "Give Fireball"
    "Give Acid Rain"
    "Give Hellfire"
    "Give ItemTest.c"
    "Fill magic with ItemTest.c"
    "Drop all ItemTest.c"
    "Kill currently armed magic"
    "Nevermind"
   choice_end();
   wait(1);

  if (&result <= 5)
  {
    &[ult]count = free_magic();
    if (&[ult]count < 1)
    {
      stop_entire_game(1);
      choice_start()
        set_title_color 10
        title_start();
      Magic slots are already full.
        title_end();
        "Ok"
      choice_end();
      end_this_task();
    }
  }

  if (&result == 1) add_magic("item-fb",437, 1);
  if (&result == 2) add_magic("item-ice",437, 5);
  if (&result == 3) add_magic("item-sfb",437, 2);
  if (&result == 4) add_magic("itemtest",438, 17);

  if (&result == 5)
  {
    &[ult]count = free_magic();
  fillmagicloop:
    if (&[ult]count > 0)
    {
      &[ult]count -= 1;
      add_magic("itemtest",438, 17);
      goto fillmagicloop;
    }
  }

  if (&result == 6)
  {
    &[ult]count = count_magic("itemtest");
  dropmagicloop:
    if (&[ult]count > 0)
    {
      &[ult]count -= 1;
      kill_this_magic("itemtest");
      goto dropmagicloop;
    }
  }

  if (&result == 7)
  {
    stop_entire_game(1);
    choice_start()
      set_title_color 10
      title_start();
    Are you sure you want to permanently delete this spell?
      title_end();
      "Yes, kill this spell!"
      "No, I think I'll keep it"
    choice_end();
    if (&result == 1)
    {
      kill_cur_magic();
      // also kills script...
    }
  }

  kill_this_task();
}