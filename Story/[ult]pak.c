// "The Ultimate Cheat" version 3.1: "Precision Attack" Routine

void main( void )
{
  wait(1);

  int &[ult]purpstar;
  int &[ult]cur_sp;
  int &[ult]hits;
  int &[ult]def;
  int &[ult]nohit;

  &[ult]purpstar = create_sprite(320, 200, 6, 163, 1);
  sp_seq(&[ult]purpstar, 163);
  sp_size(&[ult]purpstar, 200);
  sp_timing(&[ult]purpstar, 300);
  &[ult]cur_sp = 1;
precisionloop:
  &[ult]cur_sp += 1;
  if (&[ult]cur_sp > 99)
    goto precisiondone;
  &[ult]hits = sp_hitpoints(&[ult]cur_sp, -1);
  if (&[ult]hits == -1)
    // no such sprite
    goto precisionloop;
  if (&[ult]hits == 0)
    // sprite is invincible
    goto precisionloop;
  if (&[ult]hits > 9999)
    // sprite is intended to be invincible
    goto precisionloop;
  &[ult]def = sp_defense(&[ult]cur_sp, -1);
  if (&[ult]def > 9999)
    // sprite is intended to be invincible
    goto precisionloop;
  &[ult]nohit = sp_no_hit(&[ult]cur_sp, -1);
  if (&[ult]nohit == 1)
    // sprite is invincible
    goto precisionloop;
  &[ult]hits += &[ult]def;
  &[ult]hits -= 1;
  hurt(&[ult]cur_sp, &[ult]hits);
  wait(1);
  goto precisionloop;
precisiondone:
  sp_kill(&[ult]purpstar,100);
  kill_this_task();
}
