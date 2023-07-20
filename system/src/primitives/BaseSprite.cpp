#include "IPlatform.h"
#include "IPrimitive.h"

#include "glad/glad.h"
#include <GLES2/gl2.h>

#include "BaseSprite.h"
#include "ESShaderRepository.h"
#include "Log.h"
#include "RenderPacket.h"
#include "stb_image.h"

#define TEXTURE_NOT_LOADED 0xFF000000

BaseSprite::BaseSprite()
    : IPrimitive(),
      mpRenderPacket(0),
      msFilename(""),
      mOGLHandle(TEXTURE_NOT_LOADED),
      mbTrim(false)
{
    mColors[0] = mColors[1] = mColors[2] = mColors[3] = Color(1.0f, 1.0f);
}

BaseSprite::BaseSprite(const ScreenRect& r, const char* pImageSpec)
    : IPrimitive(),
      mpRenderPacket(0),
      msFilename(pImageSpec),
      mOGLHandle(TEXTURE_NOT_LOADED),
      mbTrim(false),
      mScreen(r)
{
    mColors[0] = mColors[1] = mColors[2] = mColors[3] = Color(1.0f, 1.0f);
}

BaseSprite::~BaseSprite()
{
    if (mpRenderPacket)
    {
        glDeleteBuffers(1, &mpRenderPacket->miVbo);
        delete[] mpRenderPacket->mfVertices;
        delete mpRenderPacket;
    }
    if (mOGLHandle != TEXTURE_NOT_LOADED)
    {
        glDeleteTextures(1, &mOGLHandle);
    }
}

void BaseSprite::SetScreenLocation(const ScreenRect& r)
{
    mScreen = r;
}

void BaseSprite::SetImage(const char* pImageSpec)
{
    msFilename = pImageSpec;
}

void BaseSprite::Instantiate()
{
//    if (bActivate)
    {
        // Load up the image
        unsigned char* pTexData = stbi_load(msFilename.c_str(), &w, &h, &n, 0);
        if (pTexData)
        {
            // expand to image h/w if requested
            if (mScreen.h <= 0)
            {
                mScreen.h = static_cast<float>(h) / IPlatform::instance().ScreenPixelHeight();
            }
            if (mScreen.w <= 0)
            {
                mScreen.w = static_cast<float>(w) / IPlatform::instance().ScreenPixelWidth();
            }

            glGenTextures(1, &mOGLHandle);
            // Binds this texture handle so we can load the data into it
            glBindTexture(GL_TEXTURE_2D, mOGLHandle);

            GLint format = GL_RGB;
            if (n == 4)
            {
                format = GL_RGBA;
            }

            glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, pTexData);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D, 0);
            free(pTexData);  // Yes, free. The library uses malloc and is a c language file, not cpp
        }
        if (!mpRenderPacket)
        {
            mpRenderPacket = new RenderPacket;

            // Init the render packet which will be passed to the scene graph on render.
            mpRenderPacket->mMasterZ = 0.0f;

            // Set the texture id
            mpRenderPacket->miTexture = mOGLHandle;
            // Create VBO for drawing the image
            glGenBuffers(1, &mpRenderPacket->miVbo);
            // Set the shader program
            mpRenderPacket->miShaderProgram =
                ESShaderRepository::Instance().GetShaderProgram(ESShaderRepository::COLOR_SPRITE);
            // Set to no rotation etc...
            mpRenderPacket->mTransform.identity();
            // Set type of primatives
            mpRenderPacket->miType = GL_TRIANGLE_STRIP;

            // shader (COLOR_SPRITE)
            mpRenderPacket->miVertArraySize = 3;
            mpRenderPacket->miVertArrayOffset = 0;
            mpRenderPacket->miTextureArraySize = 2;
            mpRenderPacket->miTextureArrayOffset = 3;
            mpRenderPacket->miColorArraySize = 4;
            mpRenderPacket->miColorArrayOffset = 5;
            mpRenderPacket->miVertexStride =
                9 * sizeof(GLfloat);  // 3 floats for the pos, 2 for the UVs, 4 for color;

            mpRenderPacket->miVertexCount = 4;
            // copy verts to local buffer
            mpRenderPacket->mfVertices =
                new float[mpRenderPacket->miVertexStride * mpRenderPacket->miVertexCount];

        }
    }
}

