#ifndef BASE_SPRITE_H
#define BASE_SPRITE_H
#include "glad/glad.h"
#include <GLES2/gl2.h>
#include <stdint.h>
#include <string>

#include "Color.h"
#include "ScreenRect.h"
#include "IPrimitive.h"

class RenderPacket;

class BaseSprite : public IPrimitive
{
   public:
    BaseSprite();
    BaseSprite(const ScreenRect& r, const char* pImageSpec);
    virtual ~BaseSprite();
    // *** Derived classes must provide pure virtual methods
    virtual void Instantiate() override;
    virtual void Draw() override;

    void SetImage(const char* pImageSpec);
    
    const ScreenRect& SetScreenLocation() {return mScreen;}
    void SetScreenLocation(const ScreenRect& r);

    //    static BaseSprite* createSprite(Widget* pParent, const ScreenRect& r, const char*
    //    pImageSpec, bool bTrim);

   private:
    RenderPacket* mpRenderPacket;
    void LoadVertexData();
    std::string msFilename;
    void SetVertexColors(const Color* c);

    int w, h, n;
    GLuint mOGLHandle;
    Color mColors[4];
    ScreenRect mScreen;

    bool mbTrim;
};

#endif  // BASE_SPRITE_H
