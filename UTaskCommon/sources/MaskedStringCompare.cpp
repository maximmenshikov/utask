#include "stdafx.h"

wchar_t * wcsstrn (const wchar_t * wcs1, const wchar_t * wcs2, size_t numberOfChars) {
	wchar_t *cp = (wchar_t *) wcs1;
	wchar_t *s1, *s2;

	if (!*wcs2)
	    return((wchar_t *)wcs1);
	while (*cp) {
		size_t currentNum = 0;
		s1 = cp;
		s2 = (wchar_t *) wcs2;
		while ( *s1 && *s2 && !(*s1 - *s2) && currentNum < numberOfChars )
			s1++, s2++, currentNum++;
	
		if (currentNum == numberOfChars)
			return(cp);
		cp++;
	}
	return(NULL);
}

BOOL MaskedStringCompare(const wchar_t *text, const wchar_t *mask)
{
	DWORD result = FALSE;
	__try
	{
		if (text == NULL || mask == NULL)
			return FALSE;

		int textLength = wcslen(text);
		int maskLength = wcslen(mask);

		if (maskLength > textLength || textLength < 3 || maskLength < 3)
			return FALSE;

		BOOL leftMask = FALSE, rightMask = FALSE;

		if (mask[0] == L'*')
			leftMask = TRUE;
		if (mask[maskLength - 1] == L'*')
			rightMask = TRUE;

		if (leftMask == TRUE && rightMask == FALSE)
			result =  wcsncmp(&text[textLength - maskLength + 1], mask + 1, maskLength - 1) == 0 ? TRUE : FALSE;
		else if (leftMask == TRUE && rightMask == TRUE)
			result = wcsstrn(text , mask + 1, maskLength - 2) ? TRUE : FALSE;
		else if (leftMask == FALSE && rightMask == TRUE)
			result = wcsncmp(text, mask, maskLength - 1) == 0 ? TRUE : FALSE;
		else 
			result = wcscmp(text, mask) == 0 ? TRUE : FALSE;
	}
	__except (GetExceptionCode())
	{
	}
	return result;
};
