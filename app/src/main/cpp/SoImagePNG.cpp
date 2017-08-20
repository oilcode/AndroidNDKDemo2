//------------------------------------------------------------
#include "SoImagePNG.h"
#include <stdlib.h>
#include "SoImageDefine.h"
#include "SoFileHelp.h"
//------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
#include "../third_party/png/png.h"
#elif (SoTargetPlatform == SoPlatform_Android)
#include "../thirdparty/02_png/png.h"
#endif
//------------------------------------------------------------
struct tImageSource
{
    const unsigned char* data;
    int size;
    int offset;
};
//------------------------------------------------------------
void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
    tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);
    int readLen = (int)length;
    if (isource->offset + readLen <= isource->size)
    {
        memcpy(data, isource->data+isource->offset, readLen);
        isource->offset += readLen;
    }
    else
    {
        png_error(png_ptr, "pngReaderCallback failed");
    }
}
//------------------------------------------------------------
bool SoImagePNG::LoadFromFile(const char* pszFileName, SoImageFileInfo* pImageInfo)
{
    SoFile* pFile = SoFileHelp::CreateFile(pszFileName, "rb");
    if (pFile->IsValid() == false)
    {
        return false;
    }

    const unsigned char* fileData = pFile->GetFileData();
    const int fileDataLen = pFile->GetFileSize();
    bool br = LoadFromFileData(fileData, fileDataLen, pImageInfo);
    SoFileHelp::DeleteFile(pFile);
    return br;
}
//------------------------------------------------------------
bool SoImagePNG::LoadFromFileData(const unsigned char* pFileData, const int nFileSize, SoImageFileInfo* pImageInfo)
{
    // length of bytes to check if it is a valid png file
#define PNGSIGSIZE  8

    bool ret = false;
    png_structp png_ptr = 0;
    png_infop info_ptr = 0;

    do
    {
        // png header len is 8 bytes
        if (nFileSize < PNGSIGSIZE)
        {
            break;
        }

        // check the data is png or not
        png_byte header[PNGSIGSIZE] = {0};
        memcpy(header, pFileData, PNGSIGSIZE);
        if (png_sig_cmp(header, 0, PNGSIGSIZE) != 0)
        {
            break;
        }

        // init png_struct
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
        if (png_ptr == 0)
        {
            break;
        }

        // init png_info
        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == 0)
        {
            break;
        }

        if (setjmp(png_jmpbuf(png_ptr)))
        {
            break;
        }


        // set the read call back function
        tImageSource imageSource;
        imageSource.data = pFileData;
        imageSource.size = nFileSize;
        imageSource.offset = 0;
        png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

        // read png header info
        png_read_info(png_ptr, info_ptr);
        const int imageWidth = (int)png_get_image_width(png_ptr, info_ptr);
        const int imageHeight = (int)png_get_image_height(png_ptr, info_ptr);
        png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

        // force palette images to be expanded to 24-bit RGB
        // it may include alpha channel
        if (color_type == PNG_COLOR_TYPE_PALETTE)
        {
            png_set_palette_to_rgb(png_ptr);
        }
        // low-bit-depth grayscale images are to be expanded to 8 bits
        if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        {
            bit_depth = 8;
            png_set_expand_gray_1_2_4_to_8(png_ptr);
        }
        // expand any tRNS chunk data into a full alpha channel
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        {
            png_set_tRNS_to_alpha(png_ptr);
        }
        // reduce images with 16-bit samples to 8 bits
        if (bit_depth == 16)
        {
            png_set_strip_16(png_ptr);
        }
        // Expanded earlier for grayscale, now take care of palette and rgb
        if (bit_depth < 8)
        {
            png_set_packing(png_ptr);
        }
        // update info
        png_read_update_info(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        if (bit_depth != 8)
        {
            break;
        }
        if (color_type != PNG_COLOR_TYPE_RGB_ALPHA
            && color_type != PNG_COLOR_TYPE_RGB)
        {
            break;
        }


        // read png data
        const int rowbytes = (int)png_get_rowbytes(png_ptr, info_ptr);
        const int imageDataLen = rowbytes * imageHeight;
        unsigned char* imageData = (unsigned char*)malloc(imageDataLen);
        if (imageData == 0)
        {
            break;
        }

        png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * imageHeight);
        if (row_pointers == 0)
        {
            free(imageData);
            imageData = 0;
            break;
        }

        for (int i = 0; i < imageHeight; ++i)
        {
            row_pointers[i] = imageData + i * rowbytes;
        }
        png_read_image(png_ptr, row_pointers);
        png_read_end(png_ptr, 0);
        free(row_pointers);
        row_pointers = 0;

        pImageInfo->pData = imageData;
        pImageInfo->nDataSize = imageDataLen;
        pImageInfo->nWidth = imageWidth;
        pImageInfo->nHeight = imageHeight;
        pImageInfo->theFileType = SoImageFile_PNG;
        pImageInfo->theBitDepth = SoImageBitDepth_8;

        if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
        {
            pImageInfo->theColorType = SoImageColor_RGBA;
        }
        else if (color_type == PNG_COLOR_TYPE_RGB)
        {
            pImageInfo->theColorType = SoImageColor_RGB;
        }

        ret = true;

    } while (0);

    if (png_ptr)
    {
        png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
    }

    return ret;
}
//------------------------------------------------------------

