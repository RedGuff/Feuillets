#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Sorties, accent ?

bool errBadVAlue(string texteBadValue, auto min, auto max) {
    cerr << "Min = "  << min << endl;
    cerr << "Max = "  << max << endl;
    cerr << texteBadValue << endl;
    return false;
}

auto inputNb(auto max = 42, auto min = 0, string texteDemande = "How many?", string texteBadValue = "A good number!")  {  // C++14 minimum.{
    if(max < min) {    // En général, on donne le minimum avant le maximum, et parfois pas la valeur par défaut.
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
            getline(cin, tentativeString);    // Pour éviter des bugs de non nombre.
        } catch(const std::invalid_argument& e) {
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue(texteBadValue, min, max);
        }
        try {
            a = stoi(tentativeString);    // cin.;
        } catch(exception& e) {    // Nombre dépassant la limite : 99999999999999999999999999999999 par exemple.
            cerr << "Standard exception: " << e.what() << endl;
            inputOk = errBadVAlue(texteBadValue, min, max);
        }
        if((a < min) || (a > max)) {
            a = max; // Valeur valide.
            inputOk = errBadVAlue(texteBadValue, min, max);
        }
    } while(inputOk == false);
    return a;
}

void iout(string message = "",  int colorisationFin = 0, int colorisation1 = 4, int colorisation2 = 1) {   // Ok with GNU/Linux.
    // 31 = RED.
    // 1 = bold.
    // 3 = italic.
    // 4 = underline.
    // 0 = normal.
    // 2 effects or color only.
    // 41 = red background...
    printf("\033[%dm", colorisation1);
    printf("\033[%dm", colorisation2);
    cout << message;  // http://www.cplusplus.com/forum/beginner/108474/
    printf("\033[%dm", colorisationFin);
}

void ierr(string message = "",  int colorisationFin = 0, int colorisation1 = 1, int colorisation2 = 31) {   // Ok with GNU/Linux.
    // 31 = RED.
    // 1 = bold.
    // 3 = italic.
    // 4 = underline.
    // 0 = normal.
    // 2 effects or color only.
    // 41 = red background...
    printf("\033[%dm", colorisation1);
    printf("\033[%dm", colorisation2);
    cerr << message;  // http://www.cplusplus.com/forum/beginner/108474/
    printf("\033[%dm", colorisationFin);
}

int AppendFunctionFileString(string file, string data = "")  {// And create new file if does not exist. SLOW.
    ofstream outfile(file.c_str(), ios_base::app);
    if(!outfile) {
        cerr << "Error Opening File " << file << "!" << endl;
        return -1;
    } else {
        outfile << data;
        outfile.close();
    }
    return 0;
}

