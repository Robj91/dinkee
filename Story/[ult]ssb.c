// "The Ultimate Cheat" 3.1:
//   "sprite blinker" for "Scripted Sprite Detector" function

void main( void )
{
  int &[sb]spr = &result;
  int &[sb]brn = sp_brain(&[sb]spr, -1);
  int &[sb]que = sp_que(&[sb]spr, -1);
  int &[sb]ndw = sp_nodraw(&[sb]spr, -1);
  int &[sb]x = sp_x(&[sb]spr, -1);
  int &[sb]y = sp_y(&[sb]spr, -1);

  int &[sb]tspr = 0;
  int &[sb]dspr = 0;
  int &[sb]dfr = 0;
  int &[sb]dx = &[sb]x;
  int &[sb]dy = &[sb]y;

  script_attach(0);

//freeze(&[sb]spr) -- "borrow" &[sb]dfr for a moment:
  &[sb]dfr = sp_seq(&[sb]spr, -1);
  if (&[sb]dfr > 0)
  {
    sp_brain(&[sb]spr, 6);
  } else
  {
    sp_brain(&[sb]spr, 0);
  }
//Note to the daring programmer: if you put comment slashes on all the above
//lines up to the previous "//freeze..." comment, Dink will be able to
//interact with the sprite normally if you also comment-out his freeze()
//command in [ult]ssd.c...
  sp_que(&[sb]spr, 22000);
  &[sb]dfr = 0;

  if (&[sb]x >= 20)
  {
    if (&[sb]x < 620)
    {
      if (&[sb]y >= 0)
      {
        if (&[sb]y < 400)
          goto onscreen;
        }
      }
    }
  }

  &[sb]dy += 50;

  if (&[sb]x < 20)
  {
    &[sb]dx = 55;
    &[sb]dfr = 4;
  }
  if (&[sb]x > 619)
  {
    &[sb]dx = 585;
    &[sb]dfr = 6;
  }

  if (&[sb]y < 0)
  {
    if (&[sb]dfr == 0)
    {
      &[sb]dy = 65;
      &[sb]dfr = 8;
    }
    if (&[sb]dfr == 4)
    {
    //&[sb]dx = 55;
      &[sb]dy = 45;
      &[sb]dfr = 7;
    }
    if (&[sb]dfr == 6)
    {
      &[sb]dx = 594;
      &[sb]dy = 53;
      &[sb]dfr = 5;
    }
  }
  if (&[sb]y > 399)
  {
    if (&[sb]dfr == 0)
    {
      &[sb]dy = 415;
      &[sb]dfr = 2;
    }
    if (&[sb]dfr == 4)
    {
    //&[sb]dx = 55;
      &[sb]dy = 425;
      &[sb]dfr = 1;
    }
    if (&[sb]dfr == 6)
    {
      &[sb]dx = 583;
      &[sb]dy = 429;
      &[sb]dfr = 3;
    }
  }

  preload_seq(25);
  &[sb]dspr = create_sprite(&[sb]dx, &[sb]dy, 0, 25, &[sb]dfr);
  sp_que(&[sb]dspr, 22000);
//say_stop("&[sb]dspr = create_sprite(&[sb]dx, &[sb]dy, 0, 25, &[sb]dfr);", 1);
  &[sb]tspr = say("`#&[sb]spr: X,Y=&[sb]x,&[sb]y", &[sb]dspr);
  goto freeze_text;

onscreen:
  &[sb]tspr = say("`0&[sb]spr: X,Y=&[sb]x,&[sb]y", &[sb]spr);

freeze_text:
  sp_kill(&[sb]tspr, 0);

blnk_loop:
  sp_nodraw(&[sb]spr, 0);
  if (&[sb]dspr)
    sp_nodraw(&[sb]dspr, 1);
  wait(125);
  sp_nodraw(&[sb]spr, 1);
  if (&[sb]dspr)
    sp_nodraw(&[sb]dspr, 0);
  wait(125);
  goto blnk_loop;
}

// restore all attributes and exit:
void kill( void )
{
  sp_active(&[sb]tspr, 0);
  if (&[sb]dspr)
    sp_active(&[sb]dspr, 0);
  sp_nodraw(&[sb]spr, &[sb]ndw);
  if (&[sb]que == -1)
  {
    &[sb]que = -2;
  }
  sp_que(&[sb]spr, &[sb]que);
  sp_brain(&[sb]spr, &[sb]brn);
  kill_this_task();
}
