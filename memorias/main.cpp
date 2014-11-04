#include "cachegui.h"
#include <QApplication>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <random>
#include <fstream>
#include <string>

#define POS_DISCO 4096
#define POS_MEMORIA 1024
#define DIR_VIRUTALES 4096

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
 * Genera las potencias de 2 a la n>0
 * lento pero evita usar pow().
 */
int potencia(int n)
{
    int i, acumulador;
	i = 1;
    acumulador = 2;
	while (i < n)
	{
		++i;
		acumulador = acumulador * 2;
	}
	return acumulador;
}


/* 
 * Utilidad para convertir el tag, offset y la direccion cache
 * en la direccion fisica.
 */
int cache_fisica(int direccion, int n_dir, int n_offset, int tag)
{
	int result, i, acumulador;
	result = tag;
	result = (result * potencia(n_dir)) + direccion;
	result = result * potencia(n_offset);
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
		bdir,
		tag_pot,
		offset_pot,
		dir_pot;
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
		tag_pot = potencia(boffset + bdir);
		offset_pot = potencia(boffset);
		dir_pot = potencia(bdir);
	}

	std::vector<int> read_cache(int direccion, std::vector<int> dato)
	{
		std::vector<int> result (3+bloque_size, 0);
		int posicion, tag, offset, pos_reemplazo, menor;
		bool hit;

		posicion = (direccion/offset_pot) % dir_pot; 
		tag = direccion / tag_pot;
		offset = direccion % offset_pot;
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

		posicion = (direccion/offset_pot) % dir_pot; 
		tag = direccion / tag_pot;
		offset = direccion % offset_pot;
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

typedef std::map<int, std::vector<int> > t_tabla;

std::pair<int, int> simulacion(bloques, bloque_size, vias, accesos, pagina_size)
{
	int paginas_disco, paginas_mem, fallos_pagina, fallos_cache, bits_offset, div_virt;

	std::random_device rseed; // Para numeros aleatorios
	std::mt19937 rgen(rseed()); // mersenne_twister
	std::uniform_int_distribution<int> idist(0, DIR_VIRUTALES - 1); // [0,4095]
	std::uniform_int_distribution<int> odist(0, 1); // [0,1]
	std::uniform_int_distribution<int> ddist(0, 255); // [0,255]

	std::vector<std::vector<int> > ins_virtuales (accesos, std::vector<int> (3,0));
	std::vector<int> memoria (POS_MEMORIA);
	std::vector<int> disco (POS_DISCO);
	t_tabla tabla;

	/* Inicializacion */
	paginas_disco = POS_DISCO / pagina_size;
	paginas_mem = POS_MEMORIA / pagina_size;
	fallos_pagina = 0;
	fallos_cache = 0;
	bits_offset = bits_para(pagina_size);
	div_virt = potencia(bits_offset);// para posterior division

	/* Generar instrucciones virtuales */
	for (int i = 0; i < accesos; ++i)
	{
		ins_virtuales[i][0] = idist(rgen);
		ins_virtuales[i][1] = odist(rgen);
		ins_virtuales[i][2] = ddist(rgen);
	}

	/* Generamos la tabla de traduccion */
	int contador;
	for (contador = 0; contador < accesos; ++contador)
	{
		int tmp = ins_virtuales[contador][0]/div_virt;
		if(tabla.size() > paginas_mem) break;
		if(tabla.count(tmp) == 0)
		{
			tabla[tmp].push_back(odist(rgen)); /* 1 - memoria principal */
			tabla[tmp].push_back(0); /* 1 - dato en disco  mem llena */
			tabla[tmp].push_back(contador); /* dir fisica */
		}
	}
	for (contador; contador < accesos; ++i)
	{
		int tmp = ins_virtuales[contador][0]/div_virt;
		if(tabla.size() > (paginas_mem + paginas_disco)) break;
		if(tabla.count(tmp) == 0)
		{
			tabla[tmp].push_back(0); /* 1 - memoria principal */
			tabla[tmp].push_back(1); /* 1 - dato en disco  mem llena */
			tabla[tmp].push_back(contador); /* dir disco */
		}
	}

	/* leemos la memoria y el disco */
	std::ifstream inputmem;
	std::ifstream inputdisc;
	std::string outmem;
	std::string outdisc;
	int valor_io;
	int contador_io = 0;

	inputmem.open("memoria.txt", std::ifstream::in);

	while(inputmem >> valor_io)
	{
		memoria[contador_io] = valor_io;
		contador_io++;
	}
	inputmem.close();

	inputdisc.open("disco.txt", std::ifstream::in);

	contador_io = 0;
	while(inputdisc >> valor_io)
	{
		disco[contador_io] = valor_io;
		contador_io++;
	}
	inputdisc.close();

	/* Iteramos en cada instruccion */
	int dir_fisica, tmp;
	std::vector<int> (bloque_size,0);
	for (int i = 0; i < accesos; ++i)
	{
		/* code */
	}

	/* Excribimos en los archivos */
	std::ofstream ofm ("memoria.txt", std::ofstream::out);
	for (int i = 0; i < POS_MEMORIA; ++i)
	{
		ofm << memoria[i] << "\n";
	}
	ofm.close();
	std::ofstream ofd ("disco.txt", std::ofstream::out);
	for (int i = 0; i < POS_DISCO; ++i)
	{
		ofd << disco[i] << "\n";
	}
	ofd.close();

	return std::make_pair(fallos_pagina, fallos_cache);
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    cachegui w;
    w.show();

    return a.exec();
}
