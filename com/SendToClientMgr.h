/*
发送到client的打包压缩等管理
*/
#pragma once
#include "log_def.h"

//class Packet
//{
//public:
//	void Serialize(std::string &str) {};
//};


using ushort = uint16_t;

template<class T>
void Serial2Str(std::string &str, const T &v)
{
	str.append((const char *)&v, sizeof(v));
}

//适配UO C#写法
struct StreamAdaptor : std::string
{
	inline void WriteByte(byte v)
	{
		Serial2Str(*this, v);
	}
};
class PacketWriter
{
	
	StreamAdaptor m_Stream;

	int m_Capacity;

	PacketWriter()
		: PacketWriter(32)
	{ }

	PacketWriter(int capacity)
	{
		m_Stream.resize(capacity);
		m_Capacity = capacity;
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
		m_Buffer[0] = (byte)(value >> 8);
		m_Buffer[1] = (byte)value;

		m_Stream.Write(m_Buffer, 0, 2);
	}

	void Write(ushort value)
	{
		m_Buffer[0] = (byte)(value >> 8);
		m_Buffer[1] = (byte)value;

		m_Stream.Write(m_Buffer, 0, 2);
	}

	/// <summary>
	///     Writes a 4-byte signed integer value to the underlying stream.
	/// </summary>
	void Write(int value)
	{
		m_Buffer[0] = (byte)(value >> 24);
		m_Buffer[1] = (byte)(value >> 16);
		m_Buffer[2] = (byte)(value >> 8);
		m_Buffer[3] = (byte)value;

		m_Stream.Write(m_Buffer, 0, 4);
	}

	/// <summary>
	///     Writes a 4-byte unsigned integer value to the underlying stream.
	/// </summary>
	void Write(uint value)
	{
		m_Buffer[0] = (byte)(value >> 24);
		m_Buffer[1] = (byte)(value >> 16);
		m_Buffer[2] = (byte)(value >> 8);
		m_Buffer[3] = (byte)value;

		m_Stream.Write(m_Buffer, 0, 4);
	}

	/// <summary>
	///     Writes a sequence of bytes to the underlying stream
	/// </summary>
	void Write(byte[] buffer, int offset, int size)
	{
		m_Stream.Write(buffer, offset, size);
	}

