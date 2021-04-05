// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}
double exponent(double left, double right){
    if (right > 0)
    {
        for (double i=1;i < right;i++)
        {
            left*=left;
        }
    }
    else
    {
        left = 1;
    }
    return left;
}
