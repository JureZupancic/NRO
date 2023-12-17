// Projektna naloga_koda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <omp.h>
#include <ctime>
#include <map>
#include <regex>

using namespace std;

int main()
{
    std::string filename = "./primer3mreza.txt";

    std::vector<double> X;
    std::vector<double> Y;
    std::vector<vector<int>> celice;
    std::map<int, std::vector<int>> vozlisca_robnih_pogojev;
    std::vector<int> tipi_robnih_pogojev;
    std::vector<double> vrednosti_robnih_pogojev;
    std::vector<double> vrednosti_prestopa_toplote;

    

    std::ifstream file;
    file.open(filename);
    std::string str_tocke;
    std::ifstream indata;
    indata >> str_tocke;
    std::string str_points;
    indata >> str_points;
    int n_vozlisc = std::stoi(str_points); //Št. vozlišè

//Branje vozlišè

    for (int i = 0; i < n_vozlisc; i++) {
        std::string s;
        std::getline(file, s); // preberemo vrstico
        std::replace(s.begin(), s.end(), ';', ' ');
        std::replace(s.begin(), s.end(), ',', ' ');
        std::istringstream iss(s);
        int node_id;
        double x;
        double y;
        iss >> node_id >> x >> y;


        X.push_back(x);
        Y.push_back(y);
    }

    /*
    // Print the resulting vectors
    for (int i = 0; i < X.size(); i++) {
        std::cout << "X[" << i << "] = " << X[i] << std::endl;
        std::cout << "Y[" << i << "] = " << Y[i] << std::endl;
    }
    */

    std::string prazna_vrstica;
    std::getline(file, prazna_vrstica);

//Branje celic

    std::string cell_line;
    std::getline(file, cell_line);

    std::vector<std::string> cells_string;
    std::string cell;
    std::istringstream iss(cell_line);
    while (iss >> cell) {
        cells_string.push_back(cell);
    }
    int n_celice = std::stoi(cells_string[1]);
    
    for (int i = 0; i < n_celice; i++) {
        std::string s;
        std::getline(file, s); // preberemo vrstico
        std::replace(s.begin(), s.end(), ';', ' ');
        std::replace(s.begin(), s.end(), ',', ' ');
        std::istringstream iss(s);
        int cell_id;
        int node1_id;
        int node2_id;
        int node3_id;
        int node4_id;
        iss >> cell_id >>node1_id >> node2_id >> node3_id >> node4_id;
        vector<int> celica;

        celica.push_back(cell_id);
        celica.push_back(node1_id);
        celica.push_back(node2_id);
        celica.push_back(node3_id);
        celica.push_back(node4_id);

        celice.push_back(celica);
        
    }

    std::string prazna_vrstica;
    std::getline(file, prazna_vrstica);

// Branje robnih pogojev

    std::string robni_pogoji_line;
    std::getline(file, robni_pogoji_line);

    std::vector<std::string> robni_pogoji_string;
    std::string rp;
    std::istringstream iss(robni_pogoji_line);
    while (iss >> rp) {
        robni_pogoji_string.push_back(rp);
    }
    int n_pogoji = std::stoi(robni_pogoji_string[1]);

    for (int i = 0; i < n_pogoji; i++) {
        std::string s;
        string tip_pogoja;
        std::getline(file, s); // preberemo vrstico
        std::cout << "pogoj 1:" << tip_pogoja << "\n";

        if (tip_pogoja == "temperatura") {
            tipi_robnih_pogojev.push_back(0);
            int temperatura = 0;
            std::cout << "temperatura:" << temperatura << "\n";

            vrednosti_robnih_pogojev.push_back(temperatura);
            vrednosti_prestopa_toplote.push_back(-1);
            
        }

        else if (tip_pogoja == "toplotni") {
            tipi_robnih_pogojev.push_back(1);
            int toplotni_tok = 0;
            std::cout << "toplotni tok:" << toplotni_tok << "\n";

            vrednosti_robnih_pogojev.push_back(toplotni_tok);
            vrednosti_prestopa_toplote.push_back(-1);

        }

        else if (tip_pogoja == "prestop") {
            tipi_robnih_pogojev.push_back(2);
            int temp_prestopa = 0;
            int koef_prestopa = 0;
            std::cout << "temperatura:" << temp_prestopa << "\n";
            std::cout << "koeficient prestopa:" << koef_prestopa << "\n";

            vrednosti_robnih_pogojev.push_back(temp_prestopa);
            vrednosti_prestopa_toplote.push_back(koef_prestopa);

        }

        int st_vozlisc_v_rp;
        std::cout << st_vozlisc_v_rp << "\n";

        vector<int> vozlisca_v_robnem_pogoju;

        for (int i; i < st_vozlisc_v_rp; i++) {
            int id_vozlisca;
            std::cout << id_vozlisca << "\n";

            vozlisca_v_robnem_pogoju.push_back(id_vozlisca);

        }

        vozlisca_robnih_pogojev.insert({ i, vozlisca_v_robnem_pogoju });
       
    }

// Tu je konec branja datoteke


    std::cout << n_vozlisc;


    std::cout << "Hello World!\n";
}

