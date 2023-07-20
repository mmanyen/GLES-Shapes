// Include this file after Log.h to disable all logging in the file.

#ifdef log
#undef log
#endif

#ifdef vaddlog
#undef vaddlog
#endif

#define log(lvl, msg, ...) {  }  (void)0
#define vaddlog(lvl, msg, ...) {  }  (void)0
