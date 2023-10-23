N = 10000;
[x1_znotraj, y1_znotraj, x1_zunaj, y1_zunaj, znotraj]= mcc_pi(N);
[pi_izrac, napaka] = area_pi(N, znotraj);

% Izriše točke
plot(x1_znotraj,y1_znotraj,'b.');
hold on
plot(x1_zunaj,y1_zunaj,'r.');
xlabel('x','FontSize',16)
ylabel('y','FontSize',16)
title({'Monte Carlo - Približna vrednost \pi'},'FontSize',16);
legend('točke v krogu','točke iz kroga')

% Izriše krožnico z radijem r
fplot(@(t) 0.5*sin(t), @(t) 0.5*cos(t))

% Funkcija, ki vse to omogoča
function[pi_izr, napaka] = area_pi(N, znotraj)
mcc_pi(N);
pi_izr = 4*sum(znotraj)/N;
napaka = abs(pi - pi_izr);
end
