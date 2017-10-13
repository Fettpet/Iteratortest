#pragma once

/**
 * @author Sebastian Hahn t.hahn < at > hzdr.de
 * @brief We use this trait to check whether an iterators position is ahead an
 * other iterators position. This means it1 > it2. The trait need the operator().
 * It has four arguments:
 * 1. A pointer to the container of the first iterator,
 * 2. The index of the first iterator,
 * 3. A pointer to the container of the second iterator 
 * 4. The index of the second iterator
 * 
 * @return true, if the first iterator is ahead the second one, false otherwise
 *
 */
namespace hzdr
{
namespace traits
{
namespace accessor
{
namespace details
{
    
}
    
template<
    typename TContainer,
    typename TComponent,
    typename TIndex,
    typename TContainerCategory>
struct Ahead
{
    HDINLINE
    bool
    operator() (TContainer*, TIndex&, TContainer*, TIndex&);
    
    // this function is used to 
    HDINLINE void UNDEFINED(){};
};




} // namespace accessor
} // namespace traits
    
} // namespace hzdr
