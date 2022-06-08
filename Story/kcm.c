//called by dc-f.c as part of the fix for the bugged DinkC function "kill_cur_magic"
void main(void)
{
  script_attach(0);
  kill_cur_magic();
}

void killscript(void)
{
 //so we can force kill the script remotely
 //(the buggy kill_cur_item command stops the script executing
 //so a kill this task won't even kill it!
 kill_this_task();
}

