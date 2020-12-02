//*****************************************************************************
//! @file
//! @brief Vector math.
//!
//!  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
//! CREATED: 2007-02-14
//! UPDATED: 2011-12-07
//! Adapted: 2012-01-02
//!
//! Original Copyright (C) 2011 Song Ho Ahn
//! Modifications Copyright (C) 2012 Gambro INC. All rights reserved.
//*****************************************************************************

#ifndef VECTORS_H_DEF
#define VECTORS_H_DEF

#include <cmath>

//! @brief 2D Vector
struct Vector2
{
   float x; //!< X component.
   float y; //!< Y component.

   //! @brief Default Constructor.
   Vector2() : x(0), y(0) {};
   //! @brief Initializing Constructor.
   //! @param[in] x X component.
   //! @param[in] y Y component.
   Vector2(float x, float y) : x(x), y(y) {};

   //! @brief Set the vector components.
   //! @param[in] x X component.
   //! @param[in] y Y component.
   void        set(float x, float y);
   //! @brief Get vector length
   //! @return Length of the vector
   float       length() const; 
   //! @brief Distance between this and other vector.
   //! @param[in] vec Other vector.
   //! @return Distance.
   float       distance(const Vector2& vec) const; 
   //! @brief Normalize this vector.
   //! @return Reference to this vector.
   Vector2&    normalize();
   //! @brief Calculate the dot product.
   //! @param[in] vec Other vector.
   //! @return Dot product.
   float       dot(const Vector2& vec) const;      
   //! @brief Compare with epsilon.
   //! @param[in] vec Other vector.
   //! @param[in] e Epsilon.
   //! @return Boolean equality (with epsilon)
   bool        equal(const Vector2& vec, float e) const; 

   //! @brief unary operator (negate).
   //! @return modified Vector.
   Vector2     operator-() const; 
   //! @brief add rhs
   //! @param[in] rhs Vector to add.
   //! @return result.
   Vector2     operator+(const Vector2& rhs) const;    
   //! @brief subtract rhs
   //! @param[in] rhs Vector to subtract.
   //! @return result.
   Vector2     operator-(const Vector2& rhs) const;    
   //! @brief add rhs and update this object.
   //! @param[in] rhs Vector to add.
   //! @return Reference to this vector.
   Vector2&    operator+=(const Vector2& rhs);        
   //! @brief subtract rhs and update this object
   //! @param[in] rhs Vector to subtract.
   //! @return Reference to this vector.
   Vector2&    operator-=(const Vector2& rhs);    
   //! @brief Scale this Vector
   //! @param[in] scale Amount to scale.
   //! @return Result.
   Vector2     operator*(const float scale) const;     
   //! @brief multiply each element
   //! @param[in] rhs Vector to multiply
   //! @return Result.
   Vector2     operator*(const Vector2& rhs) const; 
   //! @brief scale and update this object
   //! @param[in] scale Amount to scale.
   //! @return Reference to this vector.
   Vector2&    operator*=(const float scale);   
   //! @brief multiply each element and update this object
   //! @param[in] rhs Vector to multiply
   //! @return Reference to this vector.
   Vector2&    operator*=(const Vector2& rhs); 
   //! @brief inverse scale
   //! @param[in] scale Amount to scale.
   //! @return result.
   Vector2     operator/(const float scale) const;   
   //! @brief inverse scale and update this object
   //! @param[in] scale Amount to scale.
   //! @return Reference to this vector.
   Vector2&    operator/=(const float scale);     
   //! @brief exact compare, no epsilon
   //! @param[in] rhs Comparand
   //! @return Boolean equality.
   bool        operator==(const Vector2& rhs) const;   
   //! @brief exact compare, no epsilon
   //! @param[in] rhs Comparand
   //! @return Boolean inequality.
   bool        operator!=(const Vector2& rhs) const;
   //! @brief comparison for sort.
   //! @param[in] rhs Comparand.
   //! @return Boolean this < rhs.
   bool        operator<(const Vector2& rhs) const;    

   //! @brief scale operator, new vector.
   //! @param[in] a scale value.
   //! @param[in] vec Source Vector.
   //! @return Scaled Vector.
   friend Vector2 operator*(const float a, const Vector2 vec);
};



//! @brief 3D Vector
struct Vector3
{
   float x; //!< X component
   float y; //!< Y component
   float z; //!< Z component

