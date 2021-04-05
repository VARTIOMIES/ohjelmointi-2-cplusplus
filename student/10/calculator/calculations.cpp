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
    double result = left;
    if (right > 0)
    {
        for (double i=1;i < right;i++)
        {
            result*=left;
        }
    }
    else
    {
        result = 1;
    }
    return result;
}
