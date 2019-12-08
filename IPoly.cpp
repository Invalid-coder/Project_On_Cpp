#include "IPoly.h"

int random_int(int a,int b)
{
    return rand() % (b - a) + a;
}

int IPoly::mod(int a)
{
    //a negative value
    while(a < 0)
    {
        a += m;
    }

    return a;
}

IPoly::IPoly()
{
    m = 0;
    n = 0;
}

void IPoly::set_polinom()
{
    int biggest_p,coef;

    cout << "Enter m (m >= 0): ";
    cin >> m;

    cout << "Enter biggest power: ";
    cin >> biggest_p;

    for(int i = 0; i < biggest_p + 1; i++)
    {
        cout << "power["<< i <<"] = ";
        cin >> coef;

        if(m != 0)
        {
            while(coef < 0 || coef > m - 1)
            {
                cout << "This coefficient is not in the range from 0 to " << m - 1 << endl;
                cout << "power["<< i <<"] = ";
                cin >> coef;
            }
        }

        p.push_back(coef);


    }

    n = p.size();
}

IPoly IPoly::operator +(const IPoly & other)
{
    IPoly sum;
    vector<int> a,b;

    if(n > other.n)
    {
        a = p;
        b = other.p;
    }
    else
    {
        a = other.p;
        b = p;
    }

    for(int i = 0; i < a.size(); i++)
    {
        if(i == a.size() - 1 && a[i] + b[i] == 0)
        {
            break;
        }

        if(i <= b.size() - 1)
        {
            if(m != 0)
            {
                if(a[i] + b[i] > 0)
                {
                    sum.p.push_back((a[i] + b[i]) % m);
                }
                else
                {
                    sum.p.push_back(mod(a[i] + b[i]));
                }
            }
            else
            {
                    sum.p.push_back(a[i] + b[i]);
            }
        }
        else
        {
            if(m != 0)
            {
                if(a[i] > 0)
                {
                    sum.p.push_back(a[i] % m);
                }
                else
                {
                    sum.p.push_back(mod(a[i]));
                }
            }
            else
            {
                sum.p.push_back(a[i]);
            }
        }
    }

    sum.n = sum.p.size();

    return sum;
}

IPoly IPoly::operator -(const IPoly & other)
{
    IPoly diff;
    int a,b;

    if(this->n > other.n)
    {
        a = other.n;
        b = this->n;
    }
    else
    {
        a = this->n;
        b = other.n;
    }

    for(int i = 0; i < a; i++)
    {
        if(b == a && i == a - 1 && p[i] - other.p[i] == 0)
        {
            break;
        }

        if(m != 0)
        {
            if(p[i] - other.p[i] > 0)
            {
                diff.p.push_back((p[i] - other.p[i]) % m);
            }
            else
            {
                diff.p.push_back(mod(p[i] - other.p[i]));
            }
        }
        else
        {
            diff.p.push_back(p[i] - other.p[i]);
        }
    }

    for(int i = a; i < b; i++)
    {
        if(b == this->n)
        {
            if(m != 0)
            {
                if(p[i] > 0)
                {
                    diff.p.push_back(p[i] % m);
                }
                else
                {
                    diff.p.push_back(mod(p[i]));
                }
            }
            else
            {
                diff.p.push_back(p[i]);
            }
        }
        else
        {
            if(m != 0)
            {
                if(other.p[i]*(-1) > 0)
                {
                    cout << other.p[i]*(-1) << " " << other.p[i]*(-1) % m << " " << m << endl;
                    diff.p.push_back(other.p[i]*(-1) % m);
                }
                else
                {
                    diff.p.push_back(mod(other.p[i]*(-1)));
                }
            }
            else
            {
                diff.p.push_back(other.p[i]*(-1));
            }
        }
    }

    diff.n = diff.p.size();

    return diff;
}

IPoly IPoly::operator *(const IPoly & other)
{
    IPoly product;
    int biggest_p = n + other.n - 2;//Найбільша степінь нового поліному = сумі найбільших степенів поліномів співмножників
    product.p.resize(biggest_p + 1,0);

    for(int i = 0; i < p.size(); i++)
    {
        for(int j = 0; j < other.p.size(); j++)
        {
            if(m != 0)
            {
                if(p[i] * other.p[j] > 0)
                {
                    product.p[i + j] += ((p[i] * other.p[j]) % m);
                }
                else
                {
                        product.p[i + j] += mod(p[i] * other.p[j]);
                }
            }
            else
            {
                product.p[i + j] += (p[i] * other.p[j]);
            }
        }
    }

    product.n = product.p.size();

    return product;
}

