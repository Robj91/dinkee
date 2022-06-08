//Robj's dinkC spawned cooldown timer - saved in an editor sprite's info instead of a global
//uses 3 local vars and 2 juggle vars (&save_x, and &save_y are used as juggle globals in this case)
//spawned from "cooldown_timer" procedure in script "dc-f.c"

void main(void)
{
 //decalre locals
 int &tstart;
 int &ttotal;
 int &m_s_w;
 
 //search for and find the correct temp sprite holding our values we need passed to this script
 //temp sprite wil be brain 99 and have a sprite id of -234234
 external("dc-f", "sprite_retrieve", 99, 99, -234234);
 &tstart = &return;
 
 //check to see if a timer script was already spawned for this sprite
 &save_x = sp_custom("arg4", &tstart, -1);
 &save_y = sp_custom("arg5", &tstart, -1);
 if (&save_x != &player_map)
 {
  external("dc-f", "remoteframe", &save_x, &save_y, -1);
  &save_y = &return;
 }
 else
 {
  &save_y = editor_frame(&save_y, -1);
 }
 if (&save_y > 0)
 {
  //there's a currently running timer script spawned by this sprite
  //kill the old one off before starting the new one - only 1 timer per editor_sprite!
  run_script_by_number(&save_y, "killscript");
 }
 
 //save the current script number in the editor_frame of the chosen editor sprite
   //and also make sure editor_seq is set to 0
 &save_x = sp_custom("arg4", &tstart, -1);
 &save_y = sp_custom("arg5", &tstart, -1);
 if (&save_x != &player_map)
 {
  external("dc-f", "remoteframe", &save_x, &save_y, &current_script);
  external("dc-f", "remoteseq", &save_x, &save_y, 0);
 }
 else
 {
  editor_frame(&save_y, &current_script);
  editor_seq(&save_y, 0);
 } 
 
 //convert hours to milliseconds
 &ttotal = sp_custom("arg1", &tstart, -1);
 &ttotal *= 60;
 &ttotal *= 60;
 &ttotal *= 1000;
 sp_custom("hours_ms", &tstart, &ttotal);
 
 //convert minutes to milliseconds
 &ttotal = sp_custom("arg2", &tstart, -1);
 &ttotal *= 60;
 &ttotal *= 1000;
 sp_custom("minutes_ms", &tstart, &ttotal); 

 //convert seconds to milliseconds
 &ttotal = sp_custom("arg3", &tstart, -1);
 &ttotal *= 1000;
 sp_custom("seconds_ms", &tstart, &ttotal); 
 
 //add them all together
 //After this, &ttotal now contains the total timer amount in milliseconds
 &ttotal = sp_custom("hours_ms", &tstart, -1);
 &save_x = sp_custom("minutes_ms", &tstart, -1);
 &save_y = sp_custom("seconds_ms", &tstart, -1); 
 &ttotal += &save_x;
 &ttotal += &save_y;

 //save timer info in editor_seq - timer reamining(in hrs,min,sec).
   //saved in a supervar in the following format: hmmss
 //seconds
 &save_x = &ttotal;
 &save_x /= 1000;
 &save_x = math_mod(&save_x, 60);
 external("dc-f", "svar_store", 0, 1, 100, &save_x);
 &save_y = &return;
 
 //minutes
 &save_x = &ttotal;
 &save_x /= 1000;
 &save_x /= 60;
 &save_x = math_mod(&save_x, 60);
 external("dc-f", "svar_store", &save_y, 2, 100, &save_x);
 &save_y = &return;
 
 //hours
 &save_x = &ttotal;
 &save_x /= 1000;
 &save_x /= 60;
 &save_x /= 60;
 external("dc-f", "svar_store", &save_y, 5, 10, &save_x);
 &vision = &return;
   
 &save_x = sp_custom("arg4", &tstart, -1);
 &save_y = sp_custom("arg5", &tstart, -1);
 if (&save_x != &player_map)
 {
  external("dc-f", "remoteseq", &save_x, &save_y, &vision);
 }
 else
 {
  editor_seq(&save_y, &vision);
 }

 //Store editor player_map(0-768), editor sprite number(0-99), and wait time(0-9999) in &m_s_w as a supervar.
 //this means we don't need to waste a global for each different timer in the game.
 //The values will be represented like this: mmmsswwww
   //store "m" (player map/arg4), position 3 (from the right), base 1000(0-999, or a 3 digit number)
   &save_x = sp_custom("arg4", &tstart, -1);
   external("dc-f", "svar_store", &m_s_w, 3, 1000, &save_x); 
   &m_s_w = &return;
   
   //store "s" (editor sprite/arg5), position 3, base 100(0-99, or a 2 digit number)
   &save_x = sp_custom("arg5", &tstart, -1);
   external("dc-f", "svar_store", &m_s_w, 3, 100, &save_x); 
   &m_s_w = &return;
   
   //store "w" (wait() between loops/arg6), position 1, base 10000(0-9999, or a 4 digit number)
   &save_x = sp_custom("arg6", &tstart, -1);
   external("dc-f", "svar_store", &m_s_w, 1, 10000, &save_x); 
   &m_s_w = &return;

 //check if timer has a delay on it
 &save_x = sp_custom("arg7", &tstart, -1);
 if (&save_x != 0)
 {
  if (&save_x == -2)
  {
   //start timer on next screen change
   //free up &tstart so we can use it - kill the temp sprite off
   sp_kill_wait(&tstart, 1);
   &tstart = &player_map;
   pmap_loop:
    if (&player_map == &tstart)
    {
     &save_y = &m_s_w;
     &save_y = math_mod(&m_s_w, 10000);
     wait(&save_y);
     goto pmap_loop;
    }
    else
    {
     goto start_timer;
    }
  }
  else
  {
   wait(&save_x);
  }
 }
 
 //kill off the temp sprite we used to pass values to spawn
 sp_active(&tstart, 0);

start_timer: 
 //start the timer - get the engine's uptime in milliseconds (checking attack wait on any active sprite returns this value)
 //this is more accurate than wait()
 //we can just check it on sprite 1 (the player sprite)
 &tstart = sp_attack_wait(1, -1);
 
 //loop to check if time has passed
 timerloop:
  &save_x = sp_attack_wait(1, -1);
  &save_x -= &tstart;
  if (&save_x < &ttotal)
  {
   //the uptime in millseconds since first checking has not increased by the required total timer time.
   //extract the loop time from supervar &m_s_w and loop.
   &save_y = &m_s_w;
   &save_y = math_mod(&m_s_w, 10000);
   wait(&save_y);
   goto timerloop;
  }

 //timer has expired - reset editor_seq on original sprite
 //first extract the info from &m_s_w

 //extract the player map
 external("dc-f", "svar_extract", &m_s_w, 3, 1000);
 &tstart = &return;

 //extract the editor sprite number
 external("dc-f", "svar_extract", &m_s_w, 3, 100);
 &ttotal = &return; 
 
 //use the info to reset the editor_seq of the editor_seq of the specified sprite
 if (&player_map != &tstart)
 {
  external("dc-f", "remoteseq", &tstart, &ttotal, 0);  
 }
 else
 {
  editor_seq(&ttotal, 0);
 }
 
 //we are done
 kill_this_task();
}

