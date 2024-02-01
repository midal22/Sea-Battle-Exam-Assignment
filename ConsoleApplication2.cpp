#include <iostream>
#include <Windows.h> 
#include <cctype>
#include <conio.h>
#define N cout << endl;
using namespace std;

struct Ships
{
    int x;
    int y;
    int size;
    bool rip = false;
    int poz;
    int hit = 0;
};

void fOutput(int m, char arrL[][10], char arrR[][10]);
void fInmas(int m, char arr[][10]);
void fShip(int m, char arr[][10],bool avto, char arrL[][10],char arrR[][10], Ships sh[10]);
int fPozihin();
void fCordinats(int m, int& x, int& y, bool shot);
bool fProverca1(int saiz, int x, int y, char arr[][10], int poz,int z);
int fRandom(int a);
void fError(int m, char arrL[][10], char arrR[][10]);
bool fShot(char arr[][10],bool avto, int m, char arrL[][10],int& x,int& y,bool corect);
bool fLogica(Ships sh[10], int& x, int& y,  char arr[][10],int& xshot, int& yshot);
void fRip(Ships sh[10], char arr[][10]);
bool fTactic(int corect, int& x, int& y, char arr[][10], int& tacticShot, int& stroca);

int main()
{
    setlocale(LC_ALL, "Rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(NULL));
    const int m = 10;
    bool avto;
    char leftMargin[m][m]; // ползователь работает на этом поле
    char rightMargin[m][m]; //пк работает на этом поле
    char leftshot[m][m]; // пк видит это поле
    char rightshot[m][m];//пользовотел видит это поле

    cout << "\n\n\n";               //приветствие
    cout << "\t\t\tДобро ";
    Sleep(1000);
    cout << "пожаловать ";
    Sleep(1000);
    cout << "в \"морской бой\"\n";
    Sleep(1000);
    system("Cls");


    bool restart = false;
    do{
        fInmas(m, leftMargin);   // заполнение пустотой
        fInmas(m, rightMargin);
        fInmas(m, leftshot);
        fInmas(m, rightshot);
        fOutput(m, leftMargin, rightshot); // вывод для ползователя 

        Ships shPC[10]; // коробли пк
        Ships shME[10]; // мои корбли
        int a = 0;
        int tactic = 0;
        int menu;
        bool chec1 = false;
        do{
            cout << "Для продолжения ответи на три вопроса.";
        cout << "\n1 хотите воспользоватса автозаполнеием?";
        cout << "\n2 Хотите ли вы чтобы за вас играл копютер?";
        cout << "\n3 Хотите ли вы \"умного\" протиника?";
        do{
            cout << "\n выберите вопрос на который хотите ответить.\n";
            cin >> menu;
        } while (menu < 0 && menu > 4);
        int b1 = 0, b2 = 0, b3 = 0;

        switch (menu)
        {
        case 1:
            do
            {
                cout << "\nхотите воспользоватса автозаполнеием?";
                cout << "\t\tда/1\tнет/2\n";
                cin >> a;
            } while (a < 0 && a > 5);
            if (a == 1)
            {
                fShip(m, leftMargin, avto = true, leftMargin, rightshot, shME);//авто растановка лев поля
            }
            else
            {
                fShip(m, leftMargin, avto = false, leftMargin, rightshot, shME);
            }
            fShip(m, rightMargin, avto = true, leftMargin, rightshot, shPC);//авто растановка прав поля
            b1 = 1;
            break;

        case 2:
            do
            {
                cout << "\nХотите ли вы чтобы за вас играл копютер?";
                cout << "\t\tда/1\tнет/2\n";
                cin >> a;
            } while (a < 0 && a > 5);
            b2 = true;
            break;

        case 3:
            do
            {
                cout << "\nХотите ли вы сыграть в интеликтуальную игру?";
                cout << "\t\tда/1\tнет/2\n";
                cin >> tactic;
            } while (a < 0 && a > 5);
            b3 = true;
            break;
        }
        if (b1 == 1 && b2 == 1 && b3 == 1)
        {
            chec1 = true;
        }
    } while (chec1 == false);
        system("Cls");
        fOutput(m, leftMargin, rightshot); // вывод для ползователя 

        int xshot = 0;
        int yshot = 0;
        bool chec;
        bool corect;
        int x2 = 0, y2 = 0;
        int x1 = 0, y1 = 0;
        int KilPc = 0, KilUser = 0;
        int tacticShot = 0;
        int stroca = 0;
        do {
            KilPc = 0, KilUser = 0;
            for (int i = 0; i < 10; i++)
            {
                if (shPC[i].rip == true)
                    KilUser++;  // фраги игрока
                if (shME[i].rip == true)
                    KilPc++; // фраги пк
            }
            do {
                if (a != 1) //выстрел
                {
                    int plei = 0;
                    corect = false;
                    {
                        cout << "\n1 закончить игру";
                        cout << "\n2 начать заново";
                        cout << "\n3 стрелять";
                        cout << "\nвыберите вариант";
                        cin >> plei;
                } while (menu < 0 && menu > 4);
                        switch (plei)
                        {
                        case 1:
                                return 0;
                            break;
                        case 2:
                            restart = true;
                            break;
                        case 3:
                            chec = fShot(rightMargin, avto = false, m, rightshot, x1, y1, corect);
                            break;
                        }
                    fRip(shPC, rightshot);
                    system("Cls");
                    fOutput(m, leftMargin, rightshot); // вывод для ползователя 
                }
                else   // авто выстрел
                {
                    corect = fLogica(shPC, x1, y1, rightshot, xshot, yshot);
                    chec = fShot(rightMargin, avto = true, m, rightshot, x1, y1, corect);
                    fRip(shPC, rightshot);
                    system("Cls");
                    fOutput(m, leftMargin, rightshot);
                    Sleep(1500);
                }
            } while (chec == true);
            system("Cls");
            fOutput(m, leftMargin, rightshot);

            if (tactic == 2)
            {
                do {     // выстрел врага
                    corect = fLogica(shME, x2, y2, leftMargin, xshot, yshot);
                    chec = fShot(leftMargin, avto = true, m, leftMargin, x2, y2, corect);
                    fRip(shME, leftMargin);
                    Sleep(1500);
                    system("Cls");
                    fOutput(m, leftMargin, rightshot); // вывод для ползователя 
                } while (chec == true);
            }
            else
            {
                do {     // выстрел врага по тактике
                    corect = fLogica(shME, x2, y2, leftMargin, xshot, yshot);
                    corect = fTactic(corect, x2, y2, leftMargin, tacticShot, stroca);
                    chec = fShot(leftMargin, avto = true, m, leftMargin, x2, y2, corect);
                    fRip(shME, leftMargin);
                    Sleep(1500);
                    system("Cls");
                    fOutput(m, leftMargin, rightshot); // вывод для ползователя 
                    fOutput(m, leftshot, rightMargin); // вывод для меня
                } while (chec == true);
            }

        } while (KilPc != 10 || KilUser != 10);

        if (KilPc == 1)
        {
            cout << "Победил компютер";
            N
        }
        else
        {
            cout << "Победил пользоатель";
            N
        }
    }while (restart == true);
    return 0;
}

void fInmas(int m, char arr[][10])
{
    for (int i = 0; i <= m; i++)
    {
        for(int j = 0;j <= m; j++)
        {
            arr[i][j] = ' ';
        }
    }
}


void fOutput(int m, char arrL[][10], char arrR[][10])
{
    cout << "Ползователь\t\t\tКомпютер\n";
    for (int r = 0; r < 2; r++)
    {
        char b = 'А';
        for (int j = 0; j < m; j++)
        {
            if (b == 'Й')
                b++;
            cout << b << " ";
            b++;
        }
        cout << "\t\t";
    }
    N
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++) // вывод матрицы
        {
            cout << arrL[i][j] << " ";
        }
        cout << "\t" << i+1 << "\t";
        for (int j = 0; j < m; j++) // вывод матрицы
        {
            cout << arrR[i][j] << " ";
        }
        N
    }
}

