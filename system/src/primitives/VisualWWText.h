#ifndef VISUAL_WW_TEXT_H
#define VISUAL_WW_TEXT_H
#include <string>
#include <list>
#include <stdint.h>
#include <GLES2/gl2.h>

#include "IVisual.h"
#include "Color.h"

class RenderPacket;

namespace BaxGUI
{
   class Widget;
   class VisualText;

   class VisualWWText : public IVisual
   {
     protected:
      //! @brief Only factory methods can construct Visual objects.
      VisualWWText(Widget* pParent);

     public:
      virtual ~VisualWWText();
      // *** Derived classes must provide pure virtual methods
      virtual bool Instantiate(bool bActivate);
      virtual void Update(float fTime);
      virtual void Draw();

      virtual void Move(float x, float y);

      static VisualWWText* createWWText(Widget* pParent, const ScreenRect& r, const Color& c, const char* pFontSpec, const char* pContent, bool bTrim);

     private:
      std::string mFontName;
      Color mColor;
      std::string mContent;
      std::list<std::string> mTokens;
      std::list<VisualText*> mRenders;
   };
}

#endif  // VISUAL_WW_TEXT_H
