#ifndef GRILLE_H
#define GRILLE_H

#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <QObject>

using namespace std;

class Grille : public QObject
{

    Q_OBJECT
public:
    Grille(int lignes, int colonnes);
    ~Grille();
    void Insert();
    friend ostream& operator<< (ostream& sortie, Grille& G);
    int Get(int i, int j);
    void ChangerLigne(int i, vector<int> v);
    void ChangerCol(int j, vector<int> v);
    friend vector<int> Swipe(vector<int> v);
    vector<int> ExtractLigne(int i);
    vector<int> ExtractCol(int j);
    Q_INVOKABLE void SwipeGauche();
    Q_INVOKABLE void SwipeDroite();
    Q_INVOKABLE void SwipeHaut();
    Q_INVOKABLE void SwipeBas();
    Q_INVOKABLE bool IsOver();

    void AddScore(int n);
    Q_INVOKABLE int get_score();
    static bool JustMoved;
    static int score;

    void Tour_inc();
    void Tour_dec();

    Q_INVOKABLE void sauvegarde();
    Q_INVOKABLE void load_sauvegarde();
    Q_INVOKABLE bool get_Undone();
    void change_Undone();

    QList<int> getVals();
    QList<int> mat2List();

    void start();
    Q_INVOKABLE void restart();

    Q_PROPERTY(QList<int> tab READ getVals NOTIFY Swiped);

signals:

    void Swiped();

private:
    int h,w; // height and width
    int **TAB = NULL;
    int tour = 0;
    int **SAVE = NULL;
    int Nb_sauvegarde = 3;
    bool Undone = false;
    int save_score;
    QList<int> vals;
};

#endif // GRILLE_H
