#pragma once

// stl
#include <string>
#include <utility>
#include <vector>

// img2term
#include "img2term/color/color_base.hxx"


namespace img2term
{

class ColorDistance;

class ColorRGB : public Color
{
 public:
  typedef std::string RGBColor;

  static const std::vector<uint> RGB_8_UINT;
  static const std::vector<uint> RGB_16_UINT;
  static const std::vector<uint> RGB_256_UINT;

  static const std::vector<VigraColor> RGB_8;
  static const std::vector<VigraColor> RGB_16;
  static const std::vector<VigraColor> RGB_256;

  static std::vector<VigraColor> generateVigraColor( const std::vector<uint>& uint_colors );

  ColorRGB() = delete;
  ColorRGB( std::shared_ptr<ColorDistance> distance, const std::vector<VigraColor>& colors );

  virtual std::string to_string() const;
  virtual void operator() ( const VigraColor& color );

 private:
  const std::shared_ptr<ColorDistance> distance_;
  const std::vector<VigraColor>& colors_;
  int current_color_index_;
};

} /* namespace img2term */
