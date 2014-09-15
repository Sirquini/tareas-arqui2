#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>  

/* Definicion del tipo de dato para el diccionario de palabras */
typedef std::unordered_map<std::string, std::string> stringmap;
typedef std::unordered_map<std::string, int> strintmap;

std::vector<std::string> GetWords(std::string instruc)
{
	std::vector<std::string> words;
	char *inst = strdup(instruc.c_str());
    char *token=strtok(inst," :,()");
  	while (token != NULL)
  	{
	 	words.push_back(token);  	   
	    token = strtok (NULL, " :,()");
  	}
  	return words;
}

std::string transform(int numero, int nbits)
{
	std::string base = "";
	int realsize;

	do
	{
		if ((numero & 1) == 0 )
			base = "0" + base;
		else
			base = "1" + base;
		numero >>= 1; 
	} while( numero );

	realsize = nbits - base.length();

	if (realsize > 0)
	{
		std::string prefix = "0";
		for (int i = 1; i < realsize; ++i)
		{
			prefix.push_back('0');
		}
		base = prefix + base;
	}
	return base;
}


int main(int argc, char const *argv[])
{
	// Declaramos el diccionario a usar para la traduccion con sus respectivas llaves, valores.
	stringmap opcodedic ({
		{"add", "000"},
		{"sub", "000"},
		{"div", "000"},
		{"mult", "000"},
		{"slt", "000"},
		{"lw", "001"},
		{"sw", "010"},
		{"beq", "011"},
		{"addi", "101"},
		{"j", "100"},
		{"read", "110"},
		{"show", "111"}
	});

	stringmap regdic ({
		{"$zero", "0000"},
		{"$at", "0001"},
		{"$v0", "0010"},
		{"$v1", "0011"},
		{"$t0", "0100"},
		{"$t1", "0101"},
		{"$t2", "0110"},
		{"$t3", "0111"},
		{"$t4", "1000"},
		{"$t5", "1001"},
		{"$t6", "1010"},
		{"$t7", "1011"},
		{"$s0", "1100"},
		{"$s1", "1101"},
		{"$s2", "1110"},
		{"$s3", "1111"}
	});

	stringmap functdic ({
		{"add", "00000"},
		{"sub", "00001"},
		{"div", "00011"},
		{"mult", "00010"},
		{"slt", "00100"}
	});

	/* Mapa con las etiquetas y su valor */
	strintmap labeldic;

	/* Contenedor del texto a traducir separado por linea y tokens */
	std::vector<std::vector<std::string> > basecode; 
	int basecode_size; 

	std::string instruction;
	std::ifstream text;
  	text.open ("testinput.txt", std::ifstream::in);

  	/* Convertimos la entrada de texto a un formato manipulable */
	while(std::getline (text,instruction))
	{
		basecode.push_back(GetWords(instruction));
	}

	/* Escaneamos la entrada en busca de etiquetas */
	basecode_size = basecode.size();
	for (int i = 0; i < basecode_size; ++i)
	{
		if (opcodedic.count(basecode[i][0]) == 0)
		{
			labeldic[basecode[i][0]] = i;
		}
	}

	return 0;
}