#pragma once

// stl
#include <string>
#include <utility>
#include <vector>

// img2term
#include "img2term/color/color_base.hxx"


namespace img2term
{

class ColorGrayScale : public Color
{
 public:
  typedef std::string AsciiColor;
  typedef std::pair<uint, AsciiColor> IndexedColor;
  typedef std::vector<IndexedColor> IndexedColorVector;

  static const IndexedColorVector default_colors;
  static const size_t max_index_value;
  static IndexedColorVector create_indexed_color_vector( const std::vector<AsciiColor>& colors );

  ColorGrayScale();
  ColorGrayScale( const IndexedColorVector& colors );

  virtual std::string to_string() const;
  virtual void operator() ( const VigraColor& color );

 private:
  const IndexedColorVector& colors_;
  int current_color_index_;
};

} /* namespace img2term */
