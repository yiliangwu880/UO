#pragma once
#include "log_def.h"

struct Point3D;
struct Point2D
{
	int X = 0;
	int Y = 0;

	Point2D()
	{
	}
	Point2D(int x, int y)
	{
		X = x;
		Y = y;
	}

	Point2D(const Point3D &pos);
};
struct Point3D
{
	int X = 0;
	int Y = 0;
	int Z = 0;

	Point3D()
	{
	}

	Point3D(int x, int y, int z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	Point3D(Point2D p, int z)
		: Point3D(p.X, p.Y, z)
	{ }

};



inline bool operator ==(const Point3D &l, const Point3D &r)
{
	return l.X == r.X && l.Y == r.Y && l.Z == r.Z;
}

inline bool operator !=(const Point3D &l, const Point3D &r)
{
	return l.X != r.X || l.Y != r.Y || l.Z != r.Z;
}


inline bool operator ==(const Point2D &l, const Point2D &r)
{
	return l.X == r.X && l.Y == r.Y;
}

inline bool operator !=(const Point2D &l, const Point2D &r)
{
	return l.X != r.X || l.Y != r.Y;
}

inline bool operator >(const Point2D &l, const Point2D &r)
{
	return l.X > r.X && l.Y > r.Y;
}

inline bool operator >(const Point2D &l, const Point3D &r)
{
	return l.X > r.X && l.Y > r.Y;
}


inline bool operator <(const Point2D &l, const Point2D &r)
{
	return l.X < r.X && l.Y < r.Y;
}

inline bool operator <(const Point2D &l, const Point3D &r)
{
	return l.X < r.X && l.Y < r.Y;
}



inline bool operator >=(const Point2D &l, const Point2D &r)
{
	return l.X >= r.X && l.Y >= r.Y;
}

inline bool operator >=(const Point2D &l, const Point3D &r)
{
	return l.X >= r.X && l.Y >= r.Y;
}



inline bool operator <=(const Point2D &l, const Point3D &r)
{
	return l.X <= r.X && l.Y <= r.Y;
}

inline bool operator <=(const Point2D &l, const Point2D &r)
{
	return l.X <= r.X && l.Y <= r.Y;
}



#if 0


struct Rectangle2D
{
	private Point2D m_Start;
	private Point2D m_End;

	Rectangle2D(IPoint2D start, IPoint2D end)
	{
		m_Start = new Point2D(start);
		m_End = new Point2D(end);
	}

	Rectangle2D(int x, int y, int width, int height)
	{
		m_Start = new Point2D(x, y);
		m_End = new Point2D(x + width, y + height);
	}

	Rectangle2D(int width, int height)
	{
		m_Start = new Point2D(0, 0);
		m_End = new Point2D(width, height);
	}


	void Set(int x, int y, int width, int height)
	{
		m_Start = new Point2D(x, y);
		m_End = new Point2D(x + width, y + height);
	}

	inline Rectangle2D Parse(string value)
	{
		int start = value.IndexOf('(');
		int end = value.IndexOf(',', start + 1);

		string param1 = value.Substring(start + 1, end - (start + 1)).Trim();

		start = end;
		end = value.IndexOf(',', start + 1);

		string param2 = value.Substring(start + 1, end - (start + 1)).Trim();

		start = end;
		end = value.IndexOf(',', start + 1);

		string param3 = value.Substring(start + 1, end - (start + 1)).Trim();

		start = end;
		end = value.IndexOf(')', start + 1);

		string param4 = value.Substring(start + 1, end - (start + 1)).Trim();

		return new Rectangle2D(
			Convert.ToInt32(param1),
			Convert.ToInt32(param2),
			Convert.ToInt32(param3),
			Convert.ToInt32(param4));
	}

	[CommandProperty(AccessLevel.Counselor)]
	Point2D Start{ get { return m_Start; } set { m_Start = value; } }

		[CommandProperty(AccessLevel.Counselor)]
	Point2D End{ get { return m_End; } set { m_End = value; } }

		[CommandProperty(AccessLevel.Counselor)]
	int X{ get { return m_Start.m_X; } set { m_Start.m_X = value; } }

		[CommandProperty(AccessLevel.Counselor)]
	int Y{ get { return m_Start.m_Y; } set { m_Start.m_Y = value; } }

		[CommandProperty(AccessLevel.Counselor)]
	int Width{ get { return m_End.m_X - m_Start.m_X; } set { m_End.m_X = m_Start.m_X + value; } }

		[CommandProperty(AccessLevel.Counselor)]
	int Height{ get { return m_End.m_Y - m_Start.m_Y; } set { m_End.m_Y = m_Start.m_Y + value; } }

		void MakeHold(Rectangle2D r)
	{
		if (r.m_Start.m_X < m_Start.m_X)
		{
			m_Start.m_X = r.m_Start.m_X;
		}

		if (r.m_Start.m_Y < m_Start.m_Y)
		{
			m_Start.m_Y = r.m_Start.m_Y;
		}

		if (r.m_End.m_X > m_End.m_X)
		{
			m_End.m_X = r.m_End.m_X;
		}

		if (r.m_End.m_Y > m_End.m_Y)
		{
			m_End.m_Y = r.m_End.m_Y;
		}
	}

