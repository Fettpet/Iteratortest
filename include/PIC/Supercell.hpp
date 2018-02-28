/**
 * @author Sebastian Hahn
 * @brief A PIConGPU like datastructure. The supercell contains some frames.
 * The frames are in a linked list. Each frame has the pointer nextFrame and 
 * previousFrame. Only the lastFrame frame is not full with particles. The supercell
 * stores the number of particles in the lastFrame frame. Each supercell has two 
 * pointers to frame: firstFrame and lastFrame.
 */
#pragma once
#include "Definitions/hdinline.hpp"
#include <iostream>
#include "Traits/Componenttype.hpp"
#include "Traits/IndexType.hpp"
#include "Traits/IsRandomAccessable.hpp"
#include "Traits/IsBidirectional.hpp"
#include "Traits/RangeType.hpp"
#include "Traits/HasConstantSize.hpp"
#include "Traits/NumberElements.hpp"

namespace hzdr
{
template<typename TFrame>
struct Supercell
{

    typedef TFrame frame_type;
    typedef TFrame FrameType;
    typedef TFrame ValueType;
    
    HDINLINE 
    Supercell():
        firstFrame(nullptr),
        lastFrame(nullptr)
    {}
    
    HDINLINE 
    Supercell(const Supercell & other)
    {
        firstFrame = other.firstFrame;
        lastFrame = other.lastFrame;
    }
    
    HDINLINE 
    Supercell( Supercell && other)
    {
        firstFrame = other.firstFrame;
        lastFrame = other.lastFrame;
        other.firstFrame = nullptr;
        other.lastFrame = nullptr;
    }
    
    HDINLINE
    ~Supercell() 
    {
        TFrame* cur = firstFrame;
        while(cur != nullptr)
        {
            TFrame* buffer = cur->nextFrame;
            delete cur;
            cur = buffer;
        }
    }
    
    HDINLINE
    Supercell& 
    operator=(const Supercell& other)
    {
        firstFrame = other.firstFrame;
        lastFrame = other.lastFrame;
        return *this;
    }
    
        
    HDINLINE
    Supercell& 
    operator=( Supercell&& other)
    {
        
        firstFrame = other.firstFrame;
        lastFrame = other.lastFrame;
        other.firstFrame = nullptr;
        other.lastFrame = nullptr;
        return *this;
    }
    
    /**
     * @param nbFrames: number of frames within the supercell,
     * @param nbParticle number of particles in the lastFrame frame
     */
    HDINLINE
    Supercell(uint32_t nbFrames, uint32_t nbParticles):
        firstFrame(new TFrame())
    {
        TFrame *curFrame;
        curFrame = firstFrame;
        for(uint32_t i=1; i<nbFrames; ++i)
        {
            curFrame->nextFrame = new TFrame();
            curFrame->nextFrame->previousFrame = curFrame;
            curFrame = curFrame->nextFrame;
        }
        curFrame->nbParticlesInFrame = nbParticles;
        lastFrame = curFrame;
        
        for(uint32_t i=nbParticles; i<TFrame::maxParticlesInFrame; ++i)
        {
            for(uint32_t dim=0; dim < TFrame::Dim; ++dim)
                lastFrame->particles[i].data[dim] = -1;
        }
        
    }
    
    TFrame *firstFrame = nullptr;
    TFrame *lastFrame = nullptr;
 //   uint32_t nbParticlesInLastFrame;
} ; // struct Supercell

// traits
namespace traits 
{
    
template<typename TFrame>
struct IndexType<hzdr::Supercell<TFrame> >
{
    typedef TFrame* type; 
} ;

template<
    typename TFrame, 
    typename SFIANE
>
struct RangeType<
    hzdr::Supercell<TFrame>, 
    SFIANE 
>
{
    typedef int type; 
} ;
    


template<
    typename TFrame>
struct HasConstantSize<Supercell<TFrame> >
{
    static const bool value = false;
} ;


template<
    typename TFrame>
struct ComponentType<Supercell<TFrame> >
{
    typedef TFrame type;
} ;

template<typename TFrame>
struct NumberElements<Supercell<TFrame> >
{  
    typedef Supercell<TFrame> Container;
    
    NumberElements() = default;
    NumberElements(NumberElements const &) = default;
    NumberElements(NumberElements &&) = default;
    
    HDINLINE
    int_fast32_t 
    operator()(Container* container)
    const
    {
        auto result = 0;
        auto tmp = container->firstFrame;
        while(tmp != nullptr)
        {
            tmp =tmp->nextFrame;
            ++result;
        }
        return result;
    }
    
} ; // NumberElements
} // namespace traits


template<typename TFrame>
HDINLINE
std::ostream& operator<<(std::ostream& out, const Supercell<TFrame>& Supercell)
{
    TFrame *curFrame;
    
    curFrame = Supercell.firstFrame;
    
    while(curFrame != nullptr)
    {
        out << *curFrame << std::endl;
        curFrame = curFrame->nextFrame;
    }
    
    return out;
}

} // namespace PIC