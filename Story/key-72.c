//Simplified Cheat script - Applied to H key (key 72)
void main( void)
{
  choice_start()
    "Restore health"
    "50000 gold"
    "Unlock screen"
    "Save game"
    "Raise stats by 10"
    "Reduce stats by 10"
    "Nevermind"
  choice_end()
  
  if (&result == 1)
    &life = &lifemax;
  if (&result == 2)
    &gold += 50000;
  if (&result == 3)
  {
    screenlock(0);
    playsound(43, 22050, 0, 0, 0);
  }
  if (&result == 4)
    external("savebot", "talk");
  if (&result == 5)
  {
    &strength += 10;
    &defense += 10;
    &magic += 10;
    &lifemax += 10;
    &life += 10;
    playsound(43, 22050, 0, 0, 0);
  }
  if (&result == 6)
  {
    &strength -= 10;
    &defense -= 10;
    &magic -= 10;
    playsound(43, 22050, 0, 0, 0);
  }
  kill_this_task();
}
