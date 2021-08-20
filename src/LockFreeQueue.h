//
// Created by Paul Walker on 8/23/21.
//

#ifndef AIRWINDOW_JUCE_TOY_LOCKFREEQUEUE_H
#define AIRWINDOW_JUCE_TOY_LOCKFREEQUEUE_H

#include <JuceHeader.h>

/*
 * A convenience wrapper on the juce::AbstractFifo lock free queue. See the docs for
 * juce::AbstractFifo for more
 */
template <typename T, int qSize = 4096> class LockFreeQueue
{
  public:
    LockFreeQueue() : af(qSize) {}
    bool push(const T &ad)
    {
        auto ret = false;
        int start1, size1, start2, size2;
        af.prepareToWrite(1, start1, size1, start2, size2);
        if (size1 > 0)
        {
            dq[start1] = ad;
            ret = true;
        }
        af.finishedWrite(size1 + size2);
        return ret;
    }
    bool pop(T &ad)
    {
        bool ret = false;
        int start1, size1, start2, size2;
        af.prepareToRead(1, start1, size1, start2, size2);
        if (size1 > 0)
        {
            ad = dq[start1];
            ret = true;
        }
        af.finishedRead(size1 + size2);
        return ret;
    }
    juce::AbstractFifo af;
    T dq[qSize];
};

#endif // AIRWINDOW_JUCE_TOY_LOCKFREEQUEUE_H
