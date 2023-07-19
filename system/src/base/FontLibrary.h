#ifndef __FONT_LIBRARY_H__
#define __FONT_LIBRARY_H__

#include <list>
#include <map>
#include <string>
#include <stdint.h>


   class Font;

   //! @brief Contains/Parses/Draws Text
   //! @par Classic Singleton pattern
   class FontLibrary
   {
     private:
      //! @brief private constructor
      FontLibrary();

     public:
      //! @brief Return the instance of the singleton
      //! @return reference to the singleton instance
      static FontLibrary& instance();

      //! @brief Register a font
      //! @param[in] pFontName Name of the new font
      //! @param[in] pFontFile Name of the file to load (freetype supported formats)
      //! @param[in] pointSize font point size to create
      //! @return bool true for success, false for fail (error in log)
      bool Register(const char* pFontName, const char* pFontFile, uint32_t pointSize);

      //! @brief Render a string in the given font for the FONT shader to draw
      //! @return pointer to pixels, may be NULL if error (logged)
      //! @param[in] pString UTF-8 string to render
      //! @param[in] pFontName Name of the previously Registered font
      //! @param[out] w Width of the returned texture (in pixels)
      //! @param[out] h Height of the returned texture (in pixels)
      //! @par Note: Caller must delete[] the returned pointer
      uint8_t* Render(const char* pString, const char* pFontName, uint32_t& w, uint32_t& h);

      int32_t CharWidth(const char* pFontName, uint32_t codepoint);

      ~FontLibrary();
     private:
      std::map<std::string, Font*> mFonts;
   };


#endif  // __FONT_LIBRARY_H__
