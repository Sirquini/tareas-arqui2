#include "cachegui.h"
#include "ui_cachegui.h"
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
    int result;
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
class Cache
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


    Cache(int a_vias, int a_bloques, int a_bloque_size)
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
        std::cout << "Vias: " << vias << "\n";
        std::cout << "Bloques: " << bloques << "\n";
        std::cout << "bloque_size: " << bloque_size << "\n";
        std::cout << "posiciones: " << posiciones << "\n";
        std::cout << "boffset: " << boffset << "\n";
        std::cout << "bdir: " << bdir << "\n";
        std::cout << "tag_pot: " << tag_pot << "\n";
        std::cout << "offset_pot: " << offset_pot << "\n";
        std::cout << "dir_pot: " << dir_pot << "\n";
    }

    ~Cache()
    {

    }

    std::vector<int> read_cache(int direccion, std::vector<int> dato)
    {
        std::vector<int> result (3+bloque_size, 0);
        int posicion, tag, offset, pos_reemplazo, menor;
        bool hit;

        posicion = (direccion/offset_pot) % posiciones; 
        tag = direccion / tag_pot;
        offset = direccion % offset_pot;
        pos_reemplazo = 0;
        menor = LFU_counter[posicion][0];
        hit = false;
        //std::cout << "Cache Read" << std::endl;

        for (int i = 0; i < vias; ++i)
        {
            std::cout << i << std::endl;
            /* Para aplicar LFU mas adelante */
            if(menor > LFU_counter[posicion][i])
            {
                menor = LFU_counter[posicion][i];
                pos_reemplazo = i;
            }
            /* Esta en la cache y es valido? */
            if(mem[posicion][i][2] == tag && mem[posicion][i][0] == 1)
            {
                std::cout << "Hit Cache!" << std::endl;
                hit = true;
                result[0] = 1;

                LFU_counter[posicion][i] += 1; // Para politica LFU
                break;
            }
        }
        /* No lo encontro en cache? */
        if (!hit)
        {
            std::cout << "Miss Cahce!" << std::endl;
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

        posicion = (direccion/offset_pot) % posiciones; 
        tag = direccion / tag_pot;
        offset = direccion % offset_pot;
        pos_reemplazo = 0;
        std::cout << posicion << std::endl;
        menor = LFU_counter[posicion][0];
        hit = false;
        //std::cout << "Cache Write" << std::endl;
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
                std::cout << "Hit Cache!" << std::endl;
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
            std::cout << "Miss Cahce!" << std::endl;
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

    
};

cachegui::cachegui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cachegui)
{
    ui->setupUi(this);
}

cachegui::~cachegui()
{
    delete ui;
}

typedef std::map<int, std::vector<int> > t_tabla;

std::pair<int, int> simulacion(int bloques, int bloque_size, int vias, int accesos, int pagina_size);

void cachegui::on_analisis_clicked()
{
    int bloquescache = ui->cacheblocks->value();
    int numerovias = ui->nvias->value();
    int numeromemp = ui->nmemp->value();
    int tampagina = ui->tampag->value();
    int tambloque = ui->tambloq->value();

    if(tampagina > 32)
        QMessageBox::critical(0, QString("Error"),QString("El tamaño de pagina no puede superar los 32 bytes") , QMessageBox::Ok);
    else if(numerovias > 0 && (bloquescache % numerovias) != 0)
        QMessageBox::critical(0, QString("Error"),QString("El número de bloques debe ser divisible por el número de vías") , QMessageBox::Ok);
    else if(tampagina > 0 && (1024 % tampagina) != 0)
        QMessageBox::critical(0, QString("Error"),QString("El tamaño de pagina debe dividir al tamaño de la memoria principal que es un 1KB") , QMessageBox::Ok);
    else if(bloquescache == 0 || numerovias == 0 || numeromemp == 0 || tampagina == 0 || tambloque == 0)
        QMessageBox::critical(0, QString("Error"),QString("Le falta ingresar uno o más datos") , QMessageBox::Ok);      
    else
    {
        // generate some data:
        QVector<double> x,y; // initialize with entries 0..100
        

        // create graph and assign data to it:
        ui->plot1->addGraph();
        ui->plot1->graph(0)->setData(x, y);
        // give the axes some labels:
        ui->plot1->xAxis->setLabel("Tamaño del bloque");
        ui->plot1->yAxis->setLabel("Tamaño de la cache");
        // set axes ranges, so we see all data:
        ui->plot1->xAxis->setRange(-1, 1);
        ui->plot1->yAxis->setRange(0, 1);
        ui->plot1->replot();
    
        x.clear();
        y.clear();
        x.push_back(1);
        for (int i = 2; bloquescache % i == 0 && i < bloquescache; i += 2)
        {
            x.push_back(i);
        }
        for (auto& via : x)
        {
            std::pair<int, int> falloscalc = simulacion(bloquescache, tambloque, via, numeromemp, tampagina);
            y.push_back(falloscalc.second);
        }
        // create graph and assign data to it:
        ui->plot2->addGraph();
        ui->plot2->graph(0)->setData(x, y);
        // give the axes some labels:
        ui->plot2->xAxis->setLabel("Número de vías");
        ui->plot2->yAxis->setLabel("Tamaño de la cache");
        // set axes ranges, so we see all data:
        ui->plot2->xAxis->setRange(-1, 1);
        ui->plot2->yAxis->setRange(0, 1);
    
        ui->plot2->replot();
    }
}

