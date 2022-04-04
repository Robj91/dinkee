//script for individual fireball
// Modified for the Ultimate Cheat, version 3.1

void main( void )
{
  int &[ult]wk;
}

void damage( void )
{
  playsound(18, 8000,0,0,0);

  kill_shadow(&current_sprite);
  sp_seq(&current_sprite, 70);
  sp_pseq(&current_sprite, 70);
  sp_frame(&current_sprite, 1);
  sp_brain(&current_sprite, 7);
//&mcrap = sp_y(&current_sprite, -1);
//&mcrap -= 35;
//sp_y(&current_sprite, &mcrap);

  &[ult]wk = sp_pseq(&missile_target, -1);
  if (&[ult]wk == 32)
  {
    &[ult]wk = sp_pframe(&missile_target, -1);
    if (&[ult]wk == 1)
    //they hit a tree, let's burn the thing
    {
      sp_hard(&missile_target, 1);
      draw_hard_sprite(&missile_target);

      &[ult]wk = is_script_attached(&missile_target);
      if (&[ult]wk > 0)
      //Script is attached to this tree, let's run it's die() procedure:
      {
        run_script_by_number(&[ult]wk, "die");
        return;
      }

      &[ult]wk = sp_editor_num(&missile_target);

      if (&[ult]wk != 0)
      //this tree was placed by the editor, let's make it stay burned:
      {
        editor_type(&[ult]wk, 4); 
        editor_seq(&[ult]wk, 20);
        editor_frame(&[ult]wk, 29);
        //type means show this seq/frame combo as background in the future
      }
  
      sp_pseq(&missile_target, 20);
      sp_pframe(&missile_target, 29);
      sp_hard(&missile_target, 0);
      draw_hard_sprite(&missile_target);
      sp_seq(&missile_target, 20);
      playsound(6, 8000,0,&missile_target,0);
    }
  }
}
