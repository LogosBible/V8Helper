
#include <CoreFoundation/CoreFoundation.h>

#include "MacUtil.h"
#include <iostream>
#include <algorithm>

#define ASSERT(x)

char16_t * utf32ToUtf16(const wchar_t * string, size_t length, size_t * convertedLength)
{
	// check if null
	if (string == NULL)
		return NULL;

	int nNumberInputBytes = length * sizeof(wchar_t);

	// Create a string for the input encoding
	CFStringRef cfstr = CFStringCreateWithBytesNoCopy(kCFAllocatorDefault, (const UInt8*)string, nNumberInputBytes, kCFStringEncodingUTF32LE, FALSE, kCFAllocatorNull);
	if (cfstr == NULL)
	{
		std::wcerr << "Error converting string " << string << " in " << __FILE__ << " at " << __LINE__ << std::endl;
		return NULL;
	}

	// Calculate number of bytes to copy
	CFIndex nBytesToCopy;
	CFRange inputRange = CFRangeMake(0, CFStringGetLength(cfstr));
	CFIndex nInputChars = CFStringGetBytes(cfstr, inputRange, kCFStringEncodingUTF16LE, 0, FALSE, NULL, 0, &nBytesToCopy);
	int nNumberOutputBytes = nBytesToCopy + sizeof(char16_t);

	if (length > 0)
	{
		// Only assert if we got input data to convert and the calculation of nBytesToCopy failed
		ASSERT(nInputChars > 0);
		if (nInputChars <= 0)
		{
			std::wcerr << "Error converting string " << string << " in " << __FILE__ << " at " << __LINE__ << std::endl;
			CFRelease(cfstr);
			return NULL;
		}
	}

	// allocate and convert to UTF-16
	char16_t * pszResult = (char16_t *)malloc(nNumberOutputBytes);
	if (pszResult != NULL)
	{
		// Convert the input string into the output buffer with output encoding
		CFIndex nBytesCopied;
		CFStringGetBytes(cfstr, inputRange, kCFStringEncodingUTF16LE, 0, FALSE, (UInt8*)pszResult, nNumberOutputBytes, &nBytesCopied);

		size_t utf16Length = nBytesCopied / sizeof(char16_t);
		// Put null at the end of the output
		pszResult[utf16Length] = 0;
		if (convertedLength != NULL)
			*convertedLength = utf16Length;
	}

	CFRelease(cfstr);
	return pszResult;
}


char16_t * utf32ToUtf16(const wchar_t * string)
{
	return utf32ToUtf16(string, wcslen(string), NULL);
}

stdext::ustring utf32ToUstring(const wchar_t *psz)
{
	char16_t *pszString = utf32ToUtf16(psz);
	stdext::ustring ustrResult;
	if (pszString != NULL)
	{
		ustrResult = pszString;
		free(pszString);
	}

	return ustrResult;
}

stdext::ustring wstringToUstring(const std::wstring & string)
{
	return utf32ToUstring(string.c_str());
}

size_t wcslen(const char16_t * string)
{
	// Need to manually calculate the length of the UTF16 input string since no functions for this sort of thing already exist
	size_t nLen = 0;
	while (string[nLen])
		nLen++;

	return nLen;
}

char16_t * wcsncpy(char16_t* dst, const char16_t* src, size_t n)
{
	size_t nLengthToCopy = std::min(wcslen(src), n);
	size_t nBytesToCopy = nLengthToCopy * sizeof(char16_t);
	size_t nRemainingLength = n - nLengthToCopy;
	std::memcpy(dst, src, nBytesToCopy);
	if (nRemainingLength != 0)
		memset(dst + nLengthToCopy, 0, nRemainingLength * sizeof(char16_t));
	return dst;
}

// safe_malloc: This macro calls malloc to allocate the specified number of
//  elements of the specified type, returning a properly cast pointer.
#define safe_malloc(Type, Count) \
static_cast<Type *>(malloc(static_cast<size_t>(Count) * sizeof(Type)))


// char16_t equivalent of strdup
char16_t * wcsdup(const char16_t * str)
{
	size_t nLength = wcslen(str);
	char16_t * pwszDup = safe_malloc(char16_t, nLength + 1);
	wcsncpy(pwszDup, str, nLength + 1);

	return pwszDup;
}