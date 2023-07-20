#ifndef VISUAL_TEXT_H
#define VISUAL_TEXT_H
#include <string>
#include <stdint.h>
#include <GLES2/gl2.h>

#include "IVisual.h"
#include "Color.h"
class RenderPacket;

namespace BaxGUI
{
   class Widget;

   class VisualText : public IVisual
   {
     protected:
      //! @brief Only factory methods can construct Visual objects.
      VisualText(Widget* pParent);

     public:
      virtual ~VisualText();
      // *** Derived classes must provide pure virtual methods
      virtual bool Instantiate(bool bActivate);
      virtual void Update(float fTime);
      virtual void Draw();

      static VisualText* createText(Widget* pParent, const ScreenRect& r, const Color& c, const char* pFontSpec, const char* pContent, bool bTrim);
     private:

      RenderPacket* mpRenderPacket;
      void LoadVertexData();
      std::string msFilename;

      std::string mFontName;
      Color mColor;
      std::string mContent;

      uint32_t w,h;
      GLuint mOGLHandle;

      bool mbTrim;
   };
}

#endif  // VISUAL_TEXT_H
