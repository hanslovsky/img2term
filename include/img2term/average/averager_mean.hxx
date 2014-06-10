#pragma once

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/color/color_base.hxx"
#include "img2term/average/averager_base.hxx"

namespace img2term {


class AveragerMean : public AveragerBase
{

public:
virtual Color::VigraColor operator() ( const vigra::MultiArrayView<3, uint> patch ) const;
  
};


} /* namespace img2term */
