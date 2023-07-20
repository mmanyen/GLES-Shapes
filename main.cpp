#include "BaseSprite.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>  // Includes <GLES2/gl2.h>

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "IPlatform.h"

#include "ShapeDrawing.h"

int main(int argc, char* argv[])
{
   // Start up platform
   IPlatform& rPlatform = IPlatform::instance();

   // TODO: Switch to smart pointer
   std::list<IPrimitive*> sceneGraph;
   // Create some shapes
   sceneGraph.push_back(new CLine(0.0f, 0.0f, -0.7f, -0.5f, (10.0f / 1024.0f)));
   sceneGraph.push_back(new CCircle(0.6f, 0.5f, 0.2f, 35));
   sceneGraph.push_back(new CCircleLine(-0.6f, -0.5f, 0.2f, 35));
   sceneGraph.push_back(new CFanLine(-0.6f, 0.5f, 0.2f, 15, 0, 180));
   sceneGraph.push_back(new CFan(-0.4, 0.1f, 200.0 / 1024.0, 10, 90, 180));
   sceneGraph.push_back(new CRoundRectangle(-0.9, 0.9, 0.9, -0.9, 40.0 / 1024.0));
   sceneGraph.push_back(new BaseSprite({-0.5, 0.0, -1.0, -1.0}, "assets/logo32.png" ));
   // Instanciate all shapes
   for(auto s : sceneGraph)
   {
      s->Instantiate();
   }

   while (!rPlatform.ShouldExit())
   {
      rPlatform.FrameBegin();
      
      // Draw Everything
      for(auto s : sceneGraph)
      {
         s->Draw();
      }

      rPlatform.FrameEnd();

      rPlatform.HandleEvents();

      // May sleep here for rest of system to have oxygen
   }

   // clean, remove when smart pointers
   for(auto s : sceneGraph)
   {
      delete s;
   }


   rPlatform.Terminate();
   return EXIT_SUCCESS;
}
