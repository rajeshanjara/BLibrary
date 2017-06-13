#pragma once

#include "common.h"
#include <boost/gil/gil_all.hpp>
#include "png.h"
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

typedef enum
{
    PNG, JPG
}IMAGE_e;

typedef enum
{
    ICON, THUMBNAIL
}IMAGE_TYPE_e;

using namespace boost::gil;

class imageutil
{
public:
    static imageutil& getInstance()
    {
        static imageutil obj;
        return obj;
    }
    bool compress(SIZE) {}
    static rgb8_image_t readJpeg(LPCSTR file) {
        try {
            std::vector<uint8_t> storage;
            using namespace boost::gil;
            rgb8_image_t img;
            jpeg_read_image(file, img);
            storage.reserve(img.width() * img.height() * num_channels<rgba8_image_t>());
            return img;
        }
        catch (std::exception e)
        {
            std::string error = e.what();
        }
    }
    static rgba8_image_t readPng( LPCSTR file ) {
        try {
            std::vector<uint8_t> storage;
            using namespace boost::gil;
            rgba8_image_t img;
            png_read_image(file, img);
            storage.reserve(img.width() * img.height() * num_channels<rgba8_image_t>());
            return img;

        }
        catch (std::exception e)
        {
            std::string error = e.what();
        }
    }

    static IMAGE_e getExtension(LPCSTR file)
    {
        if (file != NULL)
        {
            CString str(file);
            CString rstr = str.Right(3);
            if( rstr.CompareNoCase(_T("PNG")) == 0 )
            {
                return PNG;
            }
            else if(rstr.CompareNoCase(_T("JPG")) == 0)
            {
                return JPG;
            }
        }
    }

    static LPCTSTR getFileName(LPCSTR file)
    {
        if (file != NULL)
        {
            CString str(file);
            int nPos = str.ReverseFind('\\');
            CString rstr = str.Right(str.GetLength() - nPos - 1);
            return rstr;
        }
        return NULL;
    }
};

class imagetype
{
public:
    virtual SIZE getDimension() = 0;
    void SetImage(const rgb8_image_t& image)
    {
        m_JpgImageData = image;
    }

    void SetImage(const rgba8_image_t& image)
    {
        m_PngImageData = image;
    }


    void GetImage( rgb8_image_t& image)
    {
        image = m_JpgImageData;
    }

    void GetImage( rgba8_image_t& image)
    {
        image = m_PngImageData;
    }

private:
    rgb8_image_t m_JpgImageData;
    rgba8_image_t m_PngImageData;
};

template<class T>
class BLimage
{
public:
    BLimage() {}
    BLimage(LPCSTR lpszFilePath) : m_lpszFilePath(lpszFilePath), m_hBitmap(0){}
   /* ~BLimage() {
        DeleteObject(m_hBitmap);
        m_hBitmap = 0;
    }*/
    HBITMAP getbitmap() { return m_hBitmap; }
    SIZE getimagesize() { return m_ImageType.getDimension(); }
    bool CreateImage(IMAGE_e e)
    {
        SIZE size = m_ImageType.getDimension();
        m_Format = e;
        switch (e)
        {
            case PNG:
            {
                rgba8_image_t mkicon(size.cx, size.cy);
                rgba8_image_t img = imageutil::getInstance().readPng(m_lpszFilePath);
                //const boost::gil::rgba8_image_t::const_view_t view1 = boost::gil::const_view(img);
                resize_view(const_view(img), view(mkicon), bilinear_sampler());
                m_ImageType.SetImage(mkicon);
                //png_write_view("out-resize.png", const_view(mkicon));
                break;
            }
            case JPG:
            {
                rgb8_image_t mkicon(size.cx, size.cy);
                rgb8_image_t img = imageutil::getInstance().readJpeg(m_lpszFilePath);
                //const boost::gil::rgb8_image_t::const_view_t view1 = boost::gil::const_view(img);
                resize_view(const_view(img), view(mkicon), bilinear_sampler());
                m_ImageType.SetImage(mkicon);
                const boost::gil::rgb8_image_t::const_view_t view1 = const_view(mkicon);
                //jpeg_write_view("out-resize.jpg", const_view(mkicon));
                // Create bitmap, handle PNG
                const int nSize = size.cx * size.cy * 3;
                BYTE* pbyPixels = new BYTE[nSize];
                BYTE* ptr = pbyPixels;
                for (int i = 0; i < size.cy; ++i)
                {
                    rgb8c_view_t::x_iterator ite;
                    ite = const_view(mkicon).row_begin(i);

                    for (int j = 0; j < size.cx; ++j)
                    {
                        rgb8c_pixel_t pixel = ite[j];
                        byte r = (byte) pixel[0];
                        byte g = (byte)pixel[1];
                        byte b = (byte)pixel[2];
                        *ptr = b;
                        ptr++;
                        *ptr = g;
                        ptr++;
                        *ptr = r;
                        ptr++;
                    }
                }

                HBITMAP hBitmap = createbitmap(pbyPixels);
              //  if (NULL != hBitmap)
              //      DeleteObject(m_hBitmap);
                m_hBitmap = hBitmap;
                delete [] pbyPixels;
                break;
            }
        }

        return true;
    }