   //! @brief Default Constructor.
   Vector3() : x(0), y(0), z(0) {};
   //! @brief Initializing Constructor.
   //! @param[in] x X component.
   //! @param[in] y Y component.
   //! @param[in] z Z component.
   Vector3(float x, float y, float z) : x(x), y(y), z(z) {};

   //! @brief Set the vector components.
   //! @param[in] x X component.
   //! @param[in] y Y component.
   //! @param[in] z Z component.
   void        set(float x, float y, float z);
   //! @brief Get vector length
   //! @return Length of the vector
   float       length() const;                         
   //! @brief Distance between this and other vector.
   //! @param[in] vec Other vector.
   //! @return Distance.
   float       distance(const Vector3& vec) const;     
   //! @brief Normalize this vector.
   //! @return Reference to this vector.
   Vector3&    normalize();                            
   //! @brief Calculate the dot product.
   //! @param[in] vec Other vector.
   //! @return Dot product.
   float       dot(const Vector3& vec) const;          
   //! @brief Calculate the cross product.
   //! @param[in] vec Other vector.
   //! @return Cross product.
   Vector3     cross(const Vector3& vec) const;        
   //! @brief Compare with epsilon.
   //! @param[in] vec Other vector.
   //! @param[in] e Epsilon.
   //! @return Boolean equality (with epsilon)
   bool        equal(const Vector3& vec, float e) const; 

   //! @brief unary operator (negate).
   //! @return modified Vector.
   Vector3     operator-() const;                     
   //! @brief add rhs
   //! @param[in] rhs Vector to add.
   //! @return result.
   Vector3     operator+(const Vector3& rhs) const;    
   //! @brief subtract rhs
   //! @param[in] rhs Vector to subtract.
   //! @return result.
   Vector3     operator-(const Vector3& rhs) const;    
   //! @brief add rhs and update this object.
   //! @param[in] rhs Vector to add.
   //! @return Reference to this vector.
   Vector3&    operator+=(const Vector3& rhs);         
   //! @brief subtract rhs and update this object.
   //! @param[in] rhs Vector to subtract.
   //! @return Reference to this vector.
   Vector3&    operator-=(const Vector3& rhs);         
   //! @brief Scale this Vector
   //! @param[in] scale Amount to scale.
   //! @return Result.
   Vector3     operator*(const float scale) const;     
   //! @brief multiply each element
   //! @param[in] rhs Vector to multiply
   //! @return Result.
   Vector3     operator*(const Vector3& rhs) const;    
   //! @brief scale and update this object
   //! @param[in] scale Amount to scale.
   //! @return Reference to this vector.
   Vector3&    operator*=(const float scale);          
   //! @brief multiply each element and update this object
   //! @param[in] rhs Vector to multiply
   //! @return Reference to this vector.
   Vector3&    operator*=(const Vector3& rhs);         
   //! @brief inverse scale
   //! @param[in] scale Amount to scale.
   //! @return result.
   Vector3     operator/(const float scale) const;   
   //! @brief inverse scale and update this object
   //! @param[in] scale Amount to scale.
   //! @return Reference to this vector.
   Vector3&    operator/=(const float scale);          
   //! @brief exact compare, no epsilon
   //! @param[in] rhs Comparand
   //! @return Boolean equality.
   bool        operator==(const Vector3& rhs) const;   
   //! @brief exact compare, no epsilon
   //! @param[in] rhs Comparand
   //! @return Boolean inequality.
   bool        operator!=(const Vector3& rhs) const;   
   //! @brief comparison for sort.
   //! @param[in] rhs Comparand.
   //! @return Boolean this < rhs.
   bool        operator<(const Vector3& rhs) const;  

   //! @brief scale operator, new vector.
   //! @param[in] a scale value.
   //! @param[in] vec Source Vector.
   //! @return Scaled Vector.
   friend Vector3 operator*(const float a, const Vector3 vec);
};



//! @brief 4D Vector
struct Vector4
{
   float x; //!< X component
   float y; //!< Y component
   float z; //!< Z component
   float w; //!< W component

   //! @brief Default Constructor.
   Vector4() : x(0), y(0), z(0), w(0) {};
   //! @brief Initializing Constructor.
   //! @param[in] x X component.
   //! @param[in] y Y component.
   //! @param[in] z Z component.
   //! @param[in] w W component.
   Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

