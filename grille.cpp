#include "grille.h"

bool Grille::JustMoved = false;
int Grille ::score = 0;

Grille::Grille(int lignes, int colonnes)
{
    h = lignes;
    w = colonnes;

    TAB = new int*[h];
    for (int i = 0; i < h; i++){
        TAB[i] = new int[w];
        for (int j = 0; j < w; j++){
            TAB[i][j] = 0;
        }
    }
    SAVE = new int*[h];
    for (int i = 0; i < h; i++){
        SAVE[i] = new int[w];
        for (int j = 0; j < w; j++){
            SAVE[i][j] = 0;
        }
    }
}

Grille::~Grille(){
    if (TAB != NULL){
        for (int i = 0; i < h; i++){
            delete [] TAB [i];
        }
        delete TAB;
        TAB = NULL;
    }

    if (SAVE != NULL){
        for (int i = 0; i < h; i++){
            delete [] SAVE [i];
        }
        delete SAVE;
        SAVE = NULL;
    }
}

void Grille::Insert(){
    int zeros = 0;
    for (int i = 0; i < h; i++){    //On compte le nombre de 0
        for (int j =0; j < w; j++){
            if (TAB[i][j] == 0){
                zeros++;
            }
        }
    }
    if (zeros == 0) return;


    int n = rand() % zeros; // On choisit un 0 à remplacer
    int val;
    if (rand()%10 >0){
        val = 2;
    }
    else{
        val = 4;
    }

    bool done = false;
    int k = 0;
    while (!done){
        if (TAB[k/w][k%w] == 0){
            if (k == n){
                done = true;
//                cout << "ligne :" << k/w << " " << "colonne :" << k % w << endl;
//                cout << k << endl;
                TAB[k/w][k%w] = val;
            }
            k++;
        }
        else{
            n++;
            k++;
        }
    }
}


ostream& operator<< (ostream& sortie, Grille& G){

    sortie << endl;
    for(int i=0;i<G.h;i++){
        for(int j=0;j<G.w;j++){
            sortie << G.TAB[i][j] << " ";
        }
        sortie << endl;
    }
    sortie << endl;
    return sortie;
}

int Grille::Get(int i, int j){
    return TAB[i][j];
}

void Grille::ChangerLigne(int i, vector<int> v){
    for (int j = 0; j < w; j++){
        TAB[i][j] = v[j];
    }
}

void Grille::ChangerCol(int j, vector<int> v){
    for (int i = 0; i < h; i++){
        TAB[i][j] = v[i];
    }
}

vector<int> Swipe(vector<int> v){   // Cette fonction réalise le Swipe à gauche d'un vecteur.
    vector<int> copie = v;
    int len = v.size();

    int compteur = 0;

    for (int i =0 ; i < len ; i++){
        if (v[i] != 0) compteur++;
    }
    if (compteur == 0) return v;

    // On colle tous les éléments non nuls
    int k = 0;
    for (int i = 0; i < len ; i++){
        if (v[k] == 0) {
            v.erase(v.begin() + k);
            v.push_back(0);
        }
        else{
            k++;
        }

    }

    int j = 0;
    while (j < compteur - 1){
        if (v[j] == v[j+1]){
            v[j] = 2 * v[j];
            Grille::score += v[j];
            v.erase(v.begin() + j + 1);
            v.push_back(0);
            compteur--;
        }
        j++;
    }
    if (copie != v){
        Grille::JustMoved = true;
    }
    return v;
}

vector<int> Grille::ExtractLigne(int i){
    vector<int> v;
    for (int j = 0; j < w ; j++){
        v.push_back(TAB[i][j]);
    }
    return v;
}

vector<int> Grille::ExtractCol(int j){
    vector<int> v;
    for (int i = 0; i < h ; i++){
        v.push_back(TAB[i][j]);
    }
    return v;
}

void Grille::SwipeGauche(){
    for (int i = 0; i < h; i++){
        ChangerLigne(i, Swipe(ExtractLigne(i)));
    }
    if (JustMoved){
        Insert();
        vals = mat2List();
        emit Swiped();
        JustMoved = false;
        Undone = false;
    }
}

