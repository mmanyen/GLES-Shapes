#include "Log.h"
#include <stdarg.h>
#include <stdio.h>

namespace Log
{
   static Level sCurrentLevel = L_DEBUG;

   void SetLevel(Level l) { sCurrentLevel = l; }
   void Add(const Level level, const char* s, ...)
   {
      // dis-allow logging to L_SILENT
      if ((level == L_SILENT) || (sCurrentLevel == L_SILENT))
         return;

      va_list vl;
      va_start(vl, s);

      // TODO: Redirect this to a file, network, com port or whatever
      // TODO: std::string stream?
      if (level <= sCurrentLevel)
      {
         vfprintf(stdout, s, vl);
         fflush(stdout);
      }

      va_end(vl);
   }
}
