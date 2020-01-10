//
// Created by vladimir on 19.12.2019.
//

#include "FastAlgoritmh.h"
#define DEBUG_MODE 1

extern int p[1000], r[3][1000];

string mult(string x, string y) {
    /*
     * Если однорязрядные, то выводим, умножаем и заканчиваем
     */
    if (x.length() == 1 && y.length() == 1) {
        if(DEBUG_MODE)cout << x << " x " << y << endl;
        p[1]++;
        return to_string(atoi(x.c_str()) * atoi(y.c_str()));
    }
    if (x[0] == '0' && y[0] == '0') {
        while (x[0] == '0') {
            x = x.substr(1, x.length());
        }
        while (y[0] == '0') {
            y = y.substr(1, y.length());
        }
    }

    /*
     * Находим наибольшее число и подстраиваемся под него
     */
    int len = x.length() > y.length() ? x.length() : y.length();
    while (len > x.length()) {
        x = '0' + x;
    }
    while (len > y.length()) {
        y = '0' + y;
    }
    p[len]++;
    if(DEBUG_MODE)cout << x << " x " << y << endl;

    string  a = x.substr(0, len / 2), // Раскладываем числа
            b = x.substr(len / 2, len),
            c = y.substr(0, len / 2),
            d = y.substr(len / 2, len);

    /*
     * Запоминаем разрядность чисел
     */
    int n = len;

    if (n % 2) {
        n++;
    }
    if(DEBUG_MODE)cout << "n = " << n << endl;
    int k = n / 2;

    while (a[0] == '0' && a.length() > 1) {
        a = a.substr(1, a.length());
    }
    while (b[0] == '0' && b.length() > 1) {
        b = b.substr(1, b.length());
    }
    while (c[0] == '0' && c.length() > 1) {
        c = c.substr(1, c.length());
    }
    while (d[0] == '0' && d.length() > 1) {
        d = d.substr(1, d.length());
    }

    if(DEBUG_MODE)cout << a << " * 10^" << k << " + " << b << endl;
    if(DEBUG_MODE)cout << c << " * 10^" << k << " + " << d << endl;

    string sumAB = sum(a, b), sumCD = sum(c, d);
    if(DEBUG_MODE)cout << "(" << sumAB << ") * (" << sumCD << ")" << endl;
    string u;
    if (sumAB.length() > a.length() || sumCD.length() > c.length()) {
        /*
         * Находим наибольшее число и подстраиваемся под него
         */
        len = sumAB.length() > sumCD.length() ? sumAB.length() : sumCD.length();
        while (len > sumAB.length()) {
            sumAB = '0' + sumAB;
        }
        while (len > sumCD.length()) {
            sumCD = '0' + sumCD;
        }
        /*
         * Берем первые цифры для проверки на переполнение
         */
        int a1 = sumAB[0] - '0', b1 = sumCD[0] - '0';

        if (a1 == 1 && b1 == 1) {
            r[2][len]++;
        } else if ((a1 == 1 && b1 == 0) || (b1 == 1 || a1 == 0)) {
            r[1][len]++;
        }
        /*
         * Находим наибольшее число и подстраиваемся под него
         */
        len = n;
        while (len > sumAB.length()) {
            sumAB = '0' + sumAB;
        }
        while (len > sumCD.length()) {
            sumCD = '0' + sumCD;
        }
        if(DEBUG_MODE)cout << "a1 u b1 ~ " << a1 << " " << b1 << endl;
        /*
         * Раскладываем числа
         */
        string  asub = sumAB.substr(0, len / 2),
                bsub = sumAB.substr(len / 2, len),
                csub = sumCD.substr(0, len / 2),
                dsub = sumCD.substr(len / 2, len);

        while (asub[0] == '0' && asub.length() > 1) {
            asub = asub.substr(1, asub.length());
        }
        while (bsub[0] == '0' && bsub.length() > 1) {
            bsub = bsub.substr(1, bsub.length());
        }
        while (csub[0] == '0' && csub.length() > 1) {
            csub = csub.substr(1, csub.length());
        }
        while (dsub[0] == '0' && dsub.length() > 1) {
            dsub = dsub.substr(1, dsub.length());
        }

        if(DEBUG_MODE)cout << asub << " * 10^" << k << " + " << bsub << endl;
        if(DEBUG_MODE)cout << csub << " * 10^" << k << " + " << dsub << endl;

        if(DEBUG_MODE)cout << a1 << " * " << b1 << " * 10^" << n << " + ("
             << a1 << " * " << dsub << " + " << b1 << " * " << bsub << ") * 10^" << k
             << " + " << bsub << " * " << dsub << endl;

        string middle = multWithPow(sum(multWithNum(dsub, a1), multWithNum(bsub, b1)), k);
        string begin = sum(multWithPow(to_string(a1 * b1), n), middle);

        u = sum(begin, mult(dsub, bsub));
    } else {
        u = mult(sumAB, sumCD);
    }
    string  v = mult(a, c),
            w = mult(b, d);

    if(DEBUG_MODE)cout << v << " * 10^" << n << " + (" << u << " - "
         << v << " - " << w << ") * 10^" << k << " + " << w << endl;

    string check = sub(u, v);
    check = sub(check, w);
    string begin = sum(multWithPow(v, n), multWithPow(check, k));

    return  sum(begin, w);
}

string sum(string x, string y) {
    /*
     * Находим наибольшее число и подстраиваемся под него
     */
    int len = x.length() > y.length() ? x.length() : y.length();
    while (len > x.length()) {
        x = '0' + x;
    }
    while (len > y.length()) {
        y = '0' + y;
    }

    string c = "";
    int tmp = 0, sumRaz;
    for (int i = x.length() - 1; i > -1; i--) {
        sumRaz = (x[i] - '0') + (y[i] - '0') + tmp;
        tmp = sumRaz % 10; c = to_string(tmp) + c;
        tmp = sumRaz / 10;
    } if (tmp) c = to_string(tmp) + c;

    return c;
}

string multWithPow(string s, int n) {
    for (int i = 0; i < n; i++) s += '0';
    return s;
}

string multWithNum(string s, int alpha) {
    if (alpha == 1) return s;
    else return to_string(0);
}

string sub(string a, string b) {

    int raz = a.length() - b.length();
    if (raz > 0) {
        while (a.length() - b.length()) {
            b = '0' + b;
        }
    } else if (raz < 0) {
        while (b.length() - a.length()) {
            a = '0' + a;
        }
    }

    int i = 0, flag = 0;
    while (i < a.length() && a[i] == b[i]) {
        i++;
    }
    if (i < a.length() && a[i] > b[i]) {
        flag = 1;
    }

    string c;
    if (!flag) {
        string tmp = a; a = b; b = tmp;
    }
    for (int i = a.length() - 1; i > -1; i--) {
        int suber = (a[i] - '0') - (b[i] - '0');
        if (suber < 0) {
            suber += 10;
            int j;
            for (j = i - 1; j > -1 && a[j] == '0'; j--) {
                a[j] = '9';
            }
            a[j]--;
        }
        c = to_string(suber) + c;
    }

    return c;
}