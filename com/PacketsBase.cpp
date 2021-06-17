#include "PacketsBase.h"

Encoding::Encoding()
{
	m_utf8_2_utf16be = iconv_open("UTF-16BE", "UTF-8");
	if ((iconv_t)(-1) == m_utf8_2_utf16be)
	{
		L_ERROR("iconv_open");
		return;
	}
	m_utf8_2_ascii = iconv_open("ASCII", "UTF-8");
	if ((iconv_t)(-1) == m_utf8_2_ascii)
	{
		L_ERROR("iconv_open");
		return;
	}
	m_utf8_2_utf16le = iconv_open("UTF-16LE", "UTF-8");
	if ((iconv_t)(-1) == m_utf8_2_utf16le)
	{
		L_ERROR("iconv_open");
		return;
	}
}

bool Encoding::BigEndianUnicode(const string &src, string &out)
{
	return Change(m_utf8_2_utf16be, src, out);
}
bool Encoding::ASCII(const string &src, string &out)
{
	return Change(m_utf8_2_ascii, src, out);
}
bool Encoding::Unicode(const string &src, string &out)
{
	return Change(m_utf8_2_utf16le, src, out);
}

bool Encoding::Change(iconv_t cd, const string &src, string &out)
{
	char *pStr = (char *)src.c_str();
	char *pDst = m_dstArray;
	size_t inbytesleft = src.length();
	size_t outbytesleft = ArrayLen(m_dstArray);


	{
		//作为入参
		//	第一个参数cd是转换句柄。
		//	第二个参数inbuf是输入字符串的地址的地址。
		//	第三个参数inbytesleft是输入字符串的长度。
		//	第四个参数outbuf是输出缓冲区的首地址
		//	第五个参数outbytesLeft 是输出缓冲区的长度。

		//作为出参
		//第一个参数cd是转换句柄。
		//第二个参数inbuf指向剩余字符串的地址
		//第三个参数inbytesleft是剩余字符串的长度。
		//第四个参数outbuf是输出缓冲区剩余空间的首地址
		//第五个参数outbytesLeft 是输出缓冲区剩余空间的长度。	}

	size_t r = iconv(cd, &pStr, &inbytesleft, &pDst, &outbytesleft);
	if (size_t(-1) == r)
	{
		L_ERROR("iconv");
		return false;
	}
	else if (0 != inbytesleft)
	{
		L_ERROR("have remain bytes no conv. %d", inbytesleft);
		return false;
	}
	size_t outlen = ArrayLen(m_dstArray) - outbytesleft;
	out.assign(m_dstArray, outlen);

	//{
	//	string hexSrc = StrUtil::BinaryToHex(src);
	//	string hexDst = StrUtil::BinaryToHex(out);
	//	L_INFO("\n%s \nto\n %s", hexSrc.c_str(), hexDst.c_str());
	//}
	return true;
}
