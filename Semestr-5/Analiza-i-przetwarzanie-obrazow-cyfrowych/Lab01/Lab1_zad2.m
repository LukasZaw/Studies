% Zadanie 2
function y = Lab1_zad2(a, b, c)
x=a:b:c;
y=sin(2*x)+cos(0.5*x);
plot(x,y);
xlabel('Oś X');
ylabel('Oś Y');
title('Lukasz Zawodzinski - zad 2');