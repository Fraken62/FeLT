
README for FeLT 1.0 Release.

Felt: FRAKEN's LOAD TESTER.  I added the e because FLT sounds dumb. -Fraken

   For testing the CPU use part of utility tools and such.

This program does nothing but allow you to load up a CPU for testing.  I needed a 
way to load the CPU to get a feel for how the CPU code in my "Teeny Tiny System Monitor" 
for FreeBSD. (https://github.com/Fraken62/Frakens-TTSM).  It's not meant as sort of 
system stability tester though.  You could probably abuse it for that reason, but 
it's not designed for it.  If you're making some program that includes checking 
CPU load, this is the program for you.

VERSION: 1.0 Release.  

   There probably won't be another version.

BUILD REQUIREMENTS:

   If you have a linux or BSD machine that has a C build environment, you're probably fine.
   Heck, you might even cajole it to compile on windows.

BUILDING FeLT:

   DO NOT TRY AND OPTIMIZE IT.

   Type "make".  

   If you've fiddled with the code, type "make clean" and then type "make" or "make clean && make"

RUNNING FeLT:

   Trivial use: Running with defaults, type "./felt".  This will run FeLT for 5 seconds with 4 threads at 100% cpu use.

   More complex use:

      -t Thread count: 
         How many threads to run. Example: 4 threads will saturate a 2C/4T CPU.

      -l Load time:
         Time to run at 100 percent compute for each thread (In seconds).

      -i Idle time:
         Time to sit at 0 percent compute for each thread (Also in seconds)

      -c Number Of Cycles:  
         Number of cycles of load/idle/load/idle/etc to do before exiting.

      Example: ./felt -t 2 -l 5 -i 10 -c 10

      This will run FeLT for 10 cycles of running with 2 threads where the CPU is loaded to 100% for 5 seconds, then idles for 10 seconds.

NOTES:

   This is important: DO NOT TRY AND OPTIMIZE THIS PROGRAM!  All you're going to be 
   doing is probably making the compiler inlining a bunch of stuff that's not intended 
   to be inlined to speed up what is SUPPOSED to be slow.  This programs *entire purpose* 
   is to waste clock cycles...  I added volatile keywords to the variable declarations 
   that matter, but just don't do it anyway.  It's a teeny tiny little program that runs 
   exceedingly rarely and it's MEANT to waste clock cycles.  Optimizing that is like 
   having size 16 feet, but buying kids shoes because they're cheaper.

   IT'S NOT GOING TO FIT!!!  DON'T OPTIMIZE IT!!!

NOTES FROM THE AUTHOR:

   Originally, I made this for myself to just test stuff like TTSM and such but realized 
   that it's a good project to publish.  It's very small and simple, but shows many of 
   the things you need in a real C program ranging from sucking in console arguments to 
   making sure that some range/mix of them don't blow things up to spawning threads and such.  
   Myself, until TTSM, the last C code I had written prior was when I was still working 
   as a programmer so I had to refresh all of this stuff as well, but it's still a good 
   example anyway.  In today's world where you can hammer out half functional code with 
   A.I., I don't know how relevant it is, but I have a few things to say about that as well...

   Even when I decided I'd just have A.I. look over this project as a last check before 
   tarring it up and uploading it, A.I. half shat itself.  This is a TRIVIAL program...  
   I can't stress that enough.  It's barely a hello world with arguments, and yet even 
   Google Gemini made all kinds of errors.  It claimed I should be compiling with -O2 
   even after talking about how it was good that I had added the "volatile" keyword 
   (Full disclosure, that was a prior tip A.I. had given me in case someone decided 
   to do -O2 anyway).  It's smart enough to recognize the need for adding volatile, 
   then makes it a point to specify that I should be optimizing the code even after it 
   had specifically acknowledged our previous discussion that there should be *no* 
   optimizations.  Hell, it's even in the code comments to give Gemini a hint!

   My point here is that while A.I. is clearly helpful, I suspect it's going to be a 
   while before we can just hand the proverbial reigns over to it.  This is as trivial 
   as a C project gets and even here, it's kind of got the tail wagging the dog.  
   If you haven't done any code work for a while and you want to use A.I., you may 
   need to argue with it a bit. :)  It IS helpful at times though.  This program was 
   trivial, but in the case of my TTSM program, it took development from probably 
   half a year or more and *brutal* clawing and scratching to get done, 
   down to something like 3 weeks.  For an old guy like me with serious 
   cognitive and memory issues, A.I. has been a tremendous boon to jog memory, 
   bounce ideas off of and such.  I just have to make sure to pay attention because
   it seems to do some pretty stupid things sometimes! :)

   YMMV...

   -Fraken
