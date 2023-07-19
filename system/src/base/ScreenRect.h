#ifndef __SCREEN_RECT_H__
#define __SCREEN_RECT_H__
#include <stdint.h>
#include <algorithm>

   class ScreenRect
   {
     public:
      ScreenRect(float nx = 0.0f, float ny = 0.0f, float nw = 0.0f, float nh = 0.0f)
         : x(nx), y(ny), w(nw), h(nh)
      {
      }

      ScreenRect(const char* pString, int32_t vw, int32_t vh);
      virtual ~ScreenRect() {}
      float x, y, w, h;

      bool inside(float tx, float ty) const;

      //! @brief Move the current screen location (no change to dimensions)
      //! @param[in] nx screen location x
      //! @param[in] ny screen location y
      virtual void Move(float nx, float ny)
      {
         x = nx;
         y = ny;
      }
      //! @brief Union.
      //! @param[in] rhs Addend Rect.
      ScreenRect& operator|=(const ScreenRect& rhs)
      {
         float left = std::min(x, rhs.x);
         float right = std::max(x + w, rhs.x + rhs.w);
         float top = std::max(y, rhs.y);
         float bottom = std::min(y - h, rhs.y - rhs.h);

         x = left;
         w = right - left;
         y = top;
         h = top - bottom;

         return *this;
      }
      //! @brief Intersection.
      //! @param[in] rhs operand Rect.
      ScreenRect& operator&=(const ScreenRect& rhs)
      {
         float left = std::max(x, rhs.x);
         float right = std::min(x + w, rhs.x + rhs.w);
         float top = std::min(y, rhs.y);
         float bottom = std::max(y - h, rhs.y - rhs.h);

         x = left;
         w = right - left;
         y = top;
         h = top - bottom;

         return *this;
      }
   };


#endif  //__SCREEN_RECT_H__
