void extended_GCD(LL a, LL b, LL &x, LL &y){
    if (b == 0) {x = 1; y = 0;}
    else{
        extended_GCD(b, a % b, y, x);
        y = y - a / b * x;
    }
}
