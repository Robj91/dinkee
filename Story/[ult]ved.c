// "The Ultimate Cheat" version 3.1: "Variable Editor"

void main( void )
{
  wait(1);
  // &result is set by the caller to the number of the first variable to edit:
  int &[ult]vnum = &result;
  int &[ult]nextv;

  int &[ult]vval;
  int &[ult]svval;
  int &[ult]maxval;
  int &[ult]valwk;

  int &[ult]edmsg;
  int &[ult]valmsg;

  int &[ult]incamt;
  int &[ult]incmax;
  int &[ult]incmsg;

variable_editor:

  freeze(1);
  if (&[ult]vnum == 1)
  {
    &[ult]vval = &strength;
    &[ult]maxval = 999;
    &[ult]incamt = 1;
    &[ult]incmax = 100;
    &[ult]edmsg = say_xy("`3Editing Strength", 0, 344);
  }
  if (&[ult]vnum == 2)
  {
    &[ult]vval = &defense;
    &[ult]maxval = 999;
    &[ult]incamt = 1;
    &[ult]incmax = 100;
    &[ult]edmsg = say_xy("`3Editing Defense", 0, 344);
  }
  if (&[ult]vnum == 3)
  {
    &[ult]vval = &magic;
    &[ult]maxval = 999;
    &[ult]incamt = 1;
    &[ult]incmax = 100;
    &[ult]edmsg = say_xy("`3Editing Magic", 0, 344);
  }
  if (&[ult]vnum == 4)
  {
    &[ult]vval = &lifemax;
    &[ult]maxval = 499;
    &[ult]incamt = 10;
    &[ult]incmax = 100;
    &[ult]edmsg = say_xy("`3Editing Maximum Life", 0, 344);
  }
  if (&[ult]vnum == 5)
  {
    &[ult]vval = &life;
    &[ult]maxval = &lifemax;
    &[ult]incamt = 10;
    &[ult]incmax = 100;
    &[ult]edmsg = say_xy("`3Editing Current Life", 0, 344);
  }
  if (&[ult]vnum == 6)
  {
    &[ult]vval = &gold;
    &[ult]maxval = 999999;
    &[ult]incamt = 100;
    &[ult]incmax = 1000;
    &[ult]edmsg = say_xy("`3Editing Gold", 0, 344);
  }
  if (&[ult]vnum == 7)
  {
    &[ult]vval = &story;
    &[ult]maxval = 99999999;
    &[ult]incamt = 1;
    &[ult]incmax = 100;
    &[ult]edmsg = say_xy("`3Editing 'Story' variable", 0, 344);
  }
  sp_kill(&[ult]edmsg, 0);
  &[ult]nextv = 0;
  &[ult]svval = &[ult]vval;

vedit_loop:

  &[ult]valmsg = say_xy("`% change value to &[ult]vval", 0, 362);
  sp_kill(&[ult]valmsg, 0);
  &[ult]incmsg = say_xy("`9increment: &[ult]incamt (toggle with space bar)", 0, 380);
  sp_kill(&[ult]incmsg, 0);

  wait_for_button();
  // kill messages:
  sp_active(&[ult]valmsg, 0);
  sp_active(&[ult]incmsg, 0);

  if (&result == 1)
  // (Ctrl)
  {
    goto confirm_vchange;
  }
  if (&result == 4)
  // (Enter)
  {
    goto confirm_vchange;
  }
  if (&result == 5)
  // (Esc)
  {
    goto quit_vedit;
  }

  if (&result == 2)
  // (Space)
  {
    if (&[ult]incamt >= &[ult]incmax)
    {
      &[ult]incamt = 1;
    } else
    {
      &[ult]incamt *= 10;
    }
  }

  if (&result == 14)
  // (left)
  {
    &[ult]valwk = &[ult]vval;
    &[ult]valwk -= &[ult]incamt;
    if (&[ult]valwk >= 0)
      &[ult]vval = &[ult]valwk;
  }
  if (&result == 16)
  // (right)
  {
    &[ult]valwk = &[ult]vval;
    &[ult]valwk += &[ult]incamt;
    if (&[ult]valwk <= &[ult]maxval)
      &[ult]vval = &[ult]valwk;
  }

  if (&result == 12)
  // (down)
  {
    &[ult]nextv = 1;
    goto confirm_vchange;
  }
  if (&result == 18)
  // (up)
  {
    &[ult]nextv = -1;
    goto confirm_vchange;
  }

  goto vedit_loop;

confirm_vchange:

  if (&[ult]vval == &[ult]svval)
  {
    if (&[ult]nextv)
    {
      goto vedit_next;
    }
    choice_start()
      "(leave value at &[ult]vval)"
    choice_end();
    goto quit_vedit;
  }

  choice_start()
    "Change value to &[ult]vval"
    "Cancel change"
    (&[ult]nextv) "Continue editing this variable"
  choice_end();

  if (&result == 3) goto vedit_loop;
  if (&result == 2) goto vedit_next;

  if (&[ult]vnum == 1)
  {
    &strength = &[ult]vval;
  }
  if (&[ult]vnum == 2)
  {
    &defense = &[ult]vval;
  }
  if (&[ult]vnum == 3)
  {
    &magic = &[ult]vval;
  }
  if (&[ult]vnum == 4)
  {
    &lifemax = &[ult]vval;
    if (&life > &lifemax)
    {
      &life = &lifemax;
      wait(1000);
      draw_status();
    }
  }
  if (&[ult]vnum == 5)
  {
    &life = &[ult]vval;
  }
  if (&[ult]vnum == 6)
  {
    &gold = &[ult]vval;
  }
  if (&[ult]vnum == 7)
  {
    &story = &[ult]vval;
  }

vedit_next:

  if (&[ult]nextv == 0) goto quit_vedit;
  sp_active(&[ult]edmsg, 0);
  &[ult]vnum += &[ult]nextv;
  if (&[ult]vnum < 1)
  {
    &[ult]vnum = 7;
  }
  if (&[ult]vnum > 7)
  {
    &[ult]vnum = 1;
  }
  goto variable_editor;

quit_vedit:
  sp_active(&[ult]edmsg, 0);
  unfreeze(1);
  kill_this_task();
}
