% Zadanie 3
function [x,y,z] = Lab1_zad3(a,b,c)
x=a:b:c;
y=sin(2*x)+cos(0.5*x);
plot(x,y);
xlabel('Oś X');
xlabel('Oś Y');
title('Lukasz Zawodzinski - zadanie 3 wykres');

figure;
z=0.8*cos(x+4);
plot(x,z);
xlabel('Oś X');
xlabel('Oś Y');
title('Lukasz Zawodzinski - zadanie 3 wykres drugi ');

figure;
subplot(2,1,1);
plot(x,y);
title('Wykres dla X');
subplot(2,1,2);
plot(x,z);
title('Wykres dla Z');
minx = min(x);
maxx = max(x);
miny = min(y);
maxy = max(y);
axis([minx-1, maxx+1, miny-1, maxy+1]);
end