#include <iostream>
#include <vector>

typedef std::vector< std::vector< std::vector<int> > > tipo_mem;
typedef std::vector< std::vector<int> > tipo_vias;

class cache
{
public:
	int vias,
		bloques,
		bloque_size;
	std::vector< std::vector< std::vector<int> > > mem;

	cache(a_vias, a_bloques, a_bloque_size)
	{
		vias = a_vias;
		bloques = a_bloques;
		bloque_size = a_bloque_size;
		mem = tipo_mem (bloques/vias, tipo_vias (vias, std::vector<int> (2+bloque_size,0)));
	}
	~cache();
};



int main(int argc, char const *argv[])
{
	int bloques,
		paginas,
		vias,
		accesos,
		bloque_size,
		pagina_size
		fallos_pagina,
		fallos_cache;



	std::cout << "test memorias" << std::endl;
	return 0;
}