// stl
#include <cassert>

// img2term
#include "img2term/color/distance_l2_squared.hxx"

namespace img2term
{

double DistanceL2Squared::operator()( const Color::VigraColor& c1, const Color::VigraColor& c2 ) const
{

  assert( c1.shape()[0] == c2.shape()[0] );

  double dist = 0.;
  {
    auto it1 = c1.begin();
    auto it2 = c2.begin();

    for (; it1 != c1.end(); ++it1, ++it2 ) {
      dist += ( *it2 - *it1 ) * ( *it2 - *it1 );
    }
  }

  return dist;

}

}