IPoly IPoly::operator /(const IPoly & other)
{
    IPoly q;//Відношення двух поліномів(ціла частина відношення)
    IPoly r;//Остача від ділення поліномів
    IPoly temp;//Тимчасовий поліном для виконання певних дій

    if(n < other.n)
    {
        cout << "Impossible to divide!" << endl;
        q.p.resize(1,0);
        q.n = q.p.size();
        return q;
    }

    q.p.resize(n - other.n + 1,0); //Найбільша степінь нового поліному = різниці найбільших степенів поліномів діленого і дільника
    q.n = q.p.size();
    r.p = p;
    r.n = r.p.size();

    while(r.n >= other.n)//Поки найбільша степень остачі >= степені дільника поліному
    {
        temp.p.resize(r.n - other.n + 1,0);
        temp.n = temp.p.size();
        temp.p[r.n - other.n] = (r.p[r.n - 1] / other.p[other.n - 1]);
        q.p[r.n - other.n] = (r.p[r.n - 1] / other.p[other.n - 1]);
        temp = temp * other;
        r = r - temp;
    }

    return q;
}

IPoly IPoly::operator %(const IPoly & other)
{
    IPoly q;//Відношення двух поліномів(ціла частина відношення)
    IPoly r;//Остача від ділення поліномів
    IPoly temp;//Тимчасовий поліном для виконання певних дій

    if(n < other.n)
    {
        cout << "Impossible to divide!" << endl;
        q.p.resize(1,0);
        q.n = q.p.size();
        return q;
    }

    q.p.resize(n - other.n + 1,0); //Найбільша степінь нового поліному = різниці найбільших степенів поліномів діленого і дільника
    q.n = q.p.size();
    r.p = p;
    r.n = r.p.size();

    while(r.n >= other.n)//Поки найбільша степень остачі >= степені дільника поліному
    {
        temp.p.resize(r.n - other.n + 1,0);
        temp.n = temp.p.size();
        temp.p[r.n - other.n] = (r.p[r.n - 1] / other.p[other.n - 1]);
        q.p[r.n - other.n] = (r.p[r.n - 1] / other.p[other.n - 1]);
        temp = temp * other;
        r = r - temp;
    }

    return r;
}

IPoly IPoly::derivative()
{
    IPoly temp;
    temp.p.resize(n - 1,0);
    temp.n = temp.p.size();

    for(int i = 1; i < n; i++)
    {
        temp.p[i - 1] = i * p[i];
    }

    return temp;
}

IPoly IPoly::integral()
{
    IPoly temp;
    temp.p.resize(n + 1,0);
    temp.n = temp.p.size();
    int c = random_int(0,10000);
    temp.p[0] = c;

    for(int i = 0; i < n; i++)
    {
        temp.p[i + 1] = p[i] / (i + 1);
    }

    return temp;
}


int IPoly::definite_integral(int a,int b)
{
    int t2 = 0;
    int t1 = 0;

    for(int i = 0; i < n; i++)
    {
        t2 += p[i] * pow(a,i + 1) / (i + 1);
        t1 += p[i] * pow(b,i + 1) / (i + 1);
    }

    return t2 - t1;
}


void IPoly::write_to_file(string path)
{
    ofstream out;
    out.open(path.c_str());

    if (out.is_open())
    {
        out << p[n - 1] << "*x^" << n - 1;

        for(int i = n - 2; i > - 1; i--)
        {
            if(p[i] == 0)
            {
                continue;
            }
            else if(i == 0)
            {
                if(p[i] > 0)
                {
                    out << " + " << p[i];
                }
                else
                {
                    out << " - " << p[i] * (-1);
                }
            }
            else if(i == 1)
            {
                if(p[i] == 1)
                {
                    out <<" + x";
                }
                else if(p[i] == -1)
                {
                    out << " - x";
                }
                else if(p[i] > 1)
                {
                    out << " + " << p[i] << "*x";
                }
                else
                {
                    out << " - " <<  p[i] * (-1) << "*x";
                }
            }
            else if(p[i] > 0)
            {
                if(p[i] == 1)
                {
                    out <<" + x^" << i;
                }
                else
                {
                    out << " + " << p[i] << "*x^" << i;
                }
            }
            else
            {
                if(p[i] == -1)
                {
                    out << " - x^" << i;
                }
                else
                {
                    out << " - " << p[i] * (-1) << "*x^" << i;
                }
            }
        }
         out << endl;
    }
    else
    {
        cout << "Error incorrect path" << endl;
    }

    out.close();
}


