#include "sigslot.h"

void SigSlot::setValue( int v ) {
  if ( v != _val ) {
    _val = v;
    emit valueChanged(v);
  }
}

