#ifndef CONTEXT_H
#define CONTEXT_H

struct RangeContext {
    double xa, xb, ya, yb;

    RangeContext(double xa, double xb, double ya, double yb) : xa(xa), xb(xb),
                                                               ya(ya), yb(yb)
    { }
};

#endif // CONTEXT_H
