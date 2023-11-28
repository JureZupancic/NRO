// Domača naloga 4.cpp : Računanje odvoda z diferenčnimi shemami.

#include <iostream>
#include <fstream>
#include <vector>

double CentralnaDifShema(std::vector<std::pair<double, double>>& data, int idx, double dx) {
    return (data[idx + 1].second - data[idx - 1].second) / (2 * dx);
}


double DifShemaNaprej(std::vector<std::pair<double, double>>& data, int idx, double dx) {
    return (-3 * data[idx].second + 4 * data[idx + 1].second - data[idx + 2].second) / (2 * dx);
}


double DifShemaNazaj(std::vector<std::pair<double, double>>& data, int idx, double dx) {
    return (3 * data[idx].second - 4 * data[idx - 1].second + data[idx - 2].second) / (2 * dx);
}



int main()
{
    std::ifstream inputFile("vhodna_datoteka.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Neuspelo odpiranje vhodne datoteke\n";
        return 1;
    }

    int ŠteviloTočk;
    inputFile >> ŠteviloTočk;

    std::vector<std::pair<double, double>> data;
    int n;
    double x, fx;
    char dvop = ':';

    for (int i = 0; i < ŠteviloTočk; ++i) {
        inputFile >> n >> dvop >> x >> fx;
        data.emplace_back(x, fx);
    }

    inputFile.close();

    double dx = ((4. - 1.) / (ŠteviloTočk - 1));
    std::ofstream outputFile("odvod_z_dif_shemo.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Neuspelo ustvarjanje datoteke z odvodi funkcije\n";
        return 1;
    }


    for (int i = 0; i < ŠteviloTočk; ++i) {
        double odvod;
        if (i == 0) {
            odvod = DifShemaNaprej(data, i, dx);
        }
        else if (i == ŠteviloTočk - 1) {
            odvod = DifShemaNazaj(data, i, dx);
        }
        else {
            odvod = CentralnaDifShema(data, i, dx);
        }
        outputFile << "f'(" << data[i].first << ") = " << odvod << std::endl;
    }

    outputFile.close();

    std::cout << "Odvod je shranjen v datoteki odvod_z_dif_shemo.txt\n";

    return 0;
}
