/*
	日志宏
*/
#pragma once
#include "log_def.h"
enum class SeekOrigin {
	Begin,
	Current,
	End
};

class PacketReader
{
	const char *m_Data;
	int m_Size;
	int m_Index;

public:
	//data 来源网络包。 格式：
	//[0] = packetId
	//[1,2] = 如果不是固定长度，这里存  ？
	//.... msg
	PacketReader(const char * data, int size, bool fixedSize)
	{
		m_Data = data;
		m_Size = size;
		m_Index = fixedSize ? 1 : 3;
	}

	const char * Buffer(){  return m_Data; }

	int Size(){  return m_Size; }

	int Seek(int offset, SeekOrigin origin)
	{
		switch (origin)
		{
		case SeekOrigin::Begin:
			m_Index = offset;
			break;
		case SeekOrigin::Current:
			m_Index += offset;
			break;
		case SeekOrigin::End:
			m_Index = m_Size - offset;
			break;
		}

		return m_Index;
	}

	int ReadInt32()
	{
		if ((m_Index + 4) > m_Size)
		{
			return 0;
		}
		int ret= (m_Data[m_Index + 0] << 24) | (m_Data[m_Index + 1] << 16) | (m_Data[m_Index + 2] << 8) | m_Data[m_Index + 3];
		m_Index += 4;
		return ret;
	}

	short ReadInt16()
	{
		if ((m_Index + 2) > m_Size)
		{
			return 0;
		}

		short ret = (short)((m_Data[m_Index + 0] << 8) | m_Data[m_Index + 1]);
		m_Index += 2;
		return ret;
	}

	uint8_t ReadByte()
	{
		if ((m_Index + 1) > m_Size)
		{
			return (uint8_t)0;
		}

		return (uint8_t)(m_Data[m_Index++]);
	}

	uint32 ReadUInt32()
	{
		if ((m_Index + 4) > m_Size)
		{
			return 0;
		}

		uint32 ret= (uint32)((m_Data[m_Index+0] << 24) | (m_Data[m_Index+1] << 16) | (m_Data[m_Index+2] << 8) | m_Data[m_Index+3]);
		m_Index += 4;
		return ret;
	}

	uint16 ReadUInt16()
	{
		if ((m_Index + 2) > m_Size)
		{
			return 0;
		}

		uint16 ret = (uint16)((m_Data[m_Index + 0] << 8) | m_Data[m_Index + 1]);
		m_Index += 2;
		return ret;
	}

	char ReadSByte()
	{
		if ((m_Index + 1) > m_Size)
		{
			return 0;
		}

		return (char)m_Data[m_Index++];
	}

	bool ReadBoolean()
	{
		if ((m_Index + 1) > m_Size)
		{
			return false;
		}

		return (m_Data[m_Index++] != 0);
	}

	string ReadUnicodeStringLE()
	{
		//string sb;//StringBuilder sb = new StringBuilder();
		string sb;
		int c;

		while ((m_Index + 1) < m_Size && (c = (m_Data[m_Index+0] | (m_Data[m_Index+1] << 8))) != 0)
		{
			sb.append(1, (char)c);
		}
		m_Index += 2;
		return sb;
	}

	string ReadUnicodeStringLESafe(int fixedLength)
	{
		int bound = m_Index + (fixedLength << 1);
		int end = bound;

		if (bound > m_Size)
		{
			bound = m_Size;
		}

		//string sb;//StringBuilder sb = new StringBuilder();
		string sb;
		int c;

		for (int i = 0; i < 10000 ; i++)
		{
			if ((m_Index + 1) < bound)
			{
				c = (m_Data[m_Index + 0] | (m_Data[m_Index + 1] << 8));
				m_Index += 2;
				if ( c != 0)
				{
					if (IsSafeChar(c))
					{
						sb.append(1, (char)c);
					}
					continue;
				}
			}
			if (i>=9999)
			{
				L_ERROR("endless loop");
			}
			break;
		}

		m_Index = end;

		return sb;
	}
	//为了去警告，代替 m_Index++
	int InsIdx(int &idx)
	{
		idx++;
		return idx-1;
	}
	
	string ReadUnicodeStringLESafe()
	{
		string sb;//string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while ((m_Index + 1) < m_Size && (c = (m_Data[InsIdx(m_Index)] | (m_Data[InsIdx(m_Index)] << 8))) != 0)
		{
			if (IsSafeChar(c))
			{
				sb.append(1, (char)c);
			}
		}

		return sb;
	}

	string ReadUnicodeStringSafe()
	{
		string sb;//string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while ((m_Index + 1) < m_Size && (c = ((m_Data[InsIdx(m_Index)] << 8) | m_Data[InsIdx(m_Index)])) != 0)
		{
			if (IsSafeChar(c))
			{
				sb.append(1, (char)c);
			}
		}

		return sb;
	}

	string ReadUnicodeString()
	{
		string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while ((m_Index + 1) < m_Size && (c = ((m_Data[InsIdx(m_Index)] << 8) | m_Data[InsIdx(m_Index)])) != 0)
		{
			sb.append(1, (char)c);
		}

		return sb;
	}

	bool IsSafeChar(int c)
	{
		return (c >= 0x20 && c < 0xFFFE);
	}

