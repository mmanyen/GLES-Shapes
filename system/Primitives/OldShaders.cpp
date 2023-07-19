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
