// "The Ultimate Cheat" version 3.1: "Warp to a different screen"

void main( void )
{
  wait(1);

  int &[ult]mapno;
  int &[ult]wpmsg;
  int &[ult]colmsg;
  int &[ult]rowmsg;

  int &[ult]frmcol;
  int &[ult]tocol;
  int &[ult]mod32;
  int &[ult]frmrow;
  int &[ult]torow;
  int &[ult]dif;

  freeze(1);

  &[ult]mapno = &player_map;
  &[ult]frmrow = &player_map;
  &[ult]frmrow -= 1;
  &[ult]frmrow / 32;
  &[ult]mod32 = &[ult]frmrow;
  if (&[ult]mod32 != &[ult]frmrow)
  {
    say("Dink engine error -- sorry", 1);
    goto unfreeze_quit;
  }
  &[ult]mod32 *= 32;
  &[ult]frmcol = &player_map;
  &[ult]frmcol -= &[ult]mod32;
  &[ult]frmrow += 1;

main_w2adscrn_loop:

  &[ult]wpmsg = say_xy("Screen to warp to: &[ult]mapno",0, 20);
  sp_kill(&[ult]wpmsg, 0);

  &[ult]torow = &[ult]mapno;
  &[ult]torow -= 1;
  &[ult]torow / 32;
  &[ult]mod32 = &[ult]torow;
  &[ult]mod32 *= 32;
  &[ult]tocol = &[ult]mapno;
  &[ult]tocol -= &[ult]mod32;
  &[ult]torow += 1;

  if (&[ult]frmrow < &[ult]torow)
  {
    &[ult]dif = &[ult]torow;
    &[ult]dif -= &[ult]frmrow;
    &[ult]rowmsg = say_xy("[from row &[ult]frmrow to &[ult]torow, down &[ult]dif screen(s)]", 0, 35);
  } else
  {
    &[ult]dif = &[ult]frmrow;
    &[ult]dif -= &[ult]torow;
    &[ult]rowmsg = say_xy("[from row &[ult]frmrow to &[ult]torow, up &[ult]dif screen(s)]", 0, 35);
  }
  sp_kill(&[ult]rowmsg, 0);

  if (&[ult]frmcol < &[ult]tocol)
  {
    &[ult]dif = &[ult]tocol;
    &[ult]dif -= &[ult]frmcol;
    &[ult]colmsg = say_xy("[from col &[ult]frmcol to &[ult]tocol, right &[ult]dif screen(s)]", 0, 50);
  } else
  {
    &[ult]dif = &[ult]frmcol;
    &[ult]dif -= &[ult]tocol;
    &[ult]colmsg = say_xy("[from col &[ult]frmcol to &[ult]tocol, left &[ult]dif screen(s)]", 0, 50);
  }
  sp_kill(&[ult]colmsg, 0);

  wait_for_button();
  // kill messages
  sp_active(&[ult]colmsg, 0);
  sp_active(&[ult]rowmsg, 0);
  sp_active(&[ult]wpmsg, 0);
  if (&result == 1)
  // (Ctrl)
  {
    goto confirm_w2adscrn;
  }
  if (&result == 4)
  // (Enter)
  {
    goto confirm_w2adscrn;
  }
  if (&result == 5)
  // (Esc)
  {
    goto unfreeze_quit;
  }

  if (&result == 14)
  // (left)
  {
    if (&[ult]mapno > 1)
      &[ult]mapno -= 1;
  }
  if (&result == 16)
  // (right)
  {
    if (&[ult]mapno < 768)
      &[ult]mapno += 1;
  }
  if (&result == 18)
  // (up)
  {
    if (&[ult]mapno > 32)
      &[ult]mapno -= 32;
  }
  if (&result == 12)
  // (down)
  {
    if (&[ult]mapno <= 736)
      &[ult]mapno += 32;
  }

  goto main_w2adscrn_loop;

confirm_w2adscrn:
  if (&[ult]mapno == &player_map)
  {
    choice_start()
    "(remain on screen &player_map)"
    choice_end();
    goto unfreeze_quit;
  }

  choice_start()
    "Warp to screen: &[ult]mapno"
    "Leave"
  choice_end();

  if (&result == 1)
  {
    &player_map = &[ult]mapno;
    load_screen();
    draw_screen();
    draw_status();
  //invoke "warp within screen" automatically:
    spawn("[ult]wws");
  }

unfreeze_quit:
  unfreeze(1);
  kill_this_task();
}
