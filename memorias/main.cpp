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

/* 
 * Utilidad para convertir el tag, offset y la direccion cache
 * en la direccion fisica.
 */
int cache_fisica(int direccion, int n_dir, int n_offset, int tag)
{
	int result, i, acumulador;
	result = tag;
	i = 1;
	acumulador = 2;
	while(i<n_dir)
	{
		++i;
		acumulador = acumulador * 2;
	}
	result = (result * acumulador) + direccion;
	i = 1;
	acumulador = 2;
	while(i<n_offset)
	{
		++i;
		acumulador = acumulador * 2;
	}
	result = result * acumulador;
	return result;
}

typedef std::vector< std::vector< std::vector<int> > > tipo_mem;
typedef std::vector< std::vector<int> > tipo_vias;

/*
 * En las operaciones de lectura y escritura se retorna un vector con tres enteros,
 * donde el primer entero indica si hay un hit - 1 o un miss - 0,
 * el segundo entero indica si hay escritura en memoria principal,
 * el tercer entero es la direccion fisica donde escribir en memoria pricipal,
 * el cuarto entero en adelante es el dato a escribir en memoria principal (write-back).
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
		mem = tipo_mem (bloques/vias, tipo_vias (vias, std::vector<int> (3+bloque_size,0)));
		LFU_counter = tipo_vias (bloques/vias, std::vector<int> (vias,0));
	}

	std::vector<int> read_cache(int direccion, std::vector<int> dato)
	{
		std::vector<int> result (3+bloque_size, 0);
		int posicion, tag, offset, pos_reemplazo, menor;
		bool hit;
		posicion = (direccion/boffset) % bdir; 
		tag = direccion / (boffset + bdir);
		offset = direccion % boffset;
		pos_reemplazo = 0;
		menor = LFU_counter[posicion][0];
		hit = false;

		for (int i = 0; i < vias; ++i)
		{
			/* Para aplicar LFU mas adelante */
			if(menor > LFU_counter[posicion][i])
			{
				menor = LFU_counter[posicion][i];
				pos_reemplazo = i;
			}
			/* Esta en la cache y es valido? */
			if(mem[posicion][i][2] == tag && mem[posicion][i][0] == 1)
			{
				hit = true;
				result[0] = 1;
				
				LFU_counter[posicion][i] += 1; // Para politica LFU
				break;
			}
		}
		/* No lo encontro en cache? */
		if (!hit)
		{
			result[0] = 0;
			/* Es dirty? */
			if (mem[posicion][pos_reemplazo][1] == 1)
			{
				result[1] = 1;
				result[2] = cache_fisica(posicion, bdir, boffset, mem[posicion][pos_reemplazo][2]);
				for (int j = 3; j < result.size(); ++j)
				{
					result[j] = mem[posicion][pos_reemplazo][j];
				}
			}
			mem[posicion][pos_reemplazo][0] = 1;
			mem[posicion][pos_reemplazo][1] = 0;
			mem[posicion][pos_reemplazo][2] = tag;
			for (int j = 0; j < dato.size(); ++j)
			{
				mem[posicion][pos_reemplazo][j+3] = dato[j];
			}
		}
		return result;
	}

	std::vector<int> write_cache(int direccion, std::vector<int> dato, int escribir)
	{
		std::vector<int> result (3+bloque_size, 0);
		int posicion, tag, offset, pos_reemplazo, menor;
		bool hit;

		posicion = (direccion/boffset) % bdir; 
		tag = direccion / (boffset + bdir);
		offset = direccion % boffset;
		pos_reemplazo = 0;
		menor = LFU_counter[posicion][0];
		hit = false;

		for (int i = 0; i < vias; ++i)
		{
			/* Para aplicar LFU mas adelante */
			if(menor > LFU_counter[posicion][i])
			{
				menor = LFU_counter[posicion][i];
				pos_reemplazo = i;
			}
			/* Esta en la cache y es valido? */
			if(mem[posicion][i][2] == tag && mem[posicion][i][0] == 1)
			{
				hit = true;
				result[0] = 1; // Devolvemos el hit
				mem[posicion][i][1] = 1; // Dirty
				mem[posicion][i][3+offset] = escribir;

				LFU_counter[posicion][i] += 1; // Para politica LFU
				break;
			}
		}
		/* No lo encontro en cache? */
		if (!hit)
		{
			result[0] = 0;
			/* Es dirty? */
			if (mem[posicion][pos_reemplazo][1] == 1)
			{
				result[1] = 1;
				result[2] = cache_fisica(posicion, bdir, boffset, mem[posicion][pos_reemplazo][2]);
				for (int j = 3; j < result.size(); ++j)
				{
					result[j] = mem[posicion][pos_reemplazo][j];
				}
			}
			mem[posicion][pos_reemplazo][0] = 1;
			mem[posicion][pos_reemplazo][1] = 1; // Dirty
			mem[posicion][pos_reemplazo][2] = tag;
			for (int j = 0; j < dato.size(); ++j)
			{
				mem[posicion][pos_reemplazo][j+3] = dato[j];
			}
			mem[posicion][pos_reemplazo][3+offset] = escribir;
		}

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
