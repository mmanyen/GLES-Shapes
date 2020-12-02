//****************************************************************************
//! @file
//! @brief Rendering packet for SceneGraph rendering.
//!
//! Copyright (C) 2013 Gambro UF Solutions, Inc. All rights reserved.
//****************************************************************************
#ifndef _RENDER_PACKET_H_
#define _RENDER_PACKET_H_

#include "Matrices.h"


class RenderPacket
{
public:
   RenderPacket();
   virtual ~RenderPacket();

   void Render();

   static bool compare_Z_decending (const RenderPacket* first, const RenderPacket* second);
   static bool compare_Z_ascending (const RenderPacket* first, const RenderPacket* second);
   static bool compare_Texture (const RenderPacket* first, const RenderPacket* second);
   static bool compare_Program (const RenderPacket* first, const RenderPacket* second);

   float mMasterZ;
   bool mbIsOpaque;


   unsigned int miTexture;
   unsigned int miVbo;
   unsigned int miShaderProgram;

   Matrix4 mTransform;
   unsigned int miType;  // GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_LINES etc

   unsigned int miVertArraySize;
   unsigned int miVertArrayOffset;
   unsigned int miTextureArraySize;
   unsigned int miTextureArrayOffset;
   unsigned int miColorArraySize;
   unsigned int miColorArrayOffset;

   unsigned int miVertexStride;
   unsigned int miVertexCount;
   float* mfVertices;
   const float* mfUniformArray;
};


#endif // _RENDER_PACKET_H_
