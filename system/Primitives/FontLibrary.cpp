#include "FontLibrary.h"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdint.h>
#include <string>

#include "Log.h"
#include "utf8_utils.h"

   static FT_Library library;

   class Glyph
   {
     public:
      Glyph() : mpPixels(0) {}
      ~Glyph()
      {
         if (mpPixels)
         {
            delete[] mpPixels;
         }
      }

      uint32_t unicode;        //!< unicode value
      uint32_t height;         //!< Height of this glyph
      uint32_t rows, columns;  //!< Row/Cols of bitmap data
      int32_t advance;         //!< Pixels to advance for this glyph
      int32_t decender;        //!< Below baseline size
      int32_t ascender;        //!< Above baseline size
      int32_t horiBearingX;    //<! Positioning data
      int32_t horiBearingY;    //<! Positioning data
      uint8_t* mpPixels;       //!< Pointer to pixels (In file, offset from data block)

      static Glyph* create(FT_Face face, uint32_t charcode)
      {
         Glyph* pGlyph = NULL;
         // Use freetype to generate the bitmap
         FT_UInt gindex = FT_Get_Char_Index(face, charcode);
         if (gindex)
         {
            FT_Load_Glyph(face, gindex, FT_LOAD_DEFAULT);
            FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

            // build the output structure
            pGlyph = new Glyph();
            pGlyph->unicode = charcode;
            pGlyph->columns = face->glyph->bitmap.width;
            pGlyph->rows = face->glyph->bitmap.rows;
            pGlyph->height = face->glyph->metrics.height;
            pGlyph->advance = face->glyph->metrics.horiAdvance;
            pGlyph->horiBearingX = face->glyph->metrics.horiBearingX;
            pGlyph->decender = face->size->metrics.descender;
            pGlyph->ascender = face->size->metrics.ascender;
            pGlyph->horiBearingY = face->glyph->metrics.horiBearingY;
            pGlyph->mpPixels = NULL;

            if (face->glyph->bitmap.buffer != NULL)
            {
               // copy bitmap (alpha only)
               pGlyph->mpPixels = new uint8_t[pGlyph->columns * (pGlyph->rows)];
               for (uint32_t y = 0; y < pGlyph->rows; y++)
               {
                  uint8_t* pOut = &pGlyph->mpPixels[(y * pGlyph->columns)];
                  uint8_t* pIn = &face->glyph->bitmap.buffer[(y * face->glyph->bitmap.pitch)];
                  memcpy(pOut, pIn, pGlyph->columns);
               }
            }
         }
         return pGlyph;
      }
   };

   class Font
   {
     public:
      Font(uint32_t ps, const char* pFilename) : pointSize(ps), face(0), mHeight(0)
      {
         FT_Error error = FT_New_Face(library, pFilename, 0, &face);
         if (error != FT_Err_Ok)
         {
            if (error == FT_Err_Unknown_File_Format)
            {
               //... the font file could be opened and read, but it appears
               //... that its font format is unsupported
               log(Log::L_ERROR, "Unsupported font file\n");
            }
            else if (error)
            {
               //... another error code means that the font file could not
               //... be opened or read, or that it is broken...
               log(Log::L_ERROR, "Error on font file\n");
            }
         }
         else
         {
            error = FT_Set_Char_Size(face,           /* handle to face object           */
                                     0,              /* char_width in 1/64th of points  */
                                     pointSize * 64, /* char_height in 1/64th of points */
                                     96,             /* horizontal device resolution    */
                                     96);            /* vertical device resolution      */

            // Save the height of the font for the renderer
            mHeight = (face->size->metrics.height >> 6);
         }
      }
      virtual ~Font()
      {
         // delete all cached glyphs
         while (mGlyphs.begin() != mGlyphs.end())
         {
            delete (*mGlyphs.begin()).second;
            mGlyphs.erase(mGlyphs.begin());
         }
         FT_Done_Face(face);
      }

      const Glyph* GetChar(uint32_t unicode)
      {
         Glyph* pRet = 0;
         std::map<uint32_t, Glyph*>::iterator it = mGlyphs.find(unicode);
         if (it == mGlyphs.end())
         {
            // not found in cache, build it
            pRet = Glyph::create(face, unicode);
            if (pRet)
            {
               mGlyphs[unicode] = pRet;
               // update any metrics here
            }
         }
         else
         {
            // found in the cache, just return it
            pRet = (*it).second;
         }

         return pRet;
      }
      uint32_t Height() const { return mHeight; }
     private:
      FT_Face face;
      uint32_t pointSize;
      uint32_t mHeight;

      std::map<uint32_t, Glyph*> mGlyphs;
   };

   static std::map<std::string, Font*> mFonts;

   FontLibrary::FontLibrary()
   {
      // Open FreeType
      FT_Error error = FT_Init_FreeType(&library);
      if (error)
      {
         // Error
         log(Log::L_ERROR, "Failed to init freetype library (%d)\n", error);
      }
   }

   FontLibrary::~FontLibrary()
   {
      // Release all the loaded fonts
      while (mFonts.begin() != mFonts.end())
      {
         delete ((*mFonts.begin()).second);
         mFonts.erase(mFonts.begin());
      }
      FT_Done_FreeType(library);
   }

   FontLibrary& FontLibrary::instance()
   {
      // Classic Singleton Pattern
      static FontLibrary fl;
      return fl;
   }

   bool FontLibrary::Register(const char* pFontName, const char* pFontFile, uint32_t pointSize)
   {
      bool bLoaded = false;
      std::map<std::string, Font*>::iterator it = mFonts.find(pFontName);
      if (it == mFonts.end())
      {
         Font* pFont = new Font(pointSize, pFontFile);
         mFonts[pFontName] = pFont;
         // TODO: Pre-load common chars...
         pFont->GetChar(32);  // Cache the space char
         bLoaded = true;
      }
      return bLoaded;
   }

   uint8_t* FontLibrary::Render(const char* pString, const char* pFontName, uint32_t& w,
                                uint32_t& h)
   {
      uint8_t* pPixels = 0;

      // Get the requested font
      Font* pFont = mFonts[pFontName];
      if (pFont)
      {
         w = 0;
         h = pFont->Height();

         // gather the required glyphs and generate the width
         std::list<const Glyph*> lGlyphs;
         std::string str = pString;
         // Use UTF-8 codepoints instead of ASCII chars
         Utf8::Utf8Iterator sit(str.begin());
         while (sit != str.end())
         {
            const Glyph* pGlyph = pFont->GetChar(*sit);
            if (pGlyph)
            {
               lGlyphs.push_back(pGlyph);
               w += (pGlyph->advance >> 6);
            }
            else
            {
               log(Log::L_ERROR, "Unsupported code point (%x)\n", (*sit));
            }
            ++sit;
         }

         if (w > 0)
         {
            // allocate the pixel data
            // output in RGBA format with all components set to the 8 bit alpha from the glyph
            size_t bufSize = w * h * 4;
            pPixels = new uint8_t[bufSize];
            if (pPixels)
            {
               memset(pPixels, 0, bufSize);

               // copy each glyph to the buffer in place
               uint32_t x = 0;
               std::list<const Glyph*>::iterator it = lGlyphs.begin();
               while (it != lGlyphs.end())
               {
                  const Glyph* pGlyph = (*it);
                  // adjust the position in the output texture for glyph metrics
                  // Note: decender is expressed in negative values (from baseline)
                  //       Both decender and bearings are in 26.6 fixed point formats
                  uint32_t oy = h + (pGlyph->decender >> 6) - (pGlyph->horiBearingY >> 6);
                  uint32_t ox = x + (pGlyph->horiBearingX >> 6);
                  for (uint32_t y = 0; y < pGlyph->rows; y++)
                  {
                     // point to the start of the input scanline
                     uint8_t* pIn = &pGlyph->mpPixels[y * pGlyph->columns];
                     // point to the start of the output rectangle
                     uint8_t* pOut = &pPixels[((oy + y) * w * 4) + (ox * 4)];
                     for (uint32_t i = 0; i < pGlyph->columns; i++)
                     {
                        // Store the 8 bit alpha value in all 4 color components
                        *pOut++ = *pIn;
                        *pOut++ = *pIn;
                        *pOut++ = *pIn;
                        *pOut++ = *pIn++;
                     }
                  }
                  // Move x to the next char horiz. baseline, advance is in 26.6 fixed point format
                  x += (pGlyph->advance >> 6);
                  ++it;
               }
            }
         }
         else
         {
            log(Log::L_INFO, "No data for String Render\n");
         }
      }
      else
      {
         log(Log::L_ERROR, "Memory Allocation error in Font Render\n");
      }

      return pPixels;
   }


   int32_t FontLibrary::CharWidth(const char* pFontName, uint32_t codepoint)
   {
      int32_t iRet = 0;
      // Get the requested font
      Font* pFont = mFonts[pFontName];
      if (pFont)
      {
         const Glyph* pGlyph = pFont->GetChar(codepoint);
         if (pGlyph)
         {
            iRet = (pGlyph->advance >> 6);
         }
      }
      return iRet;
   }

