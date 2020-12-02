#include "ScreenRect.h"

#include <stdlib.h>
#include <string.h>

   static int32_t nextParam(const char* pString, char* pOut)
   {
      int32_t r = 0;
      while (pString[r] && pString[r] != ',')
      {
         pOut[r] = pString[r];
         r++;
      }
      pOut[r] = 0;
      if (pString[r] == ',')
         r++;
      return r;
   }

   ScreenRect::ScreenRect(const char* pString, int32_t vw, int32_t vh)
   {
      char param[6];
      int32_t i = 0;

      i += nextParam(&pString[i], param);
      x = -1.0f + ((atoi(param) / (float) vw) * 2.0f);
      i += nextParam(&pString[i], param);
      y = 1.0f - ((atoi(param) / (float) vh) * 2.0f);
      i += nextParam(&pString[i], param);
      w = 2.0f * (atoi(param) / (float) vw);
      i += nextParam(&pString[i], param);
      h = 2.0f * (atoi(param) / (float) vh);
   }


   bool ScreenRect::inside(float tx, float ty) const
   {
      bool bRet = true;
      if (tx < x) bRet = false;
      if (tx > (x+w)) bRet = false;

      if (ty > y) bRet = false;
      if (ty < (y-h)) bRet = false;

      return bRet;
   }

