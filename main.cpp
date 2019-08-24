#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool errBadVAlue ( string texteBadValue, auto min, auto max )
{
    cerr << "Min = "  << min << endl;
    cerr << "Max = "  << max << endl;
    cerr << texteBadValue << endl;
    return false;
}

auto inputNb ( auto max = 42, auto min = 0, string texteDemande = "How many?", string texteBadValue = "A good number!" ) // C++14 minimum.
{
    if ( max < min ) { // En général, on donne le minimum avant le maximum, et parfois pas la valeur par défaut.
        auto temp = max;
        max = min;
        min = temp;
    }
// Textes par défaut par fichier lgg ?

    auto a = max; // Valeur valide.
    string tentativeString = "";
    bool inputOk  = true;
    do {
        cout << texteDemande << endl;
        inputOk = true; // Pour autre demande éventuelle.
        try {
            getline ( cin, tentativeString ); // Pour éviter des bugs de non nombre.
        } catch ( const std::invalid_argument& e ) {
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue ( texteBadValue, min, max );
        }
        try {
            a = stoi ( tentativeString ); // cin.;
        } catch ( exception& e ) { // Nombre dépassant la limite : 99999999999999999999999999999999 par exemple.
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue ( texteBadValue, min, max );
        }
        if ( ( a < min ) || ( a > max ) ) {
            a = max; // Valeur valide.
            inputOk = errBadVAlue ( texteBadValue, min, max );
        }
    } while ( inputOk == false );
    return a;
}

void iout ( string message = "",  int colorisationFin = 0, int colorisation1 = 4, int colorisation2 = 1) // Ok.
{
    // 31 = RED.
    // 1 = bold.
    // 3 = italic.
    // 4 = underline.
    // 0 = normal.
    // 2 effects or color only.
    // 41 = red background...
    printf ( "\033[%dm", colorisation1 );
    printf ( "\033[%dm", colorisation2 );
    cout << message;  // http://www.cplusplus.com/forum/beginner/108474/
    printf ( "\033[%dm", colorisationFin );
}

void ierr ( string message = "",  int colorisationFin = 0, int colorisation1 = 1, int colorisation2 = 31 ) // Ok.
{
    // 31 = RED.
    // 1 = bold.
    // 3 = italic.
    // 4 = underline.
    // 0 = normal.
    // 2 effects or color only.
    // 41 = red background...
    printf ( "\033[%dm", colorisation1 );
    printf ( "\033[%dm", colorisation2 );
    cerr << message;  // http://www.cplusplus.com/forum/beginner/108474/
    printf ( "\033[%dm", colorisationFin );
}

AppendFunctionFileString(string file, string data = "")  // And create new file if does not exist.
{
    ofstream outfile(file.c_str(), ios_base::app);
    if (!outfile) {
        cerr << "Error Opening File " << file << "!" << endl;
        return -1;
    } else {
        outfile << data;
        outfile.close();
    }
}

int main()
{
    cout << "Ceci vous donne le nombre de feuillets dans un rouleau ouvert, en fonction de ses dimensions." << endl;
NouvelInventaire:
    string nomInventaire = "";
    cout << "Nom de l'inventaire ? (Validez un nom vide par ENTER pour quitter.) (Un fichier sera fait, avec l'extention \".txt\".) ";
getline ( cin, nomInventaire);
nomInventaire = nomInventaire + ".txt";

cout << "Une remarque à ajouter au fichier d'inventaire ?" << endl;
string remarque = "";
getline ( cin, remarque );
AppendFunctionFileString( nomInventaire, remarque + "\n");

NouveauRouleau:
    string nomRouleau = "";
    cout << "Nom du rouleau ? (Validez un nom vide par ENTER pour quitter.) ";
getline ( cin, nomRouleau);
    float diametreVide_cm = 0;
    diametreVide_cm = inputNb(1000000, 0, "Diamètre vide, en cm ?");
    float diametrePlein_cm = 0;
    diametrePlein_cm = inputNb(1000000, diametreVide_cm, "Diamètre plein, en cm ?");
    int nombreDeFeuilletsQuandPlein = 0;
    nombreDeFeuilletsQuandPlein = inputNb(1000000, 0, "Nombre de feuillets d'un rouleau plein ?");
    float diametreActuel_cm = 0;
    diametreActuel_cm = inputNb(diametrePlein_cm, diametreVide_cm, "Diamètre actuel ?");

    // Rappel de formule : surface d'un anneau en 2D : pi * (R2 − r2)
    // https://calculis.net/aire/anneau
    // La taille des feuillets (longueur et minceur) ne change pas. Le rapport entre le nombe de feuillets  actuels et le nombre de feuillets total est donc le rapport des surfaces de la tranche du rouleau actuel sur le nombre de feuillets d'un rouleau plein.
    int nombreDeFeuilletsActuel = nombreDeFeuilletsQuandPlein * ( diametreVide_cm - diametreActuel_cm) / (diametreVide_cm - diametrePlein_cm); // Simplification des Pis ; rapport des rayons = rapport des diaètres.
 string AfficheNombreFeuilletsActuel = "Le nombre de feuillets de ";
    // cout << "Le nombre de feuillets de ";
   // iout (nomRouleau); // Que Linux ?
   AfficheNombreFeuilletsActuel = AfficheNombreFeuilletsActuel + "\"" + nomRouleau + "\"";
//   cout << "\"" << nomRouleau << "\"";
    AfficheNombreFeuilletsActuel += " est d'environ : " ;
   cout << AfficheNombreFeuilletsActuel << nombreDeFeuilletsActuel << ". "<< endl;
AppendFunctionFileString(nomInventaire, AfficheNombreFeuilletsActuel);
AppendFunctionFileString(nomInventaire, to_string(nombreDeFeuilletsActuel));
AppendFunctionFileString(nomInventaire, ". \n");
    return 0;
}
