#include "glad/glad.h"
#include <GLFW/glfw3.h>  // Includes <GLES2/gl2.h>

#include "ESShaderRepository.h"
#include "RenderPacket.h"
#include "Vectors.h"
#include "ShapeDrawing.h"

constexpr double PI = 3.14159265359;
constexpr double TWOPI = PI * 2;
constexpr double DEG2RAD = 0.0174533;

CLine::CLine(float tx0, float ty0, float tx1, float ty1, float tfWidth) : IShape(), 
   x0(tx0), y0(ty0), x1(tx1), y1(ty1), fWidth(tfWidth)
{
   mpRenderPacket = new RenderPacket();
   // Init the render packet which will be passed to the scene graph on render.
   mpRenderPacket->mMasterZ = 0.0f;

   // Set the texture id
   mpRenderPacket->miTexture = 0;
   // Create VBO for drawing the image
   glGenBuffers(1, &mpRenderPacket->miVbo);
   // Set the shader program
   mpRenderPacket->miShaderProgram =
      ESShaderRepository::Instance().GetShaderProgram(ESShaderRepository::COLOR_FILL);
   // Set to no rotation etc...
   mpRenderPacket->mTransform.identity();
   // Set type of primatives
   mpRenderPacket->miType = GL_TRIANGLE_STRIP;

   // shader (COLOR_FILL)
   mpRenderPacket->miVertArraySize = 3;
   mpRenderPacket->miVertArrayOffset = 0;
   mpRenderPacket->miTextureArraySize = 0;
   mpRenderPacket->miTextureArrayOffset = 0;
   mpRenderPacket->miColorArraySize = 4;
   mpRenderPacket->miColorArrayOffset = 3;
   mpRenderPacket->miVertexStride =
      7 * sizeof(GLfloat);  // 3 floats for the pos, 4 for color

   mpRenderPacket->miVertexCount = 4;
   // copy verts to local buffer
   mpRenderPacket->mfVertices =
      new float[mpRenderPacket->miVertexStride * mpRenderPacket->miVertexCount];
}

void CLine::Instantiate()
{
   //Generate box corners
   Vector2 a, b, c, d;
   Vector2 p, q;
   p.x = x0;
   p.y = y0;
   q.x = x1;
   q.y = y1;
   float l = fWidth;


   // horizontal rectangle 
   if (p.x == q.x)
   {
      a.x = p.x - (l / 2.0);
      a.y = p.y;

      d.x = p.x + (l / 2.0);
      d.y = p.y;

      b.x = q.x - (l / 2.0);
      b.y = q.y;

      c.x = q.x + (l / 2.0);
      c.y = q.y;
   }

   // vertical rectangle 
   else if (p.y == q.y)
   {
      a.y = p.y - (l / 2.0);
      a.x = p.x;

      d.y = p.y + (l / 2.0);
      d.x = p.x;

      b.y = q.y - (l / 2.0);
      b.x = q.x;

      c.y = q.y + (l / 2.0);
      c.x = q.x;
   }

   // slanted rectangle 
   else
   {
      // calculate slope of the side 
      double m = (p.x - q.x) / float(q.y - p.y);

      // calculate displacements along axes 
      float dx = (l);
      dx /= sqrt(1.0 + (m * m));
      dx *= 0.5;

      float dy = m * dx;

      a.x = p.x - dx;
      a.y = p.y - dy;

      d.x = p.x + dx;
      d.y = p.y + dy;

      b.x = q.x - dx;
      b.y = q.y - dy;

      c.x = q.x + dx;
      c.y = q.y + dy;
   }

   // load verts with data
   float dz = 0.0f;
   int vi = 0;
   int ci = 0;

   mpRenderPacket->mfVertices[vi++] = a.x;  // UL
   mpRenderPacket->mfVertices[vi++] = a.y;
   mpRenderPacket->mfVertices[vi++] = dz;
   mpRenderPacket->mfVertices[vi++] = 1;    // R
   mpRenderPacket->mfVertices[vi++] = 0;  // G
   mpRenderPacket->mfVertices[vi++] = 0;   // B
   mpRenderPacket->mfVertices[vi++] = 1;  // A

   mpRenderPacket->mfVertices[vi++] = b.x;  // UR
   mpRenderPacket->mfVertices[vi++] = b.y;
   mpRenderPacket->mfVertices[vi++] = dz;
   mpRenderPacket->mfVertices[vi++] = 1;    // R
   mpRenderPacket->mfVertices[vi++] = 0;  // G
   mpRenderPacket->mfVertices[vi++] = 0;   // B
   mpRenderPacket->mfVertices[vi++] = 1;  // A

   mpRenderPacket->mfVertices[vi++] = d.x;  // LL
   mpRenderPacket->mfVertices[vi++] = d.y;
   mpRenderPacket->mfVertices[vi++] = dz;
   mpRenderPacket->mfVertices[vi++] = 1;    // R
   mpRenderPacket->mfVertices[vi++] = 0;  // G
   mpRenderPacket->mfVertices[vi++] = 0;   // B
   mpRenderPacket->mfVertices[vi++] = 1;  // A

   mpRenderPacket->mfVertices[vi++] = c.x;  // LR
   mpRenderPacket->mfVertices[vi++] = c.y;
   mpRenderPacket->mfVertices[vi++] = dz;
   mpRenderPacket->mfVertices[vi++] = 1;    // R
   mpRenderPacket->mfVertices[vi++] = 0;  // G
   mpRenderPacket->mfVertices[vi++] = 0;   // B
   mpRenderPacket->mfVertices[vi++] = 1;  // A

   mpRenderPacket->mTransform[12] = 0;
   mpRenderPacket->mTransform[13] = 0;
}

