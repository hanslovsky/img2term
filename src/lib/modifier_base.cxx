
// stl
#include <string>
#include <memory>

// vigra
#include <vigra/multi_array.hxx>

// img2term
#include "img2term/modifier/modifier_base.hxx"


namespace img2term {

////
//// ModifierBase
////
ModifierBase::ModifierBase() {

}


ModifierBase::~ModifierBase() {

}


std::string ModifierBase::generate( const vigra::MultiArrayView<3, uint> /* patch */ ) const {
  return std::string( "" );
}


////
//// ModifierDecorator
////
ModifierDecorator::ModifierDecorator() :
    modifier_( new ModifierBase )
{

}


ModifierDecorator::~ModifierDecorator()
{

}


ModifierDecorator::ModifierDecorator( std::shared_ptr<ModifierBase> modifier ) :
    modifier_( modifier )
{

}


std::string ModifierDecorator::generate( const vigra::MultiArrayView<3, uint> patch ) const
{
  return modifier_->generate( patch );
}




} /* namespace img2term */