void fShip(int m, char arr[][10], bool avto, char arrL[][10], char arrR[][10],Ships sh[10])
{
    int x = 0, y = 0;
    int a;
     bool shot = false;
     int size;
     int pieces;
     for (int i = 0; i < 10; i++)
     {
         if(i == 0)
         {   
             pieces = 1;
             sh[i].size = 4;
             while (pieces != 0)
             {
                 if (avto == true)  // кординаты авто
                 {
                     a = 10;
                     x = fRandom(a);
                     y = fRandom(a);
                     a = 2;
                     sh[i].poz = fRandom(a);
                 }
                 else                // кординаты в ручную
                 {
                     cout << "Линкор";
                     N
                     fCordinats(m, x, y, shot);
                     sh[i].poz = fPozihin();
                 }
                 sh[i].x = x;
                 sh[i].y = y;
                 size = sh[i].size;
                 if (sh[i].poz == 1)  // горизонт
                 {
                     if (fProverca1(sh[i].size, x, y, arr, sh[i].poz, x) == true)
                     {
                         for (int i = x; i < x + size; i++)
                         {
                             arr[y][i] = '#';
                         }
                         pieces--;
                     }
                     else
                     {
                         if (avto == false)
                         {
                             fError(m, arrL, arrR);
                         }
                     }
                 }
                 else
                 {
                     {   //верикаль
                         sh[i].poz = 0;
                         if (fProverca1(sh[i].size, x, y, arr, sh[i].poz, y) == true)
                         {
                             for (int i = y; i < y + size; i++)
                             {
                                 arr[i][x] = '#';
                             }
                             pieces--;
                         }
                         else
                         {
                             if (avto == false)
                             {
                                 fError(m, arrL, arrR);
                             }
                         }
                     }
                 }
             }
             //if(avto == false)
             //{
                 system("Cls");
                 fOutput(m, arrL, arrR); //вывод полей
             //}
         }

         else if (i == 1 || i == 2)
         {
             sh[i].size = 3;
             pieces = 1;
             while (pieces != 0)
             {
                 if (avto == true)  // кординаты авто
                 {
                     a = 10;
                     x = fRandom(a);
                     y = fRandom(a);
                     a = 2;
                     sh[i].poz = fRandom(a);
                 }
                 else                // кординаты в ручную
                 {
                     cout << "Кресер";
                     N
                     fCordinats(m, x, y, shot);
                     sh[i].poz = fPozihin();
                 }

                 sh[i].x = x;
                 sh[i].y = y;
                 size = sh[i].size;
                 if (sh[i].poz == 1)
                 {
                     if (fProverca1(sh[i].size, x, y, arr, sh[i].poz, x) == true)
                     {
                         for (int i = x; i < x + size; i++)
                         {
                             arr[y][i] = '#';
                         }
                         pieces--;
                     }
                     else
                     {
                         if (avto == false)
                         {
                             fError(m, arrL, arrR);
                         }
                     }
                 }
                 else
                 {   //верикаль
                     sh[i].poz = 0;
                     if (fProverca1(sh[i].size, x, y, arr, sh[i].poz, y) == true)
                     {
                         for (int i = y; i < y + size; i++)
                         {
                             arr[i][x] = '#';
                         }
                         pieces--;
                     }
                     else
                     {
                         if (avto == false)
                         {
                             fError(m, arrL, arrR);
                         }
                     }
                 }
                 //if (avto == false)
                 //{
                     system("Cls");
                     fOutput(m, arrL, arrR); //вывод полей
                 //}
             }
         }

         else if (i >= 3 && i <= 5)
         {
             sh[i].size = 2;
             pieces = 1;
             while (pieces != 0)
             {
                 if (avto == true)  // кординаты авто
                 {
                     a = 10;
                     x = fRandom(a);
                     y = fRandom(a);
                     a = 2;
                     sh[i].poz = fRandom(a);
                 }
                 else                // кординаты в ручную
                 {
                     cout << "Фрегат";
                     N
                     fCordinats(m, x, y, shot);
                     sh[i].poz = fPozihin();
                 }

                 sh[i].x = x;
                 sh[i].y = y;
                 size = sh[i].size;
                 if (sh[i].poz == 1)
                 {
                     if (fProverca1(sh[i].size, x, y, arr, sh[i].poz, x) == true)
                     {
                         for (int i = x; i < x + size; i++)
                         {
                             arr[y][i] = '#';
                         }
                         pieces--;
                     }
                     else
                     {
                         if (avto == false)
                         {
                             fError(m, arrL, arrR);
                         }
                     }
                 }
                 else
                 {   //верикаль

                     sh[i].poz = 0;
                     if (fProverca1(sh[i].size, x, y, arr, sh[i].poz, y) == true)
                     {
                         for (int i = y; i < y + size; i++)
                         {
                             arr[i][x] = '#';
                         }
                         pieces--;
                     }
                     else
                     {
                         if (avto == false)
                         {
                             fError(m, arrL, arrR);
                         }
                     }
                 }
                 //if (avto == false)
                 //{
                     system("Cls");
                     fOutput(m, arrL, arrR); //вывод полей
                 //}
             }
         }

         else if (i >= 6 && i <= 9)
         {
             sh[i].size = 1;
             pieces = 1;
             while (pieces != 0)
             {
                 if (avto == true)  // кординаты авто
                 {
                     a = 10;
                     x = fRandom(a);
                     y = fRandom(a);
                     sh[i].poz = 1;
                 }
                 else                // кординаты в ручную
                 {
                     cout << "шлюп";
                     N
                     fCordinats(m, x, y, shot);
                     sh[i].poz = 1;
                 }

                 sh[i].x = x;
                 sh[i].y = y;
                 if (sh[i].poz == 1)
                 {
                     if (fProverca1(sh[i].size, x, y, arr, sh[i].poz, x) == true)
                     {
                         arr[y][x] = '#';
                         pieces--;
                     }
                     else
                     {
                         if (avto == false)
                         {
                             fError(m, arrL, arrR);
                         }
                     }
                 }

                 //if (avto == false)
                 //{
                     system("Cls");
                     fOutput(m, arrL, arrR); //вывод полей
                 //}
             }
         }
     }
     if (avto == true)
     {
         system("Cls");
         fOutput(m, arrL, arrR); //вывод полей
     }
}

