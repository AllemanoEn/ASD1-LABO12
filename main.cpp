/*
 -----------------------------------------------------------------------------------
 Exercice : Labo 10
 Fichier     : main.c
 Auteur(s)   : Enzo Allemano, Yohann Paulus
 Date        : 20.06.2020
 Compilateur : g++ (GCC) 9.2.0
 Brief       : Programme permettant de générer la séquence la plus courte des cases à bouger pour remettre le taquin 3x3 suivant en ordre.
 -----------------------------------------------------------------------------------
 */

#include <iostream>
#include <queue>
#include <map>
#include <stack>

using namespace std;

const string CHAINE_FINALE = "012345678";
const size_t NB_LIGNE = 3;
const size_t NB_COLONNE = 3;

/**
 * Parcours en largeur le graphe
 * @param sommet Le sommet de depart
 */
void parcourLargeur(string sommet);

/**
 * Permet d'échanger la position du 0 avec une autre position
 * @param sommetDebut Sommet ou l'on va effectuer l'échange
 * @param PositionZero Position du zero dans notre sommet
 * @param PositionEchange Position avec laquelle nous voulons echanger le zero
 * @return Le Sommet après échange
 */
string swap(string sommetDebut, size_t PositionZero, size_t PositionEchange);

/**
 * Permet de découvrir les voisins d'un sommet
 * @param sommet Sommet dont nous voulons connaitre le voisin
 * @return Un Vector de string qui contient tous les voisins du sommet
 */
vector<string> recupererVoisins(string& sommet);

/**
 * Affiche la chaîne de résolution si la solution est trouvé
 * @param sommet Debut Sommet de debut
 * @param sommetActuel Sommet actuel
 * @param map Contient les sommets et leur parents
 */
void traiter(const string& sommetDebut, string& sommetActuel, const map<string, string>& map);


int main() {
    string sommetDebut;
    cout << "Sequance initiale :  ";
    cin >> sommetDebut;
    parcourLargeur(sommetDebut);

    return EXIT_SUCCESS;
}


void parcourLargeur(string sommet){
    const string sommetDebut = sommet;

    queue<string> queue;
    map<string, string> map;
    queue.push(sommet);
    map.insert(pair<string, string>(sommet, sommet));
    while(!queue.empty()){
        sommet = queue.front();
        queue.pop();
        traiter(sommetDebut, sommet, map);
        vector<string> voisins = recupererVoisins(sommet);
        for(size_t i = 0; i < voisins.size(); ++i){
            if(!map.count(voisins[i])){
                queue.push(voisins[i]);
                map.insert(pair<string, string>(voisins[i], sommet));
            }
        }
    }
}
/*
string swap(string sommetDebut, size_t PositionZero, size_t PositionEchange){
    std::swap(sommetDebut[PositionZero], sommetDebut[PositionEchange]);
    return sommetDebut;
}
 */

vector<string> recupererVoisins(string& sommet){
    vector<string> voisins;
    size_t PositionZero = sommet.find('0');

    if(PositionZero % NB_COLONNE + 1 != 1){
        size_t PositionEchange = PositionZero-1;
        swap(sommet[PositionZero], sommet[PositionEchange]);
        voisins.push_back(sommet);
    }

    if(PositionZero % NB_COLONNE + 1 != NB_COLONNE){
        size_t PositionEchange = PositionZero+1;
        swap(sommet[PositionZero], sommet[PositionEchange]);
        voisins.push_back(sommet);
    }

    if(PositionZero / NB_LIGNE + 1 != 1){
        size_t PositionEchange = PositionZero - NB_LIGNE;
        swap(sommet[PositionZero], sommet[PositionEchange]);
        voisins.push_back(sommet);
    }

    if(PositionZero / NB_LIGNE + 1 != NB_LIGNE){
        size_t PositionEchange = PositionZero + NB_LIGNE;
        swap(sommet[PositionZero], sommet[PositionEchange]);
        voisins.push_back(sommet);
    }

    return voisins;
}

void traiter(const string& sommetDebut, string& sommetActuel, const map<string, string>& map){
    if(sommetActuel == CHAINE_FINALE){
        stack<size_t> stack;
        string parent = sommetActuel;
        while(parent != sommetDebut){
            stack.push(parent.find('0'));
            parent = map.find(sommetActuel)->second;
            sommetActuel = parent;
        }
        cout << "Séquence de résolution : ";

       while(!stack.empty()){
            cout << stack.top() << " ";
            stack.pop();
        }

    }
}