	bool Contains(Point3D p)
	{
		return (m_Start.m_X <= p.m_X && m_Start.m_Y <= p.m_Y && m_End.m_X > p.m_X && m_End.m_Y > p.m_Y);
		//return ( m_Start <= p && m_End > p );
	}

	bool Contains(Point2D p)
	{
		return (m_Start.m_X <= p.m_X && m_Start.m_Y <= p.m_Y && m_End.m_X > p.m_X && m_End.m_Y > p.m_Y);
		//return ( m_Start <= p && m_End > p );
	}

	bool Contains(IPoint2D p)
	{
		return (m_Start <= p && m_End > p);
	}

	override string ToString()
	{
		return String.Format("({0}, {1})+({2}, {3})", X, Y, Width, Height);
	}

	override int GetHashCode()
	{
		unchecked
		{
			var hash = 1 + Math.Abs(Start.X + Start.Y) + Math.Abs(End.X + End.Y);

			hash = (hash * 397) ^ Start.GetHashCode();
			hash = (hash * 397) ^ End.GetHashCode();

			return hash;
		}
	}
};

struct Rectangle3D
{
	private Point3D m_Start;
	private Point3D m_End;

	Rectangle3D(Point3D start, Point3D end)
	{
		m_Start = start;
		m_End = end;
	}

	Rectangle3D(int x, int y, int z, int width, int height, int depth)
	{
		m_Start = new Point3D(x, y, z);
		m_End = new Point3D(x + width, y + height, z + depth);
	}

	void Set(int x, int y, int z, int width, int height, int depth)
	{
		m_Start = new Point3D(x, y, z);
		m_End = new Point3D(x + width, y + height, z + depth);
	}

	inline Rectangle3D Parse(string value)
	{
		int start = value.IndexOf('(');
		int end = value.IndexOf(',', start + 1);

		string param1 = value.Substring(start + 1, end - (start + 1)).Trim();

		start = end;
		end = value.IndexOf(',', start + 1);

		string param2 = value.Substring(start + 1, end - (start + 1)).Trim();

		start = end;
		end = value.IndexOf(',', start + 1);

		string param3 = value.Substring(start + 1, end - (start + 1)).Trim();

		start = end;
		end = value.IndexOf(',', start + 1);

		string param4 = value.Substring(start + 1, end - (start + 1)).Trim();

		start = end;
		end = value.IndexOf(',', start + 1);

		string param5 = value.Substring(start + 1, end - (start + 1)).Trim();

		start = end;
		end = value.IndexOf(')', start + 1);

		string param6 = value.Substring(start + 1, end - (start + 1)).Trim();

		return new Rectangle3D(
			Convert.ToInt32(param1),
			Convert.ToInt32(param2),
			Convert.ToInt32(param3),
			Convert.ToInt32(param4),
			Convert.ToInt32(param5),
			Convert.ToInt32(param6));
	}

	[CommandProperty(AccessLevel.Counselor)]
	Point3D Start{ get { return m_Start; } set { m_Start = value; } }

		[CommandProperty(AccessLevel.Counselor)]
	Point3D End{ get { return m_End; } set { m_End = value; } }

		[CommandProperty(AccessLevel.Counselor)]
	int Width{ get { return m_End.X - m_Start.X; } }

		[CommandProperty(AccessLevel.Counselor)]
	int Height{ get { return m_End.Y - m_Start.Y; } }

		[CommandProperty(AccessLevel.Counselor)]
	int Depth{ get { return m_End.Z - m_Start.Z; } }

		bool Contains(Point3D p)
	{
		return (p.m_X >= m_Start.m_X) && (p.m_X < m_End.m_X) && (p.m_Y >= m_Start.m_Y) && (p.m_Y < m_End.m_Y) &&
			(p.m_Z >= m_Start.m_Z) && (p.m_Z < m_End.m_Z);
	}

	bool Contains(IPoint3D p)
	{
		return (p.X >= m_Start.m_X) && (p.X < m_End.m_X) && (p.Y >= m_Start.m_Y) && (p.Y < m_End.m_Y) && (p.Z >= m_Start.m_Z) &&
			(p.Z < m_End.m_Z);
	}

	override string ToString()
	{
		return String.Format("({0}, {1}, {2})+({3}, {4}, {5})", Start.X, Start.Y, Start.Z, Width, Height, Depth);
	}

	override int GetHashCode()
	{
		unchecked
		{
			var hash = 1 + Math.Abs(Start.X + Start.Y + Start.Z) + Math.Abs(End.X + End.Y + End.Z);

			hash = (hash * 397) ^ Start.GetHashCode();
			hash = (hash * 397) ^ End.GetHashCode();

			return hash;
		}
	}
};

#endif



