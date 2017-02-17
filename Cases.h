typedef struct t_listeCase CelluleCase;
typedef CelluleCase *ListeCase;

ListeCase initListeCase(void);

int testListeCaseVide(ListeCase l);

ListeCase constructeurListeCase(Case *d, ListeCase l);

Case* getValeurListeCase(ListeCase l);

ListeCase getSuivantListeCase(ListeCase l);

void liberationCase(CelluleCase *c);

void liberationListeCase(ListeCase l);

int estPresentDansListeCase(Case *c, ListeCase l);

ListeCase concatenationListeCase(ListeCase l, ListeCase m);

void supprimeElementListeCase(Case *c, ListeCase *l);
