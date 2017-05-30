// example.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/gil/gil_all.hpp>
#include "png.h"
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

using namespace boost::gil;

struct PixelInserter {
    std::vector<uint8_t>* storage;
    PixelInserter(std::vector<uint8_t>* s) : storage(s) {}
    void operator()(boost::gil::rgba8_pixel_t p) const {
        storage->push_back(boost::gil::at_c<0>(p));
        storage->push_back(boost::gil::at_c<1>(p));
        storage->push_back(boost::gil::at_c<2>(p));
    }
};

void main()
{

    std::vector<uint8_t> storage;
    {
        using namespace boost::gil;
        rgba8_image_t img;
        png_read_image("C:\\Users\\1012766\\Documents\\Visual Studio 2015\\Projects\\example\\example\\gil1.png", img);
        storage.reserve(img.width() * img.height() * num_channels<rgba8_image_t>());
        boost::gil::rgba8_image_t::const_view_t view1 = boost::gil::const_view(img);

        rgb8_image_t square100x100(300, 100);
        resize_view(const_view(img), view(square100x100), bilinear_sampler());
        png_write_view("out-resize.jpg", const_view(square100x100));

        for_each_pixel( view1, PixelInserter(&storage));
        boost::gil::rgba8_image_t::const_view_t view2;

    }
}

void x_gradient(const gray8c_view_t& src, const gray8s_view_t& dst) {
    assert(src.dimensions() == dst.dimensions());
     // compute the gradient
}