int fPozihin()
{
    cout << "№1 горизонтально.\n";
    cout << "№2 вертикально.\n";
    cout << "Введите номер варианта как хотите размистить корабль.\n";
    int a;
    cin >> a;
    return a;
}


void fCordinats(int m, int& x,int& y,bool shot)
{
    if(shot == true)
    {
        cout << "\nВведите кординаты куд хотите выстрелить";
    }
    else
    {
        cout << "\nВведите кординаты коробля";
    }
    char z;
    do
    {
    cout << "\nВведите букву:\t";
    cin >> z;
    z = (char)toupper(z);
    char B = 'А';
    for (int j = 0; j < m; j++)
    {
        if (B == 'Й')
        {
            B++;
        }
        if (z == B)
        {
            x = j;
            break;
        }
        B++;
    }
    } while (x < 0 && x >= 10);
    do {
        cout << "\nВведите цифру:\t";
        cin >> y;
        y -= 1;
    } while (y < 0 && y >= 10);
}


bool fProverca1(int saiz, int x, int y, char arr[][10], int poz, int z)
{
    int counter = 0;
    bool flag = true;
    int a1 = 1, a = 1, a2 = 0;  // вертикаль
    if (x == 0)
    {
        a = 0;
        a2 = 1;
    }
    if (x == 9)
        a1 = 0;
    int c = 1, c1 = 1, c2 = 0;  //горизонт
    if (y == 0)
    {
        c1 = 0;
        c2 = 1;
    }
    //if (y + saiz + c1 + c == 11)
      //  c = 0;
   
        saiz -= 1;
    if (1 == poz) //горизонт размещение
    {
        for (int i = y - c1; i < y + c1 + c + c2; i++) // вертикаль + лево + парво
        {
            for (int j = x - a; j <= x + saiz + a1; j++) //горизонт размер + лево + парво
            {
                if (z + saiz >= 10)
                    flag = false;
                if (arr[i][j] != ' ' || flag == false)
                    return false;
                else
                {
                    //arr[i][j] = '-';
                    counter++;
                }
            }
        }
    }
    else ////вертикалное размещение
    {
        for (int j = x - a; j < x + a2 +a1 + a; j++) // вертикаль + лево + парво
        {
            for (int i = y - c1; i <= y + saiz + c; i++) //горизонт размер + лево + парво
            {
                if (z + saiz >= 10)
                    flag = false;
                if (arr[i][j] != ' ' || flag == false)
                    return false;
                else
                {
                    //arr[i][j] = '-';
                    counter++;
                }
            }
        }
    }
    if (counter > 1)
                return true;
}


