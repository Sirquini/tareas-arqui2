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
