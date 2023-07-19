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
