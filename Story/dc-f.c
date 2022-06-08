///////////////////////////
//ROBJ's fixes and tricks//
///////////////////////////
//**All procedures written by Robj**//

//requires &save_x and &save_y globals to be declared.
  //or do a search and replace to replace them with your own juggle globals

////////////////////////////
//==WHAT IS THIS SCRIPT?==//
////////////////////////////
//Fix flawed DinkC commands by replicating what they are SUPPOSED to do inside this script
//Also call procs that apply fixes to prevent bugs after running certain DinkC commands

//AND...

//DinkC tricks to accomplish other things.
//called using external with certain values required to be passed for some of these procedures.

//Passing a value of 0 to an &arg statement is the same as not passing anything.
//e.g if you need to pass the value '1' to &arg2, but nothing to &arg1 it would be:
//  external("dc-f", "<procedure>" 0, 1); 

void kill_cur_item(void)
{
  //Use external to call this in place of the kill_cur_item function.
    //kills item properly, even the armed image (which usually stays)
    //and actually kills off scripts instead of leaving them in memory
  &save_y = spawn("KCI");
  run_script_by_number(&save_y, "killscript");
  add_item("item-null", 180, 8);
  &save_x = get_item("item-null");
  &cur_weapon = &save_x;
  arm_weapon();
  &save_y = spawn("KCI");
  run_script_by_number(&save_y, "killscript");
  draw_status();
  kill_this_task();
}

void kill_cur_magic(void)
{
  //Use external to call this in place of the kill_cur_magic function.
    //kills magic properly, even the armed image (which usually stays)
    //and actually kills off scripts instead of leaving them in memory
  &save_y = spawn("KCM");
  run_script_by_number(&save_y, "killscript");
  add_magic("item-null", 180, 8);
  &save_x = get_magic("item-null");
  &cur_magic = &save_x;
  arm_magic();
  &save_y = spawn("KCM");
  run_script_by_number(&save_y, "killscript");
  draw_status();
  kill_this_task();
}

void kill_this_magic(void)
{
  //Use external to call this in place of the kill_this_magic function.
  //&arg1 = Magic to be killed (retrieve in calling script using get_magic)
    //kills magic properly, even the armed image (which usually stays)
    //and actually kills off scripts instead of leaving them in memory
  &save_x = &cur_magic;
  &cur_magic = &arg1;
  arm_magic();
  &save_y = spawn("KCM");
  run_script_by_number(&save_y, "killscript");
  add_magic("item-null", 180, 8);
  &save_y = get_magic("item-null");
  &cur_magic = &save_y;
  arm_magic();
  &save_y = spawn("KCM");
  run_script_by_number(&save_y, "killscript");
  &cur_magic = &save_x;
  arm_magic();
  draw_status();
  kill_this_task();
}

void sp_sound_fix(void)
{
  //fixes a strange, rare, bug that I'm surprised no one ever picked up before now.
  //Where if you go from one screen to another, via a warp (not a change screen)
  //and both screens had a sprite with a sound attached (either sp_sound or through editor)
  //they will "merge" together and both will be playing at the same time on the one sprite
  //If you keep going between screens quickly, they will start to bank up and exhaust all soundbank slots
  //run this on any main proc of a sprite that has a sound set in the editor.
  //OR if it has a sound set in the main proc, call this procedure immediately after the sp_sound() line
  //But make sure you call this procedure BEFORE a wait line, or the bug still has a chance of occuring.
  
  int &sfix = sp_sound(&current_sprite, -1);
  wait(0);
  sp_sound(&current_sprite, 0);
  
  //The TWO wait lines are necessary to prevent a strange rare bug - do not merge into one wait line!!
  wait(1);
  wait(99);
  sp_sound(&current_sprite, &sfix);
  
  kill_this_task();
}

void playsound_store(void)
{
 //plays a sound and returns the correct soundbank number (no matter the engine version)
   //(there is a discrepency in freedink where it returns the sounbank number + 1)
 //REQUIRES VERSION CHECKER TO WORK!
   //Install it from the Dink network under development files
   
 //pass playsound values to &args in the same order as you would when using "playsound".
 
 &save_x = playsound(&arg1, &arg2, &arg3, &arg4, &arg5);
 if (&vcheck > 110)
 {
  &save_x -= 1;
 }
 return(&save_x);
}

void sp_clip_fix(void)
{
 //simply call this this to fix sprite's so sp_clip_<side> functions on a sprite
 //without the need to clip them in the editor first - works on non-editor sprites too!
 //&arg1 = sprite to be fixed - defaults to &current_sprite if no value passed
 
 if (&arg1 > 0)
 {
  &save_x = &arg1;
 }
 else
 {
  &save_x = &current_sprite;
 }
 
 sp_clip_bottom(&save_x, 480);
 sp_clip_right(&save_x, 640);
 kill_this_task();
}

