#include <iostream>
#include <fstream>
#include <random>
#include <string>

int main(int argc, char *argv[])
{
	std::random_device rseed; // Para numeros aleatorios
    std::mt19937 rgen(rseed()); // mersenne_twister
    std::uniform_int_distribution<int> idist(0, 255); // inclusivo
    std::string entrada;
    int lineas;

    std::cout << "Ingrese el nombre del archivo: ";
    std::cin >> entrada;
    std::cout << "Ingrese lineas: ";
    std::cin >> lineas;

    std::ofstream ofs (entrada, std::ofstream::out);

    for (int i = 0; i < lineas; ++i)
    {
    	ofs << idist(rgen) << "\n";
    }

    ofs.close();

    std::cout << entrada << " generado!" << std::endl;

	return 0;
}