CLine::~CLine()
{
   delete mpRenderPacket;
}


void CLine::Draw()
{
   mpRenderPacket->Render();

}
/*******************************************/
CCircle::CCircle(float tx0, float ty0, float tradius, int tsides) : IShape(),
   x0(tx0), y0(ty0), radius(tradius), sides(tsides)
{
   mpRenderPacket = NULL;

}

CCircle::CCircle()
{
   CCircle(0.5f,0.5f, 0.2f, 25);
}
void CCircle::Instantiate()
{
   GLint numberOfVertices = sides + 2;

   mpRenderPacket = new RenderPacket();
   // Init the render packet which will be passed to the scene graph on render.
   mpRenderPacket->mMasterZ = 0.0f;

   // Set the texture id
   mpRenderPacket->miTexture = 0;
   // Create VBO for drawing the image
   glGenBuffers(1, &mpRenderPacket->miVbo);
   // Set the shader program
   mpRenderPacket->miShaderProgram =
      ESShaderRepository::Instance().GetShaderProgram(ESShaderRepository::COLOR_FILL);
   // Set to no rotation etc...
   mpRenderPacket->mTransform.identity();
   // Set type of primatives
   mpRenderPacket->miType = GL_TRIANGLE_FAN;

   // shader (COLOR_FILL)
   mpRenderPacket->miVertArraySize = 3;
   mpRenderPacket->miVertArrayOffset = 0;
   mpRenderPacket->miTextureArraySize = 0;
   mpRenderPacket->miTextureArrayOffset = 0;
   mpRenderPacket->miColorArraySize = 4;
   mpRenderPacket->miColorArrayOffset = 3;
   mpRenderPacket->miVertexStride =
      7 * sizeof(GLfloat);  // 3 floats for the pos, 4 for color

   mpRenderPacket->miVertexCount = numberOfVertices; // nVerts;
                                                     // copy verts to local buffer
   mpRenderPacket->mfVertices =
      new float[mpRenderPacket->miVertexStride * mpRenderPacket->miVertexCount];

   mpRenderPacket->mfVertices[0] = x0;
   mpRenderPacket->mfVertices[1] = y0;
   mpRenderPacket->mfVertices[2] = 0.0;
   mpRenderPacket->mfVertices[3] = 0;
   mpRenderPacket->mfVertices[4] = 0;
   mpRenderPacket->mfVertices[5] = 1;
   mpRenderPacket->mfVertices[6] = 0.4;

   float fStep = TWOPI / sides;
   float theta = 0;

   for (int i = 1; i < numberOfVertices; i++)
   {
      mpRenderPacket->mfVertices[i * 7] = x0 + (radius * cos(theta));
      mpRenderPacket->mfVertices[(i * 7) + 1] = y0 + (radius * sin(theta));
      mpRenderPacket->mfVertices[(i * 7) + 2] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 3] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 4] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 5] = 1;
      mpRenderPacket->mfVertices[(i * 7) + 6] = 0.4;
      theta += fStep;
   }
}


