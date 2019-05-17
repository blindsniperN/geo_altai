#include <iostream>
#define matMax 6
#define objMax 40

using namespace std;

int InpObj(double outp[5]){
    cin >> outp[0];
    int ans;
    cin >> ans;
    for(int i = 1; i < 4; i++){
        cin >> outp[i];
    }
    cin >> outp[4];
    outp[4]= 1;
    cout << "done!";
    return ans;
}

double Pred(double obj[5], double param[4]){
    for (int i = 1; i < 5; i++){
        obj[0]+= obj[i]* param[i - 1];
    }
    return obj[0];
}

void InpVyb(int n, double tch[matMax][objMax][5], int count[matMax]){
    for(int i = 0; i < n; i++){
        double outp[5];
        int type = InpObj(outp);
        for (int j = 0; j < 5; j++){
            tch[type][count[type]][j]= outp[j];
        }
        count[type]++;
    }
    cout << "done!";
}

void Grad(int n, double tch[objMax][5], double param[4], double grd[4]){
    for (int l = 0; l < 4; l++){
        double res = 0;
        for (int j = 0; j < n; j++){
            for (int z = 0; z < 4; z++){
                res += param[z]*tch[j][z + 1];
            }
            res -= tch[j][0];

            res *= tch[j][l + 1];

        }

        grd[l]= res * 2 / n;
    }
}

double Shag(int n, double tch[objMax][5], double* grd){
    return 0.01;
}

void AntGrad(double param[4], double grd[4], double shg){
    for (int m = 0; m < 4; m++){
        param[m]-= grd[m]*shg;
    }
}

double Q(int n, double curPar[4], double tch[objMax][5]){
    double des = 0;
    for (int m = 0; m < n; m++){
        double temp = Pred(tch[m], curPar) - tch[m][0];
        des += temp*temp;
    }
    return (des / n);
}

int osnova()
{
    int n;
    cin >> n;//вводим количество объектов обучающей выборки
    double accur;
    cin >> accur;//вводим необходимую точность
    double tch[matMax][objMax][5];
    int count[matMax];
    double param[matMax][4];
    InpVyb(n, tch, count);//вводим обучающую выборку, распределенную по признаку материала
    for (int i = 0; i < matMax; i++){//для каждого из материалов
        if(count[i]> 0 ){
        double *curPar = param[i];
        double delt = accur + 1;
        double prevQ = 0;
        int v = 1;
        while ((abs(delt) > accur)and(v-- > 0)){//пока уменьшение значения функционала ошибки больше требуемой точности
            double grd[4];
            //Grad(count[i], tch[i], param[i], grd);//  вычисляем значение частных производных

            for (int l = 0; l < 4; l++){
                double res = 0;
                for (int j = 0; j < count[i]; j++){
                    for (int z = 0; z < 4; z++){
                        res += param[i][z]*tch[i][j][z + 1];
                    }
                    res -= tch[i][j][0];

                    res *= tch[i][j][l + 1];

                }

                grd[l]= res * 2 / count[i];
            }

            //cout << grd[0] << '\t' << grd[1] << '\n';
            double shg = Shag(count[i], tch[i], grd);//  вычисляем шаг
            //AntGrad(curPar, grd, shg);//  перемещаемся по антиградиенту на значение шага
            for (int m = 0; m < 4; m++){
                param[i][m]-= grd[m]*shg;
            }
            double des = 0;
            for (int m = 0; m < count[i]; m++){
                //double temp = Pred(tch[i][m], curPar) - tch[i][m][0];
                //des += temp*temp;
            }
            double q = des / count[i];
            delt = prevQ - q;//Q(count[i], curPar, tch[i]);//  вычисляем уменьшение значения функционала ошибки
            //prevQ = prevQ - delt;//  вычисляем функционал ошибки
        }
        }
    }
    double obj[5];
    cin >> obj[0];
    int type = InpObj(obj);//вводим объект
    cout << Pred(obj, param[type]);//выводим предсказанную вероятность для ответа

    return 0;
}

