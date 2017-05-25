#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

OPJ_SIZE_T stream_read_fn(void * p_buffer, OPJ_SIZE_T p_nb_bytes, void * p_user_data)
{
    if (NULL == p_buffer)
    {
        AfxMessageBox(_T("NULL"));
    }
    return p_nb_bytes;
}

bool ImageManager::loadImage(LPCSTR lpcszFilename)
{
    LPSTR pImage = const_cast<LPSTR>(lpcszFilename);
    opj_stream_t* pImageStream = opj_stream_create_default_file_stream( pImage, true);
    if( NULL == pImageStream )
    {
        AfxMessageBox(_T("gdsg"));
    }


    opj_stream_set_read_function(pImageStream, &stream_read_fn);

    return true;
}