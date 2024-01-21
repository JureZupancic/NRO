clc;
clear all;

tic
A = readmatrix('./A.csv');
b = readmatrix('./b.csv');

T = linsolve(A, b);
toc