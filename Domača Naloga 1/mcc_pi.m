function[x1_znotraj, y1_znotraj, x1_zunaj, y1_zunaj, znotraj] = mcc_pi(n)
% Najprej funkcija naključno ustvari koordinate točk x in y, glede na
% vhodni parameter n, s katerim povemo koliko točk želimo
x = rand(n,1);
y = rand(n,1);
x1=x-0.5;
y1=y-0.5;
% Na podlagi točk določi radij krožnice
r = sqrt(x1.^2+y1.^2); 
% Preko radija pa lahko določimo ali so točke zunaj krožnice ali znotraj
% nje
znotraj = r<=0.5 ;
zunaj = r>0.5 ;
% Funkcija vrne x in y koordinate točk zunaj in znotraj krožnice v ločenih
% arrayih
x1_znotraj = x1(znotraj);
y1_znotraj = y1(znotraj);
x1_zunaj = x1(zunaj);
y1_zunaj = y1(zunaj);