int main(){
    int n;
    cin >> n;

    double a = 0, b = 0, c = 0, e = 0, h = 0, k = 0, f = 0, g = 0, j = 0, d1 = 0, d2 = 0, d3 = 0, d4 = 0;
    //double mas[10][10];
    for (int i = 0; i < n;){
        double angle, vlag, height, diam;
        double mas;
        int mat;
        cin >> angle;
        cin >> mat;
        cin >> vlag >> height >> diam;
        cin >> mas;

        if (mat == 1){
            a += vlag;
            b += height;
            c += diam;

            e += vlag*vlag;
            h += height*height;
            k += diam*diam;

            f += height*vlag;
            g += diam*vlag;
            j += diam*height;

            d1 += angle;
            d2 += angle * vlag;
            d3 += angle * height;
            d4 += angle * diam;

            i++;
        }
        else{
            n--;
        }

    }
    double w3, w2, w1 = 0, w0;
/*
    double l[] = {0, a*a - e*n, a*b - f*n, a*c - g*n, d2*n - a*d1};
    double m[] = {0, b*e - a*f, b*f - a*h, b*g - a*j, a*d3 - b*d2};
    double u[] = {0, c*f - b*g, c*h - b*j, c*j - b*k, b*d4 - c*d3};

    double p[] = {0, l[2]*m[1] - l[1]*m[2], l[3]*m[1] - l[1]*m[3], l[4]*m[1] - l[1]*m[4]};
    double r[] = {0, m[2]*u[1] - m[1]*u[2], m[3]*u[1] - m[1]*u[3], m[4]*u[1] - m[1]*u[4]};


    double temp = (p[2]*r[1] - p[1]*r[2]);
    if (temp == 0){
        w3 = 0;
    }else{
        w3 = (p[1]*r[3] - p[3]*r[1])/temp;
    }

    temp = p[1];
    if (temp == 0){
        w2 = 0;
    }else{
        w2 = (-p[2]*w3 - p[3])/temp;
    }

    temp = l[1];
    if (temp == 0){
        w1 = 0;
    }else{
        w1 = (-l[2]*w2 - l[3]*w3 - l[4])/temp;
    }

    temp = n;
    if (temp == 0){
        w0 = 0;
    }else{
        w0 = (-a*w1 - b*w2 - c*w3 + d1)/temp;
    }

    cout << w0 << '\t' << w1 << '\t' << w2 << '\t' << w3;
    //cout << a<< '\t'<< b << '\t'<< c << '\n';
*/
    double p[] = {0, b*b - h*n, b*c - j*n, d3*n - b*d1};
    double r[] = {0, c*h - b*j, c*j - b*k, b*d4 - c*d3};

    double temp = (p[2]*r[1] - p[1]*r[2]);
    if (temp == 0){
        w3 = 0;
    }else{
        w3 = (p[1]*r[3] - p[3]*r[1])/temp;
    }

    temp = p[1];
    if (temp == 0){
        w2 = 0;
    }else{
        w2 = (-p[2]*w3 - p[3])/temp;
    }

    temp = n;
    if (temp == 0){
        w0 = 0;
    }else{
        w0 = ( -b*w2 - c*w3 + d1)/temp;
    }


    cout << w0 << '\t' << w1 << '\t' << w2 << '\t' << w3;
    return 0;
}

/*
37 1 0 13.5 8.5 150
32 2 0 13.5 8.5 150
34 3 0 13.5 8.5 150
33 1 0 21 8.5 150
27 2 0 21 8.5 150
30 3 0 21 8.5 150
26 1 0 30 8.5 150
33 1 0 26 8.5 150
31 1 0 21 8.5 100
32 1 0 21 8.5 250
37 1 0 13 8.5 200
39 1 0 13 8.5 200
40 1 0 13 8.5 200
36 1 0 16 8.5 200
36 1 0 16 8.5 200
35 1 0 16 8.5 200
34 1 0 19 8.5 200
34 1 0 19 8.5 200
33 1 0 19 8.5 200
33 1 0 21 8.5 200
33 1 0 21 8.5 200
32 1 0 21 8.5 200
32 1 0 24 8.5 200
32 1 0 24 8.5 200
31 1 0 24 8.5 200
35 1 0 20 8.5 200
32.8 1 0 20 10 200
31.5 1 0 20 12 200
27.8 1 0 20 15 200
33.3 1 0 20 6.5 200
24 4 0 10 15 150
25 4 0 10 15 150
41.5 5 0 15.5 8.5 175
37.5 5 15 15.5 8.5 175
35.5 5 30 15.5 8.5 175
33.5 5 45 15.5 8.5 175*/

//answer 52.0738 0       -0.61521        -0.736828
