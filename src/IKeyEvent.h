#ifndef __IKEYEVENT_H
#define __IKEYEVENT_H

class IKeyEvent 
{
public:
  virtual void onKeyPressEvent(int key, int state);
  virtual void onKeyReleaseEvent(int key, int state);
};

#endif