#include "guiarqui2.h"
#include "ui_guiarqui2.h"
/* Definicion del tipo de dato para el diccionario de palabras */
typedef std::unordered_map<std::string, std::string> stringmap;
typedef std::unordered_map<std::string, int> strintmap;


GuiArqui2::GuiArqui2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuiArqui2)
{
    ui->setupUi(this);
}

GuiArqui2::~GuiArqui2()
{
    delete ui;
}


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

QString translate(QString trans,int empezar)
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
    int basecode_size, startpos = empezar;

    /* Texto de entrada */
   // std::ifstream text;
    /* Texto de salida */
    std::string text_out = "";

    /* Convertimos la entrada de texto a un formato manipulable */
    std::string instruction;
    QString instruc;
    QTextStream in(&trans);
    instruc=in.readLine();
    while( instruc != NULL)
    {
        instruction = instruc.toStdString();
        basecode.push_back(GetWords(instruction));
        instruc=in.readLine();
    }
    /* Escaneamos la entrada en busca de etiquetas  las agregamos al
     * diccionario y las eliminamos del contenedor. */
    basecode_size = basecode.size();
    for (int i = 0; i < basecode_size; ++i)
    {
        if (opcodedic.count(basecode[i][0]) == 0)
        {
            labeldic[basecode[i][0]] = i;
            basecode[i].erase(basecode[i].begin());
        }
    }

    /* Convertimos las lineas en su eqivalente en binario */

    for (int i = 0; i < basecode_size; ++i)
    {
        std::string linea = opcodedic[basecode[i][0]];

        /* Revisamos las instrucciones tipo R */
        if (linea == "000")
        {
            linea += regdic[basecode[i][2]];
            linea += regdic[basecode[i][1]];
            linea += functdic[basecode[i][0]];
        }
        /* Revisamos el branch */
        else if (linea == "011")
        {
            linea += regdic[basecode[i][1]];
            linea += regdic[basecode[i][2]];
            linea += transform(labeldic[basecode[i][3]]-i-1, 5);
        }
        /* Revisamos el addi */
        else if (linea == "101")
        {
            linea += regdic[basecode[i][2]];
            linea += regdic[basecode[i][1]];
            linea += transform(std::stoi(basecode[i][3]), 5);
        }
        /* Revisamos el sw y lw */
        else if (linea == "001" || linea == "010")
        {
            linea += regdic[basecode[i][3]];
            linea += regdic[basecode[i][1]];
            linea += transform(std::stoi(basecode[i][2]), 5);
        }
        /* Revisamos el jump */
        else if (linea == "100")
        {
            linea += transform(labeldic[basecode[i][1]]+startpos, 13);
        }
        /* Probicionalmente revisamos el read y show,
         * con direccion de memoria, i.e. read 1 o show 2 */
        else if (linea == "110" || linea == "111")
        {
            linea += transform(std::stoi(basecode[i][1]), 13);
        }
        /* En caso de que la informacion no se reconosca */
        else
        {
            linea = "XXXXXXXXXXXXXXXX";
        }
        linea += "\n";
        text_out += linea;
    }

    /* Mostramos en pantalla el codigo en pantalla */
    QString qdisp = QString::fromStdString(text_out);
    return qdisp;
}