void hit_freeze_fix(void)
{
 //check if Dink is frozen and if so, unfreeze him
 //this is just to save a few lines in hit procs I need to run this in
 //there's a bug where if the player hits 2 sprites at once that both have a hit proc
 //and they both have say lines, but one of them runs a freeze() on Dink (and the other doesn't)
 //Dink can be frozen by one of the hit procs, then before it can run it's say_stop line, 
 //The other hit proc interrupts with it's say() lines, and the first hit proc never continues
   //(Dink is permenantly frozen)
 //This is because say_stop stops the script from continuing, but the text never shows up - it gets stuck.

 &save_x = sp_freeze(1, -1);
 if (&save_x > 0)
 {
   unfreeze(1);
 }
 
 kill_this_task();
}

void execute_killscripts(void)
{
 //this will check every current script in memory for a "killscript" proc
 //and if they have one, run it.
 //has it's useful applications
 
 //IMPORTANT: make sure you pass &current_script to &arg1, so it can be ignored.
 //or it has a chance to bug out and NOT kill all undying scripts
 
 &save_x = 1;
 &save_y = 199;
 
killscripts_loop:
 if (&save_x < &save_y)
 {
  if (&save_x != &arg1)
  {
   run_script_by_number(&save_x, "killscript");
  }
  &save_x += 1;
  goto killscripts_loop;
 }
 
 kill_this_task();
}

void kill_texts(void)
{
 //This will kill all text sprites currently displayed on the screen
 //Will also return the total number of text sprites that were killed
 &save_x = 0;
 &save_y = 0;
 
killtexts_loop:
 &save_x = get_next_sprite_with_this_brain(8, 0, &save_x);
 if (&save_x > 0)
 {
  sp_kill(&save_x, 1);
  &save_x += 1;
  &save_y += 1;
  goto killtexts_loop;
 }
 
 return(&save_y);
}

void kill_all_sounds(void)
{
 //this actually kills all sounds
 //the DinkC "kill_all_sounds" command only kills all repeating sounds not attached to a sprite
 //Also returns the total number of sounds killed.
 &save_x = 0;

kill_all_sounds: 
 sound_set_kill(&save_x);
 &save_x += 1;
 if (&save_x < 20)
 {
  goto kill_all_sounds;
 }
 
 kill_this_task();
}

void remoteseq(void)
{
  //check or set editor_seq value remotely on any screen.
  //&arg1 = map#, &arg2 = editor-sprite#, &arg3 = value(-1 to retrieve).
  //&arg4 = set to 1 to increment the editor_seq by 1, set to 2 to reduce the editor_seq by 1. (&arg3 will be ignored)
  //        valid values for editor_seq are 0-65535
  //&arg5, &arg6 - search all editor sprites (inclusive) in the range of &arg5 - &arg6 for &arg3 value.
  //               return the first editor_sprite number that matches. If not found in range, return "0". 
  //               when &arg5 and &arg6 are set, no value's will be altered - only returned.
  int &oldmap;
  int &savevalue;
  &oldmap = &player_map;
  &player_map = &arg1;
  
  if (&arg5 > 0)
  {
   if (&arg6 > 0)
   { 
     int &sprnum = &arg5;
    RSfindloop:
     &savevalue = editor_seq(&sprnum, -1);
     if (&savevalue == &arg3)
     {
      &savevalue = &sprnum;
      goto RSend;
     }
     if (&sprnum < &arg6)
     {
      &sprnum += 1;
      goto RSfindloop;
     }
     else
     {
      //It wasn't found - return 0
      &savevalue = 0;
      goto RSend;
     }
   }
  }
  if (&arg4 > 0)
  {
    int &numvaralter;
    &numvaralter = editor_seq(&arg2, -1);
    if (&arg4 == 1)
    {
      &numvaralter += 1;
    }
    if (&arg4 == 2)
    {
      &numvaralter -= 1;
    }
    &savevalue = editor_seq(&arg2, &numvaralter);
  }
  if (&arg4 <= 0)
  {
   &savevalue = editor_seq(&arg2, &arg3);
  }

RSend:  
  &player_map = &oldmap;
  return(&savevalue);
  kill_this_task();
}

void remoteframe(void)
{
  //check or set editor_frame value remotely on any screen.
  //&arg1 = map#, &arg2 = editor-sprite#, &arg3 = value(-1 to retrieve).
  //&arg4 = set to 1 to increment the editor_frame by 1, set to 2 to reduce the editor frame by 1. (&arg3 will be ignored)
  //        valid values for frame are 0-255
  //&arg5, &arg6 - search all editor sprites (inclusive) in the range of &arg5 - &arg6 for &arg3 value.
  //               return the first editor_sprite number that matches. If not found in range, return "0". 
  //               when &arg5 and &arg6 are set, no value's will be altered - only returned.
  int &oldmap;
  int &savevalue;
  &oldmap = &player_map;
  &player_map = &arg1;

  if (&arg5 > 0)
  {
   if (&arg6 > 0)
   { 
     int &sprnum = &arg5;
    RFfindloop:
     &savevalue = editor_frame(&sprnum, -1);
     if (&savevalue == &arg3)
     {
      &savevalue = &sprnum;
      goto RFend;
     }
     if (&sprnum < &arg6)
     {
      &sprnum += 1;
      goto RFfindloop;
     }
     else
     {
      //It wasn't found - return 0
      &savevalue = 0;
      goto RFend;
     }
   }
  }  
  if (&arg4 > 0)
  {
    int &numvaralter;
    &numvaralter = editor_frame(&arg2, -1);
    if (&arg4 == 1)
    {
      &numvaralter += 1;
    }
    if (&arg4 == 2)
    {
      &numvaralter -= 1;
    }
    &savevalue = editor_frame(&arg2, &numvaralter);
  }
  else
  {
    &savevalue = editor_frame(&arg2, &arg3);
  }

RFend:   
  &player_map = &oldmap;
  return(&savevalue);
  kill_this_task();
}

