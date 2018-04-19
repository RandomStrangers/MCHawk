#ifndef MAP_H_
#define MAP_H_

#define calcMapOffset(x, y, z, xSize, zSize) ((y * zSize + z) * xSize + x)

#include <stdint.h>

#include <string>

#include "Position.hpp"

class Map {
public:
	Map();

	~Map();

	void SetDimensions(short x, short y, short z);

	uint8_t* GetBuffer() { return m_buffer; }
	size_t GetBufferSize() { return m_bufferSize; }
	short GetXSize() { return m_x; }
	short GetYSize() { return m_y; }
	short GetZSize() { return m_z; }

	void GenerateFlatMap(short x, short y, short z);

	void LoadFromFile(std::string filename);

	void SaveToFile(std::string filename);
	void SaveToFile() { SaveToFile(m_filename); }

	bool SetBlock(short x, short y, short z, int8_t type);
	int8_t GetBlockType(short x, short y, short z);

	void CompressBuffer(uint8_t** outCompBuffer, size_t* outCompSize);

private:
	uint8_t *m_buffer;
	size_t m_bufferSize;

	std::string m_filename;

	short m_x, m_y, m_z; // Size
};

#endif // MAP_H_
