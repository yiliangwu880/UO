/*
发送到client的打包压缩等管理
*/
#pragma once
#include "log_def.h"
#include "Compression.h"
#include "Geometry.h"
#include "svr_util/include/str_util.h"
//class Packet
//{
//public:
//	void Serialize(std::string &str) {};
//};

#define byte uint8_t //不能用 std::byte,有些转换编译失败
using sbyte = int8_t;

class CityInfo
{
public:
	string City;
	string Building;
	int Description;
	Point3D m_Location;
	CityInfo()
	{}
	CityInfo(string city, string building, int description, int x, int y, int z)
		:m_Location(x, y, z)
	{
		City = city;
		Building = building;
		Description = description;
		//Map = m;
	}

	CityInfo(string city, string building, int x, int y, int z)
		: CityInfo(city, building, 0, x, y, z)
	{ }



	int X() { return m_Location.X; }
	int Y() { return m_Location.Y; }
	int Z() { return m_Location.Z; }
	void X(int val) { m_Location.X = val; }
	void Y(int val) { m_Location.Y = val; }
	void Z(int val) { m_Location.Z = val; }

	const Point3D &Location() { return m_Location; }
	//Map Map{ get; set; }
};

using ushort = uint16_t;
template<class T>
inline void Serial2Str(std::string &str, const T &v)
{
	str.append((const char *)&v, sizeof(v));
}

//适配UO C#写法
struct StreamAdaptor : public std::string
{
public:
	inline void WriteByte(byte v)
	{
		Serial2Str(*this, v);
	}
	void Write(const char* buffer, int offset, int size)
	{
		append(buffer + offset, size);
	}
	const std::string &GetBuffer() { return *this; };
	size_t Length() { return length(); }

};
class PacketWriter
{

public:
	StreamAdaptor m_Stream;
private:
	int m_Capacity;//m_Stream长度

public:
	PacketWriter()
		: PacketWriter(32)
	{ }

	PacketWriter(int capacity)
	{
		//	m_Stream.resize(capacity);
		m_Capacity = capacity;
	}
	//调试，强行设置包内容
	void DebugReset(CStr &str)
	{
		m_Stream.assign(str);
	}	

	void SetCapacity(int cap)
	{
		m_Capacity = cap;
	}

	StreamAdaptor &UnderlyingStream() { return m_Stream; }
	//string指定索引写入
	void WriteByOffset(size_t offset, ushort value)
	{
		if (m_Stream.length() < offset + sizeof(value))
		{
			L_ERROR("WriteByOffset overflow offset,size=%d %d", offset, m_Stream.length());
			return;
		}
		m_Stream[offset++] = (char)(value >> 8);
		m_Stream[offset] = (char)value;
	}
	void Write(bool value)
	{
		m_Stream.WriteByte((byte)(value ? 1 : 0));

	}

	void Write(byte value)
	{
		m_Stream.WriteByte(value);
	}

	void Write(char value)
	{
		m_Stream.WriteByte((byte)value);
	}

	void Write(short value)
	{
		m_Stream.WriteByte((byte)(value >> 8));
		m_Stream.WriteByte((byte)value);

	}

	void Write(ushort value)
	{
		m_Stream.WriteByte((byte)(value >> 8));
		m_Stream.WriteByte((byte)value);
	}


	void Write(int value)
	{
		m_Stream.WriteByte((byte)(value >> 24));
		m_Stream.WriteByte((byte)(value >> 16));
		m_Stream.WriteByte((byte)(value >> 8));
		m_Stream.WriteByte((byte)value);
	}


	void Write(uint value)
	{
		m_Stream.WriteByte((byte)(value >> 24));
		m_Stream.WriteByte((byte)(value >> 16));
		m_Stream.WriteByte((byte)(value >> 8));
		m_Stream.WriteByte((byte)value);
	}


	void Write(const char* buffer, int offset, int size)
	{
		m_Stream.Write(buffer, offset, size);
	}