int fRandom(int a)
{
        return rand() % a;
}

void fError(int m, char arrL[][10], char arrR[][10])
{
    system("Cls");
    fOutput(m, arrL, arrR); //вывод полей
    cout << "По даным коадинатам нелзя разместиь этот тип коробля\n";
    cout << "Для продолжения нажмите любую клавишу\n";
    _getch();
}

bool fShot(char arr[][10], bool avto, int m, char arr2[][10],int& x, int& y,bool corect)  //arr проверяемое  arr2 изменяемое
{
    bool shot = true;

        if(avto == true && corect == false)
        {
            int a = 10;
            x = fRandom(a);
            y = fRandom(a);
        }
        else if(avto == false && corect == false)
        {
            fCordinats(m, x, y, shot);
        }
        if (arr[y][x] == ' ')
        {
            arr2[y][x] = '*';
            return false;
        }
        else if (arr[y][x] != '*')
        {
            arr2[y][x] = '+';
            return true;
        }
}

bool fLogica(Ships sh[10], int& x,int& y, char arr[][10],int& xshot,int& yshot)
{
    int j = -1;
    bool corect = false;
    for (int i = 0; i < 10; i++)
    {
        sh[i].hit = 0;
        if (sh[i].poz == 1)
        {
            for (int r = sh[i].x; r < sh[i].x + sh[i].size; r++)  //горизонт
            {
                if (arr[sh[i].y][r] == '+')
                {
                    sh[i].hit++;
                }
            }
        }
        else
        {
            for (int r = sh[i].y; r < sh[i].y + sh[i].size; r++)  //вертикаль
            {
                if (arr[r][sh[i].x] == '+')
                {
                    sh[i].hit++;
                }
            }
        }
        if (sh[i].rip == false && sh[i].hit > 0)
        {
            j = i;
            corect = true;
            break;
        }
        else
        {
            corect = false;
        }
    }

        if (sh[j].hit > 1)
        {
            xshot = 0;
            yshot = 0;
            if (sh[j].poz == 1) //горизонт
            {
                if (arr[y][x+1] == '#')
                {
                    x += 1;
                }
                else if (arr[y][x+1] == '+')
                {
                    x += sh[j].hit;
                }
                else if (arr[y][x+1] == '*' || arr[y][x+1] == ' ')
                {
                    x -= sh[j].hit;
                }
            }
            else
            {
                if (arr[y + 1][x] == '#')
                {
                    y += 1;
                }
                else if(arr[y + 1][x] == '+')
                {
                        y += sh[j].hit;
                }
                else if(arr[y+1][x] == '*' || arr[y+1][x] == ' ' )
                {
                    y -= sh[j].hit;
                }
            }
        }
   
    if (sh[j].hit == 1 && sh[j].hit < 2)
    {
        if (arr[x - 1][y] != '+'&& arr[x - 1][y] != '*' && x != 0 && xshot == 0)   //x--
        {
           
                x -= 1;
                xshot++;
        }
        else if (arr[x + 1][y] != '+' && arr[x + 1][y] != '*' && x != 9 && xshot <= 1) //x++
        {
            if(xshot == 1)
            {
                x += 2;
                xshot++;
            }
            else
            {
                    x += 1;
                    xshot += 2;
            }
        }
        else if (arr[x-1][y - 1] != '+' && arr[x - 1][y-1] != '*' && y != 0 && yshot == 0)//y--
        {
            x -= 1;
            y -= 1;
            yshot++;
        }
        else if (arr[x][y + 1] != '+' && arr[x][y + 1] != '*' && y != 9 && yshot <= 1)//y++
        {
            if (yshot == 1)
            {
                y += 2;
                yshot++;
            }
            else
            {
                y += 1;
                yshot += 2;
            }
        }
    }

    if (corect == true)
        return corect;
    else
        return false;
}