CCircle::~CCircle()
{
   if (mpRenderPacket)
      delete mpRenderPacket;
}


void CCircle::Draw()
{
   if (mpRenderPacket)
      mpRenderPacket->Render();

}

/*******************************************/
CCircleLine::CCircleLine()
{
   CCircleLine(-0.6f, -0.5f, 0.2f, 35);
}
CCircleLine::CCircleLine(float x0, float y0, float radius, int sides) : IShape(),
   mx0(x0), my0(y0), mradius(radius), msides(sides)
{
   mpRenderPacket = nullptr;
}

void CCircleLine::Instantiate()
{
   GLint numberOfVertices = msides + 1;

   mpRenderPacket = new RenderPacket();
   // Init the render packet which will be passed to the scene graph on render.
   mpRenderPacket->mMasterZ = 0.0f;

   // Set the texture id
   mpRenderPacket->miTexture = 0;
   // Create VBO for drawing the image
   glGenBuffers(1, &mpRenderPacket->miVbo);
   // Set the shader program
   mpRenderPacket->miShaderProgram =
      ESShaderRepository::Instance().GetShaderProgram(ESShaderRepository::COLOR_FILL);
   // Set to no rotation etc...
   mpRenderPacket->mTransform.identity();
   // Set type of primatives
   mpRenderPacket->miType = GL_LINE_LOOP;

   // shader (COLOR_FILL)
   mpRenderPacket->miVertArraySize = 3;
   mpRenderPacket->miVertArrayOffset = 0;
   mpRenderPacket->miTextureArraySize = 0;
   mpRenderPacket->miTextureArrayOffset = 0;
   mpRenderPacket->miColorArraySize = 4;
   mpRenderPacket->miColorArrayOffset = 3;
   mpRenderPacket->miVertexStride =
      7 * sizeof(GLfloat);  // 3 floats for the pos, 4 for color

   mpRenderPacket->miVertexCount = numberOfVertices; // nVerts;
                                                     // copy verts to local buffer
   mpRenderPacket->mfVertices =
      new float[mpRenderPacket->miVertexStride * mpRenderPacket->miVertexCount];

   float fStep = TWOPI / msides;
   float theta = 0;

   for (int i = 0; i < numberOfVertices; i++)
   {
      mpRenderPacket->mfVertices[i * 7] = mx0 + (mradius * cos(theta));
      mpRenderPacket->mfVertices[(i * 7) + 1] = my0 + (mradius * sin(theta));
      mpRenderPacket->mfVertices[(i * 7) + 2] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 3] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 4] = 1;
      mpRenderPacket->mfVertices[(i * 7) + 5] = 1;
      mpRenderPacket->mfVertices[(i * 7) + 6] = 1;
      theta += fStep;
   }
}


CCircleLine::~CCircleLine()
{
   if (mpRenderPacket)
      delete mpRenderPacket;
}


void CCircleLine::Draw()
{
   if (mpRenderPacket)
      mpRenderPacket->Render();

}

/*******************************************/

/*******************************************/
CFanLine::CFanLine()
{
   CFanLine(-0.6f, 0.5f, 0.2f, 15, 0, 180);
}

CFanLine::CFanLine(float x0, float y0, float radius, int sides, float start, float stop) : IShape(),
   mx0(x0), my0(y0), mradius(radius), msides(sides), mstart(start), mstop(stop)
{
   mpRenderPacket = NULL;
}