	string ReadUTF8StringSafe(int fixedLength)
	{
		if (m_Index >= m_Size)
		{
			m_Index += fixedLength;
			return string();
		}

		int bound = m_Index + fixedLength;
		//int end   = bound;

		if (bound > m_Size)
		{
			bound = m_Size;
		}

		int count = 0;
		int index = m_Index;
		int start = m_Index;

		while (index < bound && m_Data[index++] != 0)
		{
			++count;
		}

		index = 0;

		//var buffer = new byte[count];
		std::vector<byte> buffer(count, byte());
		int value = 0;

		while (m_Index < bound && (value = m_Data[m_Index++]) != 0)
		{
			buffer[index++] = (byte)value;
		}

		//string s = Utility.UTF8.GetString(buffer);
		string s((const char *)&buffer[0], buffer.size());
		L_ERROR("unfinished"); //Utility.UTF8.GetString(buffer); 未实现

		bool isSafe = true;

		for (int i = 0; isSafe && i < (int)s.length(); ++i)
		{
			isSafe = IsSafeChar(s[i]);
		}

		m_Index = start + fixedLength;

		if (isSafe)
		{
			return s;
		}

		string sb; //StringBuilder sb = new StringBuilder(s.Length);

		for (int i = 0; i < (int)s.length(); ++i)
		{
			if (IsSafeChar(s[i]))
			{
				sb.append(1, s[i]);
			}
		}

		return sb;
	}

	string ReadUTF8StringSafe()
	{
		if (m_Index >= m_Size)
		{
			return string();
		}

		int count = 0;
		int index = m_Index;

		while (index < m_Size && m_Data[index++] != 0)
		{
			++count;
		}

		index = 0;

		//var buffer = new byte[count];
		std::vector<byte> buffer(count, byte());

		int value = 0;

		while (m_Index < m_Size && (value = m_Data[m_Index++]) != 0)
		{
			buffer[index++] = (byte)value;
		}

		//string s = Utility.UTF8.GetString(buffer);
		string s((const char *)&buffer[0], buffer.size());
		L_ERROR("unfinished"); //Utility.UTF8.GetString(buffer); 未实现

		bool isSafe = true;

		for (int i = 0; isSafe && i < (int)s.length(); ++i)
		{
			isSafe = IsSafeChar(s[i]);
		}

		if (isSafe)
		{
			return s;
		}

		string sb; //StringBuilder sb = new StringBuilder(s.Length);

		for (int i = 0; i < (int)s.length(); ++i)
		{
			if (IsSafeChar(s[i]))
			{
				sb.append(1, s[i]);
			}
		}

		return sb;
	}

	string ReadUTF8String()
	{
		if (m_Index >= m_Size)
		{
			return string();
		}

		int count = 0;
		int index = m_Index;

		while (index < m_Size && m_Data[index++] != 0)
		{
			++count;
		}

		index = 0;

		//var buffer = new byte[count];
		std::vector<byte> buffer(count, byte());
		int value = 0;

		while (m_Index < m_Size && (value = m_Data[m_Index++]) != 0)
		{
			buffer[index++] = (byte)value;
		}

		//return Utility.UTF8.GetString(buffer);
		string s((const char *)&buffer[0], buffer.size());
		L_ERROR("unfinished"); //Utility.UTF8.GetString(buffer); 未实现
		return s;
	}

	string ReadString()
	{
		string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while (m_Index < m_Size && (c = m_Data[m_Index++]) != 0)
		{
			sb.append(1, (char)c);
		}

		return sb;
	}

	string ReadStringSafe()
	{
		string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while (m_Index < m_Size && (c = m_Data[m_Index++]) != 0)
		{
			if (IsSafeChar(c))
			{
				sb.append(1, (char)c);
			}
		}

		return sb;
	}

	string ReadUnicodeStringSafe(int fixedLength)
	{
		int bound = m_Index + (fixedLength << 1);
		int end = bound;

		if (bound > m_Size)
		{
			bound = m_Size;
		}

		string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while ((m_Index + 1) < bound && (c = ((m_Data[InsIdx(m_Index)] << 8) | m_Data[InsIdx(m_Index)])) != 0)
		{
			if (IsSafeChar(c))
			{
				sb.append(1, (char)c);
			}
		}

		m_Index = end;

		return sb;
	}

	string ReadUnicodeString(int fixedLength)
	{
		int bound = m_Index + (fixedLength << 1);
		int end = bound;

		if (bound > m_Size)
		{
			bound = m_Size;
		}

		string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while ((m_Index + 1) < bound && (c = ((m_Data[InsIdx(m_Index)] << 8) | m_Data[InsIdx(m_Index)])) != 0)
		{
			sb.append(1, (char)c);
		}

		m_Index = end;

		return sb;
	}

	string ReadStringSafe(int fixedLength)
	{
		int bound = m_Index + fixedLength;
		int end = bound;

		if (bound > m_Size)
		{
			bound = m_Size;
		}

		string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while (m_Index < bound && (c = m_Data[m_Index++]) != 0)
		{
			if (IsSafeChar(c))
			{
				sb.append(1, (char)c);
			}
		}

		m_Index = end;

		return sb;
	}

	string ReadString(int fixedLength)
	{
		int bound = m_Index + fixedLength;
		int end = bound;

		if (bound > m_Size)
		{
			bound = m_Size;
		}

		string sb;//StringBuilder sb = new StringBuilder();

		int c;

		while (m_Index < bound && (c = m_Data[m_Index++]) != 0)
		{
			sb.append(1, (char)c);
		}

		m_Index = end;

		return sb;
	}
};