void BaseSprite::Draw()
{
    // Send the vertex buffer to be rendered
    if (mpRenderPacket)
    {
        LoadVertexData();
        mpRenderPacket->mTransform[12] = 0;
        mpRenderPacket->mTransform[13] = 0;
        mpRenderPacket->Render();
    }
}

void BaseSprite::SetVertexColors(const Color* c)
{
    for (int i = 0; i < 4; i++)
    {
        mColors[i] = c[i];
    }
}

void BaseSprite::LoadVertexData()
{
    if (mpRenderPacket)
    {
        float dz = 0.0f;

        float fTop = mScreen.y;
        float fBottom = mScreen.y - mScreen.h;
        float fLeft = mScreen.x;
        float fRight = mScreen.x + mScreen.w;

        int vi = 0;

        mpRenderPacket->mfVertices[vi++] = fLeft;  // UL
        mpRenderPacket->mfVertices[vi++] = fTop;
        mpRenderPacket->mfVertices[vi++] = dz;
        mpRenderPacket->mfVertices[vi++] = 0;                   // U
        mpRenderPacket->mfVertices[vi++] = 0;                   // V
        mpRenderPacket->mfVertices[vi++] = mColors[0].Red();    // R
        mpRenderPacket->mfVertices[vi++] = mColors[0].Green();  // G
        mpRenderPacket->mfVertices[vi++] = mColors[0].Blue();   // B
        mpRenderPacket->mfVertices[vi++] = mColors[0].Alpha();  // A

        mpRenderPacket->mfVertices[vi++] = fRight;              // UR
        mpRenderPacket->mfVertices[vi++] = fTop;
        mpRenderPacket->mfVertices[vi++] = dz;
        mpRenderPacket->mfVertices[vi++] = 1;                   // U
        mpRenderPacket->mfVertices[vi++] = 0;                   // V
        mpRenderPacket->mfVertices[vi++] = mColors[1].Red();    // R
        mpRenderPacket->mfVertices[vi++] = mColors[1].Green();  // G
        mpRenderPacket->mfVertices[vi++] = mColors[1].Blue();   // B
        mpRenderPacket->mfVertices[vi++] = mColors[1].Alpha();  // A

        mpRenderPacket->mfVertices[vi++] = fLeft;               // LL
        mpRenderPacket->mfVertices[vi++] = fBottom;
        mpRenderPacket->mfVertices[vi++] = dz;
        mpRenderPacket->mfVertices[vi++] = 0;                   // U
        mpRenderPacket->mfVertices[vi++] = 1;                   // V
        mpRenderPacket->mfVertices[vi++] = mColors[2].Red();    // R
        mpRenderPacket->mfVertices[vi++] = mColors[2].Green();  // G
        mpRenderPacket->mfVertices[vi++] = mColors[2].Blue();   // B
        mpRenderPacket->mfVertices[vi++] = mColors[2].Alpha();  // A

        mpRenderPacket->mfVertices[vi++] = fRight;              // LR
        mpRenderPacket->mfVertices[vi++] = fBottom;
        mpRenderPacket->mfVertices[vi++] = dz;
        mpRenderPacket->mfVertices[vi++] = 1;                   // U
        mpRenderPacket->mfVertices[vi++] = 1;                   // V
        mpRenderPacket->mfVertices[vi++] = mColors[3].Red();    // R
        mpRenderPacket->mfVertices[vi++] = mColors[3].Green();  // G
        mpRenderPacket->mfVertices[vi++] = mColors[3].Blue();   // B
        mpRenderPacket->mfVertices[vi++] = mColors[3].Alpha();  // A
    }
}

