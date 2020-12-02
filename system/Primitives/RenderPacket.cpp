//****************************************************************************
//! @file
//! @brief Rendering packet for SceneGraph rendering.
//!
//! Copyright (C) 2013 Gambro UF Solutions, Inc. All rights reserved.
//****************************************************************************
#include "glad/glad.h"
#include <GLFW/glfw3.h>  // Includes <GLES2/gl2.h>

#include "RenderPacket.h"
#include "ESShaderRepository.h"


bool RenderPacket::compare_Z_decending (const RenderPacket* first, const RenderPacket* second)
{
   return first->mMasterZ > second->mMasterZ;
}

bool RenderPacket::compare_Z_ascending (const RenderPacket* first, const RenderPacket* second)
{
   return first->mMasterZ < second->mMasterZ;
}

bool RenderPacket::compare_Texture (const RenderPacket* first, const RenderPacket* second)
{
   return first->miTexture < second->miTexture;
}

bool RenderPacket::compare_Program (const RenderPacket* first, const RenderPacket* second)
{
   return first->miShaderProgram < second->miShaderProgram;
}

RenderPacket::RenderPacket() : mfUniformArray(0)
{
   mMasterZ = 0.05f;
   mbIsOpaque = true;

   miTexture = 0;
   miVbo = 0;
   miShaderProgram = 0;

   mTransform.identity();
   miType = GL_TRIANGLE_STRIP;

   // Set up for most common shader (COLOR_SPRITE)
   miVertArraySize      = 3;
   miVertArrayOffset    = 0;
   miTextureArraySize   = 2;
   miTextureArrayOffset = 3;
   miColorArraySize     = 4;
   miColorArrayOffset   = 5;
   miVertexStride       = 9 * sizeof(GLfloat); // 3 floats for the pos, 2 for the UVs, 4 for color;

   miVertexCount        = 0;
   mfVertices           = 0;
}

RenderPacket::~RenderPacket()
{
}

void RenderPacket::Render()
{
   // Bind the Texture and the VBO
   if (miTextureArraySize > 0)
   {
      glBindTexture(GL_TEXTURE_2D, miTexture);
   }
   else
   {
      glBindTexture(GL_TEXTURE_2D, 0);
   }

   glBindBuffer(GL_ARRAY_BUFFER, miVbo);

   // Set the buffer's data
   glBufferData(GL_ARRAY_BUFFER, miVertexCount * miVertexStride, mfVertices, GL_STATIC_DRAW);

   // Pass the vertex data
   glEnableVertexAttribArray(VERTEX_ARRAY);
   glVertexAttribPointer(VERTEX_ARRAY, miVertArraySize, GL_FLOAT, GL_FALSE, miVertexStride, (void*)(miVertArrayOffset * sizeof(GLfloat)));

   if (miTextureArraySize > 0)
   {
      // Pass the texture coordinates data
      glEnableVertexAttribArray(TEXCOORD_ARRAY);
      glVertexAttribPointer(TEXCOORD_ARRAY, miTextureArraySize, GL_FLOAT, GL_FALSE, miVertexStride, (void*)(miTextureArrayOffset * sizeof(GLfloat)));
   }

   if (miColorArraySize  > 0)
   {
      // Pass the color coordinates data
      glEnableVertexAttribArray(COLOR_ARRAY);
      glVertexAttribPointer(COLOR_ARRAY, miColorArraySize, GL_FLOAT, GL_FALSE, miVertexStride, (void*)(miColorArrayOffset * sizeof(GLfloat)));
   }

   glUseProgram(miShaderProgram);

   // pass the matrix to the shader variable
   // First gets the location of that variable in the shader using its name
   int i32Location = glGetUniformLocation(miShaderProgram, "uModelview");
   glUniformMatrix4fv(i32Location, 1, GL_FALSE, mTransform.get());

   if (mfUniformArray)
   {
      // set color (uColor)
      int iColorLocation = glGetUniformLocation(miShaderProgram, "uColor");
      glUniform4fv(iColorLocation, 1, mfUniformArray);
   }

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glEnable(GL_BLEND);

   glDrawArrays(miType, 0, miVertexCount);
   glDisable(GL_BLEND);

   // Unbind the VBO and texture
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindTexture(GL_TEXTURE_2D, 0);
}