void CFanLine::Instantiate()
{
   mstart *= DEG2RAD;
   mstop *= DEG2RAD;

   GLint numberOfVertices = msides + 1;

   mpRenderPacket = new RenderPacket();
   // Init the render packet which will be passed to the scene graph on render.
   mpRenderPacket->mMasterZ = 0.0f;

   // Set the texture id
   mpRenderPacket->miTexture = 0;
   // Create VBO for drawing the image
   glGenBuffers(1, &mpRenderPacket->miVbo);
   // Set the shader program
   mpRenderPacket->miShaderProgram =
      ESShaderRepository::Instance().GetShaderProgram(ESShaderRepository::COLOR_FILL);
   // Set to no rotation etc...
   mpRenderPacket->mTransform.identity();
   // Set type of primatives
   mpRenderPacket->miType = GL_LINE_STRIP;

   // shader (COLOR_FILL)
   mpRenderPacket->miVertArraySize = 3;
   mpRenderPacket->miVertArrayOffset = 0;
   mpRenderPacket->miTextureArraySize = 0;
   mpRenderPacket->miTextureArrayOffset = 0;
   mpRenderPacket->miColorArraySize = 4;
   mpRenderPacket->miColorArrayOffset = 3;
   mpRenderPacket->miVertexStride =
      7 * sizeof(GLfloat);  // 3 floats for the pos, 4 for color

   mpRenderPacket->miVertexCount = numberOfVertices; // nVerts;
                                                     // copy verts to local buffer
   mpRenderPacket->mfVertices =
      new float[mpRenderPacket->miVertexStride * mpRenderPacket->miVertexCount];

   float fStep = (mstart - mstop) / msides;
   float theta = mstart;

   for (int i = 0; i < numberOfVertices; i++)
   {
      mpRenderPacket->mfVertices[i * 7] = mx0 + (mradius * cos(theta));
      mpRenderPacket->mfVertices[(i * 7) + 1] = my0 + (mradius * sin(theta));
      mpRenderPacket->mfVertices[(i * 7) + 2] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 3] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 4] = 1;
      mpRenderPacket->mfVertices[(i * 7) + 5] = 1;
      mpRenderPacket->mfVertices[(i * 7) + 6] = 1;
      theta += fStep;
   }
}

/**************************/
CFanLine::~CFanLine()
{
   if (mpRenderPacket)
      delete mpRenderPacket;
}


void CFanLine::Draw()
{
   if (mpRenderPacket)
      mpRenderPacket->Render();

}

/*****************/
CFan::CFan()
{
   CFan(-0.4, 0.1f, 200.0 / 1024.0, 10, 90, 180);
}

CFan::CFan(float x0, float y0, float radius, int sides, float start, float stop)  : IShape(),
   mx0(x0), my0(y0), mradius(radius), msides(sides), mstart(start), mstop(stop)
{
   mpRenderPacket = NULL;
}

