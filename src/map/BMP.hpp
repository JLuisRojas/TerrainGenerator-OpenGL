# include <iostream>
# include <fstream>
# include <sstream>

//# pragma pack (push, 1)
struct BMPHeader
{
	std::uint16_t bfType;
	std::uint32_t bfSize;
	std::uint16_t bfReserved1;
	std::uint16_t bfReserved2;
	std::uint32_t bfOffBits;
	std::uint32_t biSize;
	std::int32_t  biWidth;
	std::int32_t  biHeight;
	std::uint16_t biPlanes;
	std::uint16_t biBitCount;
	std::uint32_t biCompression;
	std::uint32_t biSizeImage;
	std::int32_t  biXPelsPerMeter;
	std::int32_t  biYPelsPerMeter;
	std::uint32_t biClrUsed;
	std::uint32_t biClrImportant;
};

static_assert(sizeof(BMPHeader) == 54);
//# pragma pack (pop)

struct RGB
{
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;
	constexpr RGB() = default;
	explicit constexpr RGB(double _rgb) noexcept
		: r(_rgb), g(_rgb), b(_rgb) {}
	constexpr RGB(double _r, double _g, double _b) noexcept
		: r(_r), g(_g), b(_b) {}
};

class Image
{
private:

	std::vector<RGB> m_data;
	
	std::int32_t m_width = 0, m_height = 0;

	bool inBounds(std::int32_t y, std::int32_t x) const noexcept
	{
		return (0 <= y) && (y < m_height) && (0 <= x) && (x < m_width);
	}

	static constexpr std::uint8_t ToUint8(double x) noexcept
	{
		return x >= 1.0 ? 255 : x <= 0.0 ? 0 : static_cast<std::uint8_t>(x * 255.0 + 0.5);
	}

public:

	Image() = default;

	Image(std::int32_t width, std::int32_t height)
		: m_data(width * height)
		, m_width(width)
		, m_height(height) {}

	void set(std::int32_t x, std::int32_t y, const RGB& color)
	{
		if (!inBounds(y, x))
		{
			return;
		}

		m_data[y * m_width + x] = color;
	}

	int width() const
	{
		return m_width;
	}

	int height() const
	{
		return m_height;
	}

	bool saveBMP(const std::string& path)
	{
		const std::int32_t  rowSize = m_width * 3 + m_width % 4;
		const std::uint32_t bmpsize = rowSize * m_height;
		const BMPHeader header =
		{
			0x4d42,
			static_cast<std::uint32_t>(bmpsize + sizeof(BMPHeader)),
			0,
			0,
			sizeof(BMPHeader),
			40,
			m_width,
			m_height,
			1,
			24,
			0,
			bmpsize,
			0,
			0,
			0,
			0
		};

		if (std::ofstream ofs{ path, std::ios_base::binary })
		{
			ofs.write((const char*)&header, sizeof(header));

			std::vector<std::uint8_t> line(rowSize);

			for (std::int32_t y = m_height - 1; -1 < y; --y)
			{
				size_t pos = 0;

				for (std::int32_t x = 0; x < m_width; ++x)
				{
					const RGB& col = m_data[y * m_width + x];
					line[pos++] = ToUint8(col.b);
					line[pos++] = ToUint8(col.g);
					line[pos++] = ToUint8(col.r);
				}

				ofs.write((const char*)line.data(), line.size());
			}

			return true;
		}
		else
		{
			return false;
		}
	}
};