void cachegui::on_Generar_clicked()
{
    int bloquescache = ui->cacheblocks->value();
    int numerovias = ui->nvias->value();
    int numeromemp = ui->nmemp->value();
    int tampagina = ui->tampag->value();
    int tambloque = ui->tambloq->value();
    if(tampagina > 32)
        QMessageBox::critical(0, QString("Error"),QString("El tamaño de pagina no puede superar los 32 bytes") , QMessageBox::Ok);
    else if(numerovias > 0 && (bloquescache % numerovias) != 0)
        QMessageBox::critical(0, QString("Error"),QString("El número de bloques debe ser divisible por el número de vías") , QMessageBox::Ok);
    else if(tampagina > 0 && (1024 % tampagina) != 0)
        QMessageBox::critical(0, QString("Error"),QString("El tamaño de pagina debe dividir al tamaño de la memoria principal que es un 1KB") , QMessageBox::Ok);
    else if(bloquescache == 0 || numerovias == 0 || numeromemp == 0 || tampagina == 0 || tambloque == 0)
        QMessageBox::critical(0, QString("Error"),QString("Le falta ingresar uno o más datos") , QMessageBox::Ok);
    else
    {
        std::pair<int, int> falloscalc = simulacion(bloquescache, tambloque, numerovias, numeromemp, tampagina);
        
        float fallospor = falloscalc.first;
        float fallospor2 = numeromemp;
        float fallospor3 = (fallospor/fallospor2)*100;
        QString fallospagvir;
        fallospagvir = QString("La tasa de fallos es de: ")+ QString::number(fallospor3)+QString("%");
        QMessageBox::information(0, QString("Fallos Pagina Virtual"), fallospagvir, QMessageBox::Ok);
    }
}