    HBITMAP createbitmap(BYTE* pbyPixels)
    {
        HDC dc = CreateCompatibleDC(NULL);
        BITMAPINFO i;
        ZeroMemory(&i.bmiHeader, sizeof(BITMAPINFOHEADER));
        SIZE size = m_ImageType.getDimension();
        i.bmiHeader.biWidth = size.cx;     // Set size you need
        i.bmiHeader.biHeight = -size.cy;    // Set size you need
        i.bmiHeader.biPlanes = 1;
        i.bmiHeader.biBitCount = 24; // Can be 8, 16, 32 bpp or 
                                     // other number
        i.bmiHeader.biSizeImage = 0;
        i.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        i.bmiHeader.biClrUsed = 0;
        i.bmiHeader.biClrImportant = 0;
        VOID *pvBits = 0; 
        HBITMAP hbmp = CreateDIBSection(dc,
            &i,
            DIB_RGB_COLORS,
            &pvBits,
            NULL,
            0);
 
        memcpy(pvBits, (VOID*)pbyPixels, size.cx*size.cy * 3);
        DeleteObject(dc);
        /*FILE* fp = fopen("file.dat", "wb");
        if (fp)
        {
            fwrite(pbyPixels, size.cx*size.cy * 3,1, fp);
            fclose(fp);
        }/**/
    return hbmp;
    }


private:
    T m_ImageType;
    IMAGE_e m_Format;
    LPCSTR m_lpszFilePath;
    HBITMAP m_hBitmap;
};

class icon : public imagetype
{
public:
    SIZE getDimension()
    {
        SIZE s;
        s.cx = 32;
        s.cy = 32;
        return s;
    }
};

class thumbnail : public imagetype
{
public:
    SIZE getDimension()
    {
        SIZE s;
        s.cx = 140;
        s.cy = 150;
        return s;
    }
};

class normal : public imagetype
{};

class ImageManager
{
public:
    static ImageManager& instance()
    {
        static ImageManager theobj;
        return theobj;
    }
    ~ImageManager();

    string RelocateImages(LPCSTR lpcszFilename)
    {
        TCHAR file[255] = { 0 };
        GetCurrentDirectory(255, file);
        CString csPath = file;
        csPath += _T("\\images\\");
        csPath += imageutil::getFileName(lpcszFilename);
        USES_CONVERSION;
        LPCTSTR lpSrc = A2W(lpcszFilename);
        // copy image
        Utils::copyfile(lpSrc, (LPCTSTR)csPath);
        string filename = W2A(csPath);
        return filename;
    }

    template<class T>
    bool loadImage(LPCSTR lpcszFilename, T& image_o)
    {
        IMAGE_e type = imageutil::getExtension(lpcszFilename);
        T img(lpcszFilename);
        bool status = img.CreateImage(type);
        image_o = img;
        return true;
    }

    SIZE getImageDimension(IMAGE_TYPE_e e)
    {
        SIZE size;
        switch (e)
        {
            case ICON:
            {
                BLimage<icon> image1;
                size = image1.getimagesize();
                break;
            }
        }
        return size;
    }

private:
    ImageManager();
};