void mod_val(void)
{
 //This will return a random value between &arg2% and &arg3% of &arg1
 //If &arg4 = 1, results will be rounded UP, otherwise they will be default (rounded down)
    //E.g round up: if the lower limit would be 12.7, the lowest possible value will be 13.  
    //              if the higher limit would be 15.7, the highest possible value will be 16.
 
 //Example, if &arg1 = 14, &arg2 = 50, &arg3 = 75 and &arg4 = 1,
 //            This will return a random value between 7(50% of 14) and 11(75% of 14), inclusive.
 
 if (&arg1 == 0)
 {
  //can't divide by 0!
  kill_this_task();
 }
 
 int &junk;

 &save_x = &arg1;
 &save_y = &save_x;
 &save_x *= &arg2;
 &junk = math_mod(&save_x, 100);
 &save_x /= 100;
 &save_y *= &arg3;
 &save_y /= 100;
 &save_y -= &save_x;
 &save_y += 1;

 if (&arg4 > 0)
 {
  //round up &save_x
  if (&junk > 0)
  {
   &save_x += 1;
  }
  
  //round up &save_y
  &junk = &arg1;
  &junk *= &arg3;
  &junk = math_mod(&junk, 100);
  if (&junk > 0)
  {
   &save_y += 1;
  }
 }

 //get the random value
 &save_x = random(&save_y, &save_x);
 return(&save_x);

 kill_this_task();
}

void preload_seq(void)
{
 //prelaod any sequences passed to &arg1 - 8.
 //Basically, this is to run multiple preloads in one line
 //rather than having multiple preload_seq lines in your script
 if (&arg1 > 0)
 {
  preload_seq(&arg1);
 }
 if (&arg2 > 0)
 {
  preload_seq(&arg2);
 }
 if (&arg3 > 0)
 {
  preload_seq(&arg3);
 }
 if (&arg4 > 0)
 {
  preload_seq(&arg4);
 }
 if (&arg5 > 0)
 {
  preload_seq(&arg5);
 }
 if (&arg6 > 0)
 {
  preload_seq(&arg6);
 }
 if (&arg7 > 0)
 {
  preload_seq(&arg7);
 }
 if (&arg8 > 0)
 {
  preload_seq(&arg8);
 }

 kill_this_task();
}

void reset_dink_speed(void)
{
  //sets dink's speed according to what he has equppied
  //need to add a manual check against each item in Dmod that alters Dink's speed.
  //HERB BOOTS
  &save_x = compare_weapon("item-bt");
  if (&save_x > 0)
  {
    //dink has herb boots armed - reset his speed to herb boots speed
    set_dink_speed(2);
    sp_frame_delay(1, 30);
    kill_this_task();
  }
  
  //All checks must be before this point, this is what will run if all other checks return false.
  set_dink_speed(3);
  sp_frame_delay(1, 0);
  
  kill_this_task();
}

void sprite_scr_edge(void)
{
  //procedure to detect if any the border of a sprite's hardbox is against the screen edge
  //and if so will auto adjust sprite so it has at least &arg5 pixels of room between screen edge and hardbox edge
  //good for moveable objects that save their position so it doesn't mess up push/pull and get dink stuck!
  
  //arg1 = left edge, arg2 = top edge, arg3 = right edge, arg4 = bottom edge
  //&arg5 = pixels of room to allow between screen edges 
  //&arg6 = Sprite being checked - defaults to &current_sprite if no value passed.
  
  //IF NO VALUE IS PASSED TO &arg5, will default to 8 pixels of room.
  
  int &val1;
  
  if (&arg5 > 0)
  {
   &val1 = &arg5;
  }
  else
  {
   &val1 = &current_sprite;
  }
  
  //let's locate the hardbox edges first
  external("dc-f", "LocateEdges", &arg1, &arg2, &arg3, &arg4, &val1);
  
  //LEFT EDGE
  //retrieve location of left edge
  &save_x = sp_custom("LocateEdges-L", &val1, -1);
  if (&save_x < 28)
  {
    //this sprite's left hardbox edge is closer than 8 pixels to the left edge of the screen
    
    //set it to &arg5 + 8, then subtract the distance between depth dot and left hardbox edge
    //this will give us where the sprite will be to make the hardbox edge at &arg5
    if (&arg5 <= 0)
    {
     &save_x = 28;
    }
    else
    {
     &save_x = &arg5;
     &save_x += 20;
    }
    &save_x -= &arg1;
    sp_x(&val1, &save_x);
  }
  
  //TOP EDGE
  &save_y = sp_custom("LocateEdges-T", &val1, -1);
  if (&arg5 <= 0)
  {
   &save_x = 8;
  }
  else
  {
   &save_x = &arg5;
  }
  if (&save_y < &save_x)
  {
    &save_y = &save_x;
    &save_y -= &arg2;
    sp_y(&val1, &save_y);
  }
  
  //RIGHT EDGE
  &save_x = sp_custom("LocateEdges-R", &val1, -1);
  if (&arg5 <= 0)
  {
   &save_y = 614;
  }
  else
  {
   &save_y = &arg5;
  }
  if (&save_x > &save_y)
  {
    &save_x = &save_y;
    &save_y = sp_custom("dc-f-sse-r", &val1, -1);
    &save_x -= &save_y;
    sp_x(&val1, &save_x);
  }
  
  //BOTTOM EDGE
  &save_y = sp_custom("LocateEdges-B", &val1, -1);
  &save_x = sp_custom("LocateEdges-R", &val1, -1);
  if (&arg5 <= 0)
  {
   &save_x = 392;
  }
  else
  {
   &save_x = &arg5;
  }
  if (&save_y > &save_x)
  {
    &save_y = &save_x;
    &save_x = sp_custom("dc-f-sse-b", &val1, -1);
    &save_y -= &save_x;
    sp_y(&val1, &save_y);
  }
  
  draw_hard_map();
  kill_this_task();
}

