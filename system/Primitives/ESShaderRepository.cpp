#include "glad/glad.h"
#include <GLFW/glfw3.h>
 
#include "ESShaderRepository.h"

#include <stdio.h>
#include "Log.h"

// Fragment and vertex shaders code

// modified to discard low alpha values for stencil operations
static const char* pColorSpriteFragShader =
   "uniform sampler2D    uSampler2d;                         \n"
   "varying mediump vec2 v_texCoord;                         \n"
   "varying mediump vec4 vColor;                             \n"
   "void main (void)                                         \n"
   "{                                                        \n"
   "   mediump vec4 color = texture2D(uSampler2d, v_texCoord) * vColor;     \n"
   "   if(color.a > 0.1)                                     \n"
   "      gl_FragColor = color;                              \n"
   "   else                                                  \n"
   "      discard;                                           \n"
   "}                                                        \n";

static const char* pColorSpriteVertShader =
   "attribute highp   vec4  aPosition;                       \n"
   "attribute mediump vec2  aUV;                             \n"
   "attribute mediump vec4  aColor;                          \n"
   "uniform   mediump mat4  uModelview;                      \n"
   "varying   mediump vec2  v_texCoord;                      \n"
   "varying   mediump vec4  vColor;                          \n"
   "                                                         \n"
   "void main()                                              \n"
   "{                                                        \n"
   "   vColor = aColor;                                      \n"
   "   v_texCoord  = aUV.st;                                 \n"
   "   gl_Position = uModelview * aPosition;                 \n"
   "}                                                        \n";

static const char* pBasicSpriteFragShader =
   "uniform sampler2D    uSampler2d;                           \n"
   "varying mediump vec2 v_texCoord;                           \n"
   "void main (void)                                           \n"
   "{                                                          \n"
   "   mediump vec4 color = texture2D(uSampler2d, v_texCoord); \n"
   "   if(color.a > 0.1)                                       \n"
   "      gl_FragColor = color;                                \n"
   "   else                                                    \n"
   "      discard;                                             \n"
   "}                                                          \n";

static const char* pBasicSpriteVertShader =
   "attribute highp   vec4  aPosition;                       \n"
   "attribute mediump vec2  aUV;                             \n"
   "uniform   mediump mat4  uModelview;                      \n"
   "varying   mediump vec2  v_texCoord;                      \n"
   "                                                         \n"
   "void main()                                              \n"
   "{                                                        \n"
   "   v_texCoord  = aUV.st;                                 \n"
   "   gl_Position = uModelview * aPosition;                 \n"
   "}                                                        \n";

static const char* pColorFillFragShader =
   "varying mediump vec4 vColor;                             \n"
   "void main (void)                                         \n"
   "{                                                        \n"
   "   if(vColor.a > 0.1)                                     \n"
   "   {                                                     \n"
   "      gl_FragColor = vColor;                             \n"
   "      gl_FragColor.a = vColor.a;                         \n"
   "   }                                                     \n"
   "   else                                                  \n"
   "      discard;                                           \n"
   "}                                                        \n";

static const char* pColorFillVertShader =
   "attribute highp   vec4  aPosition;                       \n"
   "uniform   mediump mat4  uModelview;                      \n"
   "attribute mediump vec4  aColor;                          \n"
   "varying   mediump vec4  vColor;                          \n"
   "                                                         \n"
   "void main()                                              \n"
   "{                                                        \n"
   "   vColor = aColor;                                      \n"
   "   gl_Position = uModelview * aPosition;                 \n"
   "}                                                        \n";

static const char* pFontVertexShader =
   "attribute highp   vec4  aPosition;                       \n"
   "attribute mediump vec2  aUV;                             \n"
   "uniform   mediump mat4  uModelview;                      \n"
   "varying   mediump vec2  v_texCoord;                      \n"
   "                                                         \n"
   "void main()                                              \n"
   "{                                                        \n"
   "   v_texCoord  = aUV.st;                                 \n"
   "   gl_Position = uModelview * aPosition;                 \n"
   "}                                                        \n";


static const char* pFontFragmentShader =
   "uniform mediump vec4      uColor;                        \n"
   "uniform sampler2D         uSampler2d;                    \n"
   "varying mediump vec2      v_texCoord;                    \n"
   "void main (void)                                         \n"
   "{                                                        \n"
   "   gl_FragColor   = texture2D(uSampler2d, v_texCoord);   \n"
   "   gl_FragColor.rgb = uColor.rgb;                        \n"
   "}                                                        \n";

