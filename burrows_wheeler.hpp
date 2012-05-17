#ifndef BURROWS_WHELLER_HPP
#define BURROWS_WHELLER_HPP

#include <vector>
#include <utility>
#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/adaptor/map.hpp>
//#include <boost/range/irange.hpp>

//template<typename BidirectionalRangeT> void burrows_wheeler(BidirectionalRangeT &);
//template<typename OutputIteratorT, ForwardRangeT> OutputIteratorT burrows_wheeler_copy(OutputIteratorT, const ForwardRangeT &);

template<typename VecType> void setSecondFromPrevious(VecType& vec, size_t index, typename VecType::value_type::first_type c)
{
   if(index == 0)
      vec.back().second = c;
   else
      vec[index - 1].second = c;
}

template<typename SequenceT> SequenceT burrows_wheeler_copy(const SequenceT& input)
{
   typedef typename SequenceT::value_type value_type;
   typedef std::pair<value_type, value_type> pair_type;
   typedef std::vector<pair_type> pair_vec;

   pair_vec working(input.size());

   auto indexed_range = input | boost::adaptors::indexed(0);
   for(auto iter = boost::begin(indexed_range),
         end = boost::end(indexed_range);
         iter != end;
         ++iter)
   {
      working[iter.index()].first = *iter;
      setSecondFromPrevious(working, iter.index(), *iter);
   }

   boost::range::sort(working, [](pair_type const& lhs, pair_type const& rhs) { return lhs.first < rhs.first; });

   auto secondRange = working | boost::adaptors::map_values;
   return SequenceT(boost::begin(secondRange), boost::end(secondRange));
}

#endif
