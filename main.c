
/********************************************************************

 ███████████          █████       ███████████
░░███░░░░░░█         ░░███       ░█░░░███░░░█
 ░███   █ ░   ██████  ░███       ░   ░███  ░ 
 ░███████    ███░░███ ░███           ░███    
 ░███░░░█   ░███████  ░███           ░███    
 ░███  ░    ░███░░░   ░███      █    ░███    
 █████      ░░██████  ███████████    █████   
░░░░░        ░░░░░░  ░░░░░░░░░░░    ░░░░░    
(Who even does ascii art/text anymore!?!)

   FeLT 1.0 RELEASE

   FeLT: A TRIVIAL LOAD TESTER                                                              
                                                                                                        
   FeLT Fraken's (e) Load Tester.  The "e" is because FLT isn't a word.  Just loads the CPU for a bit and exits.  It's helpful for testing.  Half stolen from TTSM, half ripped apart and rekerjiggered by me, half of it suggestions from A.I.  I'll leave it to you to decide which half is which.  The ironic part is that I used this to test how I like various defaults for TTSM.  Are the time paradox police about to show up?

   If you want to vastly increase how long it can run (aka, bump up the sanity counter), the
   variable you want is "MaxLoadTime".  It's in seconds and there's really no practical limit
   as to how big you make it.  I just added it so people don't accidentally run it and wonder
   why it won't exit and why the CPU is at 100% and freak out in a panic.  That way, if you know
   what you're doing to change it, you probably know how to kill it too.
   
   "Sometimes it's *not* imposter syndrome, sometimes I'm just bad..."  -Fraken

**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

// Woo! Globals!  A trivial way to talk to threads.  It's fine.. IT'S FINE!! -Fraken.
// Full disclose: Gemini told me to use volatile.  My solution was to chastise people
// in the readme with "DO NOT OPTIMIZE".  Fine.  We'll do it this way.  
// IT'S FINE! IT'S FINE! DON'T OPTIMIZE ANYWAY!!!
// (Would you believe my youtube channel is called "Crabby Old Buggers"? (COBS))

volatile int Idle = 0;
volatile int Exit = 0;

void* threadFunc(void* arg) {
   
   // Worker threads.  All they do is waste cycles
   // until we tell em to knock it off. -Fraken
 
   //I still want to chastise someone though  It's fine I guess...  -Fraken
   volatile int j; 
   int threadNum = *(int*)arg;
   printf("Thread %d: running.\n", threadNum);

    while (Exit==0){
      if (Idle==0){
         //do work
         for (j=0; j<1000000; j++ ){
            // Embigging a j for a while because k was taken...
            //just whiling away, making a number bigger.  Then making
            // it smaller once it's big.  Then making it bigger again.
         }
      }
      else{
         //sleep and don't do work
         usleep(10000); //sleep for 1/10th of a second
      }
   }
   pthread_exit(NULL);
}

void help(){

   printf("\n\n      FeLT 1.0 Release (And there probably won't be another)");
   printf("\n----------------------------");
   printf("\nFeLT... FrakEn's Load Tester");
   printf("\n");
   printf("\nPurpose: A basic CPU loading tool.  I needed something trivial to test TTSM");
   printf("\nwith and I decided to release it too, so here you are...");
   printf("\nFeLT can load your CPU up with a user configurable number of threads (default is 4)");
   printf("\nand can also cycle back and forth from no load to full load as many times as you");
   printf("\nspecify.  By default, FeLT will run 4 threads for 3 seconds and exit.");
   printf("\nIf you want different settings, you can specify them with the -t, -l, -i and -c flags");
   printf("\n");
   printf("\n -t Thread count. How many threads to run. Example: 4 threads will saturate a 2C/4T CPU.");
   printf("\n -l Load time to run at 100 percent compute for each thread (In seconds).");
   printf("\n -i Idle time to sit at 0 percent compute for each thread (Also in seconds)");
   printf("\n -c Cycles.  Number of cycles of load/idle/load/idle/etc to do before exiting.");
   printf("\n");
   printf("\n    Example: ./felt -t 2 -l 5 -i 10 -c 10");
   printf("\n");
   printf("\nThis will run FeLT with 2 threads at 100 percent CPU use for 5 seconds, and");
   printf("\nthen drop to idle for 10 seconds and repeat this for 10 cycles.");
   printf("\n");
   printf("\nQuote: 'Because flt isn't a word.  So I added an e.' -Fraken");
   printf("\n");
   return;
}

int main(int argc, char *argv[]){

   //Unlike a 'dungeon soup' cartoon where you 'know it's good because...'
   //you know a human wrote a good chunk of this, because it's bad. :P -Fraken

   // Lower entire process priority before spawning threads.
   // I'd like to make this idprio, but not everyone can be r00t I guess.
   // If this fails on linux, just comment it out.  This is just so the 
   // machine doesn't become unresponsive.
   if (nice(19) == -1 && errno != 0){
      perror("nice");
   }
  
   //*********************   GRABBING SETUP DATA   ******************************

      //Basic configuration variables
   int Threads  = 4;  //Number of threads to load up. Valid values, 1 to total core count.
   int LoadTime = 5;  //Amount of time to run the cores
   int IdleTime = 0;  //How long we sit at 0% cpu use in between load periods.
   int Cycles   = 1;

      //Some reasonable limits so we don't blow the lid off.
   int MaxThreads    = 128;   //Threadripper?
   int MaxLoadTime   = 60;    //One minute load. 
   int MaxIdleTime   = 60;    //One minute idle.
   int MaxCycles     = 30;    //And, one hour on/off at most.. YAY! I can math nao! -Fraken

   printf("\nMax Values: Threads: %i, Load Time: %i, Idle Time: %i, Max Cycles: %i\n",
            MaxThreads, MaxLoadTime, MaxIdleTime, MaxCycles);

	/* DEAL WITH COMMAND LINE ARGUMENTS */
   for (int i = 1; i < argc; i++) {
      if (strlen(argv[i]) == 2 && argv[i][0] == '-') {
      	char option = argv[i][1];
      	if (i + 1 >= argc) {
            // use '' instead of "" to fix the char pointer issue
         	if (option == 'h'){
            	help();
            	return 1;
         	}
            printf("Option -%c requires a value\n", option);
            printf("Use the -h flag for help.  Example: ./felt -h \n");
            return 1;
      	}
      	char *value = argv[i + 1];
      	int intValue = atoi(value);
      	switch (option) {
         	case 't':
            	Threads = intValue;
               if(Threads<1){ 
                  Threads = 1;
                  printf("\nOut of bounds thread value, setting it to 1\n");
               }
               if(Threads>MaxThreads){
                  Threads = MaxThreads;
                  printf("\nThreads beyond reasonable bounds. Setting to %i\n", MaxThreads);
               }
               break;
      	}
         switch (option) {
         	case 'l':
               if (LoadTime<1){
                  LoadTime = 1;
                  printf("\nCPU Load time should be at least 1.  Setting it t 1\n");
               }
               if (LoadTime > MaxLoadTime){
                  LoadTime = MaxLoadTime;
                  printf("\nMaximum time to load CPU per cycle to high. Setting to %i\n", MaxLoadTime);
               }
            	LoadTime = intValue;
               break;
      	}
         switch (option) {
         	case 'i':
               if (IdleTime<1){
                  IdleTime=1;
                  printf("\nIdle time was set below 1, resetting to 1\n");
               }
               if (IdleTime>MaxIdleTime){
                  IdleTime=MaxIdleTime;
                  printf("\nIdle time was set higher than %i, setting it to %i\n", MaxIdleTime, MaxIdleTime);
               }
            	IdleTime = intValue;
               break;
      	}
         switch (option) {
         	case 'c':
            	Cycles = intValue;
               if(Cycles<1){
                  Cycles=1;
                  printf("\nNumber of cycles set below 1, bumping it up to 1...\n");
               }
               if(Cycles>MaxCycles){
                  printf("\nCycles set past sane values.  Reducing to %i\n", MaxCycles);
                  Cycles=MaxCycles;
               }
               break;
      	}
      	i++;
   	} 
	}
	//****************** END GRABBING SETUP DATA   ***************************

   //Before we start, let's give the user basic use information:
   printf("\n Hit control-c to exit early or -h for help. -Fraken\n\n");
   printf("\nRunning with %i CPU threads, %i seconds of load time, %i seconds of idle time and %i cycles\n\n", Threads, LoadTime, IdleTime, Cycles);

   //Create a home for threads.  You'd never guess by the name of these funcs/args!
   pthread_t* threads = malloc(sizeof(pthread_t) * Threads);
   int* threadIds = malloc(sizeof(int) * Threads);
   if (!threads || !threadIds) {
      perror("malloc");
      return EXIT_FAILURE;
   }

   //Put our threads in our home.  GO TO YOUR HOME!
   for (int i = 0; i < Threads; i++) {
      threadIds[i] = i;
      int rc = pthread_create(&threads[i], NULL, threadFunc, &threadIds[i]);
      if (rc != 0) {
         fprintf(stderr, "Error: pthread_create failed for thread %d\n", i);
         Threads = i; // Adjust join count
         break;
      }
   }

   //This simply prevents you from seeing things out of order as things spool up.
   //otherwise, you might see "Starting load cycle" before all the threads report.
   usleep(200000);

   //Let's talk to our threads by the globals.  Load and idle baby! WOO! -Fraken
   int Cycle = 0;
   for (Cycle=0; Cycle<Cycles; Cycle++){
      printf("\nStarting load cycle # %i...\n", Cycle);
      Idle=0;
      sleep (LoadTime);
      printf("\nStarting sleep cycle # %i\n", Cycle);
      Idle=1;
      sleep (IdleTime);
   }

   Exit=1;

   // Wait for all threads to finish
   for (int i = 0; i < Threads; i++) {
      pthread_join(threads[i], NULL);
   }

   printf("All threads joined. Exiting.\n");

   free(threads);
   free(threadIds);

   return EXIT_SUCCESS;
}