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
    string lgg = "";  // Language.

    ifstream fileLgg("lgg.txt", ios::in);  // What language?
    if(!fileLgg) { // No file.
        lgg = "fr.lgg";
    } else {
        while (lgg == "") {
            getline(fileLgg, lgg);
        }
        fileLgg.close();
        if (lgg == "") { // Empty file...
            lgg = "fr.lgg";
        }
    }
// clog << lgg  << endl; // Test ok.
string howMany = "How many?";
string tBadValue = "A good number!";
    string unityIs = "Unité : ";
    string inUnity = "En ";
    string titre = "           Logiciel de comptage de feuillets.";
    cout << titre << endl;
    cout << "" << endl;
    string intro1 = "Je vous donne approximativement le nombre de feuillets dans un rouleau ouvert, \nen fonction de ses dimensions.";
    cout << intro1 << endl;
    string intro2 = "C'est approximatif : \nil est possible de mesurer quelques tours de spirales en plus ou en moins.";
    cout << intro2 << endl;
    string intro3 = "Cela vous aidera pour un contexte d'inventaire. \nJ'enregistre donc le bilan dans un fichier d'inventaire.";
    cout << intro3 << endl;
    string intro4 = "Vous pouvez vous exprimer en mm, en cm ou autrement, cela n'a aucune importance,\nmais vous devrez conserver ce choix durant tout le calcul de cet objet.";
    cout << intro4 << endl;
    string nomInventaire = "";
    string nomRouleau = " ";

    string intro5 = "Quel est l'inventaire que je dois continuer, avec son chemin facultatif ?";
    cout << intro5 << endl;
    string intro6 = "Un fichier vide de ce nom sera fait si besoin, et j\'y ajouterai l'extention \n\".txt\".";
    cout << intro6 << endl;
    string noEmpty = "Pas de nom vide, svp.";

    while (nomInventaire=="") {
        cout << noEmpty << endl;
        getline(cin, nomInventaire);
    }
    nomInventaire = nomInventaire + ".txt"; // si existe : lecture et non redemande !
    string remarque = " ";
    while(remarque != "") {
        string remark1 = "Ajoutez une ligne de remarques au fichier d'inventaire.";
        cout << remark1 << endl;
        string remark2 = "Remarques possibles : date, heure, personnes participantes, lieu...";
        cout << remark2 << endl;
        string remark3 = "(Validez une ligne vide par ENTER pour poursuivre, sinon on vous reproposera une autre ligne de remarques.)";
        cout << remark3 << endl;
        getline(cin, remarque);
        AppendFunctionFileString(nomInventaire, remarque + "\n");
    }
    bool start = true;
    while(true) {
        string nombreRouleau = "";
        string NameRoll1 = "Nom de l\'objet, du rouleau";
        cout << NameRoll1;
        string next = " suivant";
        if (!start) {
            cout << next;
        }
        string NameRoll2 = " ?";
        cout << NameRoll2 << endl;
        string emptyToQuit = "(Validez un nom vide par ENTER pour quitter.) ";
        cout << emptyToQuit << endl;
        getline(cin, nomRouleau);
        if (nomRouleau=="") {
            break;
        }
        start = false;
        string howManyRoll1 = "Combien de rouleaux entiers de ";
        string howManyRoll2 = " avez-vous ? ";
        cout << howManyRoll1 << nomRouleau << howManyRoll2;
        getline(cin, nombreRouleau);
        string textNbRouleaux1 = "Il y a ";
        string textNbRouleaux2 = " rouleau(x) entier(s) de ";
        string textNbRouleaux = textNbRouleaux1 + nombreRouleau  + textNbRouleaux2 + nomRouleau + " ";
        AppendFunctionFileString(nomInventaire, textNbRouleaux);
        string unity = "";
        float diametreVide  = 0;
        float diametrePlein = 0;
        int nombreDeFeuilletsQuandPlein = 0;
        if (!exists_test1(nomRouleau+".txt")) {
            string unknownObject = "Je ne connais pas cet objet.";
            cout << unknownObject << endl;
            string whatUnity = "Quelle est son unité ? (cm, mm... ?) ";
            cout << whatUnity;
            getline(cin, unity);
            AppendFunctionFileString(nomRouleau+".txt", unity+"\n");

            cout << inUnity << unity << ", ";
            string whatIsEmptyDiameter = "quel est son diamètre vide ?";
            diametreVide = inputNb(1000000, 0, whatIsEmptyDiameter);
            string nomRouleau_txt = nomRouleau+".txt";
            AppendFunctionFileString(nomRouleau_txt, to_string(diametreVide)+"\n");
            cout << inUnity << unity << ", ";
            string whatIsFullDiameter = "quel est son diamètre plein ?";
            diametrePlein = inputNb(1000000, diametreVide, whatIsFullDiameter);
            AppendFunctionFileString(nomRouleau_txt, to_string(diametrePlein)+"\n");
            string numberFull = "Quel est le nombre de feuillets d'un rouleau plein ?";
            nombreDeFeuilletsQuandPlein = inputNb(1000000, 0, numberFull);
            AppendFunctionFileString(nomRouleau_txt, to_string(nombreDeFeuilletsQuandPlein)+"\n");
        } else {
            string IKnow = "Je connais cet objet, il est ainsi :";
            cout << IKnow << endl;
            ifstream fichier(nomRouleau+".txt");
            if (fichier) {
                getline(fichier, unity);
                cout << unityIs << unity << endl;
                fichier >> diametreVide;
                string emptyDiameterIs = "le diamètre vide est : ";
                cout << emptyDiameterIs << diametreVide << endl;
                fichier >> diametrePlein;
                string fullDiameterIs = "le diamètre plein est : ";
                cout << fullDiameterIs << diametrePlein << endl;
                fichier >> nombreDeFeuilletsQuandPlein;
                string numberOfSheetsWhenFullIs = "Nombre de feuillets quand il est plein : ";
                cout << numberOfSheetsWhenFullIs << nombreDeFeuilletsQuandPlein << endl << endl;
                fichier.close();
            } else {
                string noRead = "Impossible de lire le fichier : ";
                string detected = ", que j\'ai pourtant détecté !";
                cerr << noRead << nomRouleau+".txt" << detected << endl;
                string closeRestart = "Fermez tout et recommencez !";
                cerr << closeRestart << endl;
            }
        }
        float diametreActuel = 0;
        cout << inUnity << unity << ", ";
        string askDiameterNow = "quel est le diamètre actuel ?";
        diametreActuel = inputNb(diametrePlein, diametreVide, askDiameterNow);
        // Rappel de formule : surface d'un anneau en 2D : pi * (R^2 - r^2)
        // https://calculis.net/aire/anneau
        int nombreDeFeuilletsActuel = nombreDeFeuilletsQuandPlein * (diametreVide - diametreActuel) / (diametreVide - diametrePlein);  // Simplification des Pis ; rapport des rayons = rapport des diamètres.
        string AfficheNombreFeuilletsActuel1 = "et en plus, le nombre de feuillets du rouleau partiel de ";
        // cout << "Le nombre de feuillets de ";
        // iout (nomRouleau); // Que Linux ?

//   cout << "\"" << nomRouleau << "\"";
        string AfficheNombreFeuilletsActuel2 = " est d'environ : " ;
        string AfficheNombreFeuilletsActuel = AfficheNombreFeuilletsActuel1 + nomRouleau + AfficheNombreFeuilletsActuel2 + to_string(nombreDeFeuilletsActuel) + ".";
        cout << AfficheNombreFeuilletsActuel;
        AppendFunctionFileString(nomInventaire, AfficheNombreFeuilletsActuel);
       // AppendFunctionFileString(nomInventaire, to_string(nombreDeFeuilletsActuel));
        AppendFunctionFileString(nomInventaire, "\n");
        cout << "" << endl;
    }
    return 0;
}