	/// <summary>
	///     Writes a fixed-length ASCII-encoded string value to the underlying stream. To fit (size), the string content is either truncated or padded with null characters.
	/// </summary>
	void WriteAsciiFixed(string value, int size)
	{
		if (value == null)
		{
			Console.WriteLine("Network: Attempted to WriteAsciiFixed() with null value");
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

		/*byte[] buffer = Encoding.ASCII.GetBytes( value );

		if ( buffer.Length >= size )
		{
			m_Stream.Write( buffer, 0, size );
		}
		else
		{
			m_Stream.Write( buffer, 0, buffer.Length );
			Fill( size - buffer.Length );
		}*/
	}

	/// <summary>
	///     Writes a dynamic-length ASCII-encoded string value to the underlying stream, followed by a 1-byte null character.
	/// </summary>
	void WriteAsciiNull(string value)
	{
		if (value == null)
		{
			Console.WriteLine("Network: Attempted to WriteAsciiNull() with null value");
			value = String.Empty;
		}

		int length = value.Length;

		m_Stream.SetLength(m_Stream.Length + length + 1);

		Encoding.ASCII.GetBytes(value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
		m_Stream.Position += length + 1;

		/*byte[] buffer = Encoding.ASCII.GetBytes( value );

		m_Stream.Write( buffer, 0, buffer.Length );
		m_Stream.WriteByte( 0 );*/
	}

	/// <summary>
	///     Writes a dynamic-length little-endian unicode string value to the underlying stream, followed by a 2-byte null character.
	/// </summary>
	void WriteLittleUniNull(string value)
	{
		if (value == null)
		{
			Console.WriteLine("Network: Attempted to WriteLittleUniNull() with null value");
			value = String.Empty;
		}

		int length = value.Length;

		m_Stream.SetLength(m_Stream.Length + ((length + 1) * 2));

		m_Stream.Position += Encoding.Unicode.GetBytes(value, 0, length, m_Stream.GetBuffer(), (int)m_Stream.Position);
		m_Stream.Position += 2;

		/*byte[] buffer = Encoding.Unicode.GetBytes( value );

		m_Stream.Write( buffer, 0, buffer.Length );

		m_Buffer[0] = 0;
		m_Buffer[1] = 0;
		m_Stream.Write( m_Buffer, 0, 2 );*/
	}

	/// <summary>
	///     Writes a fixed-length little-endian unicode string value to the underlying stream. To fit (size), the string content is either truncated or padded with null characters.
	/// </summary>
	void WriteLittleUniFixed(string value, int size)
	{
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

		/*size *= 2;

		byte[] buffer = Encoding.Unicode.GetBytes( value );

		if ( buffer.Length >= size )
		{
			m_Stream.Write( buffer, 0, size );
		}
		else
		{
			m_Stream.Write( buffer, 0, buffer.Length );
			Fill( size - buffer.Length );
		}*/
	}

	/// <summary>
	///     Writes a dynamic-length big-endian unicode string value to the underlying stream, followed by a 2-byte null character.
	/// </summary>
	void WriteBigUniNull(string value)
	{
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

		/*byte[] buffer = Encoding.BigEndianUnicode.GetBytes( value );

		m_Stream.Write( buffer, 0, buffer.Length );

		m_Buffer[0] = 0;
		m_Buffer[1] = 0;
		m_Stream.Write( m_Buffer, 0, 2 );*/
	}

	/// <summary>
	///     Writes a fixed-length big-endian unicode string value to the underlying stream. To fit (size), the string content is either truncated or padded with null characters.
	/// </summary>
	void WriteBigUniFixed(string value, int size)
	{
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

		/*size *= 2;

		byte[] buffer = Encoding.BigEndianUnicode.GetBytes( value );

		if ( buffer.Length >= size )
		{
			m_Stream.Write( buffer, 0, size );
		}
		else
		{
			m_Stream.Write( buffer, 0, buffer.Length );
			Fill( size - buffer.Length );
		}*/
	}

	/// <summary>
	///     Fills the stream from the current position up to (capacity) with 0x00's
	/// </summary>
	void Fill()
	{
		Fill((int)(m_Capacity - m_Stream.Length));
	}

	/// <summary>
	///     Writes a number of 0x00 byte values to the underlying stream.
	/// </summary>
	void Fill(int length)
	{
		if (m_Stream.Position == m_Stream.Length)
		{
			m_Stream.SetLength(m_Stream.Length + length);
			m_Stream.Seek(0, SeekOrigin.End);
		}
		else
		{
			m_Stream.Write(new byte[length], 0, length);
		}
	}

	/// <summary>
	///     Gets the total stream length.
	/// </summary>
	long Length{ get { return m_Stream.Length; } }

		/// <summary>
		///     Gets or sets the current stream position.
		/// </summary>
	long Position{ get { return m_Stream.Position; } set { m_Stream.Position = value; } }

		/// <summary>
		///     The internal stream used by this PacketWriter instance.
		/// </summary>
	MemoryStream UnderlyingStream{ get { return m_Stream; } }

		/// <summary>
		///     Offsets the current position from an origin.
		/// </summary>
		long Seek(long offset, SeekOrigin origin)
	{
		return m_Stream.Seek(offset, origin);
	}

	/// <summary>
	///     Gets the entire stream content as a byte array.
	/// </summary>
	byte[] ToArray()
	{
		return m_Stream.ToArray();
	}
}

//发送客户端网络包基类
/*
class Packet
{
	protected PacketWriter m_Stream;

	readonly int m_PacketID;
	readonly int m_Length;//固定长度的消息 长度。 0 表示可变长度

	PacketState m_State;

	int PacketID{ get { return m_PacketID; } }

	PacketState State{ get { return m_State; } }

		protected Packet(int packetID)
	{
		m_PacketID = packetID;

		if (Core.Profiling)
		{
			PacketSendProfile prof = PacketSendProfile.Acquire(GetType());
			prof.Increment();
		}
	}

	protected Packet(int packetID, int length)
		: this(packetID, length, PacketWriter.CreateInstance(length))
	{ }

	protected Packet(int packetID, int length, PacketWriter stream)
	{
		m_PacketID = packetID;
		m_Length = length;

		m_Stream = stream;
		m_Stream.Write((byte)packetID);

		if (Core.Profiling)
		{
			PacketSendProfile prof = PacketSendProfile.Acquire(GetType());
			prof.Increment();
		}
	}

	void EnsureCapacity(int length)
	{
		m_Stream = PacketWriter.CreateInstance(length);// new PacketWriter( length );
		m_Stream.Write((byte)m_PacketID);
		m_Stream.Write((short)0);
	}

	PacketWriter UnderlyingStream{ get { return m_Stream; } }

	const int CompressorBufferSize = 0x10000;
	static readonly BufferPool m_CompressorBuffers = new BufferPool("Compressor", 4, CompressorBufferSize);

	const int BufferSize = 4096;
	static readonly BufferPool m_Buffers = new BufferPool("Compressed", 16, BufferSize);

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

	void SetStatic()
	{
		m_State |= PacketState.Static | PacketState.Acquired;
	}

	void Acquire()
	{
		m_State |= PacketState.Acquired;
	}

	void OnSend()
	{
		Core.Set();

		lock(this)
		{
			if ((m_State & (PacketState.Acquired | PacketState.Static)) == 0)
			{
				Free();
			}
		}
	}

	void Free()
	{
		if (m_CompiledBuffer == null)
		{
			return;
		}

		if ((m_State & PacketState.Buffered) != 0)
		{
			m_Buffers.ReleaseBuffer(m_CompiledBuffer);
		}

		m_State &= ~(PacketState.Static | PacketState.Acquired | PacketState.Buffered);

		m_CompiledBuffer = null;
	}

	void Release()
	{
		if ((m_State & PacketState.Acquired) != 0)
		{
			Free();
		}
	}

	byte[] m_CompiledBuffer;
	int m_CompiledLength;

	byte[] Compile(bool compress, out int length)
	{
		lock(this)
		{
			if (m_CompiledBuffer == null)
			{
				if ((m_State & PacketState.Accessed) == 0)
				{
					m_State |= PacketState.Accessed;
				}
				else
				{
					if ((m_State & PacketState.Warned) == 0)
					{
						m_State |= PacketState.Warned;

						try
						{
							using (StreamWriter op = new StreamWriter("net_opt.log", true))
							{
								op.WriteLine("Redundant compile for packet {0}, use Acquire() and Release()", GetType());
								op.WriteLine(new StackTrace());
							}
						}
						catch
						{ }
					}

					m_CompiledBuffer = new byte[0];
					m_CompiledLength = 0;

					length = m_CompiledLength;
					return m_CompiledBuffer;
				}

				InternalCompile(compress);
			}

			length = m_CompiledLength;
			return m_CompiledBuffer;
		}
	}

	void InternalCompile(bool compress)
	{
		if (m_Length == 0)
		{
			long streamLen = m_Stream.Length;

			m_Stream.Seek(1, SeekOrigin.Begin);
			m_Stream.Write((ushort)streamLen);
		}
		else if (m_Stream.Length != m_Length)
		{
			int diff = (int)m_Stream.Length - m_Length;

			Console.WriteLine("Packet: 0x{0:X2}: Bad packet length! ({1}{2} bytes)", m_PacketID, diff >= 0 ? "+" : "", diff);
		}

		MemoryStream ms = m_Stream.UnderlyingStream;

		m_CompiledBuffer = ms.GetBuffer();
		int length = (int)ms.Length;

		if (compress)
		{
			byte[] buffer;

			lock(m_CompressorBuffers)
				buffer = m_CompressorBuffers.AcquireBuffer();
			int oldLen = length;
			Compression.Compress(m_CompiledBuffer, 0, length, buffer, ref length);

			//if (compress)
			//{//会运行的，需要压缩
			//    Utility.PushColor(ConsoleColor.Red);
			//    Console.WriteLine("tmp log. Packet compress size {0}-> {1}", oldLen, length);
			//    Utility.PopColor();
			//}

			if (length <= 0)
			{
				Console.WriteLine(
					"Warning: Compression buffer overflowed on packet 0x{0:X2} ('{1}') (length={2})",
					m_PacketID,
					GetType().Name,
					length);
				using (StreamWriter op = new StreamWriter("compression_overflow.log", true))
				{
					op.WriteLine(
						"{0} Warning: Compression buffer overflowed on packet 0x{1:X2} ('{2}') (length={3})",
						DateTime.UtcNow,
						m_PacketID,
						GetType().Name,
						length);
					op.WriteLine(new StackTrace());
				}
			}
			else
			{
				m_CompiledLength = length;

				if (length > BufferSize || (m_State & PacketState.Static) != 0)
				{
					m_CompiledBuffer = new byte[length];
				}
				else
				{
					lock(m_Buffers)
						m_CompiledBuffer = m_Buffers.AcquireBuffer();
					m_State |= PacketState.Buffered;
				}

				Buffer.BlockCopy(buffer, 0, m_CompiledBuffer, 0, length);

				lock(m_CompressorBuffers)
					m_CompressorBuffers.ReleaseBuffer(buffer);
			}
		}
		else if (length > 0)
		{
			var old = m_CompiledBuffer;
			m_CompiledLength = length;

			if (length > BufferSize || (m_State & PacketState.Static) != 0)
			{
				m_CompiledBuffer = new byte[length];
			}
			else
			{
				lock(m_Buffers)
					m_CompiledBuffer = m_Buffers.AcquireBuffer();
				m_State |= PacketState.Buffered;
			}

			Buffer.BlockCopy(old, 0, m_CompiledBuffer, 0, length);
		}

		PacketWriter.ReleaseInstance(m_Stream);
		m_Stream = null;
	}
}

*/