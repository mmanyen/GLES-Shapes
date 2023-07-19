
#include "glad/glad.h"
#include <GLFW/glfw3.h>  // Includes <GLES2/gl2.h>

#include "IPlatform.h"
#include <stdio.h>
#include "Log.h"

#define FRAME_WIDTH (1024)
#define FRAME_HEIGHT (768)

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
   int32_t cursor_num = 0;

   // Translate the cursor position from the window/pixel based value to the GLES values
   double x = -1.0 + (xpos * (2.0 / FRAME_WIDTH));
   double y = 1.0 - (ypos * (2.0 / FRAME_HEIGHT));

   // Should do something with this 
   
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
   int32_t cursor_num = 0;

   if (button == GLFW_MOUSE_BUTTON_RIGHT)
      cursor_num = 2;
   else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
      cursor_num = 1;

   // Should do something with this 
 }

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

//! @brief A Platform supporter for GLFW libraries. Used for Desktop Linux/WIN32
class GLFWPlatform : public IPlatform
{
  public:
   GLFWPlatform();
   virtual ~GLFWPlatform() {}
   virtual bool ShouldExit();
   virtual void HandleEvents();
   virtual void FrameBegin();
   virtual void FrameEnd();
   virtual void Terminate();
   virtual bool Ready();
   virtual double CurrentTime();
   virtual uint32_t ScreenPixelWidth();
   virtual uint32_t ScreenPixelHeight();

  private:
   GLuint mFrameWidth;
   GLuint mFrameHeight;
   GLFWwindow* mWindow;
};

uint32_t GLFWPlatform::ScreenPixelWidth()
{
   return mFrameWidth;
}

uint32_t GLFWPlatform::ScreenPixelHeight()
{
   return mFrameHeight;
}

GLFWPlatform::GLFWPlatform() : IPlatform()
{
   mFrameWidth = FRAME_WIDTH;
   mFrameHeight = FRAME_HEIGHT;

    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
 
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        return;
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
 
    mWindow = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!mWindow)
    {
        glfwTerminate();
    }
 
 
    glfwMakeContextCurrent(mWindow);
    gladLoadGLES2Loader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

   vlog(Log::L_INFO, "GL_VERSION  : %s\n", glGetString(GL_VERSION));
   vlog(Log::L_INFO, "GL_RENDERER : %s\n", glGetString(GL_RENDERER));

   glfwSetCursorPosCallback(mWindow, cursor_position_callback);
   glfwSetMouseButtonCallback(mWindow, mouse_button_callback);
}

bool GLFWPlatform::ShouldExit()
{
   return glfwWindowShouldClose(mWindow);
}

void GLFWPlatform::HandleEvents()
{
   glfwPollEvents();
}

void GLFWPlatform::FrameBegin()
{
   glClear(GL_COLOR_BUFFER_BIT);
}

void GLFWPlatform::FrameEnd()
{
   glfwSwapBuffers(mWindow);
}

void GLFWPlatform::Terminate()
{
   glfwTerminate();
}

bool GLFWPlatform::Ready()
{
   return (mWindow != NULL);
}

double GLFWPlatform::CurrentTime()
{
  return glfwGetTime();
}

IPlatform& IPlatform::instance(void)
{
   static GLFWPlatform sPlatform;
   if (!sPlatform.Ready())
   {
      // TODO: Assert?
      log(Log::L_ERROR, "Platform not ready!");
   }

   return sPlatform;
}

