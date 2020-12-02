// Include this file after Log.h to disable all logging in the file.

#ifdef log
#undef log
#endif

#ifdef vlog
#undef vlog
#endif

#define log(lvl, msg, ...) {  }  (void)0
#define vlog(lvl, msg, ...) {  }  (void)0
