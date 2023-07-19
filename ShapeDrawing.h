#pragma once
#include <stdint.h>
class RenderPacket;

class IPrimitive
{
public:
   IPrimitive() = default;
   virtual ~IPrimitive() {}
   virtual void Instantiate() = 0;
   virtual void Draw() = 0;

   IPrimitive(const IPrimitive&) = delete;
   IPrimitive& operator=(const IPrimitive&) = delete;
protected:
   RenderPacket* mpRenderPacket = nullptr;

};

class CLine : public IPrimitive
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

class CCircle : public IPrimitive
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

class CCircleLine : public IPrimitive
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

class CFanLine : public IPrimitive
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

class CFan : public IPrimitive
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

class CRoundRectangle : public IPrimitive
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