void game_saved(void)
{
 //get the total time remaining
 &save_x = sp_attack_wait(1, -1);
 &save_x -= &tstart;
 &ttotal -= &save_x;
 
 //retrieve the editor_seq value of the specified sprite
 //extract the player map
 external("dc-f", "svar_extract", &m_s_w, 3, 1000);
 &tstart = &return;
  
 //extract the editor sprite number
 external("dc-f", "svar_extract", &m_s_w, 3, 100);
 &m_s_w = &return;
 
 if (&tstart != &player_map)
 {
  external("dc-f", "remoteseq", &tstart, &m_s_w, -1);
  &save_y = &return;
 }
 else
 {
  editor_seq(&m_s_w, -1);
  &save_y = &return;
 } 

 //store hours, minutes and seconds
 //saved in a supervar in the following format: hmmss
 //seconds
 &save_x = &ttotal;
 &save_x /= 1000;
 &save_x = math_mod(&save_x, 60);
 external("dc-f", "svar_store_d", &save_y, 1, 100, &save_x);
 &save_y = &return;
 
 //minutes
 &save_x = &ttotal;
 &save_x /= 1000;
 &save_x /= 60;
 &save_x = math_mod(&save_x, 60);
 external("dc-f", "svar_store", &save_y, 2, 100, &save_x);
 &save_y = &return;
 
 //hours
 &save_x = &ttotal;
 &save_x /= 1000;
 &save_x /= 60;
 &save_x /= 60;
 external("dc-f", "svar_store", &save_y, 5, 10, &save_x);
 &save_y = &return;

 //save value in editor_seq of specified sprite
 if (&tstart != &player_map)
 {
  external("dc-f", "remoteseq", &tstart, &m_s_w, &save_y);
 }
 else
 {
  editor_seq(&m_s_w, &save_y);
 } 

 //resume the timer
 &tstart = &save_y;
 goto start_timer;
}

void killscript(void)
{
 kill_this_task();
}