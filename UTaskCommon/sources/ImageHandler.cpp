#include "stdafx.h"
#include <imaging.h>
#include <initguid.h>
#include <imgguids.h>

#include "..\headers\FileSystem.h"

IImagingFactory* m_pImageFactory;

// Initializing ImageFactory which is responsible for image loading
int ImageFactory_Initialize()
{
	if (m_pImageFactory == NULL)
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		if (SUCCEEDED(CoCreateInstance(CLSID_ImagingFactory, NULL, CLSCTX_INPROC_SERVER, 
			IID_IImagingFactory, (void **) & m_pImageFactory)))
			return 1;
	}
	return 0;
};

// Deinitializing ImageFactory
VOID ImageFactory_Deinitialize()
{
	if (m_pImageFactory != NULL)
		m_pImageFactory->Release();

	m_pImageFactory = NULL;
};

HBITMAP LoadTransparentImage(wchar_t *fileName)
{
	if (m_pImageFactory != NULL && IsFileExists(fileName) == TRUE)
	{
		IImage*			pImage = NULL;
		IBitmapImage*	pBitmapImage = NULL;
		ImageInfo		imageInfo; 
		BitmapData		bitmapData;

		m_pImageFactory->CreateImageFromFile(fileName, &pImage);
		m_pImageFactory->CreateBitmapFromImage(pImage, 0, 0, 
						PixelFormat32bppPARGB, InterpolationHintNearestNeighbor, 
						&pBitmapImage);
		pImage->GetImageInfo(&imageInfo);  
		RECT rect = {0, 0, imageInfo.Width, imageInfo.Height}; 

		pBitmapImage->LockBits(&rect, ImageLockModeRead, 
								PixelFormat32bppPARGB, &bitmapData);

		return CreateBitmap( imageInfo.Width, imageInfo.Height, 1, 
			GetPixelFormatSize(imageInfo.PixelFormat), bitmapData.Scan0);
	}
	return NULL;
};
