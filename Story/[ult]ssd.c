// "The Ultimate Cheat" version 3.1: "Detect Scripted Sprites" function

void main( void )
{
  wait(1);
//Note to the daring programmer: if you put comment slashes on the freeze()
//command below, and also comment-out the block of lines identified in the
//[ult]ssb.c script, Dink will be able to walk around and interact with the
//blinking sprites, even ones that are off-screen...
  freeze(1);
  dink_can_walk_off_screen(1);

  int &[ult]sctr = 1;
  int &[ult]scnt = 0;
  int &[ult]test;
  int &[ult]from = 1;
  int &[ult]to = 0;
  int &[ult]cont = 0;


  int &[ult]scr#1 = 0;
  int &[ult]scr#2 = 0;
  int &[ult]scr#3 = 0;
  int &[ult]scr#4 = 0;
  int &[ult]scr#5 = 0;
  int &[ult]scr#6 = 0;
  int &[ult]scr#7 = 0;

  int &[ult]sss;
  int &[ult]ssx = 0;
  int &[ult]ssy = 180;

// In loop 1, we count all scripted sprites and make the first 7 blink:
loop1:
  &[ult]sctr += 1;
  &[ult]test = sp_brain(&[ult]sctr, -1);
  if (&[ult]test < 0)
    goto loop1close;
  if (&[ult]test == 8)
    goto loop1close;
  &[ult]test = is_script_attached(&[ult]sctr);
  if (&[ult]test <= 0)
    goto loop1close;
  &[ult]scnt += 1;
  &result = &[ult]sctr;
  if (&[ult]scr#1 == 0)
  {
    &[ult]scr#1 = spawn("[ult]ssb");
    goto loop1close;
  }
  if (&[ult]scr#2 == 0)
  {
    &[ult]scr#2 = spawn("[ult]ssb");
    goto loop1close;
  }
  if (&[ult]scr#3 == 0)
  {
    &[ult]scr#3 = spawn("[ult]ssb");
    goto loop1close;
  }
  if (&[ult]scr#4 == 0)
  {
    &[ult]scr#4 = spawn("[ult]ssb");
    goto loop1close;
  }
  if (&[ult]scr#5 == 0)
  {
    &[ult]scr#5 = spawn("[ult]ssb");
    goto loop1close;
  }
  if (&[ult]scr#6 == 0)
  {
    &[ult]scr#6 = spawn("[ult]ssb");
    goto loop1close;
  }
  if (&[ult]scr#7 == 0)
  {
    &[ult]scr#7 = spawn("[ult]ssb");
    goto loop1close;
  }
  if (&[ult]cont == 0)
  {
    &[ult]cont = &[ult]sctr
  }
loop1close:
  if (&[ult]sctr < 99)
    goto loop1;

// loop1 done -- did we find ANY scripted sprites?
  if (&[ult]scnt == 0)
  {
    choice_start()
      title_start();
    No scripted sprites detected.
      title_end();
      "ok"
    choice_end();
    goto done;
  }

// Begin Main loop.  First task: some housekeeping...
set_to:
   &[ult]to = &[ult]from;
   &[ult]to += 6;
   if (&[ult]to > &[ult]scnt)
   {
     &[ult]to = &[ult]scnt;
   }

// Next task of main loop: show what we have done so far, then get a response from the user:
wfb:
  if (&[ult]scnt <= 7)
  {
    &[ult]sss = say_xy("`1Scripted sprites: &[ult]scnt (press Ctrl)", &[ult]ssx, &[ult]ssy);
  } else
  {
    if (&[ult]from == &[ult]to)
    {
      &[ult]sss = say_xy("`1Scripted sprite &[ult]from of &[ult]scnt (press Ctrl)", &[ult]ssx, &[ult]ssy);
    } else
    {
      &[ult]sss = say_xy("`1Scripted sprites &[ult]from-&[ult]to of &[ult]scnt (press Ctrl or Esc)", &[ult]ssx, &[ult]ssy);
    }
  }
  sp_kill(&[ult]sss, 0);
  wait_for_button();
  sp_active(&[ult]sss, 0);

  if (&result == 12)
  // down
  {
    &[ult]ssy += 10;
    goto wfb;
  }
  if (&result == 14)
  // left
  {
    &[ult]ssx -= 10;
    goto wfb;
  }
  if (&result == 16)
  // right
  {
    &[ult]ssx += 10;
    goto wfb;
  }
  if (&result == 18)
  // up
  {
    &[ult]ssy -= 10;
    goto wfb;
  }

  if (&result == 2)
  // Space
    goto wfb;
  if (&result == 3)
  // Shift
    goto wfb;
  if (&result == 4)
  // Enter
    goto wfb;

  if (&result == 5)
  // Esc
  {
    &[ult]cont = 0;
  }

//kill the current set of sprite blinkers:
  run_script_by_number(&[ult]scr#1, "kill");
  run_script_by_number(&[ult]scr#2, "kill");
  run_script_by_number(&[ult]scr#3, "kill");
  run_script_by_number(&[ult]scr#4, "kill");
  run_script_by_number(&[ult]scr#5, "kill");
  run_script_by_number(&[ult]scr#6, "kill");
  run_script_by_number(&[ult]scr#7, "kill");

//are we done?
  if (&[ult]to >= &[ult]scnt)
    goto done;
  if (&[ult]cont == 0)
    goto done;

//setup for next loop:
  &[ult]scr#1 = 0;
  &[ult]scr#2 = 0;
  &[ult]scr#3 = 0;
  &[ult]scr#4 = 0;
  &[ult]scr#5 = 0;
  &[ult]scr#6 = 0;
  &[ult]scr#7 = 0;
  &[ult]from = &[ult]to;
  &[ult]from += 1;

//blink next set of sprites:

loop2:
  &[ult]test = sp_brain(&[ult]cont, -1);
  if (&[ult]test < 0)
    goto loop2close;
  if (&[ult]test == 8)
    goto loop2close;
  &[ult]test = is_script_attached(&[ult]cont);
  if (&[ult]test <= 0)
    goto loop2close;
  &result = &[ult]cont;
  if (&[ult]scr#1 == 0)
  {
    &[ult]scr#1 = spawn("[ult]ssb");
    goto loop2close;
  }
  if (&[ult]scr#2 == 0)
  {
    &[ult]scr#2 = spawn("[ult]ssb");
    goto loop2close;
  }
  if (&[ult]scr#3 == 0)
  {
    &[ult]scr#3 = spawn("[ult]ssb");
    goto loop2close;
  }
  if (&[ult]scr#4 == 0)
  {
    &[ult]scr#4 = spawn("[ult]ssb");
    goto loop2close;
  }
  if (&[ult]scr#5 == 0)
  {
    &[ult]scr#5 = spawn("[ult]ssb");
    goto loop2close;
  }
  if (&[ult]scr#6 == 0)
  {
    &[ult]scr#6 = spawn("[ult]ssb");
    goto loop2close;
  }
  &[ult]scr#7 = spawn("[ult]ssb");

loop2close:
  &[ult]cont += 1;
  if (&[ult]cont > 99)
  {
    &[ult]cont = 0;
    goto set_to;
  }
  if (&[ult]scr#7)
    goto set_to;

  goto loop2;

done:
  unfreeze(1);
  dink_can_walk_off_screen(0);
  kill_this_task();
}