   //! @brief Set the vector components.
   //! @param[in] x X component.
   //! @param[in] y Y component.
   //! @param[in] z Z component.
   //! @param[in] w W component.
   void        set(float x, float y, float z, float w);
   //! @brief Get vector length
   //! @return Length of the vector
   float       length() const;                         
   //! @brief Distance between this and other vector.
   //! @param[in] vec Other vector.
   //! @return Distance.
   float       distance(const Vector4& vec) const;     
   //! @brief Normalize this vector.
   //! @return Reference to this vector.
   Vector4&    normalize();                          
   //! @brief Calculate the dot product.
   //! @param[in] vec Other vector.
   //! @return Dot product.
   float       dot(const Vector4& vec) const;         
   //! @brief Compare with epsilon.
   //! @param[in] vec Other vector.
   //! @param[in] e Epsilon.
   //! @return Boolean equality (with epsilon)
   bool        equal(const Vector4& vec, float e) const; 

   //! @brief unary operator (negate).
   //! @return modified Vector.
   Vector4     operator-() const;                     
   //! @brief add rhs
   //! @param[in] rhs Vector to add.
   //! @return result.
   Vector4     operator+(const Vector4& rhs) const;   
   //! @brief subtract rhs
   //! @param[in] rhs Vector to subtract.
   //! @return result.
   Vector4     operator-(const Vector4& rhs) const;    
   //! @brief add rhs and update this object.
   //! @param[in] rhs Vector to add.
   //! @return Reference to this vector.
   Vector4&    operator+=(const Vector4& rhs);        
   //! @brief subtract rhs and update this object.
   //! @param[in] rhs Vector to subtract.
   //! @return Reference to this vector.
   Vector4&    operator-=(const Vector4& rhs);        
   //! @brief Scale this Vector
   //! @param[in] scale Amount to scale.
   //! @return Result.
   Vector4     operator*(const float scale) const;     
   //! @brief multiply each element
   //! @param[in] rhs Vector to multiply
   //! @return Result.
   Vector4     operator*(const Vector4& rhs) const;    
   //! @brief scale and update this object
   //! @param[in] scale Amount to scale.
   //! @return Reference to this vector.
   Vector4&    operator*=(const float scale);          
   //! @brief multiply each element and update this object
   //! @param[in] rhs Vector to multiply
   //! @return Reference to this vector.
   Vector4&    operator*=(const Vector4& rhs);         
   //! @brief inverse scale
   //! @param[in] scale Amount to scale.
   //! @return result.
   Vector4     operator/(const float scale) const;    
   //! @brief inverse scale and update this object
   //! @param[in] scale Amount to scale.
   //! @return Reference to this vector.
   Vector4&    operator/=(const float scale);          
   //! @brief exact compare, no epsilon
   //! @param[in] rhs Comparand
   //! @return Boolean equality.
   bool        operator==(const Vector4& rhs) const;  
   //! @brief exact compare, no epsilon
   //! @param[in] rhs Comparand
   //! @return Boolean inequality.
   bool        operator!=(const Vector4& rhs) const;   
   //! @brief comparison for sort.
   //! @param[in] rhs Comparand.
   //! @return Boolean this < rhs.
   bool        operator<(const Vector4& rhs) const;    

   //! @brief scale operator, new vector.
   //! @param[in] a scale value.
   //! @param[in] vec Source Vector.
   //! @return Scaled Vector.
   friend Vector4 operator*(const float a, const Vector4 vec);
};

///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector2
///////////////////////////////////////////////////////////////////////////////
inline Vector2 Vector2::operator-() const
{
   return Vector2(-x, -y);
}

inline Vector2 Vector2::operator+(const Vector2& rhs) const
{
   return Vector2(x + rhs.x, y + rhs.y);
}

inline Vector2 Vector2::operator-(const Vector2& rhs) const
{
   return Vector2(x - rhs.x, y - rhs.y);
}

inline Vector2& Vector2::operator+=(const Vector2& rhs)
{
   x += rhs.x;
   y += rhs.y;
   return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& rhs)
{
   x -= rhs.x;
   y -= rhs.y;
   return *this;
}

inline Vector2 Vector2::operator*(const float a) const
{
   return Vector2(x * a, y * a);
}

inline Vector2 Vector2::operator*(const Vector2& rhs) const
{
   return Vector2(x * rhs.x, y * rhs.y);
}

