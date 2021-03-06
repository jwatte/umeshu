//
//  Copyright (c) 2011-2013 Vladimir Chalupecky
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  IN THE SOFTWARE.

#ifndef UMESHU_IO_EPS_H
#define UMESHU_IO_EPS_H

#include "Postscript_ostream.h"

namespace umeshu {
namespace io {

template <typename Tria>
void write_eps( std::string const& filename, Tria const& tria )
{
  Postscript_ostream ps( filename, tria.bounding_box() );
  Point2 p1, p2, p3;

  ps.setgray( 0.8 );

  for ( typename Tria::Face_const_iterator iter = tria.faces_begin(); iter != tria.faces_end(); ++iter )
  {
    iter->vertices( p1, p2, p3 );
    ps.newpath().moveto( p1.x(), p1.y() ).lineto( p2.x(), p2.y() ).lineto( p3.x(), p3.y() ).fill();
  }

  ps.setgray( 0 );
  ps.newpath();

  for ( typename Tria::Edge_const_iterator iter = tria.edges_begin(); iter != tria.edges_end(); ++iter )
  {
    iter->vertices( p1, p2 );
    ps.moveto( p1.x(), p1.y() ).lineto( p2.x(), p2.y() );
  }

  ps.stroke();

  for ( typename Tria::Node_const_iterator iter = tria.nodes_begin(); iter != tria.nodes_end(); ++iter )
  {
    if ( iter->is_boundary() )
    {
      ps.setrgbcolor( 1, 0, 0 );
    }
    else
    {
      ps.setrgbcolor( 1, 1, 0 );
    }

    ps.newpath().dot( iter->position().x(), iter->position().y() ).fill();
  }
}

} // namespace io
} // namespace umeshu

#endif // UMESHU_IO_EPS_H
