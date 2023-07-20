#include "VisualWWText.h"
#include "FontLibrary.h"
#include "Screen.h"
#include "Tokenize.h"
#include "VisualText.h"
#include "Widget.h"

#include "Log.h"

namespace BaxGUI
{
   VisualWWText::VisualWWText(Widget* pParent) : IVisual(pParent) {}
   VisualWWText::~VisualWWText()
   {
      // Free the renders
      while (mRenders.begin() != mRenders.end())
      {
         delete *mRenders.begin();
         mRenders.erase(mRenders.begin());
      }
   }
   // *** Derived classes must provide pure virtual methods
   bool VisualWWText::Instantiate(bool bActivate)
   {
      if (bActivate)
      {
         float hspace = (float)(FontLibrary::instance().CharWidth(mFontName.c_str(), 32)) /
            (float)(mpParent->GetParent()->LogicalWidth()) * 2.0f;
         float vspace = 1.0f / (float)(mpParent->GetParent()->LogicalHeight());

         // create renders of all the tokens
         ScreenRect r(mScreen.x, mScreen.y, 0, 0);
         std::list<std::string>::iterator it = mTokens.begin();
         while (it != mTokens.end())
         {
            VisualText* pText =
               VisualText::createText(mpParent, r, mColor, mFontName.c_str(), (*it).c_str(), true);
            pText->Instantiate(true);
            // Get the actual position of the text for testing and for next token
            r = pText->Screen();
            // if new text is outside of bounds, reset the location to the next line
            float right = mScreen.x + mScreen.w;
            if ((r.x >= right) || ((r.x + r.w) > right))
            {
               r.x = mScreen.x;
               r.y -= r.h + vspace;  // -y is down on the screen
               pText->Resize(r);
            }
            // always advance
            r.x += r.w + hspace;

            mRenders.push_back(pText);
            ++it;
         }
      }
      else
      {
         // Free the renders
         while (mRenders.begin() != mRenders.end())
         {
            delete *mRenders.begin();
            mRenders.erase(mRenders.begin());
         }
      }
      return true;
   }

   void VisualWWText::Update(float fTime)
   {
      // Update all the renders (in case we need to do something)
      std::list<VisualText*>::iterator it = mRenders.begin();
      while (it != mRenders.end())
      {
         (*it)->Update(fTime);
         ++it;
      }
   }

   void VisualWWText::Draw()
   {
      // Draw all the renders
      std::list<VisualText*>::iterator it = mRenders.begin();
      while (it != mRenders.end())
      {
         (*it)->Draw();
         ++it;
      }
   }

   void VisualWWText::Move(float x, float y)
   {
      float dx = x - mScreen.x;
      float dy = y - mScreen.y;
      // move all the renders
      std::list<VisualText*>::iterator it = mRenders.begin();
      while (it != mRenders.end())
      {
         (*it)->Move((*it)->Screen().x + dx, (*it)->Screen().y + dy);
         ++it;
      }

      IVisual::Move(x, y);
   }

   VisualWWText* VisualWWText::createWWText(Widget* pParent, const ScreenRect& r, const Color& c,
                                            const char* pFontSpec, const char* pContent, bool bTrim)
   {
      VisualWWText* pRet = new VisualWWText(pParent);
      pRet->Resize(r);
      pRet->mFontName = pFontSpec;
      pRet->mColor = c;
      pRet->mContent = pContent;

      int32_t count = Tokenize(pContent, pRet->mTokens);

      return pRet;
   }
}