inline Vector2& Vector2::operator*=(const float a)
{
   x *= a;
   y *= a;
   return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& rhs)
{
   x *= rhs.x;
   y *= rhs.y;
   return *this;
}

inline Vector2 Vector2::operator/(const float a) const
{
   return Vector2(x / a, y / a);
}

inline Vector2& Vector2::operator/=(const float a)
{
   x /= a;
   y /= a;
   return *this;
}

inline bool Vector2::operator==(const Vector2& rhs) const
{
   return (x == rhs.x) && (y == rhs.y);
}

inline bool Vector2::operator!=(const Vector2& rhs) const
{
   return (x != rhs.x) || (y != rhs.y);
}

inline bool Vector2::operator<(const Vector2& rhs) const
{
   if (x < rhs.x) return true;

   if (x > rhs.x) return false;

   if (y < rhs.y) return true;

   if (y > rhs.y) return false;

   return false;
}

inline void Vector2::set(float x, float y)
{
   this->x = x;
   this->y = y;
}

inline float Vector2::length() const
{
   return sqrtf(x * x + y * y);
}

inline float Vector2::distance(const Vector2& vec) const
{
   return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y));
}

inline Vector2& Vector2::normalize()
{
   const float EPSILON = 0.000001f;
   float xxyy = x * x + y * y;

   if (xxyy < EPSILON)
      return *this;

   //float invLength = invSqrt(xxyy);
   float invLength = 1.0f / sqrtf(xxyy);
   x *= invLength;
   y *= invLength;
   return *this;
}

inline float Vector2::dot(const Vector2& rhs) const
{
   return (x * rhs.x + y * rhs.y);
}

inline bool Vector2::equal(const Vector2& rhs, float epsilon) const
{
   return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon;
}

inline Vector2 operator*(const float a, const Vector2 vec)
{
   return Vector2(a * vec.x, a * vec.y);
}

