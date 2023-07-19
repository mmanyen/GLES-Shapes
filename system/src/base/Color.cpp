//********************************************************************
//! @file
//! @brief The implementation for Color and Colors.
//!
//! Copyright (C) 2012 Gambro UF Solutions, Inc.  All rights reserved.
//********************************************************************
#include "Color.h"
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>

   Color::Color(float gray, float alpha)
   {
      mRGBA[0] = gray;
      mRGBA[1] = gray;
      mRGBA[2] = gray;
      mRGBA[3] = alpha;
   }

   Color::Color(float red, float green, float blue, float alpha)
   {
      mRGBA[0] = red;
      mRGBA[1] = green;
      mRGBA[2] = blue;
      mRGBA[3] = alpha;
   }

   Color::~Color() {}
   bool Color::operator==(const Color& rhs) const
   {
      return mRGBA[0] == rhs.mRGBA[0] && mRGBA[1] == rhs.mRGBA[1] && mRGBA[2] == rhs.mRGBA[2] &&
         mRGBA[3] == rhs.mRGBA[3];
   }

   bool Color::operator!=(const Color& rhs) const { return !(*this == rhs); }
   bool Color::operator>(const Color& rhs) const
   {
      if (mRGBA[0] != rhs.mRGBA[0])
         return mRGBA[0] > rhs.mRGBA[0];

      if (mRGBA[1] != rhs.mRGBA[1])
         return mRGBA[1] > rhs.mRGBA[1];

      if (mRGBA[2] != rhs.mRGBA[2])
         return mRGBA[2] > rhs.mRGBA[2];

      if (mRGBA[3] != rhs.mRGBA[3])
         return mRGBA[3] > rhs.mRGBA[3];

      return false;
   }

   bool Color::operator<(const Color& rhs) const
   {
      if (mRGBA[0] != rhs.mRGBA[0])
         return mRGBA[0] < rhs.mRGBA[0];

      if (mRGBA[1] != rhs.mRGBA[1])
         return mRGBA[1] < rhs.mRGBA[1];

      if (mRGBA[2] != rhs.mRGBA[2])
         return mRGBA[2] < rhs.mRGBA[2];

      if (mRGBA[3] != rhs.mRGBA[3])
         return mRGBA[3] < rhs.mRGBA[3];

      return false;
   }

   Color Color::operator*(const Color& rhs) const
   {
      return Color(mRGBA[0] * rhs.mRGBA[0], mRGBA[1] * rhs.mRGBA[1], mRGBA[2] * rhs.mRGBA[2],
                   mRGBA[3] * rhs.mRGBA[3]);
   }

   Color Color::operator+(const Color& rhs) const
   {
      return Color(mRGBA[0] + rhs.mRGBA[0], mRGBA[1] + rhs.mRGBA[1], mRGBA[2] + rhs.mRGBA[2],
                   mRGBA[3] + rhs.mRGBA[3]);
   }

   Color Color::operator-(const Color& rhs) const
   {
      return Color(mRGBA[0] - rhs.mRGBA[0], mRGBA[1] - rhs.mRGBA[1], mRGBA[2] - rhs.mRGBA[2],
                   mRGBA[3] - rhs.mRGBA[3]);
   }

   Color Color::FromRgb(int red, int green, int blue, int alpha)
   {
      return Color(red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f);
   }

   float Color::Alpha() const { return mRGBA[3]; }
   float Color::Red() const { return mRGBA[0]; }
   float Color::Green() const { return mRGBA[1]; }
   float Color::Blue() const { return mRGBA[2]; }
   static int32_t parseHexDigit(char hexDigit)
   {
      static const char* hexchars = "0123456789ABCDEF";
      int32_t r = 0;
      while (hexchars[r] && hexchars[r] != hexDigit)
         r++;

      return r;
   }

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

   Color::Color(const char* pString)
   {
      // is it a hashed html style?
      if (pString[0] == '#')
      {
         if (strlen(pString) >= 8)
         {
            int32_t one, two;

            // read hex type value #RRBBGGAA
            one = parseHexDigit(toupper(pString[1])) << 4;
            two = parseHexDigit(toupper(pString[2]));
            this->mRGBA[0] = (one + two) / 255.0f;
            one = parseHexDigit(toupper(pString[3])) << 4;
            two = parseHexDigit(toupper(pString[4]));
            this->mRGBA[1] = (one + two) / 255.0f;
            one = parseHexDigit(toupper(pString[5])) << 4;
            two = parseHexDigit(toupper(pString[6]));
            this->mRGBA[2] = (one + two) / 255.0f;
            one = parseHexDigit(toupper(pString[7])) << 4;
            two = parseHexDigit(toupper(pString[8]));
            this->mRGBA[3] = (one + two) / 255.0f;
         }
      }
      else
      {
         // is it a named color?
         if (!NamedColors::instance().Lookup(pString, *this))
         {
            // Read comma seperated values R,G,B (,A)
            char param[6];
            int32_t p = 0;
            int32_t i = 0;
            this->mRGBA[3] = 255;

            while (p < 4 && pString[i] != 0)
            {
               i += nextParam(&pString[i], param);
               this->mRGBA[p] = atoi(param) / 255.0f;
               p++;
            }
         }
      }
   }

   static std::map<std::string, Color> sColorNames;
   NamedColors::NamedColors() { sColorNames.clear(); }
   NamedColors& NamedColors::instance()
   {
      static NamedColors nc;

      return nc;
   }

   bool NamedColors::Add(const char* pName, const Color& out)
   {
      bool bRet = false;
      std::map<std::string, Color>::iterator it = sColorNames.find(pName);
      if (it == sColorNames.end())
      {
         sColorNames[pName] = out;
         bRet = true;
      }

      return bRet;
   }

   bool NamedColors::Add(const char* pName, const char* pColorSpec)
   {
      bool bRet = false;
      std::map<std::string, Color>::iterator it = sColorNames.find(pName);
      if (it == sColorNames.end())
      {
         sColorNames[pName] = Color(pColorSpec);
         bRet = true;
      }

      return bRet;
   }

   bool NamedColors::Lookup(const char* pName, Color& out)
   {
      bool bRet = false;
      std::map<std::string, Color>::iterator it = sColorNames.find(pName);
      if (it != sColorNames.end())
      {
         bRet = true;
         out = (*it).second;
      }
      return bRet;
   }