void LocateEdges(void)
{
  //Get the current x coordinates of the left and right hardbox edges
  //Also get the current y coordinates of the top and bottom hardbox edges
  //Will retrieve values for &arg5, or &current_sprite if no sprite passed to &arg5.
  //Saves values in custom keys "LocateEdges-[Edge]", where [Edge] is L, T, R or B.
  
  //The hardbox value for the right and bottom hardbox are actually 1 less than what's written in Dink.ini!
  //  -- This is already accounted for in the returned value.
  
  //&arg 1 - 4 = hardbox boundaries (L, T, R, B)
  //&arg5 = sprite's hardbox being checked (defaults to &current_sprite if not specified)
  //&arg6 = NULL. Pass 0, then whatever for &arg7 and &arg8, if wanting to use an override.
  //        Left blank to remain consistent with the withinHB proc's argument structure.
  //&arg7 = override x DD position (check a future position without the sprite actually being there)
  //        i.e, will act as if the sprite is in the OVERRIDE position, rather than it's current position.
  //&arg8 = override y DD position - same as above but for y.
  
  int &val1;
  int &val2;
  int &val3;
  
  if (&arg5 > 0)
  {
    &val3 = &arg5;
  }
  else
  {
    &val3 = &current_sprite;
  }
  
  //first let's fix the bottom and right edge to the correct number
  &val1 = &arg3;
  &val2 = &arg4;
  &val1 -= 1;
  &val2 -= 1;
  
  //save these values in custom key of current sprite
  //but let's make sure it's an obscure one so we won't use one the author is already using
  sp_custom("dc-f-sse-r", &val3, &val1);
  sp_custom("dc-f-sse-b", &val3, &val2);
  
  //LEFT edge
  //check for position override
  if (&arg7 > 0)
  {
    &save_x = &arg7;
  }
  else
  {
    &save_x = sp_x(&val3, -1);
  }
  
  //let's add the distance between depth dot and left edge
  //so we have the x position of the left edge stored
  &save_x += &arg1;
  sp_custom("LocateEdges-L", &val3, &save_x);
  
  //TOP edge
  if (&arg8 > 0)
  {
    &save_y = &arg8;
  }
  else
  {
    &save_y = sp_y(&val3, -1);
  }
  
  &save_y += &arg2;
  sp_custom("LocateEdges-T", &val3, &save_y);
  
  //RIGHT edge
  if (&arg7 > 0)
  {
    &save_x = &arg7;
  }
  else
  {
    &save_x = sp_x(&val3, -1);
  }
  
  //retrieve the corrected right edge of current sprite's hardbox
  &val2 = sp_custom("dc-f-sse-r", &val3, -1);
  &save_x += &val2;
  sp_custom("LocateEdges-R", &val3, &save_x);
  
  //BOTTOM edge
  if (&arg8 > 0)
  {
    &save_y = &arg8;
  }
  else
  {
    &save_y = sp_y(&val3, -1);
  }
  
  //retrieve the corrected bottom edge of current sprite's hardbox
  &val2 = sp_custom("dc-f-sse-b", &val3, -1);
  &save_y += &val2;
  sp_custom("LocateEdges-B", &val3, &save_y);
  
  kill_this_task();
}

