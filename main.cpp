#include <iostream>
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
    if ( max < min ) // En général, on donne le minimum avant le maximum, et parfois pas la valeur par défaut.
        {
        auto temp = max;
        max = min;
        min = temp;
        }
// Textes par défaut par fichier lgg ?

    auto a = max; // Valeur valide.
    string tentativeString = "";
    bool inputOk  = true;
    do
        {
        cout << texteDemande << endl;
        inputOk = true; // Pour autre demande éventuelle.
        try
            {
            getline ( cin, tentativeString ); // Pour éviter des bugs de non nombre.
            }
        catch ( const std::invalid_argument& e )
            {
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue ( texteBadValue, min, max );
            }
        try
            {
            a = stoi ( tentativeString ); // cin.;
            }
        catch ( exception& e ) // Nombre dépassant la limite : 99999999999999999999999999999999 par exemple.
            {
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue ( texteBadValue, min, max );
            }
        if ( ( a < min ) || ( a > max ) )
            {
            a = max; // Valeur valide.
            inputOk = errBadVAlue ( texteBadValue, min, max );
            }
        }
    while ( inputOk == false );
    return a;
}


int main()
{
    cout << "Ceci vous donne le nombre de feuillets dans un rouleau ouvert, en fonction de ses dimensions." << endl;

  // Référence ?
    // Fichier ?
    float diametreVide_cm = 0;
    diametreVide_cm = inputNb(1000000, 0, "Diamètre vide, en cm ?");
    float diametrePlein_cm = 0;
    diametrePlein_cm = inputNb(1000000, diametreVide_cm, "Diamètre plein, en cm ?");
    int nombreDeFeuilletsQuandPlein = 0;
nombreDeFeuilletsQuandPlein = inputNb(1000000, 0, "Nombre de feuillets d'un rouleau plein ?");
    float diametreActuel_cm = 0;
    diametreActuel_cm = inputNb(diametrePlein_cm, diametreVide_cm, "Diamètre actuel ?");

//    Rappel de formule : surface d'un anneau en 2D : pi * (R2 − r2)
// https://calculis.net/aire/anneau
  //    La taille dess feuillets (longueur et gosseur) ne change pas. Le rapport entre le nombe de feuillets  actuels et le nombre de feuillets total est donc le rapport des surfaces de la tranche du rouleau actuel sur le nombre de feuillets d'un rouleau plein.
 int nombreDeFeuilletsActel = nombreDeFeuilletsQuandPlein * ( diametreVide_cm - diametreActuel_cm) / (diametreVide_cm - diametrePlein_cm); // Simplification des Pis ; rapport des rayons = rapport des diaètres.
   cout << "Le nombre de feuillets est de : "  << nombreDeFeuilletsActel << ". "<< endl;
    return 0;
}
