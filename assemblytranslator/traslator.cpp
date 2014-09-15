#include <iostream>
#include <string>
#include <unordered_map>

/* Definicion del tipo de dato para el diccionario de palabras */
typedef std::unordered_map<std::string, std::string> stringmap;

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



	std::cout << "Hello World!" << std::endl;
	return 0;
}