void withinHB(void)
{
  //returns 1 if &arg6 is within &arg5's hardbox. &arg5's hardbox values must be passed in &arg 1 - 4.
  //i.e.. if sprite was set to hard, Dink would be trapped in the hard box if 1 is returned.
  //&arg1 = left edge, arg2 = top edge, arg3 = right edge, arg4 = bottom edge
  //&arg5 = sprite's hardbox we are checking against - defaults to &current_sprite if nothing passed
  //&arg6 = Sprite to check if it is within &arg5's HB (Defaults to Dink if no sprite passed)
  //&arg7 = override x DD position (check a future position without the sprite actually being there)
  //        i.e, will act as if the sprite is in the OVERRIDE position, rather than it's current position.
  //&arg8 = override y DD position - same as above but for y.
  
  int &val1;
  int &val2;
  int &val3;
  int &val4;
  
  //Get current x and y position of hardbox edges
  external("dc-f", "LocateEdges", &arg1, &arg2, &arg3, &arg4, &arg5, 0, &arg7, &arg8);
  
  if (&arg6 > 0)
  {
    &save_y = &arg6;
  }
  else
  {
    &save_y = 1;
  }
  
  &val1 = sp_custom("LocateEdges-L", &save_x, -1);
  &val2 = sp_custom("LocateEdges-T", &save_x, -1);
  &val3 = sp_custom("LocateEdges-R", &save_x, -1);
  &val4 = sp_custom("LocateEdges-B", &save_x, -1);
  
  &save_x = sp_x(&save_y, -1);
  &save_y = sp_y(&save_y, -1);
  &save_x = inside_box(&save_x, &save_y, &val1, &val2, &val3, &val4);
  return(&save_x);
  
  kill_this_task();
}

void sprite_retrieve(void)
{
 //used to retrieve a sprite from another script without assigning it to a global
 //just set a custom key "sprite-id" on the sprite instead and give it a value.
 //then pass it to this proc, along with the brain or set a range of brains to search.
 //as soon as it finds a sprite that matches brain and custom key value it will stop searching
 //and return the active sprite number of the found sprite.
 //IF sprite doesn't exist, and can't be found, will return '0'.
 
 //&arg1, &arg2 = brain range to search (inclusive).
 //               set both to same value to search just one brain
 //&arg3 = custom key "sprite-id" value to search for.
 
  int &val1 = &arg1;
  int &val2 = 0;
  
 sprite_retrieve_RS:
  &save_x = 0;
 sprite_retrieve:
  &save_x = get_next_sprite_with_this_brain(&val1, 0, &save_x);
  if (&save_x > 0)
  {
   &save_y = sp_custom("sprite-id", &save_x, -1);
   if (&save_y == &arg3)
   {
    return(&save_x);   
   }
   else
   {
    &save_x += 1;
    goto sprite_retrieve;
   }
  }
 
  &val1 += 1;
  if (&val1 <= &val2)
  {
   goto sprite_retrieve_RS;
  }

 //Sprite with that id doesn't exist.. return a value of 0
 return(0);
 kill_this_task();
}

void brain_retrieve(void)
{
 //searches for a brain and returns the first sprite found, or returns 0 if no sprite found with specified brain.
 
 //&arg1 = brain value 
 
 //&arg2 = sprite skip amount (used to skip sprites). 
 //	   e.g: if set to 2, it will skip the first 2 sprites it finds with brain &arg1, and return the 3rd one.
 //        Returns the LAST &arg1 brain sprite found if skip amount is greater than sprites with specified brain.
 //         e.g: if skip is set to '3' and there is only one &arg1 brain found, that one will be returned.
 
 //&arg3 = Retry amount. If a sprite with the specified brain cannot be found, will retry &arg3 times.
 //        A wait(0) will be run between each retry, to allow qeued scripts to execute.
 //        This is useful to make sure you can still retrieve sprites that execute AFTER this script, on screen entry
 //         Add 1 retry per wait(0) or wait(1) that runs PRIOR to brain being set, in any other scripts main proc.
 //          (Not cumulative) - if there are 5 main procs with 1 wait(0) in each of them, that's only 1 retry needed.
 //            set to 999 to retry indefinitely (only use if you are certain the brain will be set and retrievable)
 
 //&arg4 = Only search for and return active sprite number's with value of &arg4 stored in "sprite-id" custom key.
 
 //&arg5 = active sprite number to start with.
 
 int &val1;
 if (&arg3 > 0)
 {
  if (&arg3 < 999)
  {
   int &val2 = 0;
  }
 }
 if (&arg4 > 0)
 {
  int &val3 = 0;
 }
   
BR_restart: 
 &val1 = 0;  
 if (&arg5 > 0)
 {
  &save_x = &arg5;
 } 
 else
 {
  &save_x = 0;
 }
 &save_y = 0;
brain_ret:
 &save_x = get_next_sprite_with_this_brain(&arg1, 0, &save_x);
 if (&save_x > 0)
 {
  if (&arg4 > 0)
  {
   &val3 = sp_custom("sprite-id", &save_x, -1);
   if (&val3 == &arg4)
   {
    &val1 = &save_x;
   }
   else
   {
    &save_x += 1;
    goto brain_ret;
   }
  }
  else
  {
   &val1 = &save_x;
  }
  
  if (&arg2 > 0)
  {
   if (&save_y != &arg2)
   {
    &save_y += 1;
    &save_x += 1;
    goto brain_ret;
   }
  }
 } 
 if (&val1 > 0)
 {
  return(&val1);
 }
 else
 {
  if (&arg3 > 0)
  {
   if (&arg3 == 999)
   {
    wait(0);
    goto BR_restart;
   }
   else
   {
    if (&val2 != &arg3)
    {
     &val2 += 1;
     wait(0);
     goto BR_restart;
    }
   }
  }
  
  return(0);
 }
}

