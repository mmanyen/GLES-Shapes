//****************************************************************************
//! @file
//! @brief Image file format processes.
//!
//! STB Image is a public domain c language library that loads many
//! different image formats.
//! This header just defines the entry points we need.
//! For more information on this library see stb_image.c
//!
//! Copyright (C) 2012 Gambro UF Solutions, Inc. All rights reserved.
//****************************************************************************

#ifdef __cplusplus
extern "C" {
#endif

//! @brief Library required data type
typedef unsigned char stbi_uc;


   //! @brief Load image from memory
   //! @param[in] buffer Pointer to the image file data in memory.
   //! @param[in] len Length in bytes of the buffer.
   //! @param[out] x storage for the width.
   //! @param[out] y storage for the height.
   //! @param[out] comp storage for num bytes per pixel.
   //! @param[in] req_comp demand for depth.
   //! @return pointer to pixel data.
   extern stbi_uc* stbi_load_from_memory(stbi_uc const* buffer, int len, int* x, int* y, int* comp, int req_comp);

   //! @brief Load image from file system
   //! @param[in] filename Name of the file to load.
   //! @param[out] x storage for the width.
   //! @param[out] y storage for the height.
   //! @param[out] comp storage for num bytes per pixel.
   //! @param[in] req_comp demand for depth.
   //! @return pointer to pixel data.
   extern stbi_uc* stbi_load(char const* filename, int* x, int* y, int* comp, int req_comp);

   //! @brief free the loaded image -- this is just free()
   //! @param retval_from_stbi_load Pointer returned from load function.
   extern void     stbi_image_free(void* retval_from_stbi_load);
#ifdef __cplusplus
}
#endif

