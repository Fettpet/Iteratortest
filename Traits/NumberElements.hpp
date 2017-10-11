/**
 * \struct NumberElements
 * @author Sebastian Hahn t.hahn@hzdr.de
 * @brief This is a helper class to get the number of elements within
 * a container. This helper class has one function, size(const containertype&), 
 * which determine the size of the container. If it is not possible, for example
 * an linked list, it return std::limits::<uint>::min()
 */

#pragma once
#include <limits>
#include <PIC/Frame.hpp>
#include <PIC/Particle.hpp>
#include <PIC/SupercellContainer.hpp>

namespace hzdr 
{
namespace traits
{
template<typename T>
struct NumberElements;

template<typename TFrame>
struct NumberElements<Supercell<TFrame> >
{
    typedef Supercell<TFrame> Container;
    
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
    
}; // NumberElements
  
template<typename Supercell>
struct NumberElements<hzdr::SupercellContainer<Supercell> >
{
    typedef hzdr::SupercellContainer<Supercell> SupercellContainer;
    
    HDINLINE
    int_fast32_t
    operator()( SupercellContainer* element)
    const
    {
        return element->getNbSupercells();
    }
};


template<typename TParticle, int_fast32_t nb>
struct NumberElements<hzdr::Frame<TParticle, nb> >
{
    typedef hzdr::Frame<TParticle, nb> Frame;
    

    
    HDINLINE
    int_fast32_t 
    operator()( Frame const * const f)
    const
    {
        return f->nbParticlesInFrame;    
    }
}; // struct NumberElements

template<typename TPos, int_fast32_t nb>
struct NumberElements<hzdr::Particle<TPos, nb> >
{
    typedef hzdr::Particle<TPos, nb> Particle;
    
    HDINLINE
    int_fast32_t 
    constexpr
    operator()(Particle* )
    const
    {
        return nb;    
    }
}; // struct NumberElements

    
} // namespace traits

}// namespace hzdr
