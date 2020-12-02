#pragma once
#include <stdint.h>
class RenderPacket;

class IShape
{
public:
   IShape() = default;
   virtual ~IShape() {}
   virtual void Instantiate() = 0;
   virtual void Draw() = 0;

   IShape(const IShape&) = delete;
   IShape& operator=(const IShape&) = delete;
protected:
   RenderPacket* mpRenderPacket = nullptr;

};

class CLine : public IShape
{
public:
   CLine() { CLine(0,0,400,400, 2); }
   CLine(float x0, float y0, float x1, float y1, float fWidth);
   virtual ~CLine();

   virtual void Instantiate() override;
   virtual void Draw() override;

protected:
   float x0;
   float y0;
   float x1;
   float y1;
   float fWidth;
};

class CCircle : public IShape
{
public:
   CCircle();
   CCircle(float x0, float y0, float radius, int sides);
   virtual ~CCircle();

   virtual void Instantiate() override;
   virtual void Draw() override;

protected:
   float x0; 
   float y0; 
   float radius; 
   int sides;
};

class CCircleLine : public IShape
{
public:
   CCircleLine();
   CCircleLine(float x0, float y0, float radius, int sides);
   virtual ~CCircleLine();

   virtual void Instantiate() override;
   virtual void Draw() override;

protected:
   float mx0, my0;
   float mradius, msides;
}; 

class CFanLine : public IShape
{
public:
   CFanLine();
   CFanLine(float x0, float y0, float radius, int sides, float start, float stop);
   virtual ~CFanLine();

   virtual void Instantiate() override;
   virtual void Draw() override;

protected:
   float mx0, my0; 
   float mradius;
   int msides;
   float mstart, mstop;
};

class CFan : public IShape
{
public:
   CFan();
   CFan(float x0, float y0, float radius, int sides, float start, float stop);
   virtual ~CFan();

   virtual void Instantiate() override;
   virtual void Draw() override;

protected:
   float mx0, my0; 
   float mradius; 
   int msides; 
   float mstart; 
   float mstop;
};

class CRoundRectangle : public IShape
{
public:
   CRoundRectangle();
   CRoundRectangle(float x0, float y0, float x1, float y1, float width);
   virtual ~CRoundRectangle();

   void Instantiate();
   virtual void Draw();

protected:
   CLine *pLines[4];
   CFan *pFans[4];

   float mx0, my0;
   float mx1, my1; 
   float mwidth;
};