void CFan::Instantiate()
{
   mstart *= DEG2RAD;
   mstop *= DEG2RAD;

   GLint numberOfVertices = msides + 2;

   mpRenderPacket = new RenderPacket();
   // Init the render packet which will be passed to the scene graph on render.
   mpRenderPacket->mMasterZ = 0.0f;

   // Set the texture id
   mpRenderPacket->miTexture = 0;
   // Create VBO for drawing the image
   glGenBuffers(1, &mpRenderPacket->miVbo);
   // Set the shader program
   mpRenderPacket->miShaderProgram =
      ESShaderRepository::Instance().GetShaderProgram(ESShaderRepository::COLOR_FILL);
   // Set to no rotation etc...
   mpRenderPacket->mTransform.identity();
   // Set type of primatives
   mpRenderPacket->miType = GL_TRIANGLE_FAN;

   // shader (COLOR_FILL)
   mpRenderPacket->miVertArraySize = 3;
   mpRenderPacket->miVertArrayOffset = 0;
   mpRenderPacket->miTextureArraySize = 0;
   mpRenderPacket->miTextureArrayOffset = 0;
   mpRenderPacket->miColorArraySize = 4;
   mpRenderPacket->miColorArrayOffset = 3;
   mpRenderPacket->miVertexStride =
      7 * sizeof(GLfloat);  // 3 floats for the pos, 4 for color

   mpRenderPacket->miVertexCount = numberOfVertices; // nVerts;
                                                     // copy verts to local buffer
   mpRenderPacket->mfVertices =
      new float[mpRenderPacket->miVertexStride * mpRenderPacket->miVertexCount];

   mpRenderPacket->mfVertices[0] = mx0;
   mpRenderPacket->mfVertices[1] = my0;
   mpRenderPacket->mfVertices[2] = 0.0;
   mpRenderPacket->mfVertices[3] = 1;
   mpRenderPacket->mfVertices[4] = 0;
   mpRenderPacket->mfVertices[5] = 1;
   mpRenderPacket->mfVertices[6] = 0.4;

   float fStep = (mstop - mstart) / msides;
   float theta = mstart;
   for (int i = 1; i < numberOfVertices; i++)
   {
      mpRenderPacket->mfVertices[i * 7] = mx0 + (mradius * cos(theta));
      mpRenderPacket->mfVertices[(i * 7) + 1] = my0 + (mradius * sin(theta));
      mpRenderPacket->mfVertices[(i * 7) + 2] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 3] = 1;
      mpRenderPacket->mfVertices[(i * 7) + 4] = 0;
      mpRenderPacket->mfVertices[(i * 7) + 5] = 1;
      mpRenderPacket->mfVertices[(i * 7) + 6] = 0.4;
      theta += fStep;
   }
}

CFan::~CFan()
{
   if (mpRenderPacket)
      delete mpRenderPacket;
}


void CFan::Draw()
{
   if (mpRenderPacket)
      mpRenderPacket->Render();

}

/****************************************/
CRoundRectangle::CRoundRectangle()
{
   CRoundRectangle(-0.9, 0.9, 0.9, -0.9, 40.0 / 1024.0);
}

CRoundRectangle::CRoundRectangle(float x0, float y0, float x1, float y1, float width) :IShape(),
   mx0(x0), my0(y0), mx1(x1), my1(y1), mwidth(width)
{
   for (int i = 0; i < 4; i++)
   {
      pLines[i] = NULL;
      pFans[i]  = NULL;
   }
}

void CRoundRectangle::Instantiate()
{
   pLines[0] = new CLine(mx0 + mwidth / 2, my0, mx1 - mwidth / 2, my0, mwidth);
   pLines[0]->Instantiate();
   pLines[1] = new CLine(mx1, my0 - mwidth / 2, mx1, my1 + mwidth / 2, mwidth);
   pLines[1]->Instantiate();
   pLines[2] = new CLine(mx1 - mwidth / 2, my1, mx0 + mwidth / 2, my1, mwidth);
   pLines[2]->Instantiate();
   pLines[3] = new CLine(mx0, my1 + mwidth / 2, mx0, my0 - mwidth / 2, mwidth);
   pLines[3]->Instantiate();


   pFans[0] = new CFan(mx0 + mwidth / 2, my0 - mwidth / 2, mwidth, 10, 90, 180);
   pFans[0]->Instantiate();
   pFans[1] = new CFan(mx1 - mwidth / 2, my0 - mwidth / 2, mwidth, 10, 0, 90);
   pFans[1]->Instantiate();
   pFans[2] = new CFan(mx0 + mwidth / 2, my1 + mwidth / 2, mwidth, 10, 270, 180);
   pFans[2]->Instantiate();
   pFans[3] = new CFan(mx1 - mwidth / 2, my1 + mwidth / 2, mwidth, 10, 0, -90);
   pFans[3]->Instantiate();
}

CRoundRectangle::~CRoundRectangle()
{
   for (int i = 0; i < 4; i++)
   {
      if (pLines[i]) delete pLines[i];
      if (pFans[i])  delete pFans[i];
   }

}


void CRoundRectangle::Draw()
{
   for (int i = 0; i < 4; i++)
   {
      if (pLines[i]) pLines[i]->Draw();
      if (pFans[i])  pFans [i]->Draw();
   }

}
