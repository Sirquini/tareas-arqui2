#include "cachegui.h"
#include <QApplication>
#include <iostream>
#include <vector>

/* 
 * Utilidad para saber el numero minimo de bits para representar
 * n valores.
 */
int bits_para(int n)
{
    int i, acumulador;
	i = 1;
    acumulador = 2;
	while (acumulador < n)
	{
		++i;
		acumulador = acumulador * 2;
	}
	return i;
}


typedef std::vector< std::vector< std::vector<int> > > tipo_mem;
typedef std::vector< std::vector<int> > tipo_vias;

/*
 * En las operaciones de lectura y escritura se retorna un vector con tres enteros,
 * donde el primer entero indica si hay un hit - 1 o un miss - 0,
 * el segundo enteri indica si hay escritura en memoria principal,
 * el tercer entero es el dato a escribir en memoria principal (de haber uno).
 */
class cache
{
public:
	int vias,
		bloques,
		bloque_size,
		posiciones,
		boffset,
		bdir;
	tipo_mem mem;
	tipo_vias LFU_counter;


	cache(int a_vias, int a_bloques, int a_bloque_size)
	{
		vias = a_vias;
		bloques = a_bloques;
		bloque_size = a_bloque_size;
		posiciones = bloques/vias;
		boffset = bits_para(bloque_size);
		bdir = bits_para(posiciones);
		mem = tipo_mem (bloques/vias, tipo_vias (vias, std::vector<int> (2+bloque_size,0)));
		LFU_counter = tipo_vias (bloques/vias, std::vector<int> (vias,0));
	}

	std::vector<int> read_cache(int direccion)
	{
		std::vector<int> result (3, 0);
		return result;

	}

	std::vector<int> write_cache(int direccion, int dato)
	{
		std::vector<int> result (3, 0);
		return result;
	}

	~cache();
};

int main(int argc, char *argv[])
{
	int bloques,
		paginas,
		vias,
		accesos,
		bloque_size,
		pagina_size,
		fallos_pagina,
		fallos_cache;

    QApplication a(argc, argv);
    cachegui w;
    w.show();

    return a.exec();
}