// END OF VECTOR2 /////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector3
///////////////////////////////////////////////////////////////////////////////
inline Vector3 Vector3::operator-() const
{
   return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator+(const Vector3& rhs) const
{
   return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

inline Vector3 Vector3::operator-(const Vector3& rhs) const
{
   return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

inline Vector3& Vector3::operator+=(const Vector3& rhs)
{
   x += rhs.x;
   y += rhs.y;
   z += rhs.z;
   return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& rhs)
{
   x -= rhs.x;
   y -= rhs.y;
   z -= rhs.z;
   return *this;
}

inline Vector3 Vector3::operator*(const float a) const
{
   return Vector3(x * a, y * a, z * a);
}

inline Vector3 Vector3::operator*(const Vector3& rhs) const
{
   return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

inline Vector3& Vector3::operator*=(const float a)
{
   x *= a;
   y *= a;
   z *= a;
   return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& rhs)
{
   x *= rhs.x;
   y *= rhs.y;
   z *= rhs.z;
   return *this;
}

inline Vector3 Vector3::operator/(const float a) const
{
   return Vector3(x / a, y / a, z / a);
}

inline Vector3& Vector3::operator/=(const float a)
{
   x /= a;
   y /= a;
   z /= a;
   return *this;
}

inline bool Vector3::operator==(const Vector3& rhs) const
{
   return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

inline bool Vector3::operator!=(const Vector3& rhs) const
{
   return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

inline bool Vector3::operator<(const Vector3& rhs) const
{
   if (x < rhs.x) return true;

   if (x > rhs.x) return false;

   if (y < rhs.y) return true;

   if (y > rhs.y) return false;

   if (z < rhs.z) return true;

   if (z > rhs.z) return false;

   return false;
}

inline void Vector3::set(float x, float y, float z)
{
   this->x = x;
   this->y = y;
   this->z = z;
}

inline float Vector3::length() const
{
   return sqrtf(x * x + y * y + z * z);
}

inline float Vector3::distance(const Vector3& vec) const
{
   return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
}

inline Vector3& Vector3::normalize()
{
   const float EPSILON = 0.000001f;
   float xxyyzz = x * x + y * y + z * z;

   if (xxyyzz < EPSILON)
      return *this; // do nothing if it is ~zero vector

   //float invLength = invSqrt(xxyyzz);
   float invLength = 1.0f / sqrtf(xxyyzz);
   x *= invLength;
   y *= invLength;
   z *= invLength;
   return *this;
}

inline float Vector3::dot(const Vector3& rhs) const
{
   return (x * rhs.x + y * rhs.y + z * rhs.z);
}

inline Vector3 Vector3::cross(const Vector3& rhs) const
{
   return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

inline bool Vector3::equal(const Vector3& rhs, float epsilon) const
{
   return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon && fabs(z - rhs.z) < epsilon;
}

inline Vector3 operator*(const float a, const Vector3 vec)
{
   return Vector3(a * vec.x, a * vec.y, a * vec.z);
}

// END OF VECTOR3 /////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
// inline functions for Vector4
///////////////////////////////////////////////////////////////////////////////
inline Vector4 Vector4::operator-() const
{
   return Vector4(-x, -y, -z, -w);
}

inline Vector4 Vector4::operator+(const Vector4& rhs) const
{
   return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

inline Vector4 Vector4::operator-(const Vector4& rhs) const
{
   return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

inline Vector4& Vector4::operator+=(const Vector4& rhs)
{
   x += rhs.x;
   y += rhs.y;
   z += rhs.z;
   w += rhs.w;
   return *this;
}

inline Vector4& Vector4::operator-=(const Vector4& rhs)
{
   x -= rhs.x;
   y -= rhs.y;
   z -= rhs.z;
   w -= rhs.w;
   return *this;
}

inline Vector4 Vector4::operator*(const float a) const
{
   return Vector4(x * a, y * a, z * a, w * a);
}

inline Vector4 Vector4::operator*(const Vector4& rhs) const
{
   return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

inline Vector4& Vector4::operator*=(const float a)
{
   x *= a;
   y *= a;
   z *= a;
   w *= a;
   return *this;
}

inline Vector4& Vector4::operator*=(const Vector4& rhs)
{
   x *= rhs.x;
   y *= rhs.y;
   z *= rhs.z;
   w *= rhs.w;
   return *this;
}

inline Vector4 Vector4::operator/(const float a) const
{
   return Vector4(x / a, y / a, z / a, w / a);
}

inline Vector4& Vector4::operator/=(const float a)
{
   x /= a;
   y /= a;
   z /= a;
   w /= a;
   return *this;
}

inline bool Vector4::operator==(const Vector4& rhs) const
{
   return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
}

inline bool Vector4::operator!=(const Vector4& rhs) const
{
   return (x != rhs.x) || (y != rhs.y) || (z != rhs.z) || (w != rhs.w);
}

inline bool Vector4::operator<(const Vector4& rhs) const
{
   if (x < rhs.x) return true;

   if (x > rhs.x) return false;

   if (y < rhs.y) return true;

   if (y > rhs.y) return false;

   if (z < rhs.z) return true;

   if (z > rhs.z) return false;

   if (w < rhs.w) return true;

   if (w > rhs.w) return false;

   return false;
}

inline void Vector4::set(float x, float y, float z, float w)
{
   this->x = x;
   this->y = y;
   this->z = z;
   this->w = w;
}

inline float Vector4::length() const
{
   return sqrtf(x * x + y * y + z * z + w * w);
}

inline float Vector4::distance(const Vector4& vec) const
{
   return sqrtf((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z) + (vec.w - w) * (vec.w - w));
}

inline Vector4& Vector4::normalize()
{
   //NOTE: leave w-component untouched
   const float EPSILON = 0.000001f;
   float xxyyzz = x * x + y * y + z * z;

   if (xxyyzz < EPSILON)
      return *this; // do nothing if it is zero vector

   //float invLength = invSqrt(xxyyzz);
   float invLength = 1.0f / sqrtf(xxyyzz);
   x *= invLength;
   y *= invLength;
   z *= invLength;
   return *this;
}

inline float Vector4::dot(const Vector4& rhs) const
{
   return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}

inline bool Vector4::equal(const Vector4& rhs, float epsilon) const
{
   return fabs(x - rhs.x) < epsilon && fabs(y - rhs.y) < epsilon &&
          fabs(z - rhs.z) < epsilon && fabs(w - rhs.w) < epsilon;
}

inline Vector4 operator*(const float a, const Vector4 vec)
{
   return Vector4(a * vec.x, a * vec.y, a * vec.z, a * vec.w);
}

// END OF VECTOR4 /////////////////////////////////////////////////////////////

#endif