void Grille::SwipeDroite(){
    for (int i = 0; i < h; i++){
        vector<int> ligne = ExtractLigne(i);
        reverse(ligne.begin(),ligne.end());
        ligne = Swipe(ligne);
        reverse(ligne.begin(),ligne.end());
        ChangerLigne(i, ligne);
    }
    if (JustMoved){
        Insert();
        vals = mat2List();
        emit Swiped();
        JustMoved = false;
        Undone = false;
    }


}

void Grille::SwipeHaut(){
    for (int j = 0; j < w; j++){
        ChangerCol(j, Swipe(ExtractCol(j)));
    }
    if (JustMoved){
        Insert();
        vals = mat2List();
        emit Swiped();
        JustMoved = false;
        Undone = false;
    }


}

void Grille::SwipeBas(){
    for (int j = 0; j < h; j++){
        vector<int> col = ExtractCol(j);
        reverse(col.begin(),col.end());
        col = Swipe(col);
        reverse(col.begin(),col.end());
        ChangerCol(j, col);
    }
    if (JustMoved){
        Insert();
        vals = mat2List();
        emit Swiped();
        JustMoved = false;
        Undone = false;
    }
}

bool Grille::IsOver() {
    bool over = true;
    for (int i = 0; i < h  ; i++) {
        for (int j = 0 ; j < w ; j++) {
            if (TAB[i][j] == 0) {
                over = false;
                return over;
            }
        }
    }

    for (int i = 0; i < h  ; i++) {
        for (int j = 0 ; j < w ; j++) {
            if (i != h - 1 && j != w - 1) {
                if (TAB[i][j] == TAB[i][j + 1] || TAB[i][j] == TAB[i + 1][j]) {
                    over = false;
                }
            }
            else if (i == h - 1 && j != w - 1) {
                if (TAB[i][j] == TAB[i][j + 1]) {
                    over = false;
                }
            }
            else if (j == w - 1 && i != h - 1) {
                if (TAB[i][j] == TAB[i + 1][j]) {
                    over = false;
                }

            }
        }
    }
    return over;
}

void Grille::AddScore(int n) {
    Grille::score += n;
}

int Grille::get_score() {
    return Grille::score;
}


void Grille::Tour_inc() {
    tour++;
}

void Grille::Tour_dec() {
    tour--;
}

void Grille::sauvegarde() {
    for (int i = 0; i < h; i++){
        SAVE[i] = new int[w];
        for (int j = 0; j < w; j++){
            SAVE[i][j] = TAB[i][j];
        }
    }
    save_score = Grille::score;
}

void Grille::load_sauvegarde() {
    for (int i = 0; i < h; i++){
        TAB[i] = new int[w];
        for (int j = 0; j < w; j++){
            TAB[i][j] = SAVE[i][j];
        }
    }
    vals = mat2List();
    emit Swiped();
    Undone = true;
    Grille::score = save_score;
}


bool Grille::get_Undone(){
    return Undone;
}

void Grille::change_Undone() {
    if (Undone) Undone = false;
    else Undone = true;
}

QList<int> Grille::getVals(){
    return vals;
}


QList<int> Grille::mat2List(){

    QList<int> s;

    for (int i=0;i<h;i++){
        for (int j=0;j<w;j++){
            s << TAB[i][j];
        }
    }


    return s;
}

void Grille::start(){

    sauvegarde();
    vals = mat2List();
    emit Swiped();

}

void Grille::restart(){

    TAB = new int*[h];
    for (int i = 0; i < h; i++){
        TAB[i] = new int[w];
        for (int j = 0; j < w; j++){
            TAB[i][j] = 0;
        }
    }
    SAVE = new int*[h];
    for (int i = 0; i < h; i++){
        SAVE[i] = new int[w];
        for (int j = 0; j < w; j++){
            SAVE[i][j] = 0;
        }
    }

    srand(time(0));

    for (int i = 0;i < 2; i++){
        Insert();
    }

    start();

}