void screen_edge_border(void)
{
 //spawn in some screen edge detection sprites to save having to loop and check position
   //in my custom bounce brain missile sprites
 //even though hardness is not drawn off screen, this'll still work
 //because we can check the sp_hard value of the sprite, not the actual hardness of the screen

 //possible, but rare (and random), hardbox bug fix.
 preload_seq(64);
 
 &save_x = create_sprite(322, -5, 20, 64, 7);
 sp_pseq(&save_x, 64);
 sp_pframe(&save_x, 7);
 sp_hard(&save_x, 0);
 sp_nodraw(&save_x, 1);
 &save_x = create_sprite(322, 410, 20, 64, 7);
 sp_pseq(&save_x, 64);
 sp_pframe(&save_x, 7);
 sp_hard(&save_x, 0);
 sp_nodraw(&save_x, 1);
 &save_x = create_sprite(15, 186, 20, 64, 8);
 sp_pseq(&save_x, 64);
 sp_pframe(&save_x, 8);
 sp_hard(&save_x, 0);
 sp_nodraw(&save_x, 1);
 &save_x = create_sprite(630, 186, 20, 64, 8);
 sp_pseq(&save_x, 64);
 sp_pframe(&save_x, 8);
 sp_hard(&save_x, 0);
 sp_nodraw(&save_x, 1);
 draw_hard_map();
 kill_this_task();
}

void NPC_say_juggle(void)
{
 //used when spawning a separate script to juggle say_stop_npc stuff,
 //which is timed to certain parts of an ordinary conversation between 2 characters
 //so that the text from BG NPC's are unskippable, but normal convo execution does not halt
 //attach a script to the first sprite to say a background line and then juggle it between sprites
 //&arg1 = LAST BG sprite that talked
 //&arg2 = NEXT BG sprite to talk
 //&arg3 = script number of script to juggle between sprites

 sp_custom("next-NPC", &arg1, &arg2); 
 run_script_by_number(&arg3, "saystuff");
 kill_this_task();
}

void grow_to_size(void)
{
 //make a sprite grow to size
 //&arg1 = sprite to grow (default &current_sprite if &arg1=0)
 //&arg2 = size to grow to
 //&arg3 = size increment per wait
 //&arg4 = wait per loop
 
 int &val1;
 int &val2;
 
 if (&arg1 <= 0)
 {
  &val2 = &current_sprite;
 }
 else
 {
  &val2 = &arg1;
 }
 
grow_to_size:
 &val1 = sp_size(&val2, -1);
 if (&val1 < &arg2)
 {
  &val1 += &arg3;
  sp_size(&val2, &val1);
  wait(&arg4);
  goto grow_to_size;
 }
 
 kill_this_task();
}

void shrink_to_size(void)
{
 //make a sprite shrink to size
 //&arg1 = sprite to shrink
 //&arg2 = size to shrink to
 //&arg3 = size increment per wait
 //&arg4 = wait per loop
 
 int &val1;
 
shrink_to_size:
 &val1 = sp_size(&arg1, -1);
 if (&val1 > &arg2)
 {
  &val1 -= &arg3;
  sp_size(&arg1, &val1);
  wait(&arg4);
  goto shrink_to_size;
 }
 
 kill_this_task();
}

void txtskip(void)
{
  sp_kill(&arg1, 0);
 waittxtskip:
  wait_for_button();
  if (&result == 2)
   sp_active(&arg1, 0); 
  else
   goto waittxtskip;
 
 kill_this_task();
}

void disable_all_sprites(void)
{
 //pass '1' to &arg1 to disable Dink as well.
 &save_x = 2;
 &save_x -= &arg1;
dis_all_spr:
 //check if a sprite exists with this active sprite number
 &save_y = sp_active(&save_x, -1);
 if (&save_y > 0)
 {
  //this sprite exists - so disable it.
  sp_disabled(&save_x, 1);
 }
 if (&save_x < 299)
 {
  //increment active sprite number '&save_x' and loop.
  &save_x += 1;
  goto dis_all_spr;
 }
 
 kill_this_task();
}

void enable_all_sprites(void)
{
 int &getsp = 1;
 int &sprite_exist;
 loop:
 //check if a sprite exists with this active sprite number
 &sprite_exist = sp_active(&getsp, -1);
 if (&sprite_exist > 0)
 {
     //this sprite exists - so enable it.
     sp_disabled(&getsp, 0);
 }
 if (&getsp < 299)
 {
     //increment active sprite number '&getsp' and loop.
     &getsp += 1;
     goto loop;
 }

 kill_this_task();
}