void fRip(Ships sh[10], char arr[][10])  //arr проверяемое
{
    int l = -1;
    for (int i = 0; i < 10; i++)
    {
        sh[i].hit = 0;
        if (sh[i].poz == 1)
        {
            for (int j = sh[i].x; j < sh[i].x + sh[i].size; j++)  //горизонт
            {               
                //arr[sh[i].y][j] = '@';
                if (arr[sh[i].y][j] == '+')
                    sh[i].hit++;
            }
        }
        else
        {
            for (int j = sh[i].y; j < sh[i].y + sh[i].size; j++)  //вертикаль
            {
                //arr[j][sh[i].x] = '@';
                if (arr[j][sh[i].x] == '+')
                    sh[i].hit++;
            }
        }
        if (sh[i].rip == false && sh[i].hit > 0)
        {
            l = i;
            break;
        }
    }
        if (sh[l].hit == sh[l].size)
        {
            sh[l].rip == true;

            int a1 = 1, a = 1, a2 = 0;  // вертикаль
            if (sh[l].x == 0)
            {
                a = 0;
                a2 = 1;
            }
            if (sh[l].x == 9)
                a1 = 0;
            int c = 1, c1 = 1, c2 = 0;  //горизонт
            if (sh[l].y == 0)
            {
                c1 = 0;
                c2 = 1;
            }
            if (sh[l].y + sh[l].size + c1 + c == 11)
                c = 0;

            sh[l].size -= 1;

            if (1 == sh[l].poz) //горизонт размещение
            {
                for (int r = sh[l].y - c1; r < sh[l].y + c1 + c + c2; r++) // вертикаль + лево + парво
                {
                    for (int j = sh[l].x - a; j <= sh[l].x + sh[l].size + a1; j++) //горизонт размер + лево + парво
                    {
                        if (arr[r][j] != '+')
                            arr[r][j] = '*';
                    }
                }
                sh[l].rip = true;
            }
            else ////вертикалное размещение
            {
                for (int j = sh[l].x - a; j < sh[l].x + a2 + a1 + a; j++) // вертикаль + лево + парво
                {
                    for (int r = sh[l].y - c1; r <= sh[l].y + sh[l].size + c; r++) //горизонт размер + лево + парво
                    {
                        if (arr[r][j] != '+')
                            arr[r][j] = '*';
                    }
                }
                sh[l].rip = true;
            }
        }
}