ESShaderRepository& ESShaderRepository::Instance()
{
   static ESShaderRepository instance;

   return instance;
}

ESShaderRepository::~ESShaderRepository()
{
}


int ESShaderRepository::GetShaderProgram(ShaderID id)
{
   int iRet = mShaders.begin()->second;
   std::map<ShaderID, int>::iterator it = mShaders.find(id);

   if (it != mShaders.end())
      iRet = (it)->second;

   return iRet;
}


static int32_t compileShader(const char* pFragment, const char* pVertex)
{
   // Create the fragment shader object
   uint32_t uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);

   // Load the source code into it
   glShaderSource(uiFragShader, 1, (const char**)&pFragment, 0);

   // Compile the source code
   glCompileShader(uiFragShader);

   // Check if compilation succeeded
   GLint bShaderCompiled;
   glGetShaderiv(uiFragShader, GL_COMPILE_STATUS, &bShaderCompiled);

   if (!bShaderCompiled)
   {
      // An error happened, first retrieve the length of the log message
      int32_t i32InfoLogLength, i32CharsWritten;
      glGetShaderiv(uiFragShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);

      // Allocate enough space for the message and retrieve it
      char* pszInfoLog = new char[i32InfoLogLength];
      glGetShaderInfoLog(uiFragShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

      // assert/end here
      //MessageBox(hWnd, i32InfoLogLength ? pszInfoLog : _T(""), _T("Failed to compile fragment shader"), MB_OK|MB_ICONEXCLAMATION);

      log(Log::L_ERROR, "Failed to compile fragment shader: %s", pszInfoLog);
      delete[] pszInfoLog;
   }

   // Loads the vertex shader in the same way
   GLuint uiVertShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(uiVertShader, 1, (const char**)&pVertex, 0);
   glCompileShader(uiVertShader);
   glGetShaderiv(uiVertShader, GL_COMPILE_STATUS, &bShaderCompiled);

   if (!bShaderCompiled)
   {
      int32_t i32InfoLogLength, i32CharsWritten;
      glGetShaderiv(uiVertShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
      char* pszInfoLog = new char[i32InfoLogLength];
      glGetShaderInfoLog(uiVertShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

      // assert/abort
      //MessageBox(hWnd, i32InfoLogLength ? pszInfoLog : _T(""), _T("Failed to compile vertex shader"), MB_OK|MB_ICONEXCLAMATION);
      log(Log::L_ERROR, "Failed to compile vertex shader: %s", pszInfoLog);

      delete[] pszInfoLog;
   }

   // Create the shader program
   uint32_t uiProgramObject = glCreateProgram();
   // Bind the custom vertex attribute "aPosition" to location VERTEX_ARRAY
   glBindAttribLocation(uiProgramObject, VERTEX_ARRAY, "aPosition");
   glBindAttribLocation(uiProgramObject, VERTEX_ARRAY + 2, "aColor");
   // Attach the fragment and vertex shaders to it
   glAttachShader(uiProgramObject, uiFragShader);
   glAttachShader(uiProgramObject, uiVertShader);


   // Link the program
   glLinkProgram(uiProgramObject);

   // Check if linking succeeded in the same way we checked for compilation success
   GLint bLinked;
   glGetProgramiv(uiProgramObject, GL_LINK_STATUS, &bLinked);

   if (!bLinked)
   {
      int32_t i32InfoLogLength, i32CharsWritten;
      glGetProgramiv(uiProgramObject, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
      char* pszInfoLog = new char[i32InfoLogLength];
      glGetProgramInfoLog(uiProgramObject, i32InfoLogLength, &i32CharsWritten, pszInfoLog);

      // assert/error
      //MessageBox(hWnd, i32InfoLogLength ? pszInfoLog : _T(""), _T("Failed to link program"), MB_OK|MB_ICONEXCLAMATION);
      log(Log::L_ERROR, "Failed to link shader program: %s", pszInfoLog);

      delete[] pszInfoLog;
   }

   return uiProgramObject;
}

ESShaderRepository::ESShaderRepository()
{
   mShaders[BASIC_SPRITE] = compileShader(pBasicSpriteFragShader, pBasicSpriteVertShader);
   mShaders[COLOR_SPRITE] = compileShader(pColorSpriteFragShader, pColorSpriteVertShader);
   mShaders[FONT]         = compileShader(pFontFragmentShader, pFontVertexShader);
   mShaders[COLOR_FILL]   = compileShader(pColorFillFragShader, pColorFillVertShader);
}

