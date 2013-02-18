#pragma once
#include "JSAPIAuto.h"

namespace JS {
    
class File : public FB::JSAPIAuto
{
public:
    File()
    {
        registerMethod("tag", make_method(this, &File::tag));
    }
    
    virtual ~File() {};
    
    int tag() const;
};
    
}
