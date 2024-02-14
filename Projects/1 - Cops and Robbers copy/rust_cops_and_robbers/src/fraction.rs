struct Fraction {
    num: i32,
    den: u16,
}

const fn fraction(num: i32,den: u16) -> Fraction {
    const fn abs(a:i32) -> u32 {
        (if a >= 0 {a} else {-a}) as u32
    }
    const fn gcd(a:u32,b:u32) -> u32 {
        if a%b==0 {b} else {gcd(b,a%b)}
    }
    Fraction {
        num: num/(gcd(abs(num),den as u32) as i32),
        den: ((den as u32)/gcd(abs(num),den as u32)) as u16,
    }
}
/*
static Fraction seqA(int series[],int mode,int k=0) {
    Fraction returnFraction = 0;
    if (mode==1) {
        returnFraction = Fraction(1,series[k+1]);
    }
    else if (mode==2) {
        returnFraction = seqA(series,1,k+1) + series[k+1];
    }
    else {
        returnFraction = seqA(series,mode-1,k+1);
        returnFraction += (mode%2==0?-1:1)*Fraction(1,seqB(series,mode-2,k)*seqARevProd(series,mode,k));
    }
    return returnFraction;
}
*/

fn float_fraction(decimal: f32) -> Fraction {
    if decimal<std::f32::EPSILON {return fraction(0,1)};
    
    todo!()
}
