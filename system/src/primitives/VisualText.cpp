#include "VisualText.h"
#include <GLES2/gl2.h>
#include "ESShaderRepository.h"
#include "RenderPacket.h"

#include "Primitives/FontLibrary.h"
#include "Screen.h"
#include "Widget.h"

namespace BaxGUI
{
   VisualText::VisualText(Widget* pParent) : IVisual(pParent), mpRenderPacket(0), mbTrim(false) {}
   VisualText::~VisualText()
   {
      if (mpRenderPacket)
      {
         glDeleteBuffers(1, &mpRenderPacket->miVbo);
         delete[] mpRenderPacket->mfVertices;
         delete mpRenderPacket;
      }
   }

   bool VisualText::Instantiate(bool bActivate)
   {
      if (bActivate)
      {
         // Load up the image
         unsigned char* pTexData =
            FontLibrary::instance().Render(mContent.c_str(), mFontName.c_str(), w, h);
         if (pTexData)
         {
            glGenTextures(1, &mOGLHandle);
            // Binds this texture handle so we can load the data into it
            glBindTexture(GL_TEXTURE_2D, mOGLHandle);

            GLint format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, pTexData);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glBindTexture(GL_TEXTURE_2D, 0);
            delete[] pTexData;

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
                  ESShaderRepository::Instance().GetShaderProgram(ESShaderRepository::FONT);
               // Set to no rotation etc...
               mpRenderPacket->mTransform.identity();
               // Set type of primatives
               mpRenderPacket->miType = GL_TRIANGLE_STRIP;

               // shader (COLOR_FILL)
               mpRenderPacket->miVertArraySize = 3;
               mpRenderPacket->miVertArrayOffset = 0;
               mpRenderPacket->miTextureArraySize = 2;
               mpRenderPacket->miTextureArrayOffset = 3;
               mpRenderPacket->miColorArraySize = 0;
               mpRenderPacket->miColorArrayOffset = 0;
               mpRenderPacket->miVertexStride =
                  5 * sizeof(GLfloat);  // 3 floats for the pos, 2 for the UVs

               mpRenderPacket->miVertexCount = 4;
               // copy verts to local buffer
               mpRenderPacket->mfVertices =
                  new float[mpRenderPacket->miVertexStride * mpRenderPacket->miVertexCount];

               mpRenderPacket->mfUniformArray = mColor.FloatArray();
               if (mbTrim)
               {
                  mScreen.w = 2.0f * (w / (float)mpParent->GetParent()->LogicalWidth());
                  mScreen.h = 2.0f * (h / (float)mpParent->GetParent()->LogicalHeight());
               }
            }
         }
      }
      else
      {
         if (mpRenderPacket)
         {
            glDeleteBuffers(1, &mpRenderPacket->miVbo);
            delete[] mpRenderPacket->mfVertices;
            delete mpRenderPacket;
            mpRenderPacket = 0;
         }
      }

      return true;
   }

   void VisualText::Update(float fTime) {}
   void VisualText::Draw()
   {
      // Send the vertex buffer to be rendered
      if (mpRenderPacket)
      {
         LoadVertexData();
         mpRenderPacket->mTransform[12] = 0;
         mpRenderPacket->mTransform[13] = 0;
#if 1
         mpRenderPacket->Render();
#else
         SceneGraph::Instance().AddPacket(mpRenderPacket);
#endif
      }
   }
   void VisualText::LoadVertexData()
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
         mpRenderPacket->mfVertices[vi++] = 0;  // U
         mpRenderPacket->mfVertices[vi++] = 0;  // V

         mpRenderPacket->mfVertices[vi++] = fRight;  // UR
         mpRenderPacket->mfVertices[vi++] = fTop;
         mpRenderPacket->mfVertices[vi++] = dz;
         mpRenderPacket->mfVertices[vi++] = 1;  // U
         mpRenderPacket->mfVertices[vi++] = 0;  // V

         mpRenderPacket->mfVertices[vi++] = fLeft;  // LL
         mpRenderPacket->mfVertices[vi++] = fBottom;
         mpRenderPacket->mfVertices[vi++] = dz;
         mpRenderPacket->mfVertices[vi++] = 0;  // U
         mpRenderPacket->mfVertices[vi++] = 1;  // V

         mpRenderPacket->mfVertices[vi++] = fRight;  // LR
         mpRenderPacket->mfVertices[vi++] = fBottom;
         mpRenderPacket->mfVertices[vi++] = dz;
         mpRenderPacket->mfVertices[vi++] = 1;  // U
         mpRenderPacket->mfVertices[vi++] = 1;  // V
      }
   }

   VisualText* VisualText::createText(Widget* pParent, const ScreenRect& r, const Color& c,
                                      const char* pFontSpec, const char* pContent, bool bTrim)
   {
      VisualText* pText = new VisualText(pParent);
      pText->Resize(r);
      pText->mFontName = pFontSpec;
      pText->mColor = c;
      pText->mContent = pContent;
      pText->mbTrim = bTrim;
      return pText;
   }
}