	void WriteAsciiFixed(const std::string &value, int size)
	{

		if ((int)value.length() >= size)
		{
			m_Stream.append(value.c_str(), size);
		}
		else
		{
			std::string t = value;
			t.resize(size);
			m_Stream.append(t);
		}
#if 0
		if (value == null)
		{
			L_ERROR("Network: Attempted to WriteAsciiFixed() with null value");
			value = String.Empty;
		}

		int length = value.Length;

		m_Stream.SetLength(m_Stream.Length + size);

		if (length >= size)
		{
			m_Stream.Position += Encoding.ASCII.GetBytes(value, 0, size, m_Stream.GetBuffer(), (int)m_Stream.Position);
		}
		else
		{
			Encoding.ASCII.GetBytes(value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
			m_Stream.Position += size;
		}
#endif		

	}


	void WriteAsciiNull(const std::string &value)
	{
		L_ERROR("unfinished");
#if 0
		if (value == null)
		{
			Console.WriteLine("Network: Attempted to WriteAsciiNull() with null value");
			value = String.Empty;
		}

		int length = value.Length;

		m_Stream.SetLength(m_Stream.Length + length + 1);

		Encoding.ASCII.GetBytes(value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
		m_Stream.Position += length + 1;

#endif
	}


	void WriteLittleUniNull(const std::string &value)
	{
		L_ERROR("unfinished");
#if 0
		if (value == null)
		{
			Console.WriteLine("Network: Attempted to WriteLittleUniNull() with null value");
			value = String.Empty;
		}

		int length = value.Length;

		m_Stream.SetLength(m_Stream.Length + ((length + 1) * 2));

		m_Stream.Position += Encoding.Unicode.GetBytes(value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
		m_Stream.Position += 2;


#endif
	}


	void WriteLittleUniFixed(const std::string &value, int size)
	{
		L_ERROR("unfinished");
#if 0
		if (value == null)
		{
			Console.WriteLine("Network: Attempted to WriteLittleUniFixed() with null value");
			value = String.Empty;
		}

		size *= 2;

		int length = value.Length;

		m_Stream.SetLength(m_Stream.Length + size);

		if ((length * 2) >= size)
		{
			m_Stream.Position += Encoding.Unicode.GetBytes(value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
		}
		else
		{
			Encoding.Unicode.GetBytes(value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
			m_Stream.Position += size;
		}


#endif
	}

	void WriteBigUniNull(const std::string &value)
	{
		L_ERROR("unfinished");
#if 0
		if (value == null)
		{
			Console.WriteLine("Network: Attempted to WriteBigUniNull() with null value");
			value = String.Empty;
		}

		int length = value.Length;

		m_Stream.SetLength(m_Stream.Length + ((length + 1) * 2));

		m_Stream.Position += Encoding.BigEndianUnicode.GetBytes(
			value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
		m_Stream.Position += 2;

#endif
	}


	void WriteBigUniFixed(const std::string &value, int size)
	{
		L_ERROR("unfinished");
#if 0
		if (value == null)
		{
			Console.WriteLine("Network: Attempted to WriteBigUniFixed() with null value");
			value = String.Empty;
		}

		size *= 2;

		int length = value.Length;

		m_Stream.SetLength(m_Stream.Length + size);

		if ((length * 2) >= size)
		{
			m_Stream.Position += Encoding.BigEndianUnicode.GetBytes(
				value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
		}
		else
		{
			Encoding.BigEndianUnicode.GetBytes(value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
			m_Stream.Position += size;
		}


#endif
	}


	void Fill()
	{
		Fill((int)(m_Capacity - m_Stream.length()));
	}

	void Fill(int length)
	{
		if (length > 0)
		{
			m_Stream.append(length, char());
		}
	}


	long Length() const { return m_Stream.length(); }


	//long Position{ get { return m_Stream.Position; } set { m_Stream.Position = value; } }

};

struct PacketState
{
	static const int Inactive = 0x00;
	static const int Static = 0x01;
	static const int Acquired = 0x02;
	static const int Accessed = 0x04;
	static const int Buffered = 0x08;
	static const int Warned = 0x10;
};

//发送客户端网络包基类
class Packet
{
protected:
	int m_PacketID = 0;
	int m_Length = 0;//固定长度的消息 长度。 0 表示可变长度
	int m_State = 0; //PacketState mask
public:
	PacketWriter m_Stream;

public:
	int PacketID() { return m_PacketID; }

	int State() { return m_State; }

protected:
	Packet(int packetID)
	{
		m_PacketID = packetID;

	}

	Packet(int packetID, int length)
	{
		m_PacketID = packetID;
		m_Length = length;
		m_Stream.Write((byte)packetID);
	}

public:
	void EnsureCapacity(int length)
	{
		m_Stream.SetCapacity(length);
		m_Stream.Write((byte)m_PacketID);
		m_Stream.Write((short)0);//预留2字节，等写长度
	}

	PacketWriter &UnderlyingStream() { return m_Stream; }

	const int CompressorBufferSize = 0x10000;
	//数组内存池
	//static readonly BufferPool m_CompressorBuffers = new BufferPool("Compressor", 4, CompressorBufferSize);

	const int BufferSize = 4096;
	//数组内存池
	//static readonly BufferPool m_Buffers = new BufferPool("Compressed", 16, BufferSize);

	static Packet SetStatic(Packet p)
	{
		p.SetStatic();
		return p;
	}

	static Packet Acquire(Packet p)
	{
		p.Acquire();
		return p;
	}
#if 0

	static void Release(ref ObjectPropertyList p)
	{
		if (p != null)
		{
			p.Release();
		}

		p = null;
	}

	static void Release(ref RemoveItem p)
	{
		if (p != null)
		{
			p.Release();
		}

		p = null;
	}

	static void Release(ref RemoveMobile p)
	{
		if (p != null)
		{
			p.Release();
		}

		p = null;
	}

	static void Release(ref OPLInfo p)
	{
		if (p != null)
		{
			p.Release();
		}

		p = null;
	}

	static void Release(ref Packet p)
	{
		if (p != null)
		{
			p.Release();
		}

		p = null;
	}

	static void Release(Packet p)
	{
		if (p != null)
		{
			p.Release();
		}
	}
#endif

	void SetStatic()
	{
		m_State |= (PacketState::Static | PacketState::Acquired);
	}

	void Acquire()
	{
		m_State |= (int)PacketState::Acquired;
	}

	void OnSend()
	{
		////Core.Set(); C#发信号

		//lock(this)
		//{
		//	if ((m_State & (PacketState::Acquired | PacketState::Static)) == 0)
		//	{
		//		Free();
		//	}
		//}
	}

#if 0
	void Free()
	{
		if (m_CompiledBuffer == null)
		{
			return;
		}

		if ((m_State & PacketState::Buffered) != 0)
		{
			m_Buffers.ReleaseBuffer(m_CompiledBuffer);
		}

		m_State &= ~(PacketState::Static | PacketState::Acquired | PacketState::Buffered);

		m_CompiledBuffer = null;
	}

	void Release()
	{
		if ((m_State & PacketState::Acquired) != 0)
		{
			Free();
		}
	}
#endif

	std::string m_CompiledBuffer;
	int m_CompiledLength;

	const std::string &Compile(bool compress)
	{
		if (m_CompiledBuffer.empty())
		{
			if ((m_State & PacketState::Accessed) == 0)
			{
				m_State |= PacketState::Accessed;
			}
			else
			{
				if ((m_State & PacketState::Warned) == 0)
				{
					m_State |= PacketState::Warned;

					L_WARN("Redundant compile for packet %x, use Acquire() and Release()", m_PacketID);
				}
				L_WARN("Compile get empty string");
				m_CompiledBuffer.clear();
				return m_CompiledBuffer;
			}

			InternalCompile(compress);
		}

		return m_CompiledBuffer;
	}

	void InternalCompile(bool compress)
	{
		//加入可变长度， 参考 EnsureCapacity 函数，预留2字节写长度。 
		if (m_Length == 0)
		{
			long streamLen = m_Stream.Length();

			//m_Stream.Seek(1, SeekOrigin::Begin);//指针设置到偏移1位置
			//m_Stream.Write((ushort)streamLen);//覆盖写入索引 1，2位置
			m_Stream.WriteByOffset(1, (ushort)streamLen);
		}
		else if (m_Stream.Length() != m_Length)
		{
			int diff = (int)m_Stream.Length() - m_Length;

			L_ERROR("Packet: %x: Bad packet length! (%d %d bytes)", m_PacketID, diff >= 0 ? "+" : "", diff);
		}

		//	MemoryStream ms = m_Stream.UnderlyingStream();
		StreamAdaptor ms = m_Stream.UnderlyingStream();

		m_CompiledBuffer = ms.GetBuffer();//复制，待优化
		int length = (int)ms.Length();

		if (compress)
		{
			std::string buffer;

			int oldLen = length;
			Compression::Compress(m_CompiledBuffer, 0, length, buffer, length);

			if (length <= 0)
			{
				L_ERROR(
					"Warning: Compression buffer overflowed on packet %x length=%d)",
					m_PacketID,
					length);
			}
			else
			{
				m_CompiledLength = length;

				{//这代码块应该删掉，待分析
					if (length > BufferSize || (m_State & PacketState::Static) != 0)
					{
						//m_CompiledBuffer = new byte[length];
					}
					else
					{
						//lock(m_Buffers)
						//	m_CompiledBuffer = m_Buffers.AcquireBuffer();
						m_State |= PacketState::Buffered;
					}
				}

				//Buffer.BlockCopy(buffer, 0, m_CompiledBuffer, 0, length);
				m_CompiledBuffer = buffer; //待优化

				//lock(m_CompressorBuffers)
				//	m_CompressorBuffers.ReleaseBuffer(buffer);
			}
		}
		else if (length > 0)
		{
			//var old = m_CompiledBuffer;
			m_CompiledLength = length;

			{//待删除
				if (length > BufferSize || (m_State & PacketState::Static) != 0)
				{
					//m_CompiledBuffer = new byte[length];
				}
				else
				{
					//lock(m_Buffers)
					//	m_CompiledBuffer = m_Buffers.AcquireBuffer();
					m_State |= PacketState::Buffered;
				}
			}

			//Buffer.BlockCopy(old, 0, m_CompiledBuffer, 0, length);
		}

		//PacketWriter.ReleaseInstance(m_Stream);
		//m_Stream = null;
		ms.clear();
	}
};


#undef byte