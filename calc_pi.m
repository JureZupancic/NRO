N = 1000
mcc_pi(N);


fplot(@(t) 0.5*sin(t), @(t) 0.5*cos(t))

function[NN] = area_pi(N)
pi_izr = 4*sum(znotraj)/N
napaka = abs(pi - pi_izr)
end