#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "ESShaderRepository.h"

#include <stdio.h>
#include "Log.h"

#define SHADER_GLSLV(VERSION, SHADER) "#version " #VERSION " es\n" #SHADER

// Fragment and vertex shaders code
static const char* pColorSpriteFragShader = SHADER_GLSLV(
    320, 
    precision mediump float; 
    uniform sampler2D uSampler2d; 
    in vec2 v_texCoord; 
    in vec4 vColor;
    out vec4 fragColor; 
    void main(void) 
    {
        vec4 color = texture(uSampler2d, v_texCoord) * vColor;
        if (color.a > 0.1)
            fragColor = color;
        else
            discard;
    });

static const char* pColorSpriteVertShader = SHADER_GLSLV(
    320, 
    precision mediump float; 
    uniform mat4 uModelview; 
    in vec4 aPosition; 
    in vec2 aUV;
    in vec4 aColor; 
    out vec2 v_texCoord; out vec4 vColor; 
    void main() 
    {
        vColor = aColor;
        v_texCoord = aUV.st;
        gl_Position = uModelview * aPosition;
    });

static const char* pBasicSpriteFragShader = SHADER_GLSLV(
    320, 
    precision mediump float; 
    uniform sampler2D uSampler2d; 
    in vec2 v_texCoord;
    out vec4 fragColor; 
    void main(void) 
    {
        vec4 color = texture(uSampler2d, v_texCoord);
        if (color.a > 0.1)
            fragColor = color;
        else
            discard;
    });

static const char* pBasicSpriteVertShader = SHADER_GLSLV(
    320, 
    precision mediump float; 
    in vec4 aPosition; 
    in vec2 aUV; 
    uniform mat4 uModelview;
    out vec2 v_texCoord; 
    void main() 
    {
        v_texCoord = aUV.st;
        gl_Position = uModelview * aPosition;
    });

static const char* pColorFillFragShader = SHADER_GLSLV(
    320, 
    precision mediump float; 
    in vec4 vColor; 
    out vec4 fragColor; 
    void main(void) 
    {
        if (vColor.a > 0.1)
        {
            fragColor = vColor;
            fragColor.a = vColor.a;
        }
        else
            discard;
    });

static const char* pColorFillVertShader = SHADER_GLSLV(
    320, 
    precision mediump float; 
    in vec4 aPosition; 
    uniform mat4 uModelview; 
    in vec4 aColor;
    out vec4 vColor; 
    void main() 
    {
        vColor = aColor;
        gl_Position = uModelview * aPosition;
    });
static const char* pFontVertexShader = SHADER_GLSLV(
    320, 
    precision mediump float; 
    in vec4 aPosition; 
    in vec2 aUV; 
    uniform mat4 uModelview;
    out vec2 v_texCoord; 
    void main() 
    {
        v_texCoord = aUV.st;
        gl_Position = uModelview * aPosition;
    });

static const char* pFontFragmentShader = SHADER_GLSLV(
    320, 
    precision mediump float; 
    uniform vec4 uColor; 
    uniform sampler2D uSampler2d;
    in vec2 v_texCoord; 
    out vec4 vColor; 
    void main(void) 
    {
        vColor = texture(uSampler2d, v_texCoord);
        vColor.rgb = uColor.rgb;
    });

ESShaderRepository& ESShaderRepository::Instance()
{
    static ESShaderRepository instance;

    return instance;
}

ESShaderRepository::~ESShaderRepository() {}

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
        // MessageBox(hWnd, i32InfoLogLength ? pszInfoLog : _T(""), _T("Failed to compile fragment
        // shader"), MB_OK|MB_ICONEXCLAMATION);

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
        // MessageBox(hWnd, i32InfoLogLength ? pszInfoLog : _T(""), _T("Failed to compile vertex
        // shader"), MB_OK|MB_ICONEXCLAMATION);
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
        // MessageBox(hWnd, i32InfoLogLength ? pszInfoLog : _T(""), _T("Failed to link program"),
        // MB_OK|MB_ICONEXCLAMATION);
        log(Log::L_ERROR, "Failed to link shader program: %s", pszInfoLog);

        delete[] pszInfoLog;
    }

    return uiProgramObject;
}

ESShaderRepository::ESShaderRepository()
{
    mShaders[BASIC_SPRITE] = compileShader(pBasicSpriteFragShader, pBasicSpriteVertShader);
    mShaders[COLOR_SPRITE] = compileShader(pColorSpriteFragShader, pColorSpriteVertShader);
    mShaders[FONT] = compileShader(pFontFragmentShader, pFontVertexShader);
    mShaders[COLOR_FILL] = compileShader(pColorFillFragShader, pColorFillVertShader);
}