void fade_down(void)
{
 //fade down and create a black full screen (640x480) sprite covering the screen, 
   //including status bar and side bars.
 //&arg1 = custom clip left
 //&arg2 = custom clip top
 //&arg3 = custom clip right
 //&arg4 = custom clip bottom
 //&arg5 = custom depth que, otherwise 9999
 //&arg6 = pass 1 to enable noclip of the sprite 
 fade_down();
 fill_screen(0);
 external("dc-f", "fill_screen_black", &arg1, &arg2, &arg3, &arg4, &arg5, &arg6);
 kill_this_task();
}

void fade_up(void)
{
 //&arg1: If set to '1', status will remain undrawn.
 
 external("dc-f", "unfill_screen");
 draw_background();
 if (&arg1 <= 0)
 {
  draw_status();
 }
 fade_up();
 kill_this_task();
}

void unfill_screen(void)
{
 //&arg1 = Will unfill screen &arg1 times.. in case fill_screen was called more than once for some reason.
 &save_x = &arg1;
 unfill_screen:
  external("dc-f", "sprite_retrieve", 0, 0, 426344);
  &save_y = &return;
  if (&save_y > 0)
  {
   sp_active(&save_y, 0);
  }
  if (&save_x < &arg1)
  {
   &save_x += 1;
   goto unfill_screen;
  }
  
 kill_this_task();
}

void fill_screen_black(void)
{
 //create a black full screen (640x480) sprite covering the screen, including status bar and side bars.
 //An alternative to fill_screen(0), which doesn't cover sprites or animated tiles.
 //&arg1 = custom clip left
 //&arg2 = custom clip top
 //&arg3 = custom clip right
 //&arg4 = custom clip bottom
 //&arg5 = custom depth que, otherwise 9999
 //&arg6 = pass 1 to enable noclip of the sprite

 //fill screen with a 640x480 black sprite
 &save_x = create_sprite(426, 344, 0, 64, 11);
 sp_custom("sprite-id", &save_x, 426344);
 sp_nohit(&save_x, 1); 
 
 //que and noclip
 if (&arg5 <= 0)
 {
  sp_que(&save_x, 9999);
 }
 else
 {
  sp_que(&save_x, &arg5);
 }
 if (&arg6 > 0)
 {
  sp_noclip(&save_x, 1);
 }

 //initiate clipping setup
 sp_clip_bottom(&save_x, 480);
 sp_clip_right(&save_x, 640);

 //apply clipping
 if (&arg1 > 0)
 {
  sp_clip_left(&save_x, &arg1);
 }
 if (&arg2 > 0)
 {
  sp_clip_top(&save_x, &arg2);
 }
 if (&arg3 > 0)
 {
  sp_clip_right(&save_x, &arg3);
 }
 if (&arg4 > 0)
 {
  sp_clip_bottom(&save_x, &arg4);
 }

 kill_this_task();
}

void cooldown_timer(void)
{
 //MAX timer because of using a supervar stored in editor_seq for timer: 65535 (6 hours, 55 minutes, and 35 seconds)
   //If you specify any higher, it'll reduce to that automatically so it doesn't break things
   //I doubt anyone will need to go near this limit anyway
 //&arg1 = hours
 //&arg2 = minutes
 //&arg3 = seconds
 //&arg4 = player_map of specified editor sprite to use for info storage in editor_seq.
 //&arg5 = editor sprite number of sprite to use for info storage in editor_seq.
 //&arg6 = wait() time between loop checks of timer and player_map checks (if arg7 = -2). If not provided will default to wait(1)
 //&arg7 = Delay before timer starts. If -2, start on screen change.

  //can't pass this much stuff onto spawn (unless we are using like 8 globals to do it.
  //so let's create a sprite to hold the info, have the spawned script retrieve it all, then kill the sprite
  int &val1 = create_sprite(-234, -234, 99, 21, 1);
  sp_nohit(&val1, 1);
  sp_nodraw(&val1, 1);
  sp_custom("sprite-id", &val1, -234234);
  sp_custom("arg1", &val1, &arg1);
  sp_custom("arg2", &val1, &arg2);
  sp_custom("arg3", &val1, &arg3);
  sp_custom("arg4", &val1, &arg4);
  sp_custom("arg5", &val1, &arg5);
  sp_custom("arg6", &val1, &arg6);
  if (&return == 0)
  {
   sp_custom("arg6", &val1, 1);
  }
  
  sp_custom("arg7", &val1, &arg7);

  //spawn the script
  spawn("dc-tm");
}