void IPoly::read_file(string path)
{
    int koef;
    string line;

    ifstream in(path.c_str());

    if (in.is_open())
    {
        while (getline(in, line))
        {
            p.push_back(atoi(line.c_str()));
        }
    }
    else
    {
        cout << "Error incorrect path" << endl;
    }

    n = p.size();

    in.close();
}

void IPoly::printPoly()
{
    cout << p[n - 1] << "*x^" << n - 1;

    for(int i = n - 2; i > - 1; i--)
    {
        if(p[i] == 0)
        {
            continue;
        }
        else if(i == 0)
        {
            if(p[i] > 0)
            {
                cout << " + " << p[i];
            }
            else
            {
                cout << " - " << p[i] * (-1);
            }
        }
        else if(i == 1)
        {
            if(p[i] == 1)
            {
                cout <<" + x";
            }
            else if(p[i] == -1)
            {
                cout << " - x";
            }
            else if(p[i] > 1)
            {
                cout << " + " << p[i] << "*x";
            }
            else
            {
                cout << " - " <<  p[i] * (-1) << "*x";
            }
        }
        else if(p[i] > 0)
        {
            if(p[i] == 1)
            {
                cout <<" + x^" << i;
            }
            else
            {
                cout << " + " << p[i] << "*x^" << i;
            }
        }
        else
        {
            if(p[i] == -1)
            {
                cout << " - x^" << i;
            }
            else
            {
                cout << " - " << p[i] * (-1) << "*x^" << i;
            }
        }
    }

    cout << endl;
}

int IPoly::value(int x)
{
    int result = p[0];

    for(int i = 1; i < n; i++)
    {
        result += p[i] * pow(x,i);
    }

    return result;
}

ostream& operator<< (ostream &out,const IPoly &poly)
{
    out << poly.p[poly.n - 1] << "*x^" << poly.n - 1;

    for(int i = poly.n - 2; i > - 1; i--)
    {
        if(poly.p[i] == 0)
        {
            continue;
        }
        else if(i == 0)
        {
            if(poly.p[i] > 0)
            {
                out << " + " << poly.p[i];
            }
            else
            {
                out << " - " << poly.p[i] * (-1);
            }
        }
        else if(i == 1)
        {
            if(poly.p[i] == 1)
            {
                out <<" + x";
            }
            else if(poly.p[i] == -1)
            {
                out << " - x";
            }
            else if(poly.p[i] > 1)
            {
                out << " + " << poly.p[i] << "*x";
            }
            else
            {
                out << " - " <<  poly.p[i] * (-1) << "*x";
            }
        }
        else if(poly.p[i] > 0)
        {
            if(poly.p[i] == 1)
            {
                out <<" + x^" << i;
            }
            else
            {
                out << " + " << poly.p[i] << "*x^" << i;
            }
        }
        else
        {
            if(poly.p[i] == -1)
            {
                out << " - x^" << i;
            }
            else
            {
                out << " - " << poly.p[i] * (-1) << "*x^" << i;
            }
        }
    }

    out << endl;

    return out;
}

istream& operator>> (istream &in,IPoly &poly)
{
    int biggest_p,coef;

    cout << "Enter m (m >= 0): ";
    in >> poly.m;

    cout << "Enter biggest power: ";
    in >> biggest_p;

    for(int i = 0; i < biggest_p + 1; i++)
    {
        cout << "power["<< i <<"] = ";
        in >> coef;

        if(poly.m != 0)
        {
            while(coef < 0 || coef > poly.m - 1)
            {
                cout << "This coefficient is not in the range from 0 to " << poly.m - 1 << endl;
                cout << "power["<< i <<"] = ";
                in >> coef;
            }
        }

        poly.p.push_back(coef);


    }

    poly.n = poly.p.size();

    return in;
}

IPoly::~IPoly()
{
    //dtor
}
