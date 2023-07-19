#ifndef __LOG_H__
#define __LOG_H__

namespace Log
{
   enum Level
   {
      L_SILENT = 0,  //!<< Nothing
      L_ERROR = 1,   //!<< Errors only
      L_INFO = 2,    //!<< + Info messages
      L_DEBUG = 3    //!<< + Debug Messages
   };

   void SetLevel(Level l);
   void Add(const Level level, const char* s, ...);
}

#define log(lvl, msg, ...)                                              \
   {                                                                    \
      Log::Add(lvl, "[%s:%d] " msg, __FILE__, __LINE__, ##__VA_ARGS__); \
   }                                                                    \
   (void)0

// Log sans file/line (vanilla)
#define vlog(lvl, msg, ...)                                             \
   {                                                                    \
      Log::Add(lvl, msg, ##__VA_ARGS__);                                \
   }                                                                    \
   (void)0



#endif  //__LOG_H__