void cooldown_resume(void)
{
 //Pass the player_map, and editor sprite number being used as var, as &arg values in pairs
 //eg. &arg1 = player_map, &arg2 = editor_sprite number. 
 //    &arg3 = player_map, &arg4 = editor_sprite number. 
 //    etc.
 //There's 2 ways to pass a custom wait() time to be used between goto loops for the timers when resuming the cooldown timers
   //Method 1: pass a custom wait() to &arg7 and don't pass anything to &arg8. &arg7 wait() value will be used for all resumed timers
   //Method 2: Pass it along with the player map in the following format: wwwwmmm (where wwww is the wait time and mmm is the player_map)
   //          It will be treated as a supervar and automatically extracted by this funcion. This method allows unique wait() value per timer
   //          Example.. let's say you were resuming a timer on &player_map 27 and want a wait time of 100, this would be: 0100 027 (or 100027)
   //IF both method 1 and method 2 are for some reason provided, method 2 will take priority for any entry that includes it.
 
 int &val1 = 1;
 int &val2;
 int &val3;
 int &val4;
 
 cd_res_loop:
  if (&val1 == 1)
  {
   &save_x = &arg1;
   &save_y = &arg2;
  }
  if (&val1 == 2)
  {
   &save_x = &arg3;
   &save_y = &arg4;
  } 
  if (&val1 == 3)
  {
   &save_x = &arg5;
   &save_y = &arg6;
  }
  if (&val1 == 4)
  {
   &save_x = &arg7;
   &save_y = &arg8;
  }
  
  if (&save_x <= 0)
  {
   goto cd_res_end;
  }
  
  if (&save_y <= 0)
  {
   goto cd_res_end;
  }
  
  //reset editor_frame of specified sprite (editor_frame stores the script number of the timer script)
  if (&player_map != &save_x)
  {  
   if (&save_x > 768)
   {
    //this is a supervar with wait time attached to it - extract player_map
    math_mod(&save_x, 1000);
    external("dc-f", "remoteframe", &return, &save_y, 0);
   }
   else
   {
    external("dc-f", "remoteframe", &save_x, &save_y, 0);
   }
  }
  else
  {
   editor_frame(&save_y, 0);
  }
     
  //get the remaining timer count
  if (&player_map != &save_x)
  {
   if (&save_x > 768)
   {
    //this is a supervar with wait time attached to it - extract player_map
    math_mod(&save_x, 1000);
    external("dc-f", "remoteseq", &return, &save_y, -1);
    &val4 = &return;
   }
   else
   {
    external("dc-f", "remoteseq", &save_x, &save_y, -1);
    &val4 = &return;
   }
  }
  else
  {
   &val4 = editor_seq(&save_y, -1);
  }
  
  if (&val4 > 0)
  {
   //the value of &val4 will now be hours, minutes, and seconds.
    //Stored in a super var in the following format: hmmss.
  
    //extract hours
    external("dc-f", "svar_extract", &val4, 5, 10);
    &vision = &return;
    
    //extract minutes
    external("dc-f", "svar_extract", &val4, 2, 100);
    &val2 = &return;
    
    //extract seconds
    external("dc-f", "svar_extract", &val4, 1, 100);
    &val3 = &return;
    
    //get the wait time to use between goto loops in the timer
    &val4 = 0;
    if (&arg8 <= 0)
    {
     if (&arg7 > 0)
     {
      &val4 = &arg7;
     }
    }
    if (&save_x > 768)
    {
     //this is a supervar with wait time attached to it - extract wait time
     &val4 = &save_x;
     &val4 /= 1000;
     &val4 = math_mod(&val4, 10000);
    }
    if (&val4 == 0)
    {
     &val4 = 1;
    }

  external("dc-f", "cooldown_timer", &vision, &val2, &val3, &save_x, &save_y, &val4);
 }
  
  if (&val1 < 4)
  { 
   &val1 += 1;
   goto cd_res_loop;
  }
 
 cd_res_end:
  return(&val1);
  kill_this_task();
}

void svar_extract(void)
{
 //&arg1: entire variable
 //&arg2: place (1=far right)
 //arg3: base (eg. 10, 100, 1000, etc)
 
 int &times = &arg2;
 int &rest = &arg1;
 int &value;

 svar_extractloop:
  &value = math_mod(&rest, &arg3);
  &rest /= &arg3;
  &times -= 1;
  
  if (&times != 0)
  {
   goto svar_extractloop;
  }

 return(&value);
}

void svar_store(void)
{
 //&arg1: entire variable
 //&arg2: place (1 = far right)
 //arg3: base (eg. 10, 100, 1000, etc)
 //arg4: new number  
 
 external("dc-f", "svar_extract", &arg1, &arg2, &arg3);
 
 int &total = &arg1;
 int &new = &arg4;
 &new -= &return;
 int &times = &arg2;
 
 svar_storeloop:
  if (&times != 1)
  {
   &new *= &arg3;
   &times -= 1;
   goto svar_storeloop;
  }

 &total += &new;

 return(&total);
}

void precise_wait(void)
{
 //this wait runs off the internal timer that starts when the engine is launched and is accurate, unlike using regular wait()
 //&arg1 = amount of milliseconds to wait
 //&arg2: if 1, will compare against a sprite with frame delay of 1 to try and keep up with a 'tab' speedup.
   //&arg3: sequence to use for above change (sequence will be created and nodrawn)
 int &val1;
 int &val2;
 
 &val1 = sp_attack_wait(1, -1);
 precise_wait:
  &val2 = sp_attack_wait(1, -1);
  &val2 -= &val1;
  if (&val2 < &arg1)
  {
   wait(1);
   goto precise_wait;
  }
 
 kill_this_task();
}