bool fTactic(int corect, int& x, int& y, char arr[][10], int& tacticShot,int& stroca)
{
    if (corect == false)
    {
        if (arr[stroca][3] != '+' && arr[stroca][3] != '*' && tacticShot == 0)   //1
        {

            x = 3;
            y = stroca;
            tacticShot++;
        }
        else if (arr[stroca][7] != '+' && arr[stroca][7] != '*' && tacticShot == 1)   //1

        {
            x = 7;
            tacticShot++;
        }
        else if (arr[stroca+1][2] != '+' && arr[stroca+1][2] != '*' && tacticShot == 2) //2
        {
            x = 2;
            y = stroca+1;
            tacticShot++;
        }
        else if (arr[stroca][6] != '+' && arr[stroca][6] != '*' && tacticShot == 3) //2
        {
            x = 6;
            y = stroca;
            tacticShot++;
        }
        else if (arr[stroca+1][0] != '+' && arr[stroca+1][0] != '*' && tacticShot == 4)//3
        {
            x = 0;
            y = stroca+1;
            tacticShot++;
        }
        else if (arr[stroca][x +4] != '+' && arr[stroca][x+4] != '*' && tacticShot <= 6)//3
        {
            x += 4;
            y = stroca;
            tacticShot++;
        }
        else if (arr[stroca+1][1] != '+' && arr[stroca+1][1] != '*' && y != 9 && tacticShot == 7)//4
        {
            x = 1;
            y = stroca+1;
            tacticShot++;
        }
        else if (arr[stroca][x+4] != '+' && arr[stroca][x+4] != '*' && y != 9 && tacticShot <= 9)
        {
            x += 4;
            y = stroca;
            tacticShot++;
        }
        return true;
    }
    else
    {
        return true;
    }
}
