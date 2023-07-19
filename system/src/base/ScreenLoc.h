#ifndef __SCREEN_LOC_H__
#define __SCREEN_LOC_H__

#include <stdint.h>

   class ScreenLoc
   {
     public:
      //! @brief Basic Constructor
      //! @param[in] nx X location (optional)
      //! @param[in] ny Y location (optional)
      ScreenLoc(float nx = 0.0f, float ny = 0.0f) : x(nx), y(nx) {}
      //! @brief Construct from string
      //! @param[in] pString String containing location info
      //! @param[in] vw Virtual width of screen in pixels
      //! @param[in] vh Virtual height of screen in pixels
      ScreenLoc(const char* pString, int32_t vw, int32_t vh);
      //! @brief Destructor
      virtual ~ScreenLoc() {}

      float x, y;
   };


#endif  //__SCREEN_LOC_H__
