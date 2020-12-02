//****************************************************************************
//! @file
//! @brief Contains the Color struct and the Colors namespace which contains
//! all color consts and translations
//!
//! Copyright (C) 2012 Gambro UF Solutions, Inc. All rights reserved.
//****************************************************************************

#ifndef COLOR_H
#define COLOR_H

   //! @struct Color Color.h
   //! @brief Contains a color defined by four values, Alpha, Red, Green,
   //! Blue.
   //!
   //! Each value can be between 0.0f and 1.0f where 0.0f is none of that
   //! color and 1.0f is fully lit with that color. Alpha is the level of
   //! opacity. Colors can be described beyond there normal limits for different
   //! math when tinting. Ex: A gray image can get multiplied by (2.0, 1.0, 1.0)
   //! to have more red or by (2.0, 0.0, 0.0) to have only red.
   struct Color
   {
     public:
      //! @brief Factory method to create a color from three 255 based coordinates.
      //! @param[in] red Red int value between 0-255.
      //! @param[in] green Green int value between 0-255.
      //! @param[in] blue Blue int value between 0-255.
      //! @param[in] alpha Alpha int value between 0-255.
      //! @return The Color struct representation of the 255 based color.
      static Color FromRgb(int red, int green, int blue, int alpha = 255);

      //! @brief Constructor generates gray version of color. Primarily used for
      //! color math and Tinting.
      //! @param[in] gray RGB values for the color (all equal).
      //! @param[in] alpha Alpha value for the color.
      Color(float gray, float alpha);

      //! @brief Constructor to generate a color providing the 3 main
      //! colors (and optionally Alpha) in a value between 0.0f (fully
      //! dark) and 1.0f (fully lit).
      Color(float red, float green, float blue, float alpha = 1.0f);

      //! @brief Constructor to generate a color providing a string representing
      //! the 3 main colors (and optionally Alpha) in a value between
      //! 0.0f (fully dark) and 1.0f (fully lit).
      Color(const char* pString);

      //! @brief Default Constructor
      Color()
      {
         mRGBA[0] = 1.0f;
         mRGBA[1] = 1.0f;
         mRGBA[2] = 1.0f;
         mRGBA[3] = 1.0f;
      }

      //! @brief Destructor.
      ~Color();

      //! @brief Equality operator. Checks if all 4 values (ARGB) are the same.
      //! @param[in] rhs The right hand side Color of the equals statement.
      //! @return Returns true if Red == Red, Blue == Blue, Green == Green,
      //! and Alpha == Alpha. False otherwise.
      bool operator==(const Color& rhs) const;

      //! @brief Inquality operator. Checks if any of the 4 values (ARGB)
      //! are different.
      //! @param[in] rhs The right hand side Color of the equals statement.
      //! @return Returns true if the colors are different.
      bool operator!=(const Color& rhs) const;

      //! @brief Greater than operator. (For sorting only)
      //! @param[in] rhs Right-hand side of the operator to compare with.
      //! @return True if object on left is greater than object on right.
      bool operator>(const Color& rhs) const;

      //! @brief Less than operator. (For sorting only)
      //! @param[in] rhs Right-hand side of the operator to compare with.
      //! @return True if object on left is less than object on right.
      bool operator<(const Color& rhs) const;

      //! @brief Multiplication operator. (Tints two colors together)
      //! @param[in] rhs Right-hand side of the operator.
      //! @return The color of the two colors multiplied together.
      Color operator*(const Color& rhs) const;

      //! @brief Addition operator. (Brightens first color by second)
      //! @param[in] rhs Right-hand side of the operator.
      //! @return The color of the two colors added together.
      Color operator+(const Color& rhs) const;

      //! @brief Subtraction operator. (Darkens first color by second)
      //! @param[in] rhs Right-hand side of the operator.
      //! @return The difference color of the two colors.
      Color operator-(const Color& rhs) const;

      //! @brief Gets the floating point representation of the Alpha value.
      //! @return The alpha value between 0.0f and 1.0f. 0.0f is fully
      //! transparent while 1.0f is fully opaque.
      float Alpha() const;

      //! @brief Gets the floating point representation of the Red value.
      //! @return The Red value between 0.0f and 1.0f.
      float Red() const;

      //! @brief Gets the floating point representation of the Green value.
      //! @return The Green value between 0.0f and 1.0f.
      float Green() const;

      //! @brief Gets the floating point representation of the Blue value.
      //! @return The blue value between 0.0f and 1.0f.
      float Blue() const;

      //! @brief Get read only access to the array of floating point RGBA values
      //! @return Pointer to array.
      const float* FloatArray() const { return mRGBA; }
     private:
      // The data representation of the color.
      float mRGBA[4];
   };

   class NamedColors
   {
     private:
      //! @brief Singletons have private constructors
      NamedColors();

     public:
      static NamedColors& instance();
      bool Add(const char* pName, const Color& out);
      bool Add(const char* pName, const char* pColorSpec);

      bool Lookup(const char* pName, Color& out);
   };

#endif  // COLOR_H
