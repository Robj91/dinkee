// "The Ultimate Cheat" version 3.1: "Warp within screen"

void main( void )
{
   wait(1);

  int &[ult]xymsg;
  int &[ult]xloc;
  int &[ult]yloc;
  int &[ult]x_wk;
  int &[ult]y_wk;
  int &[ult]xhair;
  int &[ult]inc;

  freeze(1);

  &[ult]xloc = sp_x(1, -1);
  &[ult]yloc = sp_y(1, -1);
  &[ult]xhair = create_sprite(&[ult]xloc, &[ult]yloc, 6, 165, 1);
  sp_seq(&[ult]xhair, 165);
  sp_que(&[ult]xhair, 1000);
  &[ult]inc = 10;

main_w2adspot_loop:
  sp_x(&[ult]xhair, &[ult]xloc);
  sp_y(&[ult]xhair, &[ult]yloc);
  &[ult]xymsg = say_xy("X,Y coordinates to warp to: &[ult]xloc,&[ult]yloc",0, 20);
  sp_kill(&[ult]xymsg, 0);

  wait_for_button();
  // kill message:
  sp_active(&[ult]xymsg, 0);

  if (&result == 1)
  // (Ctrl)
  {
    goto confirm_w2adspot;
  }
  if (&result == 4)
  // (Enter)
  {
    goto confirm_w2adspot;
  }
  if (&result == 5)
  // (Esc)
  {
    goto quit_w2adspot;
  }

  if (&result == 3)
  // (Shift)
  {
    if (&[ult]inc == 50)
    {
      &[ult]inc = -1;
    }
    if (&[ult]inc == 10)
    {
      &[ult]inc = 50;
      sp_size(&[ult]xhair, 200);
    }
    if (&[ult]inc == 1)
    {
      &[ult]inc = 10;
      sp_size(&[ult]xhair, 100);
    }
    if (&[ult]inc == -1)
    {
      &[ult]inc = 1;
      sp_size(&[ult]xhair, 50);
    }
  }

  if (&result == 14)
  // (left)
  {
    &[ult]x_wk = &[ult]xloc;
    &[ult]x_wk -= &[ult]inc;
    if (&[ult]x_wk >= 20)
      &[ult]xloc = &[ult]x_wk;
  }
  if (&result == 16)
  // (right)
  {
    &[ult]x_wk = &[ult]xloc;
    &[ult]x_wk += &[ult]inc;
    if (&[ult]x_wk <= 619)
      &[ult]xloc = &[ult]x_wk;
  }
  if (&result == 12)
  // (down)
  {
    &[ult]y_wk = &[ult]yloc;
    &[ult]y_wk += &[ult]inc;
    if (&[ult]y_wk <= 399)
      &[ult]yloc = &[ult]y_wk;
  }
  if (&result == 18)
  // (up)
  {
    &[ult]y_wk = &[ult]yloc;
    &[ult]y_wk -= &[ult]inc;
    if (&[ult]y_wk >= 0)
      &[ult]yloc = &[ult]y_wk;
  }

  goto main_w2adspot_loop;

confirm_w2adspot:
  choice_start()
    "Warp to coordinates &[ult]xloc,&[ult]yloc"
    "Leave"
  choice_end();

  if (&result == 1)
  {
    sp_x(1, &[ult]xloc);
    sp_y(1, &[ult]yloc);
  }

quit_w2adspot:
  sp_kill(&[ult]xhair, 1);
  unfreeze(1);
  kill_this_task();
}