std::pair<int, int> simulacion(int bloques, int bloque_size, int vias, int accesos, int pagina_size)
{
    int paginas_disco, paginas_mem, fallos_pagina, fallos_cache, bits_offset, div_virt, div_fisica;
    
    std::cout << "Numero de bloques: " << bloques << std::endl;
    std::cout << "Tamano de bloque: " << bloque_size << std::endl;
    std::cout << "Numero de vias: " << vias << std::endl;
    std::cout << "Numero de accesos: " << accesos << std::endl;
    std::cout << "Tamanio de pagina: " << pagina_size << std::endl;
    

    std::cout << "Inicializando...";
    std::random_device rseed; // Para numeros aleatorios
    std::mt19937 rgen(rseed()); // mersenne_twister
    std::uniform_int_distribution<int> idist(0, DIR_VIRUTALES - 1); // [0,4095]
    std::uniform_int_distribution<int> odist(0, 1); // [0,1]
    std::uniform_int_distribution<int> ddist(0, 255); // [0,255]

    /* ins_virtuales[*][x], x: 0 - direccion, 1 - lectura/escritura, 2 - dato */
    std::vector<std::vector<int> > ins_virtuales (accesos, std::vector<int> (3,0));
    std::vector<int> memoria (POS_MEMORIA);
    std::vector<int> disco (POS_DISCO);
    t_tabla tabla;

    /* Creamos la cache */
    Cache mem_cache (vias, bloques, bloque_size);

    /* Inicializacion */
    paginas_disco = POS_DISCO / pagina_size;
    paginas_mem = POS_MEMORIA / pagina_size;
    std::uniform_int_distribution<int> mdist(0, paginas_mem); // [0,paginas_memoria]
    fallos_pagina = 0;
    fallos_cache = 0;
    bits_offset = bits_para(pagina_size);
    div_virt = potencia(bits_offset);// para posterior division
    div_fisica = potencia(bits_para(bloque_size));// para posterior division
    std::cout << " Inicializacion terminada!" << std::endl;
    std::cout << "Generando instrucciones..." << std::endl;
    /* Generar instrucciones virtuales */
    for (int i = 0; i < accesos; ++i)
    {
        ins_virtuales[i][0] = idist(rgen);
        ins_virtuales[i][1] = odist(rgen);
        ins_virtuales[i][2] = ddist(rgen);
    }
    std::cout << " Terminado!" << std::endl;
    std::cout << "Generando tabla de traduccion..." << std::endl;
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
    for (; contador < accesos; ++contador)
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
    std::cout << " Terminado!" << std::endl;
    /* leemos la memoria y el disco */
    std::ifstream inputmem;
    std::ifstream inputdisc;
    std::string outmem;
    std::string outdisc;
    int valor_io;
    int contador_io = 0;

    std::cout << "Leyendo memoria..." << std::endl;
    inputmem.open("memoria.txt", std::ifstream::in);

    while(inputmem >> valor_io)
    {
        memoria[contador_io] = valor_io;
        contador_io++;
    }
    inputmem.close();
    std::cout << " Terminado!" << std::endl;
    if (contador_io == 0)
    {
        std::cout << "Memoria vacia, abortando!" << std::endl;
        return std::make_pair(0,0);
    }
    std::cout << "Leyendo disco..." << std::endl;
    inputdisc.open("disco.txt", std::ifstream::in);

    contador_io = 0;
    while(inputdisc >> valor_io)
    {
        disco[contador_io] = valor_io;
        contador_io++;
    }
    inputdisc.close();
    std::cout << " Terminado!" << std::endl;
    if (contador_io == 0)
    {
        std::cout << "Disco vacio, abortando!" << std::endl;
        return std::make_pair(0,0);
    }
    std::cout << "Procesando instrucciones..." << std::endl;
    /* Iteramos en cada instruccion */
    int dir_fisica, tmp, tmp2;
    std::vector<int> movimiento (bloque_size,0);
    std::vector<int> respuesta_cache;
    for (int i = 0; i < accesos; ++i)
    {
        /* Traducimos direccion virtual a fisica */
        dir_fisica = ins_virtuales[i][0]/div_virt;
        /* No esta en memoria principal? */
        if(tabla[dir_fisica][0] == 0)
        {
            tabla[dir_fisica][0] = 1;
            fallos_pagina++; // nuevo fallo de pagina
            tmp2 = tabla[dir_fisica][2]; // direccion disco
            /* no esta asigana? */
            if(tabla[dir_fisica][1] == 1)
            {
                tabla[dir_fisica][1] = 0;
                tmp = mdist(rgen); // nueva asignacion.
                tabla[dir_fisica][2] = tmp;
                /* Movemos de disco a memoria */
            }
            else tmp = tmp2; // Si esta asignada disco - memoria concuerdan.

            tmp = tmp * div_virt;
            tmp2 = tmp2 * div_virt;
            for(int j = 0; j < pagina_size; ++j)
            {
                memoria[tmp + j] = disco[tmp2 + j];
            }
        }
        /* El dato ya esta en memoria principal */
        /* Extraemos direccion fisica */
        dir_fisica = tabla[dir_fisica][2] * div_virt;
        /* Agregamos el offset */
        dir_fisica = dir_fisica + (ins_virtuales[i][0] % div_virt);
        /* Cargamos los datos que hay en la memoria por si hay un miss en cache */
        tmp = dir_fisica - (dir_fisica % div_fisica); // quitamos el offset de un bloque.
        for (int j = 0; j < bloque_size; ++j)
        {
            movimiento[j] = memoria[tmp + j];
        }
        /* Lectura o escritura */
        if (ins_virtuales[i][1] == 0)
        {
        std::cout << "Read" << std::endl;
            respuesta_cache = mem_cache.read_cache(dir_fisica, movimiento);
        }
        else
        { 
        std::cout << "Write" << std::endl;
            respuesta_cache = mem_cache.write_cache(dir_fisica, movimiento, ins_virtuales[i][2]);
        }

        /* Analimamos la respuesta de la cache */
        /* no fue un hit? */
        if(respuesta_cache[0] != 1)
            fallos_cache++;
        /* hay que escribir en memoria, por write-back? */
        if (respuesta_cache[1] == 1)
        {
            std::cout << "write-back" << std::endl;
            tmp = respuesta_cache[2]; // donde, escribir
            tmp = tmp - (tmp % div_fisica); // quitamos el offset del bloque.
            for (int j = 0; j < bloque_size; ++j)
            {
                memoria[tmp + j] = respuesta_cache[3+j];
            }
        }

    }
    std::cout << " Terminado!" << std::endl;
    std::cout << "Reescribiendo memoria..." << std::endl;
    /* Excribimos en los archivos */
    std::ofstream ofm ("memoria.txt", std::ofstream::out);
    for (int i = 0; i < POS_MEMORIA; ++i)
    {
        ofm << memoria[i] << "\n";
    }
    ofm.close();
    std::cout << "Terminado!" << std::endl;
    std::cout << "Reescribiendo disco..." << std::endl;
    std::ofstream ofd ("disco.txt", std::ofstream::out);
    for (int i = 0; i < POS_DISCO; ++i)
    {
        ofd << disco[i] << "\n";
    }
    ofd.close();
    std::cout << "Terminado!" << std::endl;

    return std::make_pair(fallos_pagina, fallos_cache);
}