inline bool exists_test1 (const std::string& name) { // https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

int main() {
    cout << "                    Etikedo v2.8" << endl;
    cout << "           Logiciel de comptage de feuillets." << endl;
    cout << "" << endl;
    cout << "Je vous donne approximativement le nombre de feuillets dans un rouleau ouvert, \nen fonction de ses dimensions." << endl;
    cout << "C'est approximatif : \nil est possible de mesurer quelques tours de spirales en plus ou en moins." << endl;
    cout << "Cela vous aidera pour un contexte d'inventaire. \nJ'enregistre donc le bilan dans un fichier d'inventaire." << endl;
    cout << "Vous pouvez vous exprimer en mm, en cm ou autrement, cela n'a aucune importance,\nmais vous devrez conserver ce choix durant tout le calcul de cet objet." << endl;
    string nomInventaire = "";
    string nomRouleau = " ";
    cout << "Quel est l'inventaire que je dois continuer, avec son chemin facultatif ?" << endl;
    // cout << "(Validez un nom vide par ENTER pour quitter.) " << endl;
    cout << "Un fichier vide de ce nom sera fait si besoin, et j\'y ajouterai l'extention \n\".txt\"." << endl;
while (nomInventaire==""){
        cout << "Pas de nom vide, svp." << endl;
    getline(cin, nomInventaire);
}
    nomInventaire = nomInventaire + ".txt"; // si existe : lecture et non redemande !
    string remarque = " ";
    while(remarque != "") {
        cout << "Ajoutez une ligne de remarques au fichier d'inventaire." << endl;
        cout << "Remarques possibles : date, heure, personnes participantes, lieu..." << endl;
        cout << "(Validez une ligne vide par ENTER pour poursuivre, sinon on vous reproposera une autre ligne de remarques.)" << endl;
        getline(cin, remarque);
        AppendFunctionFileString(nomInventaire, remarque + "\n");
    }
    bool start = true;
    while(true) {
       string nombreRouleau = "";
        cout << "Nom de l\'objet, du rouleau ";
        if (!start) {
            cout << "suivant";
        }
        cout << " ? \n(Validez un nom vide par ENTER pour quitter.) ";
        getline(cin, nomRouleau);
        if (nomRouleau=="") { // ?
            //  exit; // ??
            break; // ??
        }
        start = false;
        cout << "Combien de rouleaux entiers de " << nomRouleau << " avez-vous ? ";
        getline(cin, nombreRouleau);
        string textNbRouleaux = "Il y a " + nombreRouleau  + " rouleaux entiers de " + nomRouleau + " ";
        AppendFunctionFileString(nomInventaire, textNbRouleaux);
        string unity = "";
        float diametreVide  = 0;
        float diametrePlein = 0;
        int nombreDeFeuilletsQuandPlein = 0;
        if (!exists_test1(nomRouleau+".txt")) {
            cout << "Je ne connais pas cet objet." << endl;
            cout << "Quelle unité ? (cm, mm... ?) ";
            getline(cin, unity);
            AppendFunctionFileString(nomRouleau+".txt", unity+"\n");
            cout << "En " << unity << ", " << endl;
            diametreVide = inputNb(1000000, 0, "Diamètre vide ?");
            string nomRouleau_txt = nomRouleau+".txt";
            AppendFunctionFileString(nomRouleau_txt, to_string(diametreVide)+"\n");
            cout << "En " << unity << ", " << endl;
            diametrePlein = inputNb(1000000, diametreVide, "Diamètre plein ?");
            AppendFunctionFileString(nomRouleau_txt, to_string(diametrePlein)+"\n");
            nombreDeFeuilletsQuandPlein = inputNb(1000000, 0, "Nombre de feuillets d'un rouleau plein ?");
            AppendFunctionFileString(nomRouleau_txt, to_string(nombreDeFeuilletsQuandPlein)+"\n");
        } else {
            cout << "Je connais cet objet, il est ainsi :" << endl;
ifstream fichier(nomRouleau+".txt");

    if (fichier) {
 getline(fichier, unity);
cout << "Unité : " << unity << endl;
fichier >> diametreVide;
cout << "Diametre vide : " << diametreVide << endl;
fichier >> diametrePlein;
cout << "Diametre plein : " << diametrePlein << endl;
fichier >> nombreDeFeuilletsQuandPlein;
cout << "Nombre de feuillets quand il est plein : " << nombreDeFeuilletsQuandPlein << endl;
    fichier.close();
    } else {
        cerr << "Impossible de lire le fichier : " << nomRouleau+".txt" << ", que j\'ai pourtant détecté !" << endl;
        cerr << "Fermez tout et recommencez !" << endl;
    }
        }
        float diametreActuel = 0;
cout << "En " << unity << ", " << endl;
        diametreActuel = inputNb(diametrePlein, diametreVide, "Diamètre actuel ?");
        // Rappel de formule : surface d'un anneau en 2D : pi * (R2 ? r2)
        // https://calculis.net/aire/anneau
        int nombreDeFeuilletsActuel = nombreDeFeuilletsQuandPlein * (diametreVide - diametreActuel) / (diametreVide - diametrePlein);  // Simplification des Pis ; rapport des rayons = rapport des diamètres.
        string AfficheNombreFeuilletsActuel = "et en plus, le nombre de feuillets du rouleau partiel de ";
        // cout << "Le nombre de feuillets de ";
        // iout (nomRouleau); // Que Linux ?
        AfficheNombreFeuilletsActuel = AfficheNombreFeuilletsActuel + "\"" + nomRouleau + "\"";
//   cout << "\"" << nomRouleau << "\"";
        AfficheNombreFeuilletsActuel += " est d'environ : " ;
        cout << AfficheNombreFeuilletsActuel << nombreDeFeuilletsActuel << ". " << endl;
        AppendFunctionFileString(nomInventaire, AfficheNombreFeuilletsActuel);
        AppendFunctionFileString(nomInventaire, to_string(nombreDeFeuilletsActuel));
        AppendFunctionFileString(nomInventaire, ". \n");
    }
    return 0;
}
