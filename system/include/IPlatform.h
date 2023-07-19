#ifndef IPLATFORM_H
#define IPLATFORM_H

#include <stdint.h>

//! @brief Pure virtual class to provide interface to platform adapters.
//! All platforms must provide all methods.
class IPlatform
{
  protected:
   IPlatform() {}
   virtual ~IPlatform() {}
  public:
   virtual bool ShouldExit() = 0;
   virtual void HandleEvents() = 0;
   virtual void FrameBegin() = 0;
   virtual void FrameEnd() = 0;
   virtual void Terminate() = 0;
   virtual bool Ready() = 0;
   virtual double CurrentTime() = 0;
   virtual uint32_t ScreenPixelWidth() = 0;
   virtual uint32_t ScreenPixelHeight() = 0;


   static IPlatform& instance(void);
};



#endif  // IPLATFORM_H
