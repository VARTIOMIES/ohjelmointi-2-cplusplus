#include <iostream>
#include <vector>

using namespace std;

string delete_empty(string s)
{
    string newstr = "";
    for (unsigned int i=0;i<s.size();i++)
    {
        if (s.at(i)!=' ')
        {
            newstr.push_back(s.at(i));
        }
    }
    return newstr;
}

int main()
{

    cout<<"Input an expression in reverse Polish notation (end with #):"<<endl;
    cout<<"EXPR> ";
    string expression = "";
    getline(cin,expression);
    string good_expr = delete_empty(expression);


    vector<int> pino = {};

    for (char character : good_expr)
    {
        if (pino.size() == 0 and (character =='+' or character=='-' or
                                character=='*' or character=='/'))
        {
            cout << "Error: Expression must start with a number" << endl;
            return EXIT_FAILURE;
        }
        if (character=='+' and pino.size()>=2)
        {
            int alkio1 = *(--pino.end());
            int alkio2 = *(pino.end()-2);
            int summa = alkio1+alkio2;
            pino.erase(--pino.end());
            pino.erase(--pino.end());
            pino.push_back(summa);
        }
        else if (character=='-' and pino.size()>=2)
        {
            int alkio1 = *(--pino.end());
            int alkio2 = *(pino.end()-2);
            int erotus = alkio2-alkio1;
            pino.erase(--pino.end());
            pino.erase(--pino.end());
            pino.push_back(erotus);
        }
        else if (character=='*' and pino.size()>=2)
        {
            int alkio1 = *(--pino.end());
            int alkio2 = *(pino.end()-2);
            int tulo = alkio1*alkio2;
            pino.erase(--pino.end());
            pino.erase(--pino.end());
            pino.push_back(tulo);
        }
        else if (character=='/' and pino.size()>=2)
        {
            int alkio1 = *(--pino.end());
            int alkio2 = *(pino.end()-2);
            if (alkio1!= 0)
            {
                int jako = alkio2/alkio1;
                pino.erase(--pino.end());
                pino.erase(--pino.end());
                pino.push_back(jako);
            }
            else {
                cout<<"Error: Division by zero"<<endl;
                return EXIT_FAILURE;
            }

        }
        else if (character=='#')
        {
            continue;
        }
        else if ((character == '+' or character == '-' or character == '*'
                 or character == '/' )and pino.size()==1)
        {
            cout << "Error: Too few operands"<< endl;
            return EXIT_FAILURE;
        }
        else
        {
            int num = character-'0';
            if (num>=0 and num<10)
            {
                pino.push_back(character-'0');
            }
            else
            {
                cout<<"Error: Unknown character"<<endl;
                return EXIT_FAILURE;
            }

        }
    }
    if (pino.size()!= 1)
    {
        cout << "Error: Too few operators"<<endl;
        return EXIT_FAILURE;
    }
    else
    {
        cout<<"Correct: "<<pino.at(0)<<" is the result"<<endl;
        return EXIT_SUCCESS;
    }





}

