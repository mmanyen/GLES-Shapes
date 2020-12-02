//****************************************************************************
//! @file
//! @brief OpenGl Shader repository (Singleton).
//!
//! Container for all shader programs, allowing access by ID.
//!
//! Copyright (C) 2012 Gambro UF Solutions, Inc. All rights reserved.
//****************************************************************************
#ifndef _ESSHADERREPOSITORY_H_
#define _ESSHADERREPOSITORY_H_
#include <stdint.h>
#include <map>

//! @brief index to the vertex uniform
#define VERTEX_ARRAY 0
//! @brief index to the texture coord uniform
#define TEXCOORD_ARRAY 1
//! @brief index to the color uniform
#define COLOR_ARRAY 2


//! @brief OpenGL Shader repository (Singleton).
//!
//! Container for all shader programs, allowing access by ID.
class ESShaderRepository
{
public:
   //! @brief Shader IDs available
   enum ShaderID
   {
      BASIC_SPRITE = 0,    //!< Basic textured shader. No colors.
      COLOR_SPRITE,        //!< Textured shader with vertex colors.
      FONT,                //!< Font shader.
      COLOR_FILL,          //!< Untextured pixels, just vertex colors.
      NUM_SHADERS          //!< Number of shaders available.
   };

   //! @brief Singleton instance access.
   //! @return Instance reference.
   static ESShaderRepository& Instance();
   //! @brief Destructor.
   virtual ~ESShaderRepository();

   //! @brief get the OpenGL program ID for the requested shader.
   //! @param[in] id ShaderID member.
   //! @return OpenGL shader program ID.
   int GetShaderProgram(ShaderID id);

private:
   ESShaderRepository();
   std::map<ShaderID, int32_t> mShaders;
};


#endif //_ESSHADERREPOSITORY_H_
