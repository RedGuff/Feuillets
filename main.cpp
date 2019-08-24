#include <iostream>
using namespace std;

int main()
{
    cout << "Ceci vous donne le nombre de feuillets dans un rouleau ouvert, en fonction de ses dimensions." << endl;

  // Référence ?
    // Fichier ?
    float diametreVide_cm = 5;
    float diametrePlein_cm = 10;
    int nombreDeFeuilletsQuandPlein = 1000;
    float diametreActuel_cm = 6;
//    Rappel de formule : surface d'un anneau en 2D : pi * (R2 − r2)
// https://calculis.net/aire/anneau
  //    La taille dess feuillets (longueur et gosseur) ne change pas. Le rapport entre le nombe de feuillets  actuels et le nombre de feuillets total est donc le rapport des surfaces de la tranche du rouleau actuel sur le nombre de feuillets d'un rouleau plein.
 int nombreDeFeuilletsActel = nombreDeFeuilletsQuandPlein * ( diametreVide_cm - diametreActuel_cm) / (diametreVide_cm - diametrePlein_cm); // Simplification des Pis ; rapport des rayons = rapport des diaètres.
   cout << "Le nombre de feuillets est de : "  << nombreDeFeuilletsActel << ". "<< endl;
    return 0;
}
