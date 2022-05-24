#ifndef ladje_h
#define ladje_h

void ladje_init(int morje[10][10], int nasprotnikovo_morje[10][10]);
void ladje_postavi(int morje[10][10]);
void ladje_ugibaj(int koordinata[2], int nasprotnikovo_morje[10][10]);
void ladje_obnovi(int koordinata[2], int zadeta);
void ladje_nasprotnik(int koordinata[2]);

#endif /* ladje_h */