std::vector<int> calcularCiclos(QString trans)
{
    // Declaramos el diccionario a usar para la traduccion con sus respectivas llaves, valores.
    strintmap opcodedic ({
        {"add", 0},
        {"sub", 1},
        {"div", 2},
        {"mult", 3},
        {"slt", 4},
        {"lw", 5},
        {"sw", 6},
        {"beq", 7},
        {"addi", 8},
        {"j", 9},
        {"read", 10},
        {"show", 10},
        {"end", 11}
    });

    strintmap regdic ({
        {"$zero", 0},
        {"$at",   0},
        {"$v0",   0},
        {"$v1",   0},
        {"$t0",   0},
        {"$t1",   0},
        {"$t2",   0},
        {"$t3",   0},
        {"$t4",   0},
        {"$t5",   0},
        {"$t6",   0},
        {"$t7",   0},
        {"$s0",   0},
        {"$s1",   0},
        {"$s2",   0},
        {"$s3",   0}
    });

    /* Simulacion de la memoria para datos */
    std::vector<int> memoria (64, 0);

    /* Mapa con las etiquetas y su valor */
    strintmap labeldic;

    /* Variable que simula el PC */
    int programCounter = 0;

    /* Contadores con el CRP para 0 - multiciclo y 1 - monociclo */
    std::vector<int> CRP(2,0);

    /* Contenedor del texto a traducir separado por linea y tokens */
    std::vector<std::vector<std::string> > basecode;
    int basecode_size;

    /* Texto de entrada */
   // std::ifstream text;
    /* Texto de salida */
    std::string text_out = "";

    /* Convertimos la entrada de texto a un formato manipulable */
    std::string instruction;
    QString instruc;
    QTextStream in(&trans);
    instruc=in.readLine();
    while( instruc != NULL)
    {
        instruction = instruc.toStdString();
        basecode.push_back(GetWords(instruction));
        instruc=in.readLine();
    }
    /* Escaneamos la entrada en busca de etiquetas  las agregamos al
     * diccionario y las eliminamos del contenedor. */
    basecode_size = basecode.size();
    for (int i = 0; i < basecode_size; ++i)
    {
        if (opcodedic.count(basecode[i][0]) == 0)
        {
            labeldic[basecode[i][0]] = i;
            basecode[i].erase(basecode[i].begin());
        }
    }

    /* Agregamos un simbolo de terminacion al programa */
    std::vector<std::string> endlinestring (1, "end");
    basecode.push_back(endlinestring);

    /* Simulamos las lineas para contar los ciclos */

    while (programCounter < basecode_size)
    {
        int linea = opcodedic[basecode[programCounter][0]];
        switch (linea)
        {
            /* Revisamos ADD */
            case 0:
                if (basecode[programCounter][1] != "$zero")
                {
                    regdic[basecode[programCounter][1]] = regdic[basecode[programCounter][1]] + regdic[basecode[programCounter][2]];
                }
                CRP[0] += 4;
                break;
            /* Revisamos SUB */
            case 1:
                if (basecode[programCounter][1] != "$zero")
                {
                    regdic[basecode[programCounter][1]] = regdic[basecode[programCounter][1]] - regdic[basecode[programCounter][2]];
                }
                CRP[0] += 4;
                break;
            /* Revisamos DIV */
            case 2:
                if (basecode[programCounter][1] != "$zero")
                {
                    regdic[basecode[programCounter][1]] = regdic[basecode[programCounter][1]] / regdic[basecode[programCounter][2]];
                }
                CRP[0] += 4;
                break;
            /* Revisamos MULT */
            case 3:
                if (basecode[programCounter][1] != "$zero")
                {
                    regdic[basecode[programCounter][1]] = regdic[basecode[programCounter][1]] * regdic[basecode[programCounter][2]];
                }
                CRP[0] += 4;
                break;
            /* Revisamos SLT */
            case 4:
                if (basecode[programCounter][1] != "$zero")
                {
                    regdic[basecode[programCounter][1]] = (regdic[basecode[programCounter][1]] < regdic[basecode[programCounter][2]]) ? 1 : 0;
                }
                CRP[0] += 4;
                break;
            /* Revisamos LW */
            case 5:
                if (basecode[programCounter][1] != "$zero")
                {
                    regdic[basecode[programCounter][1]] = memoria[ std::stoi(basecode[programCounter][2]) + regdic[basecode[programCounter][3]] ];
                }
                CRP[0] += 5;
                break;
            /* Revisamos SW */
            case 6:
                if (basecode[programCounter][1] != "$zero")
                {
                     memoria[ std::stoi(basecode[programCounter][2]) + regdic[basecode[programCounter][3]] ] = regdic[basecode[programCounter][1]];
                }
                CRP[0] += 4;
                break;
            /* Revisamos BEQ */
            case 7:
                programCounter = (regdic[basecode[programCounter][1]] == regdic[basecode[programCounter][2]])? labeldic[basecode[programCounter][3]] : programCounter + 1;
                CRP[0] += 3;
                break;
            /* Revisamos ADDi */
            case 8:
                if (basecode[programCounter][1] != "$zero")
                {
                    regdic[basecode[programCounter][1]] = regdic[basecode[programCounter][2]] + std::stoi(basecode[programCounter][3]);
                }
                CRP[0] += 4;
                break;
            /* Revisamos JUMP */
            case 9:
                programCounter = labeldic[basecode[programCounter][1]];
                CRP[0] += 3;
                break;
            /* Revisamos READ o SHOW */
            case 10:
                CRP[0] += 3;
                break;
            /* En caso de que la instrucion no se reconosca */
            default:
                programCounter = basecode_size;
        }
        if (linea != 7 && linea != 9)
        {
            ++programCounter;
        }
        CRP[1] += 1;

        /* Para evitar bucles infinitos*/
        if(CRP[1] > 1000000) break;
    }

    /* Retornamos los respectivos CRP */
    return CRP;
}

float calcularMulti(float frec, int CRP)
{
    return  CRP / frec;
}

float calcularMono(float frec, int CRP)
{
    return CRP / frec;
}
void GuiArqui2::on_Traduction_clicked()
{
    QString algo;
    int empezar = ui->spinBox->value();
    algo = ui->text_in->toPlainText();
    QString text_disp = translate(algo,empezar);
    ui->text_out->setText(text_disp);

}

/*
void GuiArqui2::on_text_in_textChanged()
{
    QString algo;
    algo = ui->text_in->toPlainText();
    QString text_disp = translate(algo);
    ui->text_out->setText(text_disp);
}
*/

void GuiArqui2::on_Calcular_clicked()
{
    QString inputText;
    float multi = ui->Multi->value();
    float mono = ui->Mono->value();
    std::vector<int> CRP = {0,0};
    if(multi<=mono)
    {
        QMessageBox::critical(0, QString("Error"), QString("La frecuencia en multiciclo tiene que ser mayor a la monociclo"), QMessageBox::Ok);        
    }
    else if (multi == 0.0)
    {
        QMessageBox::critical(0, QString("Error"), QString("La frecuencia en multiciclo tiene que ser mayor a cero"), QMessageBox::Ok);
    }
    else if (mono == 0.0)
    {
        QMessageBox::critical(0, QString("Error"), QString("La frecuencia en monociclo tiene que ser mayor a cero"), QMessageBox::Ok);
    }
    else
    {
        inputText = ui->text_in->toPlainText();
        CRP = calcularCiclos(inputText);
        multi = calcularMulti(multi, CRP[0]);
        mono = calcularMono(mono, CRP[1]);
        ui->Multidsp->display(multi);
        ui->Monodsp->display(mono);
        float ganancia =((multi/mono)-1)*100;
        ui->Gananciamm->display(ganancia);
    }
 }

void GuiArqui2::on_tcalc_clicked()
{
    GuiArqui2::on_Traduction_clicked();
    GuiArqui2::on_Calcular_clicked();
}
